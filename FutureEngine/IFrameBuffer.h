#pragma once
#include "IControl.h"

class RenderTarget2D;


class IFrameBuffer :
    public IControl
{
public:

    IFrameBuffer(glm::vec2 position, glm::vec2 size);
    void PreRender() override;
    void Render() override;
    void Update(float delta) override;

private:

    RenderTarget2D* m_RT;

};


