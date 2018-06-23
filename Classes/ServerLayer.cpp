#include "ServerLayer.h"
#include <cmath>
USING_NS_CC;
const int tileSize = 32;//瓦片大小
receiveTemp recTemp1;  

bool ServerLayer::init()   //初始化地图网络等
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
		return false;

	statusLayer = nullptr;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("testMap/fightMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("players");
	ValueMap spawnPoint = group->getObject("Apoint");

	auto x = spawnPoint["x"].asFloat();
	auto y = spawnPoint["y"].asFloat();

	hero = Hero::create();
	hero->initHeroSprite();
	hero->addHeadProgress("bloodBack.png", "bloodFore.png",80);
	hero->setPosition(Vec2(x, y));
	hero->setMoveSpeed(hero->getMoveSpeed()*1.2);
	this->addChild(hero, 2, 200);

	spawnPoint = group->getObject("Bpoint");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();

	hero2 = Hero::create();
	hero2->initHeroSprite();
	hero2->addHeadProgress("bloodBack.png", "bloodFore.png",100);
	hero2->setPosition(Vec2(x, y));
	hero2->changeAttackMode();
	this->addChild(hero2, 2, 201);
	recTemp1.receivePosition = hero2->getPosition();

	
	setViewpointCenter(hero->getPosition());
	//获取地图的不同层
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);

	_heart = _tileMap->getLayer("heart");

	this->initNetwork();
	this->scheduleUpdate();
	this->schedule(schedule_selector(ServerLayer::Place), 0.02f);   //网络部分

	return true;
}


void ServerLayer::Place(float dt)
{
	//log("!!!!%f", receivetemp.x);
	hero2->setPosition(recTemp1.receivePosition);
	hero2->setFlipp(recTemp1.heroface == 2 ? 0 : 1);
	hero2->heroface = recTemp1.heroface;
}

void ServerLayer::initNetwork()  
{

	_server = SocketServer::getInstance();
	_server->startServer(8000);
	_server->onRecv = CC_CALLBACK_3(ServerLayer::onRecv, this);
}

void ServerLayer::sendData(DataType type)
{
	GameData data;
	data.dataType = type;
	data.dataSize = sizeof(GameData);
	data.position = hero->getPosition();
	data.heroface = hero->heroface;
	data.hero2Blood = hero2->headProgress->getCurrentProgress();
	data.heroBlood = hero->headProgress->getCurrentProgress();
	_server->sendMessage((const char*)&data, sizeof(GameData));
}



void ServerLayer::onRecv(HSocket socket, const char* data, int count)
{
	GameData* gameData = (GameData*)data;
	if (gameData->dataSize == sizeof(GameData))
	{
		//Bullet* bulletTemp;
		switch (gameData->dataType)
		{
	
		case POSITION:
			/*//hero2->setPosition(gameData->position);
			this->hero2->setPosition(gameData->position);*/
			recTemp1.receivePosition = gameData->position;
			recTemp1.heroface = gameData->heroface;
			//log("????%f", receivetemp.x);
			break;
		case ATTACK:
			log("receive attack!");
			recTemp1.isNeedBullet = true;
			break;
		default:
			break;
		}
	}

}


void ServerLayer::getStatusLayer(localStatus* tLayer)
{
	if (tLayer == nullptr)
		cocos2d::log("fuck status layer!!");
	else
		cocos2d::log("status layer tag %d", tLayer->getTag());
	statusLayer = tLayer;

}
cocos2d::EventKeyboard::KeyCode ServerLayer::whichPressed()
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
	if (keyStatus[EventKeyboard::KeyCode::KEY_K])
		return EventKeyboard::KeyCode::KEY_K;//尝试用k攻击
	if (keyStatus[EventKeyboard::KeyCode::KEY_SPACE])
		return EventKeyboard::KeyCode::KEY_SPACE;
	return EventKeyboard::KeyCode::KEY_NONE;
}

void ServerLayer::update(float delta)
{
	static float curTime = 0;
	curTime += delta;
	if (curTime > delta * 2.f)
	{
		this->sendData(POSITION);
		curTime -= delta * 2.f;
	}

	Node::update(delta);
	EventKeyboard::KeyCode pressedKey = whichPressed();
	if (pressedKey != EventKeyboard::KeyCode::KEY_NONE)
	{
		onPress(pressedKey);
	}

	if (recTemp1.isNeedBullet)
	{
		log("!!add bullet");
		auto bulletTemp = Bullet::create();
		bulletTemp->initBulletSprite(hero2);
		bulletTemp->setTag(4088);
		this->addChild(bulletTemp);
		bulletVec.push_back(bulletTemp);
		bulletTemp->StartListen();
		recTemp1.isNeedBullet = false;
	}

	for (auto &j : bulletVec)
	{
		if (j->ifexist)
		{
			float x1 = hero->getPositionX() - j->bulletsprite->getPositionX();
			//得到两点y的距离 
			float y1 = hero->getPositionY() - j->bulletsprite->getPositionY();
			float distance = sqrt(pow(x1, 2) + pow(y1, 2));

			if (distance < 60)
			{
				if (hero->headProgress->cutBlood(8))
					changeToLose();
				j->removeBulletFromOutside();
			}
		}
	}

	Vec2 tileCoord = this->tileCoordFromPosition(recTemp1.receivePosition);
	//获得瓦片的GID
	int tileGid = _heart->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collected = propValueMap["isCollectable"].asString();

		if (collected == "true") { //检测成功
			_heart->removeTileAt(tileCoord);
			hero2->headProgress->addBlood(25);
		}
	}
}

void ServerLayer::onPress(EventKeyboard::KeyCode keyCode)
{
	Vec2 playerPos = hero->getPosition();
	const int movSpeed = hero->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setRunAnimation();
		hero->heroface = 4;  //设置英雄朝向
		playerPos.y += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero->setRunAnimation(1);
		hero->heroface = 1;
		playerPos.x -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero->setRunAnimation();
		hero->heroface = 3;
		playerPos.y -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero->setRunAnimation(0);
		hero->heroface = 2;
		playerPos.x += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (!hero->getAttackMode())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sword.wav");
			hero->setAttackAnimation();
			float dis = sqrt(pow(hero->getPosition().x - hero2->getPosition().x, 2) +
				pow(hero->getPosition().y - hero2->getPosition().y, 2));
			if (hero->isAttacking && dis < 64 &&
				((hero->heroface == 2 && hero->getPosition().x - hero2->getPosition().x <= 0)
					|| (hero->heroface == 1 && hero->getPosition().x - hero2->getPosition().x >= 0)))
				if (hero2->headProgress->cutBlood(1))
					changeToWin();
		}
		break;

	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

bool ServerLayer::detectPlayerPosition(Vec2 position)
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
			return false;
		}
	}

	tileGid = _heart->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collect = propValueMap["isCollectable"].asString();

		if (collect == "true") { //收集检测成功
			hero->headProgress->addBlood(25);
			_heart->removeTileAt(tileCoord);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.wav");
			return false;
		}
	}
	return true;
}

void ServerLayer::setPlayerPosition(Vec2 position)
{
	if (detectPlayerPosition(position))
	{
		//移动精灵
		hero->setPosition(position);
	}
}

Vec2 ServerLayer::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y)
		/ _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void ServerLayer::setViewpointCenter(Vec2 position)
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



/*std::vector<Monster*>& ServerLayer::getMonsterVec()
{
return monsterVec;
}*/

void ServerLayer::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//使用Lambda表达式处理键盘事件
	//捕获this以使用成员变量
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		//单次按下响应
		if (keyCode == EventKeyboard::KeyCode::KEY_J && hero->getAttackMode())
		{
			auto bulletTemp = Bullet::create();
			bulletTemp->initBulletSprite(hero);
			bulletTemp->setTag(4088);
			this->addChild(bulletTemp);
			bulletVec.push_back(bulletTemp);
			bulletTemp->StartListen();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
			this->hero->changeAttackMode();
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
	eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 2);

}

void ServerLayer::changeToWin()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto winScene = ScoreScene::create();
	winScene->putBackImage("fightScore/winBackground.png");
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->replaceScene(reScene);
}

void ServerLayer::changeToLose()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto winScene = ScoreScene::create();
	winScene->putBackImage("fightScore/loseBackground.png");
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->replaceScene(reScene);

}