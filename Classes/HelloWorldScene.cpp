#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "localPlayScene.h"
#include "ui/CocosGUI.h"
#include "OnlineServerScene.h"
#include "OnlineClientScene.h"
#include "ClientLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

string targetIP;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//����ͼƬ
	auto backGround = Sprite::create("helloBackgroud.png");
	backGround->setPosition(Vec2(origin.x + visibleSize.width / 2
		, origin.y + visibleSize.height / 2));
	this->addChild(backGround,0);

	//����ip�����
	auto editBox = EditBox::create(Size(300, 60), "whiteBox.png");
	editBox->setPosition(Vec2(origin.x + visibleSize.width / 3*2+10, origin.y + visibleSize.height / 3-115));
	editBox->setMaxLength(16);   //����������������ٸ��ַ�  
	editBox->setPlaceHolder("IP connecting here");
	editBox->setPlaceholderFontSize(20);
	editBox->setPlaceholderFontColor(Color3B::RED);
	//editBox->setText("127.0.0.1"); //��ʼ������  
	editBox->setFontColor(Color3B::RED);   //������ɫ  
	editBox->setFontSize(40);
	addChild(editBox);
	

	//ѡ��ť
	auto singleModeButton = ui::Button::create("buttonSingle.png");
	singleModeButton->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	
	//����lambda���ʽ������
	singleModeButton->addTouchEventListener([](Ref *pSender, ui::Widget::TouchEventType type) {
		log("Single Local Play Mode");
		auto locScene = localScene::create();
		locScene->setTag(579);
		//locScene->transPlayerName(nameEdit->getText());
		auto reScene = TransitionFade::create(1.0f, locScene);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("switch scene");
			Director::getInstance()->replaceScene(reScene);
			break;
		default:
			break;
		}
	});
	singleModeButton->setPressedActionEnabled(true);
	this->addChild(singleModeButton, 1);

	auto doubleModeButtonServer = ui::Button::create("doubleButtonCreate.png");
	doubleModeButtonServer->setPosition(Vec2(origin.x + visibleSize.width / 3*2, origin.y + visibleSize.height / 3+35));
	//����lambda���ʽ������
	doubleModeButtonServer->addTouchEventListener([](Ref *pSender, ui::Widget::TouchEventType type) {
		log("Double Local Play Mode");

		auto serverScene = ServerScene::create();
		serverScene->setTag(580);
		auto reScene = TransitionFade::create(1.0f, serverScene);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("switch scene");
			Director::getInstance()->replaceScene(reScene);
			break;
		default:
			break;
		}
	});
	doubleModeButtonServer->setPressedActionEnabled(true);
	this->addChild(doubleModeButtonServer, 1);

	auto doubleModeButtonClient = ui::Button::create("doubleButtonJoin.png");
	doubleModeButtonClient->setPosition(Vec2(origin.x + visibleSize.width / 3 * 2, origin.y + visibleSize.height / 3-45));
	//����lambda���ʽ������
	doubleModeButtonClient->addTouchEventListener([editBox](Ref *pSender, ui::Widget::TouchEventType type) {
		log("Double Local Play Mode");
		targetIP = editBox->getText();
		auto clientScene = ClientScene::create();
		clientScene->setTag(581);
		auto reScene = TransitionFade::create(1.0f, clientScene);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("switch scene");
			Director::getInstance()->replaceScene(reScene);
			break;
		default:
			break;
		}
	});
	doubleModeButtonClient->setPressedActionEnabled(true);
	this->addChild(doubleModeButtonClient, 1);

	//�������ֿ���
	auto *chnStrings = Dictionary::createWithContentsOfFile("string.xml");
	const char *strMusic = ((__String*)chnStrings->objectForKey("music"))->getCString();
	auto musicLabel = Label::createWithTTF(strMusic, "fonts/Deng.ttf",20);
	musicLabel->setPosition(Vec2(origin.x + visibleSize.width/4*3+40, origin.y + 50));
	this->addChild(musicLabel, 1);

	auto musicCheck = ui::CheckBox::create("unCheckBox.png","CheckBox.png");
	musicCheck->setPosition(Vec2(musicLabel->getPosition().x + 60, musicLabel->getPosition().y));
	musicCheck->addEventListener([](Ref* pSender, ui::CheckBox::EventType type) {
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3", true);
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);//��������
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			break;
		default:
			break;
		}
	});
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);//��������
	musicCheck->setSelected(true);
	this->addChild(musicCheck, 1);

    return true;
}

