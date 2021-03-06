//��������״̬��
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
	
	auto progressVie = new ProgressView;
	cBloodProgress.push_back(progressVie);
	cBloodProgress[0]->setPosition(Vec2(214, visibleSize.height - 50));
	cBloodProgress[0]->initProgressView("bloodProgress/KnightBack.png","bloodProgress/KnightFore.png");

	cBloodProgress[0]->setScale(1.0f);
	cBloodProgress[0]->setTotalProgress(100.0f);
	cBloodProgress[0]->setCurrentProgress(60.0f);
	this->addChild(cBloodProgress[0], 101);

	auto pointTip = ui::ImageView::create("pointTip.png");
	pointTip->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 55));
	this->addChild(pointTip, 101);

	playerPoint = 0;
	pointLabel = Label::createWithTTF("0","fonts/Deng.ttf", 40.0f);
	pointLabel->setPosition(Vec2(pointTip->getPosition().x + 80, pointTip->getPosition().y));
	this->addChild(pointLabel, 101);

	return true;
}

bool localStatus::cutHeroBlood(float amount)
{
	bool isDied = cBloodProgress[0]->cutBlood(amount);
	if (isDied)
		changeToLoseScene();
	return isDied;
}

void localStatus::addHeroBlood(float amount)
{
	return cBloodProgress[0]->addBlood(amount);
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

void localStatus::setPlayerName(const char * str)
{
	playerName.assign(str);
}


void localStatus::changeToLoseScene()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto loseScene = ScoreScene::create();
	loseScene->putBackImage("loseBackground.png");
	log("!!set %s", playerName.c_str());
	loseScene->setScore(playerPoint);
	auto reScene = TransitionFade::create(1.0f, loseScene);
	Director::getInstance()->replaceScene(reScene);
}

void localStatus::changeToWinScene()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto winScene = ScoreScene::create();
	winScene->putBackImage("winBackground.png");
	winScene->setScore(playerPoint);
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->replaceScene(reScene);
}