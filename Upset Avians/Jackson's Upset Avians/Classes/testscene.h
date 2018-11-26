#pragma once
//3rd Party Libraries
#include "cocos2d.h"

//Namespaces
using namespace cocos2d;

class testScene : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	void update(float deltaTime);
	CREATE_FUNC(testScene);

	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
private:
	//Engine
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vec2 mousePosition;
};