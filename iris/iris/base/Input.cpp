#include "base\Input.h"
#include "base\Director.h"
#include "platform\StdC.h"
#include "platform\GLView.h"

IRIS_BEGIN

Input::Input()
: m_mouseEnabled(true)
, m_mousePosition(Vector3f::ZERO)
, m_mousePositionScreen(Vector3f::ZERO)
{
}

Input::~Input()
{
}

Input &Input::getInstance()
{
    static Input instance;
    return instance;
}

void Input::update()
{
    for(int i = 0; i < 256; i++)
    {
        if(m_keyDown[i])
        {
            m_keyDown[i] = false;
        }

        if(m_keyUp[i])
        {
            m_keyUp[i] = false;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if(m_mouseDown[i])
        {
            m_mouseDown[i] = false;
        }

        if(m_mouseUp[i])
        {
            m_mouseUp[i] = false;
        }
    }
}

bool Input::getKey(unsigned int p_key)
{
#if defined(_WIN32)
    return m_keyStrokes[p_key];
#else
    return false;
#endif
}

bool Input::getKeyDown(unsigned int p_key)
{
#if defined(_WIN32)
    return m_keyDown[p_key];
#else
    return false;
#endif
}

bool Input::getKeyUp(unsigned int p_key)
{
#if defined(_WIN32)
    return m_keyUp[p_key];
#else
    return false;
#endif
}

Vector3f Input::getMousePosition() const
{
#if defined(_WIN32)
    return m_mousePosition;
#else
    return Vector3f::ZERO;
#endif
}

void Input::setMousePosition(const Vector3f p_mousePosition)
{
    setMousePosition(p_mousePosition.x, p_mousePosition.y);
}

void Input::setMousePosition(float p_mousePosX, float p_mousePosY)
{
    m_mousePosition = Vector3f(p_mousePosX, p_mousePosY, 0.0f);

#if defined(_WIN32)
    SetCursorPos((int)p_mousePosX, (int)p_mousePosY);
#endif
}

Vector3f Input::getMousePositionScreen() const
{
    return m_mousePositionScreen;
}

bool Input::getMouseEnabled() const
{
#if defined(_WIN32)
    return m_mouseEnabled;
#else
    return false;
#endif
}

void Input::setMouseEnabled(bool p_mouseEnabled)
{
    m_mouseEnabled = p_mouseEnabled;

#if defined(_WIN32)
    ShowCursor(p_mouseEnabled);
#endif
}

bool Input::getMouseButton(unsigned int p_buttonIdx)
{
#if defined(_WIN32)
    return m_mouseInput[p_buttonIdx];
#else
    return false;
#endif
}

bool Input::getMouseButtonDown(unsigned int p_buttonIdx)
{
#if defined(_WIN32)
    return m_mouseDown[p_buttonIdx];
#else
    return false;
#endif
}

bool Input::getMouseButtonUp(unsigned int p_buttonIdx)
{
#if defined(_WIN32)
    return m_mouseUp[p_buttonIdx];
#else
    return false;
#endif
}

#if defined(_WIN32)
bool Input::updateWin32Input(HWND p_windowHandle,
                             UINT p_windowMsg, 
                             WPARAM p_windowParam, 
                             LPARAM p_longParam)
{
    switch(p_windowMsg)
    {
        case WM_KEYDOWN:
        {
#if DESTROY_WINDOW_WITH_ESCAPE
            if(p_windowParam == VK_ESCAPE)
            {
                IRIS_DIRECTOR.end();
            }
#endif

            if(!IRIS_INPUT.m_keyStrokes[p_windowParam])
            {
                IRIS_INPUT.m_keyDown[p_windowParam] = TRUE;
            }

            IRIS_INPUT.m_keyStrokes[p_windowParam] = TRUE;
            return 0;
        }

        case WM_KEYUP:
        {
            if(IRIS_INPUT.m_keyStrokes[p_windowParam])
            {
                IRIS_INPUT.m_keyUp[p_windowParam] = TRUE;
            }

            IRIS_INPUT.m_keyStrokes[p_windowParam] = FALSE;
            return 0;
        }

        case WM_MOUSEMOVE:
        {
            // Screen points (monitor)
            POINT p = {LOWORD(p_longParam), HIWORD(p_longParam)};
            IRIS_INPUT.m_mousePosition = Vector3f(
                (float)p.x, 
                (float)p.y,
                0.0f);

            // Window points
            POINT p1[1];
            GetCursorPos(&p1[0]);

            IRIS_INPUT.m_mousePositionScreen = Vector3f(
                (float)p1[0].x, 
                (float)p1[0].y, 
                0.0f);

            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            if(!IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::LEFT])
            {
                IRIS_INPUT.m_mouseDown[IRIS_MOUSETYPE::LEFT] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::LEFT] = TRUE;
            return 0;
        }

        case WM_LBUTTONUP:
        {
            if(IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::LEFT])
            {
                IRIS_INPUT.m_mouseUp[IRIS_MOUSETYPE::LEFT] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::LEFT] = FALSE;
            return 0;
        }

        case WM_MBUTTONDOWN:
        {
            if(!IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::MIDDLE])
            {
                IRIS_INPUT.m_mouseDown[IRIS_MOUSETYPE::MIDDLE] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::MIDDLE] = TRUE;
            return 0;
        }

        case WM_MBUTTONUP:
        {
            if(IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::MIDDLE])
            {
                IRIS_INPUT.m_mouseUp[IRIS_MOUSETYPE::MIDDLE] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::MIDDLE] = FALSE;
            return 0;
        }

        case WM_RBUTTONDOWN:
        {
            if(!IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::RIGHT])
            {
                IRIS_INPUT.m_mouseDown[IRIS_MOUSETYPE::RIGHT] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::RIGHT] = TRUE;
            return 0;
        }

        case WM_RBUTTONUP:
        {
            if(IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::RIGHT])
            {
                IRIS_INPUT.m_mouseUp[IRIS_MOUSETYPE::RIGHT] = TRUE;
            }

            IRIS_INPUT.m_mouseInput[IRIS_MOUSETYPE::RIGHT] = FALSE;
            return 0;
        }

        default:
            break;
    }

    return 0;
}
#endif

IRIS_END
