#pragma once
#include <FutureApp.h>
#include <string>

class FPApp;
class AppBar;
class DesktopWallpaper;


enum AppType;

class FuturePlatform :
    public FutureApp
{
public:

    FuturePlatform();
    static void StartApp(FPApp* applicatin);
    static void RegisterAppBar(AppBar* bar);
    static void RegisterWallpaper(DesktopWallpaper* wallpaper);
    static void RegisterApp(std::string name);
    static void RegisterApp(FPApp* app);

    static std::vector<FPApp*> GetAppsOfType(AppType type);
    static AppBar* m_AppBar;
    static std::vector<FPApp*> m_RunningApps;
    static DesktopWallpaper* m_Wallpaper;
    static std::vector<FPApp*> m_Apps;

  

private:

    

};

