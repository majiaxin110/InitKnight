#include "ServerLayer.h"

USING_NS_CC;
const int tileSize = 32;//��Ƭ��С
receiveTemp recTemp1;  
						// on "init" you need to initialize your instance
bool ServerLayer::init()   //��ʼ����ͼ�����
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
	hero->setPosition(Vec2(x-100, y));
	this->addChild(hero, 2, 200);

	hero2 = Hero::create();
	hero2->initHeroSprite();
	hero2->setPosition(Vec2(x+100, y));
	this->addChild(hero2, 2, 201);
	recTemp1.receivePosition = hero2->getPosition();

	
	setViewpointCenter(hero->getPosition());
	//��ȡ��ͼ�Ĳ�ͬ��
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);


	this->initNetwork();
	this->scheduleUpdate();
	this->schedule(schedule_selector(ServerLayer::Place), 0.02f);   //���粿��

	return true;
}


void ServerLayer::Place(float dt)
{
	//log("!!!!%f", receivetemp.x);
	hero2->setPosition(recTemp1.receivePosition);
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
	_server->sendMessage((const char*)&data, sizeof(GameData));
}



void ServerLayer::onRecv(HSocket socket, const char* data, int count)
{
	GameData* gameData = (GameData*)data;
	if (gameData->dataSize == sizeof(GameData))
	{
		switch (gameData->dataType)
		{
	
		case POSITION:
			/*//hero2->setPosition(gameData->position);
			this->hero2->setPosition(gameData->position);*/
			recTemp1.receivePosition = gameData->position;
			//log("????%f", receivetemp.x);
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
		return EventKeyboard::KeyCode::KEY_K;//������k����
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

	

}

void ServerLayer::onPress(EventKeyboard::KeyCode keyCode)
{
	Vec2 playerPos = hero->getPosition();
	const int movSpeed = hero->getMoveSpeed();
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setRunAnimation();
		hero->heroface = 4;  //����Ӣ�۳���
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
		}
		break;

	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

bool ServerLayer::detectPlayerPosition(Vec2 position)
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

void ServerLayer::setPlayerPosition(Vec2 position)
{
	/*if (detectPlayerPosition(position))
	{
		//�ƶ�����
		hero->setPosition(position);

	}*/
	hero->setPosition(position);
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



/*std::vector<Monster*>& ServerLayer::getMonsterVec()
{
return monsterVec;
}*/

void ServerLayer::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//ʹ��Lambda���ʽ��������¼�
	//����this��ʹ�ó�Ա����
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		//���ΰ�����Ӧ
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

	//�����ͷ�
	keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event *event)
	{
		this->keyStatus[keyCode] = false;
		hero->stopAllAnimation();
		log("%d released", keyCode);
	};

	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 2);

}
