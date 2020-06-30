#include "GamePCH.h"

#include "GameObjects/PlayerController.h"
#include "Events/GameEvent.h"

PlayerController::PlayerController(EventManager* eventManager)
{
    m_EventManager = eventManager;
    m_Directions = 0;
    m_Actions = 0;
}

void PlayerController::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == EventType_Input )
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>( pEvent );

        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard )
        {
            int keyID = pInput->GetID();

            if( pInput->GetInputState() == InputState_Pressed )
            {
                if( keyID == VK_UP    || keyID == 'W' ) { m_Directions |= DIR_UP; }
                if( keyID == VK_DOWN  || keyID == 'S' ) { m_Directions |= DIR_DOWN; }
                if( keyID == VK_LEFT  || keyID == 'A' ) { m_Directions |= DIR_LEFT; }
                if( keyID == VK_RIGHT || keyID == 'D' ) { m_Directions |= DIR_RIGHT; }
                if( keyID == 'Z'      || keyID == ' ' ) { m_Directions |= DIR_JUMP; }
                if (keyID == 'E'                      ) { m_Directions |= DIR_CLOCKWISE; }
                if (keyID == 'Q')                       { m_Directions |= DIR_COUNTER_CLOCKWISE; }

                //One-time actions
                if (keyID == 'X')
                {
                    m_Actions |= ACTION_SHOOT;
                    /*Event* pEvent = new GameEvent(GameEventType_PlayerFire);
                    m_EventManager->QueueEvent(pEvent);*/
                }
            }

            else if( pInput->GetInputState() == InputState_Released )
            {
                if( keyID == VK_UP    || keyID == 'W' ) { m_Directions &= ~DIR_UP; }
                if( keyID == VK_DOWN  || keyID == 'S' ) { m_Directions &= ~DIR_DOWN; }
                if( keyID == VK_LEFT  || keyID == 'A' ) { m_Directions &= ~DIR_LEFT; }
                if( keyID == VK_RIGHT || keyID == 'D' ) { m_Directions &= ~DIR_RIGHT; }
                if( keyID == 'Z'      || keyID == ' ' ) { m_Directions &= ~DIR_JUMP; }
                if (keyID == 'E'                      ) { m_Directions &= ~DIR_CLOCKWISE; }
                if (keyID == 'Q'                      ) { m_Directions &= ~DIR_COUNTER_CLOCKWISE; }

                if (keyID == 'X'                      ) { m_Actions &= ~ACTION_SHOOT; }
            }
        }
        else if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            int buttonID = pInput->GetID();
            if (pInput->GetInputState() == InputState_Held)
            {
                m_RotationChange = pInput->GetPosition() - m_PreviousMouse;
                m_PreviousMouse = pInput->GetPosition();
            }
            if (pInput->GetInputState() == InputState_Pressed)
            {
                /*Event* pEvent = new GameEvent(GameEventType_PlayerFire);
                m_EventManager->QueueEvent(pEvent);*/
                if (buttonID == 0) { m_Actions |= ACTION_SHOOT; }
            }
            else if (pInput->GetInputState() == InputState_Released)
            {
                if (buttonID == 0) { m_Actions &= ~ACTION_SHOOT; }
            }
        }
#endif
    }
}
