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

void Bullet::initBulletSprite(Hero* hero)  //��ʼ���ӵ�
{
	my_hero = hero;
	x = my_hero->getPositionX();
	y = my_hero->getPositionY();
	this->bulletsprite = CCSprite::create("bullet1.png");
	this->addChild(bulletsprite);
	bulletsprite->setPosition(ccp(x, y));

}


void Bullet::bulletMoveAnimation()  //����Ŀ�ĵ�����ʹ�ӵ��ƶ�
{

	float time = 500 / speed; //���е�Ŀ��ʱ��
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

	//�ӵ�ִ���궯������к����ص��������Ƴ��ӵ�����  
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
	//this->schedule(schedule_selector(Bullet::updateBullet), 0.1f);//ÿ��0.1��������  

	
		this->schedule(schedule_selector(Bullet::cutMonsterBlood), 0.05f);
		this->schedule(schedule_selector(Bullet::removeBullet), 0.03f);
	//this->scheduleUpdate();//�����������
	//bulletMoveAnimation();

}

void Bullet::removeBullet(float delta)//�������˾��Ƴ��ӵ�
{
	if (ifexist == 1)
	{
		float x1 = x - bulletsprite->getPositionX();
		float y1 = y - bulletsprite->getPositionY();
	   //�����ӵ��Ӿ�����������
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
	nowStatus = nowStatus1;  //��mainlayer�г�ʼ��ʱ��ȡ
}

void Bullet::cutMonsterBlood(float delta)//�ɵ�����Ѫ
{
	if (ifexist == 1)
	{
		float x1 = my_monster->getPositionX() - bulletsprite->getPositionX();
		//�õ�����y�ľ��� 
		float y1 = my_monster->getPositionY() - bulletsprite->getPositionY();
		//�ȼ��������ӵ��ľ���  
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