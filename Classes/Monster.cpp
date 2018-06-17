#include "Monster.h"
#include "localPlayMainLayer.h"
USING_NS_CC;

Monster::Monster(void)
{
	IsRunning = false;//没在放动画  
	MonsterDirecton = TRUE;//向右运动  
	Monster_name = NULL;
	IsAttack = false;
	Monster_xue = NULL; //后面初始化
}

Monster::~Monster(void)
{

}

Sprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}
void  Monster::InitMonsterSprite(char *name)  //不带血条的怪物
{
	Monster_name = name;
	this->m_MonsterSprite = Sprite::create(name);
	m_MonsterSprite->setFlippedX(MonsterDirecton);  //图片初始方向
	this->addChild(m_MonsterSprite);
	isDied = false;
}

void Monster::InitMonsterSprite(char *name, char *xue_back, char* xue_fore)  //带血条的怪物  函数重载
{
	InitMonsterSprite(name);
	//设置怪物的血条   
	Monster_xue = new ProgressView();
	Monster_xue->setPosition(Vec2(m_MonsterSprite->getPositionX() + 25, m_MonsterSprite->getPositionY() + 50));//设置在怪物上头    																											  //Monster_xue->setScale(2.2f);    
	Monster_xue->initProgressView(xue_back, xue_fore);
	Monster_xue->setTotalProgress(300.0f);
	Monster_xue->setCurrentProgress(300.0f);
	this->addChild(Monster_xue);
}

void  Monster::SetAnimation(const char *name_each, unsigned int num, bool run_directon)
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
	m_MonsterSprite = Sprite::create(Monster_name);//恢复精灵原来的贴图样子  
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
	m_MonsterSprite = Sprite::create(Monster_name);//恢复精灵原来的贴图样子  
	m_MonsterSprite->setFlippedX(!MonsterDirecton);  //翻转方向
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

void Monster::FollowRun(Hero* m_hero, Node* m_map)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的  
	float x = m_hero->getPositionX() - (this->getPositionX() + m_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的  
	float y = m_hero->getPositionY() - (this->getPositionY() + m_map->getPositionY());

	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= 100)//当怪物与英雄距离超过100
		return;
	if (dis <= 64)//在怪物攻击范围内，怪物停止移动  
	{
		this->StopAnimation();//停止跑动
		JudgeAttack();//必定攻击怪物
		return;
	}

	if (x<-64)//判断怪物横坐标和英雄的距离  
	{

		MonsterDirecton = true;
		m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() - 1, this->getPositionY());//怪物向英雄移动  
		this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//播放动画  

	}
	else if (x>64)
	{

		MonsterDirecton = false;
		m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
		if (IsAttack)
			return;
		this->setPosition(this->getPositionX() + 1, this->getPositionY());
		this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//播放动画  
	}
	else if (x <= 64)//怪物橫坐標和英雄相差在64以内时，开始移动怪物纵坐标  
	{

		if (m_hero->getPositionY()>this->getPositionY())
		{
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() + 1);
			this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//播放动画  
		}
		else if (m_hero->getPositionY()<this->getPositionY())
		{
			m_MonsterSprite->setFlippedX(MonsterDirecton);//设置方向  增加！
			if (IsAttack)
				return;
			this->setPosition(this->getPositionX(), this->getPositionY() - 1);
			this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//播放动画  //knightAnime/run_%d.png
		}
	}

}
void Monster::JudgeAttack()//判定攻击
{
	srand((UINT)GetCurrentTime());
	int x = rand() % 100;
	if (x > 85)
	{
		m_MonsterSprite->setFlippedX(!MonsterDirecton);
		this->AttackAnimation("monster1/monsterattack", 6, MonsterDirecton);
	}
	//this->schedule(schedule_selector(Monster::cutHeroBlood), 1.0f); 
	//this->schedule(schedule_selector(Monster::updateMonster), 2.0f);
	//}

}

void Monster::cutHeroBlood(float delta)
{
	if (IsAttack == 1)  //怪物若正在攻击
		nowStatus->cutHeroBlood(1);  //干掉血
}

void Monster::heroCutMonsterBlood(float delta)//英雄干掉怪物血
{
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());

	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (my_hero->isAttacking == true)
		if (dis < 64)
			this->getHurt(5);
}

void  Monster::MonsterSeeRun()
{
	if (dis<100)
		return;
	this->SetAnimation("monster1/monsterwalk", 6, MonsterDirecton);//播放动画  
	MoveBy *moveby1;
	if (MonsterDirecton == true)
	{
		moveby1 = MoveBy::create(4, Vec2(-100, 0));
	}
	else
		moveby1 = MoveBy::create(4, Vec2(100, 0));
	//创建回调动作，巡逻路线完后  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//创建连续动作  
	ActionInterval* xunluo = Sequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);
}
//启动监听  

void Monster::StartListen(Hero* m_hero, Node* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	//nowStatus = nowStatus1;  放在单独函数中 
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);//每隔2秒计算距离  
	this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打  
	this->schedule(schedule_selector(Monster::cutHeroBlood), 0.2f); //0.2f判断一次
	this->schedule(schedule_selector(Monster::heroCutMonsterBlood), 0.05f);
}

//监听函数,每隔2秒检测下
void Monster::updateMonster(float delta)
{
	//得到两点x的距离,记得怪物的坐标要加上地图的  
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的  
	float y = my_hero->getPositionY() - (this->getPositionY() + my_map->getPositionY());
	//先计算怪物和英雄的距离  
	dis = sqrt(pow(x, 2) + pow(y, 2));
	if (dis >= 100)
	{
		if (!IsRunning)
			MonsterSeeRun();
	}
}

void Monster::update(float delta)
{
	if (dis < 100)//当英雄在它的可视范围内，不断追着英雄  
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