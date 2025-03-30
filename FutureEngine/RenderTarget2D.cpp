#include "RenderTarget2D.h"
#include "Texture2D.h"
#include <glad/glad.h>
#include <iostream>
#include "FutureApp.h"

RenderTarget2D::RenderTarget2D(unsigned int width, unsigned int height, bool useMipmaps) {
    m_Width = width;
    m_Height = height;
    m_UseMipmaps = useMipmaps;

    // Generate framebuffer
    glGenFramebuffers(1, &m_FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

    // Generate texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Create texture storage
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // Set up texture filtering parameters
    if (m_UseMipmaps) {
        // Configure mipmapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Enable anisotropic filtering if supported
        float maxAnisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotropy);
    }
    else {
        // Standard linear filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Set wrap mode to prevent artifacts at edges
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Attach texture to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

    // Create depth/stencil buffer
    glGenRenderbuffers(1, &m_DepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);

    // Check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    // Generate mipmaps if enabled
    if (m_UseMipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget2D::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
    FutureApp::m_Inst->SetBind(this);
}

void RenderTarget2D::Unbind() {
    // Generate mipmaps after rendering if mipmaps are enabled
    if (m_UseMipmaps) {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    FutureApp::m_Inst->SetBind(nullptr);
}

void RenderTarget2D::Clear(glm::vec3 color) {
    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderTarget2D::Resize(unsigned int width, unsigned int height) {
    if (width == m_Width && height == m_Height) {
        return; // No resize needed
    }

    m_Width = width;
    m_Height = height;

    // Resize texture
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    if (m_UseMipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Resize depth/stencil buffer
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget2D::SetTexture(Texture2D* texture) {
    m_TextureID = texture->GetID();

    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

    // Apply mipmapping and anisotropic filtering if enabled
    if (m_UseMipmaps) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        // Enable anisotropic filtering if supported
        float maxAnisotropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, maxAnisotropy);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

Texture2D* RenderTarget2D::GetTexture() {
    // Note: This creates a new Texture2D object that needs to be freed by the caller
    return new Texture2D(m_TextureID, m_Width, m_Height);
}

void RenderTarget2D::BindAsTexture(unsigned int textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void RenderTarget2D::UnbindAsTexture(unsigned int textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int RenderTarget2D::GetFrameBuffer() {
    return m_FrameBuffer;
}

unsigned int RenderTarget2D::GetDepthBuffer() {
    return m_DepthBuffer;
}

unsigned int RenderTarget2D::GetWidth() {
    return m_Width;
}

unsigned int RenderTarget2D::GetHeight() {
    return m_Height;
}

bool RenderTarget2D::HasMipmaps() {
    return m_UseMipmaps;
}

void RenderTarget2D::Free() {
    glDeleteFramebuffers(1, &m_FrameBuffer);
    glDeleteRenderbuffers(1, &m_DepthBuffer);
    glDeleteTextures(1, &m_TextureID);
}