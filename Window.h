#pragma once
#pragma comment( linker, "/subsystem:windows" )

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include "Graphics.h"
#include <bitset>
#include <queue>
#include <algorithm>

class Window
{
public:
	struct KeyEvent
	{
		
		enum class Event
		{
			Press,
			Release,
			Invalid
		};
		KeyEvent(unsigned char code, Event type) noexcept
			:
			Code(code),Type(type)
		{}
		const unsigned char Code;
		const Event Type;
	};

	struct MouseEvent
	{

		enum class Event
		{
			LeftPress,
			LeftRelease,
			RightPress,
			RightRelease,
			WheelPrees,
			WheelRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};
		MouseEvent(int x, int y, Event type) noexcept
			:
			x(x),y(y), Type(type)
		{}
		const int x;
		const int y;
		const Event Type;
	};

public:
	Window(int width, int height);
	int ProcessMessages() noexcept;
	void SetTitle();
	void DrawMessageBox(std::wstring mes);
	// Keyboard ------------------------------------
	bool IsKeyPressed(unsigned char key);
	wchar_t GetChar();
	bool IsCharEmpty();
	bool IsKeyboardEventEmpty();
	Window::KeyEvent ReadKeyEvent();
	void ClearKeyEvent();
	void ClearCharQueue();
	// Mouse ---------------------------------------
	bool IsRightPressed() noexcept;
	bool IsLeftPressed() noexcept;
	bool IsMiddlePressed() noexcept;
	int GetMousePosX() noexcept;
	int GetMousePosY() noexcept;
	float GetMousePosXNormalized() noexcept;
	float GetMousePosYNormalized() noexcept;
	bool IsMouseEventEmpty();
	Window::MouseEvent ReadMouseEvent();
	void ClearMouseQueue();
	// DX11 ---------------------------------------
	void InitDX11();
	~Window();
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	Window(int width, int height, HWND Parent);
public:
	Graphics* Dx11 = nullptr;
private:
	std::wstring CLASS_NAME;
	bool Dx11Init = false;
	HINSTANCE Hinstace;
	HWND hwnd;
	int width;
	int height;
	int QueueLimit = 13;
   // Keyboard ------------------------------------
	std::bitset<256> KeyStates;
	std::queue<wchar_t> CharQueue;
	std::queue<KeyEvent> KeyQueue;
	// Mouse ---------------------------------------
	bool LeftPress = false;
	bool RightPress = false;
	bool MiddlePress = false;
	int ScrollAcumulate = 0;
	int ScrollDelta;
	int PosX;
	int PosY;
	std::queue<MouseEvent> MouseQueue;
	std::wstring lol;
};