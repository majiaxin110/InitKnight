#include "Monster.h"
#include "localPlayMainLayer.h"
USING_NS_CC;

Monster::Monster(void)
{
	IsRunning = false;//没在放动画  
	MonsterDirecton = TRUE;//向右运动  
	IsAttack = false;
	Monster_xue = NULL; //后面初始化
	senseDistance = 160; //追踪距离
	power = 0.5;
}

Monster::~Monster(void)
{
	CC_SAFE_DELETE(m_MonsterSprite);
}

Sprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}

void Monster::InitMonsterSprite(char *name)  //不带血条的怪物
{
	Monster_name.assign(name);
	log(Monster_name.c_str());
	this->m_MonsterSprite = Sprite::create((Monster_name + "/monsterwalk1.png"));
	if (Monster_name == "monster1")
		m_MonsterSprite->setFlippedX(MonsterDirecton);  //图片初始方向
	else
		m_MonsterSprite->setFlippedX(!MonsterDirecton);
	this->addChild(m_MonsterSprite);
	isDied = false;
}

void Monster::InitMonsterSprite(char *name, char *xue_back, char* xue_fore,float totalPro)  //带血条的怪物  函数重载
{
	InitMonsterSprite(name);
	//设置怪物的血条   
	Monster_xue = new ProgressView();
	Monster_xue->setPosition(Vec2(m_MonsterSprite->getPositionX() + 25, m_MonsterSprite->getPositionY() + 50));//设置在怪物上头    																											  //Monster_xue->setScale(2.2f);    
	Monster_xue->initProgressView(xue_back, xue_fore);
	Monster_xue->setTotalProgress(totalPro);
	Monster_xue->setCurrentProgress(totalPro);
	this->addChild(Monster_xue);
}

void Monster::SetAnimation(const char *name_each, unsigned int num, bool run_directon)
{
	if (MonsterDirecton != run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterSprite->setFlippedX(run_directon);//增加！
	}
	if (IsRunning || IsAttack)
		return;
	Animation* animation = Animation::create();
	for (unsigned int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		log(szName);
		animation->addSpriteFrameWithFile(szName); //加载动画的帧    
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //动画循环  
							 //将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	m_MonsterSprite->runAction(act);
	IsRunning = true;

}
void Monster::StopAnimation()
{
	if (!IsRunning)
		return;
	m_MonsterSprite->stopAllActions();//当前精灵停止所有动画  
									  //恢复精灵原来的初始化贴图   
	this->removeChild(m_MonsterSprite, TRUE);//把原来的精灵删除掉  
	m_MonsterSprite = Sprite::create(Monster_name+"/monsterwalk1.png");//恢复精灵原来的贴图样子  
	m_MonsterSprite->setFlippedX(!MonsterDirecton);  //增加！
	this->addChild(m_MonsterSprite);
	IsRunning = false;
	MonsterDirecton = !MonsterDirecton;  //每次停下都会重置方向
}
void Monster::AttackAnimation(const char *name_each, const unsigned int num, bool run_directon)
{
	if (IsAttack || IsRunning)
		return;
	Animation* animation = Animation::create();
	for (unsigned int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		log(szName);
		animation->addSpriteFrameWithFile(szName); //加载动画的帧    
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环1次    
							//将动画包装成一个动作  
	Animate* act = Animate::create(animation);
	//创建回调动作，攻击结束后调用AttackEnd()  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//创建连续动作
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);

	m_MonsterSprite->runAction(attackact);
	IsAttack = true;

}
void Monster::AttackEnd()
{
	//恢复精灵原来的初始化贴图   
	this->removeChild(m_MonsterSprite, TRUE);//把原来的精灵删除掉  
	m_MonsterSprite = Sprite::create((Monster_name+"/monsterwalk1.png").c_str());//恢复精灵原来的贴图样子  
	m_MonsterSprite->setFlippedX(!MonsterDirecton);  //翻转方向
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

void Monster::FollowRun(Hero* m_hero, cocos2d::TMXTiledMap* m_map)
{

	  
	float x = m_hero->getPositionX() - this->getPositionX() ;

	float y = m_hero->getPositionY() - this->getPositionY() ;

	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= senseDistance)//当怪物与英雄距离超过100
	{
		MonsterSeeRun();
		return;
	}

	if (this->getPositionX()>m_hero->getPositionX()&&detectMonsterPosition(Vec2(this->getPositionX()-32, this->getPositionY())))  //这是第一层if，看看左右有没有障碍，毕竟追踪是先左右跟着跑在上下跟着跑
	{
		if (dis <= 64)//在怪物攻击范围内，怪物停止移动  
		{
			this->StopAnimation();//停止跑动
			JudgeAttack();//必定攻击怪物
			return;
		}
		std::string aniName(Monster_name);
		aniName = aniName + "/monsterwalk";

		if (x < -64/*&& detectMonsterPosition(Vec2(this->getPositionX() - 0.8, this->getPositionY()))*/)//判断怪物横坐标和英雄的距离  
		{
			log("%f \n %f", my_map->getPositionX(), this->getPositionX());
			MonsterDirecton = true;
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;

			this->setPosition(this->getPositionX() - 0.8, this->getPositionY());//怪物向英雄移动  
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

		}
		else if (x > 64/*&& detectMonsterPosition(Vec2(this->getPositionX() + 0.8, this->getPositionY()))*/)
		{

			MonsterDirecton = false;
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;

			this->setPosition(this->getPositionX() + 0.8, this->getPositionY());
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

		}
		else if (x <= 64)//怪物横坐标和英雄相差在64以内时，开始移动怪物纵坐标  
		{

			if (m_hero->getPositionY() > this->getPositionY()&& detectMonsterPosition(Vec2(this->getPositionX(), this->getPositionY() + 32)))  //这是第二层if ，判断上下撞不撞墙
			{
				m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
				if (IsAttack)
					return;

				this->setPosition(this->getPositionX(), this->getPositionY() + 0.8);
				this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

			}
			else if (m_hero->getPositionY() < this->getPositionY()&& detectMonsterPosition(Vec2(this->getPositionX(), this->getPositionY() - 32)))		//上下	
			{
				m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
				if (IsAttack)
					return;

				this->setPosition(this->getPositionX(), this->getPositionY() - 0.8);
				this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  //knightAnime/run_%d.png

			}
		}
	}
	else if (this->getPositionX()<m_hero->getPositionX() && detectMonsterPosition(Vec2(this->getPositionX()+32, this->getPositionY())))  //判断左右撞墙不
	{
		if (dis <= 64)//在怪物攻击范围内，怪物停止移动  
		{
			this->StopAnimation();//停止跑动
			JudgeAttack();//必定攻击怪物
			return;
		}
		std::string aniName(Monster_name);
		aniName = aniName + "/monsterwalk";

		if (x < -64 )//判断怪物横坐标和英雄的距离  
		{
			log("%f \n %f", my_map->getPositionX(), this->getPositionX());
			MonsterDirecton = true;
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;

			this->setPosition(this->getPositionX() - 0.8, this->getPositionY());//怪物向英雄移动  
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

		}
		else if (x > 64/*&& detectMonsterPosition(Vec2(this->getPositionX() + 0.8, this->getPositionY()))*/)
		{

			MonsterDirecton = false;
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;

			this->setPosition(this->getPositionX() + 0.8, this->getPositionY());
			this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

		}
		else if (x <= 64)//怪物横坐标和英雄相差在64以内时，开始移动怪物纵坐标  
		{

			if (m_hero->getPositionY() > this->getPositionY()&& detectMonsterPosition(Vec2(this->getPositionX(), this->getPositionY() + 32)))  //上下
			{
				m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
				if (IsAttack)
					return;

				this->setPosition(this->getPositionX(), this->getPositionY() + 0.8);
				this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  

			}
			else if (m_hero->getPositionY() < this->getPositionY()&& detectMonsterPosition(Vec2(this->getPositionX(), this->getPositionY() - 32))) //左右
			{
				m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
				if (IsAttack)
					return;

				this->setPosition(this->getPositionX(), this->getPositionY() - 0.8);
				this->SetAnimation(aniName.c_str(), 6, MonsterDirecton);//播放动画  //knightAnime/run_%d.png

			}
		}
	}
	else
	{
		MonsterSeeRun();
	}

}
void Monster::JudgeAttack()//判定攻击
{
	srand((UINT)GetCurrentTime());
	int x = rand() % 100;
	if (x > 64)
	{
		m_MonsterSprite->setFlippedX(!MonsterDirecton);
		std::string aniName(Monster_name);
		aniName = aniName + "/monsterattack";
		this->AttackAnimation(aniName.c_str(), 6, MonsterDirecton);
	}
}

void Monster::cutHeroBlood(float delta)
{
	if (IsAttack == 1)  //怪物若正在攻击
		nowStatus->cutHeroBlood(power);  //干掉血
}

void Monster::heroCutMonsterBlood(float delta)//英雄干掉怪物血
{
	float x = my_hero->getPositionX() - this->getPositionX() ;
 
	float y = my_hero->getPositionY() - this->getPositionY();

	//先计算怪物和英雄的距离
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (my_hero->isAttacking == true && !my_hero->getAttackMode() && dis<64
		&& ((my_hero->getPositionX() - this->getPositionX() <=0 && my_hero->heroface == 2)
			||(my_hero->getPositionX() - this->getPositionX() >=0 && my_hero->heroface == 1)))
		if (this->getHurt(5))
			isDied = true;
}

void  Monster::MonsterSeeRun()
{
	if (dis < senseDistance)
		return;
	this->SetAnimation((Monster_name+"/monsterwalk").c_str(), 6, MonsterDirecton);//播放动画  
	MoveBy *moveby1;
	//创建回调动作，巡逻路线完后  
	bool lefttag = true;  //记录上下左右是否能走
	bool righttag = true;
	bool uptag = true;
	bool downtag = true;
	for (int i = 1; i < 100; i++)  //for循环判断巡逻范围内有没有障碍
	{
		if (!detectMonsterPosition(Vec2(this->getPositionX() - i, this->getPositionY())) || MonsterDirecton == false)
		{
			lefttag = false;
			break;
		}
	}
	for (int i = 1; i < 100; i++)
	{
		if (!detectMonsterPosition(Vec2(this->getPositionX() + i, this->getPositionY())) ||MonsterDirecton == true)
		{
			righttag = false;
			break;
		}
	}
	for (int i = 1; i < 100; i++)
	{
		if (!detectMonsterPosition(Vec2(this->getPositionX(), this->getPositionY()+i)) )
		{
			uptag = false;
			break;
		}
	}
	for (int i = 1; i < 100; i++)
	{
		if (!detectMonsterPosition(Vec2(this->getPositionX() , this->getPositionY()-i)) )
		{
			downtag = false;
			break;
		}
	}
	//根据之前判断创建巡逻动作
	if (lefttag==true)
		moveby1 = MoveBy::create(4, Vec2(-100, 0));
	else if (righttag==true)
		moveby1 = MoveBy::create(4, Vec2(100, 0));
	else if (uptag==true)
		moveby1 = MoveBy::create(4, Vec2(0, 100));
	else if (downtag==true)
		moveby1 = MoveBy::create(4, Vec2(0, -100));
	else
		moveby1 = MoveBy::create(4, Vec2(0,0));

	//这里分别判断上下左右四个方向，优先左右，没障碍就巡逻，预判的距离是10，随便设的，比follow那个小点
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//创建连续动作  
	ActionInterval* xunluo = Sequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);
}
//启动监听  

void Monster::StartListen(Hero* m_hero, cocos2d::TMXTiledMap* m_map)
{

	my_hero = m_hero;
	my_map = m_map;
	_collidable = my_map->getLayer("barriers");
	_collidable->setVisible(false);
	//nowStatus = nowStatus1;  放在单独函数中 
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);//每1秒计算距离  
	this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打  
	this->schedule(schedule_selector(Monster::cutHeroBlood), 0.2f); //0.2f判断一次
	this->schedule(schedule_selector(Monster::heroCutMonsterBlood), 0.05f);
}

//监听函数,每隔2秒检测下
void Monster::updateMonster(float delta)
{
	
	float x = my_hero->getPositionX() - this->getPositionX();
	
	float y = my_hero->getPositionY() - this->getPositionY();
	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (dis >= senseDistance)
	{
		if (!IsRunning)
			MonsterSeeRun();
	}
}

void Monster::update(float delta)
{
	if (dis < senseDistance)//当英雄在它的可视范围内，不断追着英雄  
		FollowRun(my_hero, my_map);
}

void Monster::getBloodStatus(localStatus* nowStatus1)
{
	nowStatus = nowStatus1;  //当mainlayer中初始化时获取
}

bool Monster::getHurt(float delta)
{
	return Monster_xue->cutBlood(delta);
}

float Monster::getSense()
{
	return senseDistance;
}

void Monster::setSense(float sens)
{
	senseDistance = sens;
}

void Monster::setPower(float cPower)
{
	power = cPower;
}

bool Monster::detectMonsterPosition(Vec2 position)  //侦测碰撞，照英雄那个改的
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);

	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	//log("nimannima %d", tileGid);
	if (tileGid > 0)
	{
		Value prop = my_map->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["isCollidable"].asString();

		if (collision == "true") { //碰撞检测成功
			log("%s", collision);
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/empty.wav");
			return false;
		}
	}
	return true;
}


Vec2 Monster::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / my_map->getTileSize().width;
	int y = ((my_map->getMapSize().height * my_map->getTileSize().height) - pos.y)
		/ my_map->getTileSize().height;
	return Vec2(x, y);
}
