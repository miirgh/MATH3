#pragma once

//3rd Party Libraries
#include "cocos2d.h"

#include "bird.h"
#include "pig.h"
#include "tags.h"
#include "Obstacle.h"

//Namespaces
using namespace cocos2d;

struct Mouse
{
	Vec2 position;
};


class UA_Gameplay : public cocos2d::Scene
{
public:
	//Engine Functions
	CREATE_FUNC(UA_Gameplay);
	static cocos2d::Scene* createScene();
	virtual void onExit();
	virtual void onEnter();
	//Init Functions
	virtual bool init();
	void initSprites();
	void initObstacles();
	void initPigs();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void initContactListener();
	void initPauseMenu();

	//Main Update Loop
	void update(float deltaTime);
	void grabbedBird();
	void spawnBird();
	void updateBirds();
	void updatePigs();
	void drawBands();

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);
	bool onContactBeginCallback(PhysicsContact& contact);

	//Level creation functions
	void createObstacle(Vec2 position, Vec2 extent, Color4F color, PhysicsMaterial material);
	void createPig(Vec2 position);
	
	//Utility functions
	void damagePig(Vec2 position, int amount);
	void damagePig(Vec2 pigPosition, Vec2 birdPosition);
	void damageObstacle(Vec2 obstaclePosition, Vec2 birdPosition);
	void toggleDebugDraw();
	void toggleMenu();
	void quitToMenu();
	float lerp(float p1, float p2, float t);
	//Damages the pig that's at the given position. 


private:
	//Engine
	Director* director;
	
	//Event listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	bool mouseDown;
	bool birdHeld;
	Vec2 mousePosition;

	//Background Sprites
	Sprite* spr_Background;
	Sprite* spr_Background2;

	//The bird that's currently active
	Bird* activeBird;

	//Vectors of birds, pigs & obstacles that are currently alive
	std::vector<Bird*> birds;
	std::vector<Pig*> pigs;
	std::vector<Obstacle*> obstacles;


	//Catapult Sprites
	Vec2 slingshotPosition;
	DrawNode* leftBand;
	DrawNode* rightBand;


	//Camera Target
	Sprite* cameraTarget;
	static Scene* sceneHandle;
	float groundHeight;

	bool drawDebug = false;
	
	Menu* pauseMenu;
	bool menuDisplayed = false;

	//Mouse Information
	Mouse mouse;

};

