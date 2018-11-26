#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "cocos2d.h"
using namespace cocos2d;

enum InputState
{
	Idle,
	Pressed,
	Released,
	Held
};

#define NUM_MOUSE_BUTTONS (int)cocos2d::EventMouse::MouseButton::BUTTON_8 + 2
#define NUM_KEY_CODES (int)cocos2d::EventKeyboard::KeyCode::KEY_PLAY + 1
typedef cocos2d::EventKeyboard::KeyCode KeyCode;
typedef cocos2d::EventMouse::MouseButton MouseButton;

class InputHandler
{
protected:
	//--- Constructor ---//
	InputHandler(); //Singleton pattern
	
public:
	//--- Destructor ---/
	~InputHandler();

	//--- Getters ---//
	//Mouse
	Vec2 getMousePosition() const;
	bool getMouseButtonPress(MouseButton button) const;
	bool getMouseButtonRelease(MouseButton button) const;
	bool getMouseButton(MouseButton button) const;
	float getMouseScroll() const;

	//Keyboard
	bool getKeyPress(KeyCode key) const;
	bool getKeyRelease(KeyCode key) const;
	bool getKey(KeyCode key) const;

	//--- Methods ---//
	void initInputs(); //This HAS to be called ONCE. If not, no inputs will ever be read
	void updateInputs(); //This HAS to be called EVERY FRAME. If not, the inputs won't be synced to the current frame

	//--- Singleton Instance ---//
	static InputHandler* getInstance(); //Singleton 

private:
	//--- Private Data ---//
	//Mouse
	Vec2 mousePosition;
	InputState mouseStates[NUM_MOUSE_BUTTONS]; //States for all of the mouse buttons in cocos2D. +2 since unset is a button as well and is defaulted to -1

	//Keyboard
	InputState keyboardStates[NUM_KEY_CODES]; //States for all of the keycodes in cocos2D

	//--- Singleton Instance ---//
	static InputHandler* inst; //Singleton pattern
};

#define INPUTS InputHandler::getInstance()

#endif
