#include "localPlayMainLayer.h"


USING_NS_CC;

const int tileSize = 32;//瓦片大小

// on "init" you need to initialize your instance
bool localPlay::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
		return false;

	statusLayer = nullptr;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("testMap/bigLocalMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("player");
	ValueMap spawnPoint = group->getObject("startPoint");

	auto x = spawnPoint["x"].asFloat();
	auto y = spawnPoint["y"].asFloat();


	hero = Hero::create();
	hero->initHeroSprite();
	hero->setPosition(Vec2(x, y));
	addChild(hero, 2, 200);

	monster1 = Monster1::create();
	monster1->initMonster1Sprite();
	monster1->setPosition(Vec2((26+2)*tileSize, (45+2)*tileSize));
	monster1->startAnimation();
	this->addChild(monster1,2);
	monster1->patrol();

	monster2 = Monster::create();
	//monster2->InitMonsterSprite("monster2walk1.png");
	monster2->InitMonsterSprite("monster2walk1.png","bloodBack.png","bloodFore.png");  
	monster2->setPosition(Vec2((18 + 2)*tileSize, (38 + 2)*tileSize));
	this->addChild(monster2, 1);
	monster2->StartListen(hero, _tileMap);

	//mymap->addChild(monster1);//将怪物添加到地图中，这样怪物才能随地图移动  
	//monster2->StartListen(hero, mymap);//非常重要，这是这一讲用到的  
	

	setViewpointCenter(hero->getPosition());
	//获取地图的不同层
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);

	_heart = _tileMap->getLayer("heart");
	_heart->setVisible(true);
	
	this->scheduleUpdate();

	return true;
}

void localPlay::getStatusLayer(localStatus* tLayer)
{
	if (tLayer == nullptr)
		cocos2d::log("fuck status layer!!");
	else
		cocos2d::log("status layer tag %d", tLayer->getTag());
	statusLayer = tLayer;
	monster2->getBloodStatus(statusLayer);//让怪物接受statuslayer
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
	if (keyStatus[EventKeyboard::KeyCode::KEY_J])
		return EventKeyboard::KeyCode::KEY_J;
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
		onPress(pressedKey);
	}

}

void localPlay::onPress(EventKeyboard::KeyCode keyCode)
{
	Vec2 playerPos = hero->getPosition();
	const int movSpeed = hero->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setRunAnimation();
		playerPos.y += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero->setRunAnimation(1);
		playerPos.x -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero->setRunAnimation();
		playerPos.y -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero->setRunAnimation(0);
		playerPos.x += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sword.wav");
		hero->setAttackAnimation();

		break;
	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

void localPlay::setPlayerPosition(Vec2 position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["isCollidable"].asString();

		if (collision == "true") { //碰撞检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
			return;
		}
	}
	tileGid = _heart->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collect = propValueMap["isCollectable"].asString();

		if (collect == "true") { //摄取检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.mp3");
			_heart->removeTileAt(tileCoord);
			hero->setUpAnimation();
			statusLayer->addHeroBlood(15.0f);
			return;
		}
	}
	//移动精灵
	hero->setPosition(position);
	//滚动地图
	this->setViewpointCenter(hero->getPosition());
}

Vec2 localPlay::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) 
		/ _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void localPlay::setViewpointCenter(Vec2 position)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	this->setPosition(offset);
}

void localPlay::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//使用Lambda表达式处理键盘事件
	//捕获this以使用成员变量
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		log("%d pressed", keyCode);
	};

	//按键释放
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event)
	{
		this->keyStatus[keyCode] = false;
		hero->stopAllAnimation();
		log("%d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}
