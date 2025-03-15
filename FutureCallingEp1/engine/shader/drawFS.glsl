#version 450 core

in vec4 fragColor;      // Interpolated color from vertex shader
in vec2 fragTexCoord;   // Interpolated texture coordinates

out vec4 outColor;      // Final fragment color

uniform sampler2D uTexture; // Texture sampler

void main()
{
    vec4 texColor = texture(uTexture, fragTexCoord); // Sample texture
    if(texColor.a<0.1)
    {
        discard;
        return;
    }
    outColor = fragColor*texColor; // Combine texture, vertex color, and uniform color
}