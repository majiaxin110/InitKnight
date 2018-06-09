#include "loseScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* LoseScene::createScene()
{
	return LoseScene::create();
}

bool LoseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto imageBackground = ui::ImageView::create("loseBackground.png");
	imageBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(imageBackground);

	return true;
}
