#include "localPlayScene.h"

USING_NS_CC;

Scene* localPlay::createScene()
{
	return localPlay::create();
}

bool localPlay::init()
{
	if (!Scene::init())
		return false;

	//尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//键盘状态记录初始化
	keyStatus[EventKeyboard::KeyCode::KEY_W] = false;
	keyStatus[EventKeyboard::KeyCode::KEY_S] = false;
	keyStatus[EventKeyboard::KeyCode::KEY_A] = false;
	keyStatus[EventKeyboard::KeyCode::KEY_D] = false;
	keyStatus[EventKeyboard::KeyCode::KEY_Q] = false;
	keyStatus[EventKeyboard::KeyCode::KEY_SPACE] = false;

	//瓦片地图
	tileMap = TMXTiledMap::create("testMap/localMap.tmx");
	
	if (tileMap != nullptr)
	{
		this->addChild(tileMap, 0, 100);//Tag = 100

		TMXObjectGroup *group = tileMap->getObjectGroup("player");
		ValueMap spawnStartPoint = group->getObject("startPoint");
		float startX = spawnStartPoint["x"].asFloat();
		float startY = spawnStartPoint["y"].asFloat();

		hero = Hero::create();
		hero->initHeroSprite();
		hero->setPosition(Vec2(startX, startY));
		this->addChild(hero, 1, 201);//Tag = 201
	}
	else
	{
		log("map error!");
	}
	
	this->scheduleUpdate();

	return true;
}

void localPlay::onEnter()
{
	Scene::onEnter();
	log("local play scene onEnter");
	
	auto keyboardListener = EventListenerKeyboard::create();
	
	//使用Lambda表达式处理键盘事件
	//捕获this以使用成员变量
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) 
	{
		keyStatus[keyCode] = true;
		log("%d pressed", keyCode);
	};
	

	//按键释放
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event) 
	{
		keyStatus[keyCode] = false;
		log("%d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

cocos2d::EventKeyboard::KeyCode localPlay::whichPressed()
{
	if (keyStatus[EventKeyboard::KeyCode::KEY_W])
		return EventKeyboard::KeyCode::KEY_W;
	if (keyStatus[EventKeyboard::KeyCode::KEY_A])
		return EventKeyboard::KeyCode::KEY_A;
	if (keyStatus[EventKeyboard::KeyCode::KEY_S])
		return EventKeyboard::KeyCode::KEY_S;
	if (keyStatus[EventKeyboard::KeyCode::KEY_D])
		return EventKeyboard::KeyCode::KEY_D;
	if (keyStatus[EventKeyboard::KeyCode::KEY_Q])
		return EventKeyboard::KeyCode::KEY_Q;
	if (keyStatus[EventKeyboard::KeyCode::KEY_SPACE])
		return EventKeyboard::KeyCode::KEY_SPACE;
	return EventKeyboard::KeyCode::KEY_NONE;
}

void localPlay::update(float delta)
{
	Node::update(delta);
	EventKeyboard::KeyCode pressedKey = whichPressed();
	if (pressedKey != EventKeyboard::KeyCode::KEY_NONE)
	{
		hero->keyPressedDo(pressedKey);
	}
}

/*keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event *event) {
		Vec2 playerPos = hero->getPosition();
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			playerPos.y += 30;
			log("Move up");
			break;
		case EventKeyboard::KeyCode::KEY_S:
			playerPos.y -= 30;
			log("Move down");
			break;
		case EventKeyboard::KeyCode::KEY_A:
			playerPos.x -= 40;
			log("Move left");
			break;
		case EventKeyboard::KeyCode::KEY_D:
			playerPos.x += 40;
			log("Move right");
			break;
		default:
			log("Key with keycode %d pressed", keyCode);
			break;
		}
		hero->setPosition(playerPos);
		};*/