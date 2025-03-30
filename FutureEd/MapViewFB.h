#pragma once
#include <IFrameBuffer.h>

class GameMap;
class GameCam;

enum EditMode {


    EM_Paste,EM_Line,EM_Rect,EM_RectFill,EM_Oval,EM_OvalFill,EM_Erase,EM_Fill,EM_ClearAll


};

class MapViewFB :

    public IFrameBuffer
{
public:

    MapViewFB();
 
    void OnMouseDown(int button) override;
    void OnMouseUp(int button) override;
    void OnMouseMove(glm::vec2 position, glm::vec2 delta) override;
    void OnMouseWheel(float z) override;
    void SetMap(GameMap* map) {
        m_Map = map;
    }
    void SetCam(GameCam* cam) {

        m_Cam = cam;

   }

    static EditMode m_EditMode;
private:


   
    int m_StartX, m_StartY;
    bool m_Select = false;
    glm::vec2 m_MousePos;
    GameMap* m_Map;
    GameCam* m_Cam;
    bool m_DragCam = false;
    bool m_RotCam = false;

};

