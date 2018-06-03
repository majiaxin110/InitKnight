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

	auto statusLayer = localStatus::create();
	log("main layer position:%f  %f", mainLayer->getPosition().x, mainLayer->getPosition().y);
	//statusLayer->setPosition(mainLayer->getPosition().x, mainLayer->getPosition().y);
	
	this->addChild(mainLayer,1);
	this->addChild(statusLayer,20);
	
	return true;
}