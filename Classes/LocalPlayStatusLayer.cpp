#include "localPlayStatusLayer.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "ScoreScene.h"

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
	cBloodProgress->setCurrentProgress(20.0f);
	this->addChild(cBloodProgress, 101);

	auto pointTip = ui::ImageView::create("pointTip.png");
	pointTip->setPosition(Vec2(visibleSize.width - 120, visibleSize.height - 55));
	this->addChild(pointTip, 101);

	playerPoint = 0;
	pointLabel = Label::createWithTTF("0","fonts/Deng.ttf", 40.0f);
	pointLabel->setPosition(Vec2(pointTip->getPosition().x + 80, pointTip->getPosition().y));
	this->addChild(pointLabel, 101);

	return true;
}

bool localStatus::cutHeroBlood(float amount)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHurt.mp3");
	bool isDied = cBloodProgress->cutBlood(amount);
	if (isDied)
		changeToLoseScene();
	return isDied;
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

void localStatus::showPaojieDialog()
{
	auto image = ui::ImageView::create("NPC2.png");
	image->setPosition(Vec2(480, 320));
	image->setName("NPC2");
	this->addChild(image, 2);
}
void localStatus::removeOldNPCDialog()
{
	this->removeChildByName("NPC1");
}

void localStatus::removePaoNPCDialog()
{
	this->removeChildByName("NPC2");
}

void localStatus::addPoint(int add)
{
	playerPoint += add;
	pointLabel->setString(std::to_string(playerPoint));
}


void localStatus::changeToLoseScene()
{
	auto loseScene = ScoreScene::create();
	loseScene->putBackImage("loseBackground.png");
	loseScene->getScore(playerPoint);
	auto reScene = TransitionFade::create(1.0f, loseScene);
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(reScene);
}

void localStatus::changeToWinScene()
{
	auto winScene = ScoreScene::create();
	winScene->putBackImage("winBackground.png");
	winScene->getScore(playerPoint);
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(reScene);
}