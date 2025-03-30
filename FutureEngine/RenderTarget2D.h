#pragma once

#include <glm/glm.hpp>

class Texture2D;

class RenderTarget2D {
public:
    RenderTarget2D(unsigned int width, unsigned int height, bool useMipmaps = true);

    void Bind();
    void Unbind();
    void Clear(glm::vec3 color);
    void Resize(unsigned int width, unsigned int height);

    void SetTexture(Texture2D* texture);
    Texture2D* GetTexture();

    // Helper methods for using the render target as a texture
    void BindAsTexture(unsigned int textureUnit = 0);
    void UnbindAsTexture(unsigned int textureUnit = 0);

    unsigned int GetFrameBuffer();
    unsigned int GetDepthBuffer();
    unsigned int GetWidth();
    unsigned int GetHeight();
    bool HasMipmaps();

    void Free();

private:
    unsigned int m_FrameBuffer;
    unsigned int m_DepthBuffer;
    unsigned int m_TextureID;
    unsigned int m_Width;
    unsigned int m_Height;
    bool m_UseMipmaps;
};