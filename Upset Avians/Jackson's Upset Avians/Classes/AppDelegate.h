#pragma once

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
	//--- Constructors and Destructors ---//
	AppDelegate();
	virtual ~AppDelegate();

	//--- Virtual Methods ---//
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};

