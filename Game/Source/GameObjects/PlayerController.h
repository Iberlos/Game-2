#ifndef __PlayerController_H__
#define __PlayerController_H__

class Event;
class EventManager;

class PlayerController
{
    enum Directions
    {
        DIR_UP      = 0x0001,
        DIR_DOWN    = 0x0002,
        DIR_LEFT    = 0x0004,
        DIR_RIGHT   = 0x0008,
        DIR_JUMP    = 0x0010,
        DIR_CLOCKWISE = 0x0020,
        DIR_COUNTER_CLOCKWISE = 0x0040,
    };

    enum Actions
    {
        ACTION_SHOOT = 0x0001,
    };

protected:
    int m_Directions;
    vec2 m_RotationChange;
    vec2 m_PreviousMouse = vec2(0,0); //sshhhhhh
    int m_Actions;
    EventManager* m_EventManager;

public:
    PlayerController(EventManager* eventManager);

    void OnEvent(Event* pEvent);

    bool IsHeld_Up() { return m_Directions & DIR_UP; }
    bool IsHeld_Down() { return m_Directions & DIR_DOWN; }
    bool IsHeld_Left() { return m_Directions & DIR_LEFT; }
    bool IsHeld_Right() { return m_Directions & DIR_RIGHT; }
    bool IsHeld_Jump() { return m_Directions & DIR_JUMP; }
    bool IsHeld_Rotate_C() { return m_Directions & DIR_CLOCKWISE; }
    bool IsHeld_Rotate_CC() { return m_Directions & DIR_COUNTER_CLOCKWISE; }
    bool IsHeld_Shoot() { return m_Actions & ACTION_SHOOT; }
};

#endif //__PlayerController_H__
