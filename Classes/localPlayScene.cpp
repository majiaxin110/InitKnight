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
	//瓦片地图
	tileMap = TMXTiledMap::create("testMap/localMap.tmx");
	
	if (tileMap != nullptr)
	{
		this->addChild(tileMap, 0, 100);//Tag = 100

		TMXObjectGroup *group = tileMap->getObjectGroup("player");
		ValueMap spawnStartPoint = group->getObject("startPoint");
		float startX = spawnStartPoint["x"].asFloat();
		float startY = spawnStartPoint["y"].asFloat();

		player = Sprite::create("testMap/Player.png");
		player->setPosition(Vec2(startX, startY));
		this->addChild(player, 1, 201);//Tag = 201
	}
	else
	{
		log("map error!");
	}

	return true;
}

void localPlay::onEnter()
{
	Scene::onEnter();
	log("local play scene onEnter");
	
	auto keyboardListener = EventListenerKeyboard::create();
	Sprite* playerSprite = static_cast<Sprite*>(this->getChildByTag(201));
	
	//使用Lambda表达式处理键盘事件
	//捕获sprite
	keyboardListener->onKeyPressed = [playerSprite](EventKeyboard::KeyCode keyCode, Event *event) {
		Vec2 playerPos = playerSprite->getPosition();
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			playerPos.y += 3;
			log("Move up");
			break;
		case EventKeyboard::KeyCode::KEY_S:
			playerPos.y -= 3;
			log("Move down");
			break;
		case EventKeyboard::KeyCode::KEY_A:
			playerPos.x -= 4;
			log("Move left");
			break;
		case EventKeyboard::KeyCode::KEY_D:
			playerPos.x += 4;
			log("Move right");
			break;
		default:
			log("Key with keycode %d pressed", keyCode);
			break;
		}
		playerSprite->setPosition(playerPos);
	};

	//按键释放
	keyboardListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event) {
		log("Key with keycode %d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}