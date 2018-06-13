#include "Bullet.h"


USING_NS_CC;


Bullet::Bullet()
{
	speed = 200;
	power = 1;
	bulletname = NULL;
	ifexist = 1;
}

Bullet::~Bullet()
{

}

CCSprite* Bullet::GetSprite()
{
	return bulletsprite;
}

void Bullet::initBulletSprite(Hero* hero)  //初始化子弹
{
	my_hero = hero;
	x = my_hero->getPositionX();
	y = my_hero->getPositionY();
	this->bulletsprite = CCSprite::create("bullet1.png");
	this->addChild(bulletsprite);
	bulletsprite->setPosition(ccp(x, y));

}


void Bullet::bulletMoveAnimation()  //传入目的地坐标使子弹移动
{

	float time = 500 / speed; //飞行到目标时间
	//if (distance<40)
	//	return;
	CCMoveBy* actionMove;
	if (my_hero->heroface == 1)
	{
		actionMove = CCMoveBy::create(time, ccp(-250, 0));
	}
	else if (my_hero->heroface == 2)
	{
		actionMove = CCMoveBy::create(time, ccp(250, 0));
	}
	else if (my_hero->heroface == 3)
	{
		actionMove = CCMoveBy::create(time, ccp(0, -250));
	}
	else if (my_hero->heroface == 4)
	{
		actionMove = CCMoveBy::create(time, ccp(0, 250));
	}
	this->bulletsprite->runAction(actionMove);

	//auto actionMove = MoveTo::create(3,
	//	Point((18 + 6) * 32, (38 + 6) * 32));

	//子弹执行完动作后进行函数回调，调用移除子弹函数  
	/*auto actionDone = CallFuncN::create(
		CC_CALLBACK_1(Bullet::removeBullet, this));
 
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	this->runAction(sequence);*/

}



void Bullet::StartListen(Monster *m_monster, CCNode* m_map)
{
	my_monster=m_monster;
	my_map = m_map;
	bulletMoveAnimation();
	//this->schedule(schedule_selector(Bullet::updateBullet), 0.1f);//每隔0.1秒计算距离  

	
		this->schedule(schedule_selector(Bullet::cutMonsterBlood), 0.05f);
		this->schedule(schedule_selector(Bullet::removeBullet), 0.03f);
	//this->scheduleUpdate();//进入距离消除
	//bulletMoveAnimation();

}

void Bullet::removeBullet(float delta)//到距离了就移除子弹
{
	if (ifexist == 1)
	{
		float x1 = x - bulletsprite->getPositionX();
		float y1 = y - bulletsprite->getPositionY();
	   //计算子弹从距离出发点距离
		distance = sqrt(pow(x1, 2) + pow(y1, 2));
		if (distance ==250 )
		{
			this->removeChild(bulletsprite, true);
			ifexist = 0;
		}
	}
	
}

void Bullet::getBloodStatus(localStatus* nowStatus1)
{
	nowStatus = nowStatus1;  //当mainlayer中初始化时获取
}

void Bullet::cutMonsterBlood(float delta)//干掉怪物血
{
	if (ifexist == 1)
	{
		float x1 = my_monster->getPositionX() - bulletsprite->getPositionX();
		//得到两点y的距离 
		float y1 = my_monster->getPositionY() - bulletsprite->getPositionY();
		//先计算怪物和子弹的距离  
		distance = sqrt(pow(x1, 2) + pow(y1, 2));
		if (distance < 60)
		{
			my_monster->Monster_xue->cutBlood(3);
			this->removeChild(bulletsprite, true);
			ifexist = 0;
		}
	}
		//Monster_xue->cutBlood(3);		
}