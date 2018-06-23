#pragma once
#include "cocos2d.h"
#include "ClientLayer.h"

class ClientScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method maddnually
	CREATE_FUNC(ClientScene);
};
