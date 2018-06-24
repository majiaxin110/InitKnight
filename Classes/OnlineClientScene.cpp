
#include "OnlineClientScene.h"
#include "ClientLayer.h"
USING_NS_CC;

Scene* ClientScene::createScene()
{
	return ClientScene::create();
}

bool ClientScene::init()
{
	auto mainLayer = ClientLayer::create();

	mainLayer->setName("main");
	/*auto statusLayer = localStatus::create();
	statusLayer->setName("status");
	statusLayer->setTag(123);
	mainLayer->getStatusLayer(statusLayer);*/

	this->addChild(mainLayer, 1);
	//this->addChild(statusLayer, 20);

	return true;
}
