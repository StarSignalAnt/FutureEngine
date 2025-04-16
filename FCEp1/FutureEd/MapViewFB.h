#pragma once
#include <IFrameBuffer.h>

class GameObj;
class GameMap;
class GameCam;
class Texture2D;

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

   bool IsWithin(glm::vec2 pos, glm::vec2 size, glm::vec2 mp) {

       if (mp.x >= pos.x && mp.x < pos.x + size.x)
       {
           if (mp.y >= pos.y  && mp.y < pos.y + size.y)
           {
               return true;
           }
       }
       return false;

   }

private:


   
    GameObj* m_Selected = nullptr;
    int m_StartX, m_StartY;
    bool m_Select = false;
    glm::vec2 m_MousePos;
    GameMap* m_Map;
    GameCam* m_Cam;
    bool m_DragCam = false;
    bool m_RotCam = false;
    Texture2D* m_LightIcon;
    Texture2D* m_LeftRight;
    Texture2D* m_UpDown;
    bool m_MoveRight = false;
    bool m_MoveUp = false;
    bool m_MoveBoth = false;
};

