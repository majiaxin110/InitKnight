#include "ClientLayer.h"


USING_NS_CC;
const int tileSize = 32;//瓦片大小

receiveTemp recTemp2;

// on "init" you need to initialize your instance
bool ClientLayer::init()
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
	hero->addHeadProgress("bloodBack.png", "bloodFore.png", 80);
	hero->setPosition(Vec2(x, y));
	addChild(hero, 2, 200);

	spawnPoint = group->getObject("Bpoint");
	x = spawnPoint["x"].asFloat();
	y = spawnPoint["y"].asFloat();

	hero2 = Hero::create();
	hero2->initHeroSprite();
	hero2->addHeadProgress("bloodBack.png", "bloodFore.png", 80);
	hero2->setPosition(Vec2(x, y));
	hero2->changeAttackMode();
	addChild(hero2, 2, 201);


	setViewpointCenter(hero->getPosition());
	//获取地图的不同层
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);
	recTemp2.receivePosition = Vec2(x - 100, y);

	_heart = _tileMap->getLayer("heart");

	recTemp2.receivePosition = Vec2(x - 100, y);
	//网络初始化
	this->initNetwork();
	this->scheduleUpdate();
	this->schedule(schedule_selector(ClientLayer::PlaceAndBlood), 0.02f);

	return true;
}


void ClientLayer::PlaceAndBlood(float dt)
{
	hero->setPosition(recTemp2.receivePosition);
	hero->setFlipp(recTemp2.heroface == 2 ? 0 : 1);
	hero->headProgress->setCurrentProgress(recTemp2.heroProgress);
	hero2->headProgress->setCurrentProgress(recTemp2.hero2Progress);
	if (hero->headProgress->getCurrentProgress() <= 0)
		changeToWin();
	else if (hero2->headProgress->getCurrentProgress() <= 0)
		changeToLose();
}

void ClientLayer::initNetwork()
{
	
	_client = SocketClient::construct();
	_client->onRecv = CC_CALLBACK_2(ClientLayer::onRecv, this);
	//_client->onDisconnect = CC_CALLBACK_0(ClientLayer::onDisconnect, this);
	char *ip;
	int len = targetIP.length();
	ip = (char *)malloc((len + 1) * sizeof(char));
	targetIP.copy(ip, len, 0);
	*(ip + len) = '\0';
	log("len: %d", len);
	log("liuliuliu %s", ip);
	if (!_client->connectServer(ip, 8000))
	{
		//_lblInfo->setString("Client connect error");
	}
}

void ClientLayer::sendData(DataType type)
{
	GameData data;
	data.dataType = type;
	data.heroface = hero2->heroface;
	data.position = hero2->getPosition();
	if (type == ATTACK)
	{
		data.bulAttack = true;
	}
	data.dataSize = sizeof(GameData);
	_client->sendMessage((const char*)&data, sizeof(GameData));
}



void ClientLayer::onRecv( const char* data, int count)
{
	GameData* gameData = (GameData*)data;
	if (gameData->dataSize == sizeof(GameData))
	{
		switch (gameData->dataType)
		{
		case POSITION:
			recTemp2.receivePosition = gameData->position;
			recTemp2.hero2Progress = gameData->hero2Blood;
			recTemp2.heroProgress = gameData->heroBlood;
			recTemp2.heroface = gameData->heroface;
			break;
		default:
			break;
		}
	}

}

void ClientLayer::getStatusLayer(localStatus* tLayer)
{
	if (tLayer == nullptr)
		cocos2d::log("fuck status layer!!");
	else
		cocos2d::log("status layer tag %d", tLayer->getTag());
	statusLayer = tLayer;

	//bullettemp->getBloodStatus(statusLayer);//让子弹接受
}
cocos2d::EventKeyboard::KeyCode ClientLayer::whichPressed()
{
	if (keyStatus[EventKeyboard::KeyCode::KEY_W])
		return EventKeyboard::KeyCode::KEY_W;
	if (keyStatus[EventKeyboard::KeyCode::KEY_A])
		return EventKeyboard::KeyCode::KEY_A;
	if (keyStatus[EventKeyboard::KeyCode::KEY_S])
		return EventKeyboard::KeyCode::KEY_S;
	if (keyStatus[EventKeyboard::KeyCode::KEY_D])
		return EventKeyboard::KeyCode::KEY_D;
	if (keyStatus[EventKeyboard::KeyCode::KEY_J])
		return EventKeyboard::KeyCode::KEY_J;
	if (keyStatus[EventKeyboard::KeyCode::KEY_SPACE])
		return EventKeyboard::KeyCode::KEY_SPACE;
	return EventKeyboard::KeyCode::KEY_NONE;
}

void ClientLayer::update(float delta)
{
	static float curTime = 0;
	curTime += delta;
	if (curTime > delta * 2.f)
	{

		this->sendData(POSITION);
		curTime -= delta * 2.f;
	}

	//Node::update(delta);
	EventKeyboard::KeyCode pressedKey = whichPressed();
	if (pressedKey != EventKeyboard::KeyCode::KEY_NONE)
	{
		onPress(pressedKey);
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
				//hero->headProgress->cutBlood(20);
				j->removeBulletFromOutside();
			}
		}
	}

	Vec2 tileCoord = this->tileCoordFromPosition(recTemp2.receivePosition);
	//获得瓦片的GID
	int tileGid = _heart->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collected = propValueMap["isCollectable"].asString();

		if (collected == "true") { //检测成功
			_heart->removeTileAt(tileCoord);
			//hero->headProgress->addBlood(25);
		}
	}
}

void ClientLayer::onPress(EventKeyboard::KeyCode keyCode)
{
	Vec2 playerPos = hero2->getPosition();
	const int movSpeed = hero2->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero2->setRunAnimation();
		hero2->heroface = 4;  //设置英雄朝向
		playerPos.y += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero2->setRunAnimation(1);
		hero2->heroface = 1;
		playerPos.x -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero2->setRunAnimation();
		hero2->heroface = 3;
		playerPos.y -= movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero2->setRunAnimation(0);
		hero2->heroface = 2;
		playerPos.x += movSpeed;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		if (!hero2->getAttackMode())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/sword.wav");
			hero2->setAttackAnimation();
		}
		break;

	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

bool ClientLayer::detectPlayerPosition(Vec2 position)
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
			//hero2->headProgress->addBlood(25);
			_heart->removeTileAt(tileCoord);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.wav");
			return false;
		}
	}
	return true;
}

void ClientLayer::setPlayerPosition(Vec2 position)
{
	if (detectPlayerPosition(position))
	{
		//移动精灵
		hero2->setPosition(position);

	}
}


Vec2 ClientLayer::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y)
		/ _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void ClientLayer::setViewpointCenter(Vec2 position)
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

void ClientLayer::changeToWin()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto winScene = ScoreScene::create();
	winScene->putBackImage("fightScore/winBackground.png");
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->replaceScene(reScene);
}

void ClientLayer::changeToLose()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto winScene = ScoreScene::create();
	winScene->putBackImage("fightScore/loseBackground.png");
	auto reScene = TransitionFade::create(1.0f, winScene);
	Director::getInstance()->replaceScene(reScene);

}



/*std::vector<Monster*>& ClientLayer::getMonsterVec()
{
return monsterVec;
}*/

void ClientLayer::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//使用Lambda表达式处理键盘事件
	//捕获this以使用成员变量
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		//单次按下响应
		if (keyCode == EventKeyboard::KeyCode::KEY_J && hero2->getAttackMode())
		{
			auto bulletTemp = Bullet::create();
			bulletTemp->initBulletSprite(hero2);
			bulletTemp->setTag(4088);
			this->addChild(bulletTemp);
			bulletVec.push_back(bulletTemp);
			bulletTemp->StartListen();
			this->sendData(ATTACK);
		}
		/*if (keyCode == EventKeyboard::KeyCode::KEY_Q)
			this->hero2->changeAttackMode();*/
		log("%d pressed", keyCode);
	};

	//按键释放
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event)
	{
		this->keyStatus[keyCode] = false;
		hero2->stopAllAnimation();
		log("%d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 2);

}
