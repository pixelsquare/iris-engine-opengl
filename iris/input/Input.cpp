#include "Input.h"
#include "iris/Iris.h"
#include <stdio.h>

namespace IrisFramework
{
	Input::Input() {}

	Input::~Input() {}

	Input &Input::getInstance()
	{
		static Input instance;
		return instance;
	}

	void Input::lateUpdate()
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

#if defined(_WIN32)
	bool Input::updateWin32Input(HWND p_windowHandle,
		UINT p_windowMsg, WPARAM p_windowParam, LPARAM p_longParam)
	{
		switch(p_windowMsg)
		{
			case WM_KEYDOWN:
			{
				if(p_windowParam == VK_ESCAPE)
				{
					IRIS_ENGINE.shutdown();
				}

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
				POINT p = {LOWORD(p_longParam), HIWORD(p_longParam)};
				IRIS_INPUT.m_mousePosition = Vector3f((float)p.x, (float)p.y, 0.0f);

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
}
