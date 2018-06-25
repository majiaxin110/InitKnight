//±¾µØ²ãÈİÆ÷
#include "localPlayScene.h"
#include "localPlayMainLayer.h"
#include "localPlayStatusLayer.h"

Scene* localScene::createScene()
{
	return localScene::create();
}

bool localScene::init()
{
	log("local scene init");
	auto mainLayer = localPlay::create();
	mainLayer->setName("main");
	auto statusLayer = localStatus::create();
	statusLayer->setName("status");
	statusLayer->setTag(123);
	mainLayer->getStatusLayer(statusLayer);

	this->addChild(mainLayer,1);
	this->addChild(statusLayer,20);
	
	return true;
}