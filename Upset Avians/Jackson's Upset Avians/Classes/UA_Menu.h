#pragma once
//3rd Party Libraries
#include "cocos2d.h"
#include <ctime>
//Namespaces
using namespace cocos2d;

class UA_Menu : public cocos2d::Scene
{
public:
	//Engine Functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	void update(float deltaTime);
	CREATE_FUNC(UA_Menu);
	void initMenu();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void spawnRandomCharacter();
	Vec2 getRandomPointOnRect();
	bool getRandomBool();
	Vec2 getRandomPointInWindow();
	std::vector<Sprite*> characters;
	void killOffscreenCharacters();
private:
	//Engine
	Director* director;
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vec2 mousePosition;
	Sprite* spr_Background;
	Label* titleLabel;
	clock_t timeOfLastSpawn;
	int rectWidth;
	int rectHeight;
	int totalRect;
	Vec2 winCenter;
	Menu* menu;
};