#include "ContentBrowser.h"
#include "UIHelp.h"
#include "IVerticalScroller.h"

ContentBrowser::ContentBrowser() {
    SetDockType(DockType::m_Fill);
    m_Scroller = new IVerticalScroller;
    AddChild(m_Scroller);

}


void ContentBrowser::Update(float delta) {

    m_Scroller->Set(glm::vec2(m_Size.x-10, 0), glm::vec2(10, m_Size.y));
	UpdateChildren(delta);
}

void ContentBrowser::Render() {

    return;
    glm::vec2 offset;
    int yoff = m_Scroller->GetContentOffset();
    offset.x = 10;
    offset.y = 20 - yoff;
    float offy = 20;

   

    for (auto item : m_Items) {

        UIHelp::DrawImage(GetRenderPosition() + offset, glm::vec2(64, 64),item.m_Icon, glm::vec4(0, 1, 1, 1));
        UIHelp::DrawText(GetRenderPosition() + offset + glm::vec2(0, 72), item.m_Name, glm::vec4(1, 1, 1, 1));
        offset.x += 92;

        
        if (offset.x >= (m_Size.x - 60))
        {
            offset.x = 10;
            offset.y += 92;
            offy += 92;
        }


    }

    //Set(glm::vec2(0, 0), glm::vec2(m_Size.x, offset.y + 64));
    m_Scroller->SetContentHeight(offy+96);
    

	RenderChildren();

}

void ContentBrowser::Browse(std::string path) {


    auto files = ScanDirectoryContents(path);

    m_Items = files;

}

ContentType ContentBrowser::DetermineContentType(const std::filesystem::path& path) {
    if (std::filesystem::is_directory(path)) {
        return CT_Folder;
    }

    std::string extension = path.extension().string();
    // Convert to lowercase for case-insensitive comparison
    std::transform(extension.begin(), extension.end(), extension.begin(),
        [](unsigned char c) { return std::tolower(c); });

    if (extension == ".png") {
        return CT_PNG;
    }
    else if (extension == ".jpg" || extension == ".jpeg") {
        return CT_JPG;
    }

    return CT_File;
}

/**
 * Scans a directory and returns ContentItem objects for each entry
 * @param path The directory path to scan
 * @return Vector of ContentItem structures
 */
std::vector<ContentItem> ContentBrowser::ScanDirectoryContents(const std::string& path) {
    std::vector<ContentItem> contents;

    try {
        // Check if path exists and is a directory
        std::filesystem::path dirPath(path);
        if (!std::filesystem::exists(dirPath)) {
            return contents; // Return empty vector if path doesn't exist
        }

        if (!std::filesystem::is_directory(dirPath)) {
            return contents; // Return empty vector if path is not a directory
        }

        // Default position for first item
        glm::vec2 currentPosition(10.0f, 10.0f);
        float xOffset = 120.0f; // Horizontal spacing between items

        // Iterate through directory entries (non-recursively)
        for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
            ContentItem item;
            item.m_Name = entry.path().filename().string();
            item.m_FullPath = entry.path().string();
            item.m_Position = currentPosition;
            item.m_Type = DetermineContentType(entry.path());

            switch (item.m_Type) {

            case CT_File:
                item.m_Icon = new Texture2D("apps/mapeditor/fileicon.png");
                break;
            case CT_Folder:
                item.m_Icon = new Texture2D("apps/mapeditor/foldericon.png");
                break;
            default:
                item.m_Icon = new Texture2D("apps/mapeditor/fileicon.png");

            }

            contents.push_back(item);

            // Update position for next item
            currentPosition.x += xOffset;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        // Handle filesystem errors
        // In a real application, you might want to log this error
    }
    SortFoldersFirst(contents);
    return contents;
}

void ContentBrowser::SortFoldersFirst(std::vector<ContentItem>& items) {
    std::stable_partition(items.begin(), items.end(), [](const ContentItem& item) {
        return item.m_Type == CT_Folder;
        });
}