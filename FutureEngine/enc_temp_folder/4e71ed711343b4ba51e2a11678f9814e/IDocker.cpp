
#include "IDocker.h"
#include "IWindow.h"
#include "UIHelp.h"
#include "FutureApp.h"

IDocker::IDocker(glm::vec2 position, glm::vec2 size) : IControl(position, size)
{
    InitDockZones();
    m_HoveringWindow = nullptr;
    m_HoveringArea = DOCK_NONE;
    m_HighlightAlpha = 0.0f;
    m_Text = "Docking Area";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            Filled[x][y] = false;
        }
    }
    //Filled[0][0] =true;
   // Filled[0][2] =true;

    CreateZones();
}

void IDocker::CreateZones() {

    auto left = GetLeft();
    auto right = GetRight();
    auto bottom = GetBottom();
    auto top = GetTop();
    auto centre = GetCentre();
}

DockZone IDocker::GetCentre() {

    int startX = -1;
    int startY = -1;
    int endX = -1;
    int endY = -1;

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++) {

            if (!Filled[x][y]) {

                if (startX == -1) {
                    startX = x;
                    startY = y;
                }
                else {
                    endX = x;
                    endY = y;
                }

            }

        }
    }

    int px = startX * (m_Size.x * 0.3333);
    int py = startY * (m_Size.y * 0.3333);

    int a = 5;

    return DockZone();
}

DockZone IDocker::GetBottom() {

    int startX = -1;
    int endX = -1;

    for (int x = 0; x< 3; x++) {
        if (!Filled[x][2])
        {
            if (startX == -1)
            {
                startX = x;
                endX = x;
            }
            else {
                endX = x;
            }
        }
        else {

            if (startX != -1) {
                break;
            }
            //if (startX != -1)
           // {

            //}
        }
    }


    DockZone area;
    area.area = DockArea::DOCK_BOTTOM;

    if (startX != -1) {
        area.startX = startX;
        area.endX = endX;


        float dx = startX / 2.0f;
        float sx = 0;

        if (startX == 0) {
            dx = 0;
            if (endX == 0)
            {
                sx = m_Size.x * 0.3333;
            }
            if (endX == 1) {
                sx = m_Size.x * 0.6666;
            }
            if (endX == 2) {
                sx = m_Size.x;
            }
        }
        if (startX == 1) {
            dx = m_Size.x * 0.3333;
        }

        int stx = startX * (m_Size.x * 0.3333);
        int di = (endX - startX + 1);

        //area.position = glm::vec2(0, startY);

        //int dif = endY - startY;
        area.position = glm::vec2(stx,m_Size.y * 0.66666);
        area.size = glm::vec2(di * (m_Size.x * 0.3333),m_Size.y*0.3333);

    }
    else {
        area.occupied = false;
    }
    //area.
    m_DockZones.push_back(area);
    return area;

    //bool b1 = Filled[0][0];
    //bool b2 = Filled[0][1];
    //bool b3 = Filled[0][2];




}


DockZone IDocker::GetTop() {

    int startX = -1;
    int endX = -1;

    for (int x = 0; x < 3; x++) {
        if (!Filled[x][0])
        {
            if (startX == -1)
            {
                startX = x;
                endX = x;
            }
            else {
                endX = x;
            }
        }
        else {

            if (startX != -1) {

                break;
            }
            //if (startX != -1)
           // {

            //}
        }
    }


    DockZone area;
    area.area = DockArea::DOCK_TOP;

    if (startX != -1) {
        area.startX = startX;
        area.endX = endX;


        float dx = startX / 2.0f;
        float sx = 0;

        if (startX == 0) {
            dx = 0;
            if (endX == 0)
            {
                sx = m_Size.x * 0.3333;
            }
            if (endX == 1) {
                sx = m_Size.x * 0.6666;
            }
            if (endX == 2) {
                sx = m_Size.x;
            }
        }
        if (startX == 1) {
            dx = m_Size.x * 0.3333;
        }

        int stx = startX * (m_Size.x * 0.3333);
        int di = (endX - startX + 1);

        //area.position = glm::vec2(0, startY);

        //int dif = endY - startY;
        area.position = glm::vec2(stx,0);
        area.size = glm::vec2(di * (m_Size.x * 0.3333), m_Size.y * 0.3333);

    }
    else {
        area.occupied = false;
    }
    //area.
    m_DockZones.push_back(area);
    return area;

    //bool b1 = Filled[0][0];
    //bool b2 = Filled[0][1];
    //bool b3 = Filled[0][2];




}

DockZone IDocker::GetRight() {


    int startY = -1;
    int endY = -1;

    for (int y = 0; y < 3; y++) {
        if (!Filled[2][y])
        {
            if (startY == -1)
            {
                startY = y;
                endY = y;
            }
            else {
                endY = y;
            }
        }
        else {

            if (startY != -1) {
                break;
            }
            //if (startX != -1)
           // {

            //}
        }
    }


    DockZone area;
    area.area = DockArea::DOCK_RIGHT;

    if (startY != -1) {
        area.startY = startY;
        area.endY = endY;


        float dy = startY / 2.0f;
        float sy = 0;

        if (startY == 0) {
            dy = 0;
            if (endY == 0)
            {
                sy = m_Size.y * 0.3333;
            }
            if (endY == 1) {
                sy = m_Size.y * 0.6666;
            }
            if (endY == 2) {
                sy = m_Size.y;
            }
        }
        if (startY == 1) {
            dy = m_Size.y * 0.3333;
        }

        int sty = startY * (m_Size.y * 0.3333);
        int di = (endY - startY + 1);

        //area.position = glm::vec2(0, startY);

        //int dif = endY - startY;
        area.position = glm::vec2(m_Size.x*0.66666, sty);
        area.size = glm::vec2(m_Size.x * 0.3333, di * (m_Size.y * 0.3333));

    }
    else {
        area.occupied = false;
    }
    //area.
    m_DockZones.push_back(area);
    return area;

    //bool b1 = Filled[0][0];
    //bool b2 = Filled[0][1];
    //bool b3 = Filled[0][2];




}

DockZone IDocker::GetLeft() {


    int startY = -1;
    int endY = -1;

    for (int y = 0; y < 3; y++) {
        if (!Filled[0][y])
        {
            if (startY == -1)
            {
                startY = y;
                endY = y;
            }
            else {
                endY = y;
            }
        }
        else {

            if (startY != -1) {
                break;
            }
            //if (startX != -1)
           // {

            //}
        }
    }


    DockZone area;
    area.area = DockArea::DOCK_LEFT;

    if (startY != -1) {
        area.startY = startY;
        area.endY = endY;


        float dy = startY / 2.0f;
        float sy = 0;

        if (startY == 0) {
            dy = 0;
            if (endY == 0)
            {
                sy = m_Size.y * 0.3333;
            }
            if (endY == 1) {
                sy = m_Size.y * 0.6666;
            }
            if (endY == 2) {
                sy = m_Size.y;
            }
        }
        if (startY == 1) {
            dy = m_Size.y * 0.3333;
        }

        int sty = startY * (m_Size.y * 0.33);
        int di = (endY - startY + 1);

        //area.position = glm::vec2(0, startY);
        
        //int dif = endY - startY;
        area.position = glm::vec2(0, sty);
        area.size = glm::vec2(m_Size.x*0.3333, di*(m_Size.y*0.3333));

    }
    else {
        area.occupied = false;
    }
    //area.
    m_DockZones.push_back(area);
    return area;

    //bool b1 = Filled[0][0];
    //bool b2 = Filled[0][1];
    //bool b3 = Filled[0][2];


}

void IDocker::InitDockZones()
{
    // Clear any existing zones
 
}



void IDocker::WindowCancel()
{
  
    // Reset hovering state
    m_HoveringWindow = nullptr;
    m_HoveringArea = DOCK_NONE;

    // Reset animation state
    m_HighlightAlpha = 0.0f;
}

void IDocker::WindowOver(IWindow* window, glm::vec2 position)
{
    // Reset tracking if not dragging or no window
  
}

void IDocker::Update(float delta)
{
    // Update highlight animation
    if (m_HoveringArea != DOCK_NONE) {
        // Pulse the highlight effect smoothly
        m_HighlightAlpha += delta * 2.0f; // Control the speed of pulsing

        // Keep the value cycling for the sine wave
        if (m_HighlightAlpha > 1.0f) {
            m_HighlightAlpha = fmod(m_HighlightAlpha, 1.0f);
        }
    }
    else {
        // Fade out the highlight if no window is hovering
        m_HighlightAlpha = std::max(0.0f, m_HighlightAlpha - delta * 3.0f);
    }

    // Update all children (docked windows)
    UpdateChildren(delta);
}

void IDocker::Render()
{
    // Render the docker background
    auto pos = GetRenderPosition();
    //UIHelp::DrawRect(pos, m_Size, glm::vec4(1.15f, 0.15f, 0.15f, 0.5f));

    for (auto area : m_DockZones) {

        glm::vec4 col;

        switch (area.area) {
        case DOCK_LEFT:
            col = glm::vec4(1, 0, 0, 0.35);
            break;
        case DOCK_RIGHT:
            col = glm::vec4(0, 1, 0, 0.35);
            break;
        case DOCK_BOTTOM:
            col = glm::vec4(0, 0, 1, 0.35);
            break;
        case DOCK_TOP:
            col = glm::vec4(1, 1, 0, 0.35f);
            break;
        default:
            col = glm::vec4(0, 0, 0, 0);
            break;
        }

        UIHelp::DrawRect(area.position, area.size, glm::vec4(col));

    }
    // Ensure zones are updated and accurate before rendering
    // This ensures the visualized zones match the actual dock areas
  
    RenderChildren();
}