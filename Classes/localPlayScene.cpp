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
	barriers = tileMap->getLayer("barriers");
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
		setHero(pressedKey);
	}
}

Vec2 localPlay::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height)
		- pos.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}
bool localPlay::isCollid(Vec2 pos)
{
	Vec2 tileCoord = this->tileCoordFromPosition(pos);
	int tileGid = this->barriers->getTileGIDAt(tileCoord);
		//获取属性
	if (tileGid > 0)
	{
		Value prop = tileMap->getPropertiesForGID(tileGid);

		ValueMap propValueM = prop.asValueMap();
		std::string isPropCrash = propValueM["isCollidable"].asString();
		if (isPropCrash == "true")//真实碰撞
			return true;
	}
	
	return false;
}

void localPlay::setHero(cocos2d::EventKeyboard::KeyCode keyCode)
{
	int deltaX = 0, deltaY = 0;
	const float mSpeed = hero->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		deltaY = mSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		deltaX = -mSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		deltaY = -mSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		deltaX = mSpeed;
		break;
	default:
		deltaY = deltaX = 0;
		break;
	}
	Vec2 previousLoc = localPlay::hero->getPosition();
	Vec2 currentLoc;
	currentLoc.x = previousLoc.x + deltaX;	currentLoc.y = previousLoc.y + deltaY;
	if (!(currentLoc.x<0 || currentLoc.y<0
		|| currentLoc.x > Director::getInstance()->getVisibleSize().width
		|| currentLoc.y > Director::getInstance()->getVisibleSize().height)
		&& !isCollid(currentLoc))//既没有越界又没碰撞
		hero->runAction(MoveBy::create(0.01f, Vec2(deltaX, deltaY)));
	else
		log("beyond");	//给我动起来
}