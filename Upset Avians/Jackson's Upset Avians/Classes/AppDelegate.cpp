

#include "AppDelegate.h"
//#include "UA_Gameplay.h"
#include "UA_Menu.h"
USING_NS_CC;

//--- Constructors and Destructors ---//
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//--- Virtual Methods ---//
bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview)
	{
		glview = GLViewImpl::createWithRect("Upset Avians", Rect(0.0f, 0.0f, 960.0f, 540.0f), 1.0f, false);
		director->setOpenGLView(glview);
	}

	auto scene = UA_Menu::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}

