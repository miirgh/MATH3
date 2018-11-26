#include "UA_Menu.h"
//#include "testScene.h"
#include "UA_Gameplay.h"
#include <iostream>
#include "SimpleAudioEngine.h"

#define TIME_BETWEEN_SPAWNS 0.01f
#define RECTANGLE_OFFSET 50.0f
#define MIN_SPEED 50.0f
#define MAX_SPEED 500.0f

Scene* UA_Menu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	auto layer = UA_Menu::create();

	scene->addChild(layer);

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//startSceneFollow();

	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();

	return scene;
}

void UA_Menu::onEnter()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/themesong.wav", true);
	Scene::onEnter();
}

bool UA_Menu::init()
{
	//Ensure the parent init function was called first. If it wasn't, exit this one
	if (!Scene::init())
		return false;

	srand(time(0));

	timeOfLastSpawn = clock();

	

	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	rectWidth = (2 * RECTANGLE_OFFSET) + director->getWinSize().width;
	rectHeight = (2 * RECTANGLE_OFFSET) + director->getWinSize().height;
	totalRect = (2 * rectWidth) + (2 * rectHeight);
	winCenter = director->getWinSizeInPixels() / 2;

	//Init the sprites
	initMenu();

	initListeners();

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;
}

void UA_Menu::update(float deltatime)
{
	if (difftime(clock(), timeOfLastSpawn) / CLOCKS_PER_SEC > TIME_BETWEEN_SPAWNS)
	{
		timeOfLastSpawn = clock();
		spawnRandomCharacter();
	}
	killOffscreenCharacters();


}

void UA_Menu::initListeners()
{
	//Init the mouse listenerr
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();
}

void UA_Menu::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = [&](Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse button press
		auto mouseClickPosition = mouseEvent->getLocationInView();
		mouseClickPosition.y += 540;

		//Init the message to be output in the message box
		std::stringstream message;

		//Get the mouse button from the event handler
		auto mouseButton = mouseEvent->getMouseButton();

		//Perform different logic depending on which button was pressed
		/*if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
			std::cout << "Left Mouse Button Pressed!" << std::endl;
		else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
			std::cout << "Right Mouse Button Pressed!" << std::endl;*/
	};


	//On Mouse Up
	mouseListener->onMouseUp = [&](Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse button press
		auto mouseUpPosition = mouseEvent->getLocation();

		//Init the message to be output in the message box
		std::stringstream message;

		//Get the mouse button from the event handler
		auto mouseButton = mouseEvent->getMouseButton();

		//Perform different logic depending on which button was released
		/*if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
			std::cout << "Left Mouse Button Released!" << std::endl;
		else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
			std::cout << "Right Mouse Button Released!" << std::endl;*/
	};


	//On Mouse Move'
	mouseListener->onMouseMove = [&](cocos2d::Event* event)
	{
		//Cast the event as a mouse event
		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Get the position of the mouse from the event handler
		auto mouseEventPos = mouseEvent->getLocationInView();

		//Store the position into the mouse struct
		mousePosition = Vec2(mouseEventPos.x, 540 + mouseEventPos.y);

		//Output the position to the console
		//std::cout << this->mouse.position.x << ", " << this->mouse.position.y << std::endl;
	};


	//On Mouse Scroll
	mouseListener->onMouseScroll = [](cocos2d::Event* event)
	{
	};


	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void UA_Menu::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();


	//On Key Pressed
	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			//std::cout << "Space Bar Was Pressed!" << std::endl;
			auto gameplayScene = UA_Gameplay::createScene();
			director->replaceScene(gameplayScene);
			//director->replaceScene(new UA_Gameplay);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			spawnRandomCharacter();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_L)
		{
			auto gameplayScene = UA_Gameplay::createScene();
			director->replaceScene(gameplayScene);
		}
		//else if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		//	exit(0);
	};


	//On Key Released
	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			//auto newScene = UpsetAvians::createScene();
			//Director::getInstance()->replaceScene(newScene);
			//std::cout << "Space Bar Was Released!" << std::endl;
		}
		
	};


	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void UA_Menu::onExit()
{
	//for (auto it = characters.begin(); it != characters.end(); ++it)
	//{
	//	delete *it;
	//}
	//_eventDispatcher->removeAllEventListeners();
	characters.clear();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	Scene::onExit();
	//std::cout << "Exited!" << std::endl;
}

void UA_Menu::initMenu()
{
	spr_Background = Sprite::create("UA/Background/space.png"); //Load the handle
	spr_Background->setPosition(director->getWinSizeInPixels().width / 2.0f, director->getWinSizeInPixels().height / 2.0f); //Center the image in the window
	spr_Background->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the background is the anchor point

	this->addChild(spr_Background, -100);


	titleLabel = Label::create("Upset Avians", "fonts/arial.ttf", 100.0f, director->getWinSize(), TextHAlignment::CENTER, TextVAlignment::TOP);
	titleLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	titleLabel->enableShadow();
	this->addChild(titleLabel, 100);

	auto playLabel = Label::create("Play", "fonts/arial.ttf", 50.0f, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	playLabel->enableShadow();
	//playLabel->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	//this->addChild(playLabel, 100);


	auto playItem = MenuItemLabel::create(playLabel, [&](Ref* sender) {
		auto gameplayScene = UA_Gameplay::createScene();
		director->replaceScene(TransitionPageTurn::create(2.0f, gameplayScene, false));
		//director->
	});

	playItem->setPosition(0, -200);

	menu = Menu::create(playItem, NULL);
	this->addChild(menu, 99);

}

void UA_Menu::spawnRandomCharacter()
{

	//if true we'll spawn a bird, if false we'll spawn a pig!
	bool spawnShip = getRandomBool();
	Sprite* newCharacter;
	std::string texturePath;
	if (spawnShip)
	{
		texturePath = "UA/Ship/SpaceShip.png";
	}
	else
	{
		texturePath = "UA/Ship/asteroid.png";
	}
	newCharacter = Sprite::create(texturePath); //Load the handle
	newCharacter->setPosition(getRandomPointOnRect());
	newCharacter->setScale(0.25f); //Scale the bird since it loads in quite large 
	newCharacter->setAnchorPoint(Vec2(0.5f, 0.5f)); //Ensure the middle of the bird is the anchor point
	auto body = PhysicsBody::createCircle(newCharacter->getSpriteFrame()->getRectInPixels().size.height * newCharacter->getScale() * 1.33f); //Use a circle since the bird is roughly circular
	body->setContactTestBitmask(0xFFFFFFFF);
	newCharacter->setPhysicsBody(body);
	Vec2 target = getRandomPointInWindow();
	Vec2 velocityDir = (target - newCharacter->getPosition()).getNormalized();
	newCharacter->getPhysicsBody()->setVelocity(velocityDir * RandomHelper::random_int((int)MIN_SPEED, (int)MAX_SPEED));

	characters.push_back(newCharacter);

	this->addChild(newCharacter);

	//std::cout << "Spawning char at " << newCharacter->getPosition().x << " " << newCharacter->getPosition().y << "travelling towards: " << velocityDir.x << " " << velocityDir.y << std::endl;
	
}

Vec2 UA_Menu::getRandomPointOnRect()
{
	//Getting a point along the "unwrapped" window rectangle with the offset applied, converting this to a point on the rectangle and returning
	int rectLinePos = RandomHelper::random_int(0, totalRect);
	Vec2 result;

	//On the top 
	if (rectLinePos < rectWidth)
	{
		result.x = rectLinePos;
		result.y = rectHeight;
	}
	//On the right
	else if (rectLinePos < (rectWidth + rectHeight))
	{
		result.x = rectWidth;
		result.y = rectLinePos - rectWidth;
	}
	//On the bottom
	else if (rectLinePos < (totalRect - rectHeight))
	{
		result.x = rectLinePos - rectWidth - rectHeight;
		result.y = 0;
	}
	//On the left
	else
	{
		result.x = 0;
		result.y = rectLinePos - rectWidth - rectWidth - rectHeight;
	}

	return result;
}

bool UA_Menu::getRandomBool()
{
	return (rand() % 2) == 0;
}

Vec2 UA_Menu::getRandomPointInWindow()
{
	Vec2 result;

	result.x = RandomHelper::random_int(0, (int)director->getWinSizeInPixels().width);
	result.y = RandomHelper::random_int(0, (int)director->getWinSizeInPixels().height);

	return result;
}

void UA_Menu::killOffscreenCharacters()
{
	Vec2 pos;
	Vec2 offset(RECTANGLE_OFFSET, RECTANGLE_OFFSET);
	for (int i = 0; i < characters.size(); i++)
	{
		pos = characters[i]->getPosition() + offset;
		if ((pos.x < 0 || pos.x > rectWidth + offset.x) || (pos.y < 0 || pos.y > rectHeight + offset.y))
		{
			characters[i]->runAction(RemoveSelf::create());
			characters.erase(characters.begin() + i);
			i--;
		}
	}
	//std::cout << characters.size() << std::endl;
}