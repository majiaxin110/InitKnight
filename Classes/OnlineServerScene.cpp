
#include "OnlineServerScene.h"

USING_NS_CC;

Scene* ServerScene::createScene()
{
	return ServerScene::create();
}

bool ServerScene::init()
{
	log("local scene init");
	auto mainLayer = ServerLayer::create();
	mainLayer->setName("main");
	/*auto statusLayer = localStatus::create();
	statusLayer->setName("status");
	statusLayer->setTag(123);
	mainLayer->getStatusLayer(statusLayer);*/

	this->addChild(mainLayer, 1);
	//this->addChild(statusLayer, 20);

	return true;
}