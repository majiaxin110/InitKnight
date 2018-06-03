#include "localPlayStatusLayer.h"

bool localStatus::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto test = Sprite::create("ninja.png");
	test->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 + 50));
	this->addChild(test,1);

	return true;
}