#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "localPlayScene.h"

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

	//±³¾°Í¼Æ¬
	auto backGround = Sprite::create("helloBackgroud.png");
	backGround->setPosition(Vec2(origin.x + visibleSize.width / 2
		, origin.y + visibleSize.height / 2));
	this->addChild(backGround,0);

	//Ñ¡Ôñ°´Å¥
	auto singleModeButton = ui::Button::create("buttonSingle.png");
	singleModeButton->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	singleModeButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::localButtonCallBack, this));
	singleModeButton->setPressedActionEnabled(true);
	this->addChild(singleModeButton, 1);
    return true;
}

void HelloWorld::localButtonCallBack(Ref *pSender, ui::Widget::TouchEventType type)
{
	log("Single Local Play Mode");
	auto localScene = localPlay::createScene();
	auto reScene = TransitionFade::create(1.0f, localScene);
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:		
		log("switch scene");
		Director::getInstance()->replaceScene(reScene);
		break;
	default:
		break;
	}
}

