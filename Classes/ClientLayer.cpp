#include "ClientLayer.h"

USING_NS_CC;
const int tileSize = 32;//��Ƭ��С

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

	_tileMap = TMXTiledMap::create("testMap/bigLocalMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("player");
	ValueMap spawnPoint = group->getObject("startPoint");

	auto x = spawnPoint["x"].asFloat();
	auto y = spawnPoint["y"].asFloat();

	hero = Hero::create();
	hero->initHeroSprite();
	hero->setPosition(Vec2(x - 100, y));
	addChild(hero, 2, 200);

	hero2 = Hero::create();
	hero2->initHeroSprite();
	hero2->setPosition(Vec2(x + 100, y));
	
	addChild(hero2, 2, 201);


	setViewpointCenter(hero->getPosition());
	//��ȡ��ͼ�Ĳ�ͬ��
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);
	recTemp2.receivePosition = Vec2(x - 100, y);
	//�����ʼ��
	this->initNetwork();
	this->scheduleUpdate();
	this->schedule(schedule_selector(ClientLayer::Place), 0.02f);

	return true;
}

void ClientLayer::Place(float dt)
{
	hero->setPosition(recTemp2.receivePosition);
}

void ClientLayer::initNetwork()
{
	
	_client = SocketClient::construct();
	_client->onRecv = CC_CALLBACK_2(ClientLayer::onRecv, this);
	//_client->onDisconnect = CC_CALLBACK_0(ClientLayer::onDisconnect, this);
	if (!_client->connectServer("127.0.0.1", 8000))
	{
		//_lblInfo->setString("Client connect error");
	}
}

void ClientLayer::sendData(DataType type)
{
	GameData data;
	data.dataType = type;
	data.dataSize = sizeof(GameData);
	data.position = hero2->getPosition();
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

	//bullettemp->getBloodStatus(statusLayer);//���ӵ�����
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
	if (keyStatus[EventKeyboard::KeyCode::KEY_Q])
		return EventKeyboard::KeyCode::KEY_Q;
	if (keyStatus[EventKeyboard::KeyCode::KEY_J])
		return EventKeyboard::KeyCode::KEY_J;
	if (keyStatus[EventKeyboard::KeyCode::KEY_K])
		return EventKeyboard::KeyCode::KEY_K;//������k����
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

	

}

void ClientLayer::onPress(EventKeyboard::KeyCode keyCode)
{
	Vec2 playerPos = hero2->getPosition();
	const int movSpeed = hero2->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero2->setRunAnimation();
		hero2->heroface = 4;  //����Ӣ�۳���
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
	//�����ص�����ת��Ϊ��Ƭ����
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//�����Ƭ��GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["isCollidable"].asString();

		if (collision == "true") { //��ײ���ɹ�
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
			return false;
		}
	}
	return true;
}

void ClientLayer::setPlayerPosition(Vec2 position)
{
	/*if (detectPlayerPosition(position))
	{
		//�ƶ�����
		hero2->setPosition(position);

	}*/
	hero2->setPosition(position);
}

void ClientLayer::setEnemyPosition(Vec2 position)
{
	hero->setPosition(position);
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
	//���Է�ֹ����ͼ��߳�����Ļ֮�⡣
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);
	//���Է�ֹ����ͼ�ұ߳�����Ļ֮�⡣
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//��Ļ���ĵ�
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	//ʹ���鴦����Ļ���ģ��ƶ���ͼĿ��λ��
	Vec2 pointB = Vec2(x, y);

	//��ͼ�ƶ�ƫ����
	Vec2 offset = pointA - pointB;
	this->setPosition(offset);
}



/*std::vector<Monster*>& ClientLayer::getMonsterVec()
{
return monsterVec;
}*/

void ClientLayer::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//ʹ��Lambda���ʽ��������¼�
	//����this��ʹ�ó�Ա����
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		//���ΰ�����Ӧ
		if (keyCode == EventKeyboard::KeyCode::KEY_J && hero2->getAttackMode())
		{
			auto bulletTemp = Bullet::create();
			bulletTemp->initBulletSprite(hero2);
			bulletTemp->setTag(4088);
			this->addChild(bulletTemp);
			bulletVec.push_back(bulletTemp);
			bulletTemp->StartListen();
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
			this->hero2->changeAttackMode();
		log("%d pressed", keyCode);
	};

	//�����ͷ�
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event)
	{
		this->keyStatus[keyCode] = false;
		hero2->stopAllAnimation();
		log("%d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 2);

}
