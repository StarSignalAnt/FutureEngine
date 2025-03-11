#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>

Texture2D::Texture2D(std::string path) {

    int width, height, channels;

    // Load image using stb_image
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);  // Force 4 channels (RGBA)

    if (image == nullptr) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        exit(EXIT_FAILURE);
    }

	std::cout << "Loaded texture: " << path << " (" << width << "x" << height << ")\n";

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters (you can modify these as per your needs)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the image data to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the image memory (stbi_load uses dynamic memory)
    stbi_image_free(image);

    m_Handle = textureID;
    m_Width = width;
    m_Height = height;
    m_Channels = 4;

}

void Texture2D::Bind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Handle);
}

void Texture2D::Unbind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, 0);
}