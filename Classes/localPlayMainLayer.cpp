#include "localPlayMainLayer.h"

USING_NS_CC;

/*Scene* localPlay::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = localPlay::create();

	layer->setTag(123);
	// add layer as a child to scene
	scene->addChild(layer,0);

	return scene;
}*/

// on "init" you need to initialize your instance
bool localPlay::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("testMap/bigLocalMap.tmx");
	addChild(_tileMap, 0, 100);

	TMXObjectGroup* group = _tileMap->getObjectGroup("player");
	ValueMap spawnPoint = group->getObject("startPoint");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	hero = Hero::create();
	hero->initHeroSprite();
	hero->setPosition(Vec2(x, y));
	addChild(hero, 2, 200);

	setViewpointCenter(hero->getPosition());

	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);

	_heart = _tileMap->getLayer("heart");
	_heart->setVisible(true);
	/*
	auto statusLayer = Layer::create();
	
	m_pProgressView = new ProgressView();
	m_pProgressView->setPosition(Vec2(origin.x + 120, origin.y + 600));
	m_pProgressView->setScale(2.2f);
	m_pProgressView->setBackgroundTexture("bloodProgress/bloodBack.png");
	m_pProgressView->setForegroundTexture("bloodProgress/bloodFore.png");
	m_pProgressView->setTotalProgress(100.0f);
	m_pProgressView->setCurrentProgress(50.0f);
	statusLayer->addChild(m_pProgressView, 5);
	statusLayer->setPosition(hero->getPosition());
	this->addChild(statusLayer,1);
	*/
	
	this->scheduleUpdate();

	return true;
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
		hero->setAttackAnimation();
		break;
	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

void localPlay::setPlayerPosition(Vec2 position)
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
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	tileGid = _heart->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collect = propValueMap["isCollectable"].asString();

		if (collect == "true") { //��ȡ���ɹ�
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			_heart->removeTileAt(tileCoord);
			hero->setUpAnimation();
			return;
		}
	}
	//�ƶ�����
	hero->setPosition(position);
	//������ͼ
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

void localPlay::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//ʹ��Lambda���ʽ��������¼�
	//����this��ʹ�ó�Ա����
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
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
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

}
