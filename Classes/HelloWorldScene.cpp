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

// on "init" you need to initialize your instance
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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "InitKnight"
    // create and initialize a label
	auto *chnStrings = Dictionary::createWithContentsOfFile("string.xml");
	const char *strFromFile = ((__String*)chnStrings->objectForKey("mainTitle"))->getCString();
	auto myLabel = Label::createWithTTF(strFromFile,"fonts/Deng.ttf", 24);
	myLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 30));
	

    if (myLabel == nullptr)
    {
        problemLoading("'fonts/Deng.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        myLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - myLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(myLabel, 1);
    }    
    return true;
}


