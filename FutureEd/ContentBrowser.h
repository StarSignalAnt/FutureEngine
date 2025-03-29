#pragma once
#include <IControl.h>
#include <string>
#include <vector>
#include <filesystem>

class IVerticalScroller;
class Texture2D;

enum ContentType {

    CT_File,CT_Folder,CT_PNG,CT_JPG

};

struct ContentItem {

    std::string m_Name;
    std::string m_FullPath;
    glm::vec2 m_Position;
    ContentType m_Type = CT_File;
    Texture2D* m_Icon = nullptr;
};

class ContentBrowser :
    public IControl
{
public:
    ContentBrowser();
    void Update(float delta) override;
    void Render() override;
    void Browse(std::string path);
    ContentType DetermineContentType(const std::filesystem::path& path);
    std::vector<ContentItem> ScanDirectoryContents(const std::string& path);
    void SortFoldersFirst(std::vector<ContentItem>& items);
private:

    std::vector<ContentItem> m_Items;
    IVerticalScroller* m_Scroller;
    

};

