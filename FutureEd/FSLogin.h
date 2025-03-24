#pragma once
#include <FutureState.h>
#include <string>
#include <vector>

class Texture2D;
class SmartDraw;
class GameUI;
class IWindow;
class IButton;
class ITimeSelector;
class IDateSelector;
class ITextEdit;
class IImage;
class FUsers;
class ISizeBox;
class GameVideo;

class FSLogin :
    public FutureState
{
public:

    void InitState() override;
    void UpdateState(float delta) override;
    void RenderState() override;
    void EndState() override;

    //
    void CreateNewUser();

    //Create User
    

private:

    Texture2D* m_Background = nullptr;
    SmartDraw* m_Draw;
    float m_BGAlpha = 0.0;
    GameUI* m_UI;
    IWindow* m_Login;
    IWindow* m_CreateUser;
    IButton* m_NewUser;
    ITimeSelector* m_Time;
    IDateSelector* m_Date;
    bool m_CreatedUI = false;

    //Create User
    ITextEdit* m_Name;
    ITextEdit* m_Password;
    IImage* m_Avatar;
    IButton* m_SelectAvatar;
    std::string m_AvatarPath;
    FUsers* m_Users;
    ISizeBox* m_UsersBox;
    GameVideo* m_BGVideo;

    std::string m_UserPassword = "";


};



