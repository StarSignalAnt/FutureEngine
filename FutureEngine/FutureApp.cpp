#include "FutureApp.h"
#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "GameInput.h"
#include "RenderTarget2D.h"
#include "UIHelp.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // Adjust the OpenGL viewport to match the new framebuffer size
    //glViewport(0, 0, width, height);

	FutureApp::m_Inst->SetSize(width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {

		GameInput::Buttons[button] = true;
        //std::cout << "Mouse button " << button << " pressed\n";
    }
    else if (action == GLFW_RELEASE) {
		GameInput::Buttons[button] = false;
        //std::cout << "Mouse button " << button << " released\n";
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //std::cout << "Mouse scrolled: " << yoffset << "\n";
    GameInput::MouseDelta.z = yoffset;
}



FutureApp::FutureApp()
{
    m_Inst = this;
}


void FutureApp::SetApp(int width, int height, std::string app)
{
	m_Width = width;
	m_Height = height;
	m_App = app;

    std::cout << "Running " << m_App << " at " << m_Width << "x" << m_Height << std::endl;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return ;
    }

    // Set OpenGL version (latest available)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use Core Profile

    // Create a window
    window = glfwCreateWindow(m_Width, m_Height, m_App.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return ;
    }

    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }
    glfwSwapInterval(0); // Disable V-Sync

    // Set viewportsrand(static_cast<unsigned int>(time(0)));  // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator with the current time

    glViewport(0, 0, m_Width, m_Height);
     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
     glfwSetMouseButtonCallback(window, mouse_button_callback);
     glfwSetScrollCallback(window, scroll_callback);
    InitGL();

}

void FutureApp::SetSize(int width, int height) {

    glViewport(0, 0, width, height);
    m_Width = width;
    m_Height = height;

}

void FutureApp::InitGL() {

    // Enable blending (for transparent textures, etc.)
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ZERO);  // Common blending mode for transparency

    // Enable depth testing (useful if your 2D game has depth layers, otherwise, you may skip it)
    glEnable(GL_DEPTH_TEST);  // Enable depth testing (if you have 3D elements or Z-ordering)

    // Enable face culling (optional, good for performance if you're only rendering one side of geometry)
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);  // Cull back faces, rendering front faces only

    // Enable alpha testing (optional, for discarding transparent fragments in certain cases)
    glDisable(GL_ALPHA_TEST);
  
    // Set clear color (background color of the window)
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  // Set background to a dark gray

    UIHelp::InitHelp();

}

int FutureApp::Run()
{


    int nextfps = clock() + 1000;

    int ptime = clock();

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
    //    processInput(window);
        glfwPollEvents();
        // Render
      
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        frames++;
        int ct = clock();
        if (ct > nextfps) {

            fps = frames;
            frames = 0;
			printf("FPS: %d\n", fps);
            nextfps = ct + 1000;
        }


        if (m_States.size() > 0)
        {
            auto top = m_States.top();

            int ptime2 = clock();

            int ntime = ptime2 - ptime;;
            ptime = ptime2;

            float delta = ((float)ntime) / 1000.0f;

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);



	
			GameInput::MouseDelta = -glm::vec3(GameInput::MousePosition.x-xpos,GameInput::MousePosition.y-ypos,-GameInput::MouseDelta.z);
            GameInput::MousePosition = glm::vec2(xpos, ypos);



   

            if (top != nullptr) {
                top->UpdateState(delta);
                top->RenderState();
            }



            GameInput::MouseDelta.z = 0;

        }

        // Swap buffers and poll events
        
        glfwSwapBuffers(window);
 

    }

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}

void FutureApp::PushState(FutureState* state)
{
	m_States.push(state);
    state->InitState();
}


void FutureApp::PopState()
{
    auto top = m_States.top();
	m_States.pop();
    top->EndState();

}

int FutureApp::GetWidth() {

    if (m_BoundRT) {
		return m_BoundRT->GetWidth();
	}
    else {
        return m_Width;
    }
}

int FutureApp::GetHeight() {
    if (m_BoundRT) {
        return m_BoundRT->GetHeight();
    }
    else {
        return m_Height;
    }
}

FutureApp* FutureApp::m_Inst = nullptr;

void FutureApp::SetBind(RenderTarget2D* rt) {
	m_BoundRT = rt;
    if (rt != nullptr) {
		glViewport(0, 0, rt->GetWidth(), rt->GetHeight());
    }
    else {
		glViewport(0, 0, m_Width, m_Height);
    }
}
