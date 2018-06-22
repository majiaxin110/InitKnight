#include "localPlayScene.h"
#include "localPlayMainLayer.h"
#include "localPlayStatusLayer.h"

Scene* localScene::createScene()
{
	return localScene::create();
}

/*void localScene::transPlayerName(const char * name)
{
	localStatus* sta = static_cast<localStatus*>(this->getChildByTag(123));
	sta->setPlayerName(name);
}*/

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