#pragma once
#include <IControl.h>
class DesktopWallpaper :
    public IControl
{
public:

    DesktopWallpaper(glm::vec2 position, glm::vec2 size);
    void Update(float delta) override;
    void Render() override;
    void OnMouseDown(int button) override;

private:

    

};

