#include "OnlineServerScene.h"

USING_NS_CC;

Scene* ServerScene::createScene()
{
	return ServerScene::create();
}

bool ServerScene::init()
{
	auto mainLayer = ServerLayer::create();
	mainLayer->setName("main");

	this->addChild(mainLayer, 1);

	return true;
}