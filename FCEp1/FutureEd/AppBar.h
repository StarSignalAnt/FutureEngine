#pragma once
#include <IControl.h>
#include <vector>
#include <string>

class AppStart;
class FPApp;
class IWindow;

class AppBar :
    public IControl
{
public:

    AppBar(glm::vec2 position, glm::vec2 size);
    void Update(float delta) override;
    void Render() override;
    void AppStarted(FPApp* app) {
        m_RunningApps.push_back(app);
    }
    void RegisterWindow(IWindow* window,FPApp* app);
    int NextX();

private:

    AppStart* m_AppStart;
    std::vector<FPApp*> m_RunningApps;
    std::vector<IWindow*> m_Windows;

};

