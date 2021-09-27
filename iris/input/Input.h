#ifndef __IRIS_INPUT_H__
#define __IRIS_INPUT_H__

#include "iris/IrisDefinitions.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#include "vector3f/Vector3f.h"

namespace IrisFramework
{
	#define IRIS_INPUT Input::getInstance()

	typedef enum KeyCode
	{
		Backspace	= 0x08,		Delete		= 0x2E,
		Tab			= 0x09,		Clear		= 0x0C,
		Return		= 0x0D,		Pause		= 0x13,
		Escape		= 0x1B,		Space		= 0x20,
		Keypad0		= 0x60,		Keypad1		= 0x61,
		Keypad2		= 0x62,		Keypad3		= 0x63,
		Keypad4		= 0x64,		Keypad5		= 0x65,
		Keypad6		= 0x66,		Keypad7		= 0x67,
		Keypad8		= 0x68,		Keypad9		= 0x69,
		Divide		= 0x6F,		Multiply	= 0x6A,
		Minus		= 0x6D,		Plus		= 0x6B,
		UpArrow		= 0x26,		DownArrow	= 0x28,
		RightArrow	= 0x27,		LeftArrow	= 0x25,
		Insert		= 0x2D,		Home		= 0x24,
		End			= 0x23,
		F1	= 0x70, F2	= 0x71, F3	= 0x72, F4	= 0x73, F5	= 0x74,
		F6	= 0x75, F7	= 0x76, F8	= 0x77, F9	= 0x78, F10 = 0x79,
		F11 = 0x7A, F12 = 0x7B, F13 = 0x7C, F14 = 0x7D, F15 = 0x7E,
		A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45,
		F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
		K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F,
		P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
		U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59,
		Z = 0x5A
	} IRIS_KEYCODE;

	typedef enum MouseType
	{
		LEFT = 0x00, 
		RIGHT = 0x01, 
		MIDDLE  = 0x02
	} IRIS_MOUSETYPE;

	class Input
	{
	public:
		static Input& getInstance();

		void lateUpdate();

		inline bool getKey(unsigned int p_key);
		inline bool getKeyDown(unsigned int p_key);
		inline bool getKeyUp(unsigned int p_key);

		inline bool getMouseButton(unsigned int p_buttonIdx);
		inline bool getMouseButtonDown(unsigned int p_buttonIdx);
		inline bool getMouseButtonUp(unsigned int p_buttonIdx);

		inline Vector3f getMousePosition() const;

#if defined(_WIN32)
		static bool updateWin32Input(HWND p_windowHandle,
			UINT p_windowMsg, WPARAM p_windowParam, LPARAM p_longParam);
#endif

	private:
		Input();
		~Input();

		bool m_keyStrokes[256];
		bool m_keyDown[256];
		bool m_keyUp[256];

		bool m_mouseInput[3];
		bool m_mouseDown[3];
		bool m_mouseUp[3];

		Vector3f m_mousePosition;

	protected:
	};

	inline bool Input::getKey(unsigned int p_key)
	{
#if defined(_WIN32)
		return m_keyStrokes[p_key];
#else
		return false;
#endif
	}

	inline bool Input::getKeyDown(unsigned int p_key)
	{
#if defined(_WIN32)
		return m_keyDown[p_key];
#else
		return false;
#endif
	}

	inline bool Input::getKeyUp(unsigned int p_key)
	{
#if defined(_WIN32)
		return m_keyUp[p_key];
#else
		return false;
#endif
	}

	inline Vector3f Input::getMousePosition() const
	{
#if defined(_WIN32)
		return m_mousePosition;
#else
		return Vector3f::ZERO;
#endif
	}

	inline bool Input::getMouseButton(unsigned int p_buttonIdx)
	{
#if defined(_WIN32)
		return m_mouseInput[p_buttonIdx];
#else
		return false;
#endif
	}

	inline bool Input::getMouseButtonDown(unsigned int p_buttonIdx)
	{
#if defined(_WIN32)
		return m_mouseDown[p_buttonIdx];
#else
		return false;
#endif
	}

	inline bool Input::getMouseButtonUp(unsigned int p_buttonIdx)
	{
#if defined(_WIN32)
		return m_mouseUp[p_buttonIdx];
#else
		return false;
#endif
	}
}

#endif
