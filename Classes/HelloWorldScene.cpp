#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "localPlayScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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

	//ѡ��ť
	auto singleModeButton = ui::Button::create("buttonSingle.png");
	singleModeButton->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	
	//����lambda���ʽ������
	singleModeButton->addTouchEventListener([](Ref *pSender, ui::Widget::TouchEventType type) {
		log("Single Local Play Mode");
		auto locScene = localScene::create();
		locScene->setTag(579);
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

	

	//�������ֿ���
	auto *chnStrings = Dictionary::createWithContentsOfFile("string.xml");
	const char *strMusic = ((__String*)chnStrings->objectForKey("music"))->getCString();
	auto musicLabel = Label::createWithTTF(strMusic, "fonts/Deng.ttf",20);
	musicLabel->setPosition(Vec2(origin.x + 60, origin.y + 120));
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

