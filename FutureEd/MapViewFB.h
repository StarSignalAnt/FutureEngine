#pragma once
#include <IFrameBuffer.h>

class GameMap;
class GameCam;

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


private:

    GameMap* m_Map;
    GameCam* m_Cam;
    bool m_DragCam = false;

};

