// FutureEd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "FutureApp.h"
#include "FuturePlatform.h"
#include "llama.h"
#include <iostream>
#include <string>
#include "GpuTalk.h"


std::string answer_question(const std::string& model_path, const std::string& question) {
    // Initialize the llama backend
    llama_backend_init();
    
    // Load the model
    llama_model_params model_params = llama_model_default_params();

    //llama_model_params model_params = llama_model_default_params();
    model_params.n_gpu_layers = INT32_MAX; // Try to offload all layers to GPU
    model_params.main_gpu = 0;


    llama_model* model = llama_model_load_from_file(model_path.c_str(), model_params);
    
    if (!model) {
        return "Error: Could not load model";
    }
    
    // Create context
    llama_context_params ctx_params = llama_context_default_params();
    ctx_params.n_ctx = 2048;
    ctx_params.n_batch = 512;
    llama_context* ctx = llama_init_from_model(model, ctx_params);
    
    if (!ctx) {
        llama_model_free(model);
        return "Error: Could not create context";
    }
    
    // Create a prompt with the question
    std::string prompt = "Answer the following question:\nQuestion: " + question + "\nAnswer:";
    
    // Get the model's vocabulary
    const llama_vocab* vocab = llama_model_get_vocab(model);
    
    // Tokenize the prompt
    std::vector<llama_token> tokens(ctx_params.n_ctx);
    int n_tokens = llama_tokenize(vocab, prompt.c_str(), prompt.length(), tokens.data(), tokens.size(), true, false);
    
    if (n_tokens < 0) {
        llama_free(ctx);
        llama_model_free(model);
        return "Error: Failed to tokenize input";
    }
    
    tokens.resize(n_tokens);
    
    // Create a batch with these tokens
    llama_batch batch = llama_batch_get_one(tokens.data(), tokens.size());
    
    // Process the batch
    if (llama_decode(ctx, batch) != 0) {
        llama_batch_free(batch);
        llama_free(ctx);
        llama_model_free(model);
        return "Error: Failed to decode";
    }
    
    // Initialize samplers
    llama_sampler_chain_params sparams = llama_sampler_chain_default_params();
    llama_sampler* sampler = llama_sampler_chain_init(sparams);
    
    llama_sampler_chain_add(sampler, llama_sampler_init_top_k(40));
    llama_sampler_chain_add(sampler, llama_sampler_init_top_p(0.95, 1));
    llama_sampler_chain_add(sampler, llama_sampler_init_temp(0.8));
    llama_sampler_chain_add(sampler, llama_sampler_init_dist(0));
    

    // Generate response tokens
    std::vector<llama_token> response_tokens;
    llama_token token = 0;
    const int max_tokens = 512;
    
    for (int i = 0; i < max_tokens; i++) {
        // Sample a token
        token = llama_sampler_sample(sampler, ctx, -1);
        
        // Check for end of generation
        if (llama_vocab_is_eog(vocab, token)) {
            break;
        }
        
        response_tokens.push_back(token);
        
        // Accept the token
        llama_sampler_accept(sampler, token);
        
        // Prepare the next batch with this token
        batch = llama_batch_get_one(&token, 1);
        
        // Decode this token
        if (llama_decode(ctx, batch) != 0) {
            llama_batch_free(batch);
            llama_sampler_free(sampler);
            llama_free(ctx);
            llama_model_free(model);
            return "Error: Failed to decode";
        }
        
        // Free the batch
       // llama_batch_free(batch);
    }
    
    // Convert response tokens to text
    std::string result;
    char buffer[256];
    
    for (const auto& token : response_tokens) {
        int n = llama_token_to_piece(vocab, token, buffer, sizeof(buffer) - 1, 0, true);
        if (n > 0) {
            buffer[n] = 0;
            result += buffer;
        }
    }
    
    // Clean up
    llama_sampler_free(sampler);
    llama_free(ctx);
    llama_model_free(model);
    
    return result;
}


int main()
{

    FuturePlatform* app = new FuturePlatform;
   
    //ret
    return 0;
    GpuTalk ai("models/mistral-7b-instruct-v0.1.Q8_0.gguf");


    std::string directive =
        "You are an assistant that provides simple, direct answers to questions without asking follow-up "
        "questions. Provide only the answer to the specific question asked, nothing more.\n\n";

    directive = directive + "Future Platform is a 2D virtual OS with development tools\n\n";
    directive = directive + "You can code apps in C++ to add to the OS\n\n";
    directive = directive + "Apps can be made as dlls, to load in future platform at runtime without needing to recompile\n\n";
    directive = directive + "End every response with thank you \n\n";

    // Ask a question
    std::string response = ai.AskWithContext(directive, "Tell me what effect do you think the technological singularity will have on life on earth?");

    // Print the response
    std::cout << response << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
