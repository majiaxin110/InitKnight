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

	auto monster1 = Monster::create();
	//monster2->InitMonsterSprite("monster2walk1.png");
	monster1->InitMonsterSprite("monster1/monsterwalk1.png", "bloodBack.png", "bloodFore.png");
	monster1->setPosition(Vec2((18 + 2)*tileSize, (38 + 2)*tileSize));
	monster1->setTag(4088);
	this->addChild(monster1, 2);
	monsterVec.push_back(monster1);
	monster1->StartListen(hero, _tileMap);

	setViewpointCenter(hero->getPosition());
	//获取地图的不同层
	_collidable = _tileMap->getLayer("barriers");
	_collidable->setVisible(false);

	_heart = _tileMap->getLayer("heart");
	_heart->setVisible(true);
	
	_npc = _tileMap->getLayer("npc");
	_npc->setVisible(true);
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
	monsterVec.at(0)->getBloodStatus(statusLayer);//让怪物接受statuslayer
	//bullettemp->getBloodStatus(statusLayer);//让子弹接受
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
	if (keyStatus[EventKeyboard::KeyCode::KEY_K])
		return EventKeyboard::KeyCode::KEY_K;//尝试用k攻击
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

	for (unsigned i = 0; i < monsterVec.size(); i++)
	{
		bool flag = false;
		for (auto &j : bulletVec)
		{
			if (j->ifexist)
			{
				float x1 = monsterVec[i]->getPositionX() - j->bulletsprite->getPositionX();
				//得到两点y的距离 
				float y1 = monsterVec[i]->getPositionY() - j->bulletsprite->getPositionY();
				//先计算怪物和子弹的距离  
				float distance = sqrt(pow(x1, 2) + pow(y1, 2));
				if (distance < 60 && monsterVec[i]->isDied == false)
				{
					if ((monsterVec[i])->getHurt(10.0f))//怪兽被消灭
					{
						this->removeChild(monsterVec[i]);
						monsterVec.erase(monsterVec.begin()+i);
						statusLayer->addPoint(100);
						flag = true;
						break;
					}
					j->removeBulletFromOutside();
				}
			}
		}
		if (flag)
			break;
		log("Monster Vector size:%d", monsterVec.size());
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
		}
		break;
	
	default:
		break;
	}
	this->setPlayerPosition(playerPos);
}

bool localPlay::detectPlayerPosition(Vec2 position)
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

		if (collect == "true") { //摄取检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.mp3");
			_heart->removeTileAt(tileCoord);
			hero->setUpAnimation();
			statusLayer->addHeroBlood(15.0f);
			statusLayer->addPoint(30);
			return false;
		}
	}

	tileGid = _npc->getTileGIDAt(tileCoord);
	if (tileGid > 0)
	{
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string talk = propValueMap["isTalktoOld"].asString();

		if (talk == "true") { //老者npc对话检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.mp3");
			_npc->removeTileAt(tileCoord);
			statusLayer->showOldNPCDialog();
			auto keyboardListenerTalkOld = EventListenerKeyboard::create();
			//使用Lambda表达式处理npc对话键盘事件
			keyboardListenerTalkOld->onKeyPressed = [this, keyboardListenerTalkOld](EventKeyboard::KeyCode keyCode, Event* event)
			{
				switch (keyCode)
				{
				case EventKeyboard::KeyCode::KEY_Y:
					this->statusLayer->addHeroBlood(30);
					//键盘监听
					Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListenerTalkOld);
					this->statusLayer->removeOldNPCDialog();
					break;
				case EventKeyboard::KeyCode::KEY_X:
					hero->setMoveSpeed(hero->getMoveSpeed() * 1.5);
					Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListenerTalkOld);
					this->statusLayer->removeOldNPCDialog();
					break;
				default:
					break;
				}
			};
			EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
			eventDispatcher->addEventListenerWithFixedPriority(keyboardListenerTalkOld, 1);
			return false;
		}

		talk = propValueMap["isTalktoPao"].asString();

		if (talk == "true") { //御坂美琴npc对话检测成功
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/getHeart.mp3");
			_npc->removeTileAt(tileCoord);
			statusLayer->showPaojieDialog();
			auto keyboardListenerTalkOld = EventListenerKeyboard::create();
			//使用Lambda表达式处理npc对话键盘事件
			keyboardListenerTalkOld->onKeyPressed = [this, keyboardListenerTalkOld](EventKeyboard::KeyCode keyCode, Event* event)
			{
				switch (keyCode)
				{
				case EventKeyboard::KeyCode::KEY_Y:
					//获取道具
					//键盘监听
					statusLayer->addPoint(1000);
					Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListenerTalkOld);
					this->statusLayer->removePaoNPCDialog();
					break;
				case EventKeyboard::KeyCode::KEY_X:
					this->statusLayer->cutHeroBlood(40);
					Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListenerTalkOld);
					this->statusLayer->removePaoNPCDialog();
					break;
				default:
					break;
				}
			};
			EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
			eventDispatcher->addEventListenerWithFixedPriority(keyboardListenerTalkOld, 1);
			return false;
		}
	}
	return true;
}
void localPlay::setPlayerPosition(Vec2 position)
{
	if (detectPlayerPosition(position))
	{
		//移动精灵
		hero->setPosition(position);
		//滚动地图
		this->setViewpointCenter(hero->getPosition());
	}
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



/*std::vector<Monster*>& localPlay::getMonsterVec()
{
	return monsterVec;
}*/

void localPlay::onEnter()
{
	Layer::onEnter();
	auto keyboardListener = EventListenerKeyboard::create();
	//使用Lambda表达式处理键盘事件
	//捕获this以使用成员变量
	keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		this->keyStatus[keyCode] = true;
		//单次按下相应
		if (keyCode == EventKeyboard::KeyCode::KEY_K && hero->getAttackMode())
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
