#pragma once
#include <FutureState.h>

class FUserProfile;
class GameUI;
class Texture2D;
class IWindow;


class FSDesktop :
    public FutureState
{
public:


    void InitState() override;
    void UpdateState(float delta) override;
    void RenderState() override;
    void EndState() override;

    void SetUser(FUserProfile* profile)
    {
        m_Profile = profile;
    }

    void SetupDesktopMenu();

private:

    FUserProfile* m_Profile = nullptr;
    GameUI* m_UI;

};

