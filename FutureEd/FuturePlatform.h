#pragma once
#include <FutureApp.h>
#include <string>

class FPApp;
class AppBar;
class DesktopWallpaper;
class GpuTalk;

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
    static void BeginTalk();
    static std::vector<FPApp*> GetAppsOfType(AppType type);
    static AppBar* m_AppBar;
    static std::vector<FPApp*> m_RunningApps;
    static DesktopWallpaper* m_Wallpaper;
    static std::vector<FPApp*> m_Apps;
    static std::string Ask(std::string text);
    static std::string Ask(std::string directive, std::string text);
    static GpuTalk* m_Talk;

private:

    

};

