#include "localPlayStatusLayer.h"
#include "ui/CocosGUI.h"

bool localStatus::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto KnightHead = Sprite::create("KnightHead1.png");
	KnightHead->setPosition(Vec2(40, visibleSize.height - 50));
	KnightHead->setTag(100);
	this->addChild(KnightHead);
	

	cBloodProgress = new ProgressView;
	cBloodProgress->setPosition(Vec2(214, visibleSize.height - 50));
	cBloodProgress->initProgressView("bloodProgress/KnightBack.png","bloodProgress/KnightFore.png");

	cBloodProgress->setScale(1.0f);
	cBloodProgress->setTotalProgress(100.0f);
	cBloodProgress->setCurrentProgress(50.0f);
	this->addChild(cBloodProgress, 101);

	return true;
}

bool localStatus::cutHeroBlood(float amount)
{
	return cBloodProgress->cutBlood(amount);
}

void localStatus::addHeroBlood(float amount)
{
	return cBloodProgress->addBlood(amount);
}

void localStatus::showOldNPCDialog()
{
	auto image = ui::ImageView::create("NPC1.png");
	image->setPosition(Vec2(480, 320));
	image->setName("NPC1");
	this->addChild(image,2);
}

void localStatus::removeOldNPCDialog()
{
	this->removeChildByName("NPC1");
}