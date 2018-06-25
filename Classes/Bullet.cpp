#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet()
{
	speed = 400;
	power = 1;
	bulletname = NULL;
	ifexist = 1;
}

Bullet::~Bullet()
{

}

Sprite* Bullet::GetSprite()
{
	return bulletsprite;
}

void Bullet::initBulletSprite(Hero* hero)  //��ʼ���ӵ�
{
	my_hero = hero;
	heroFaceinBullet = hero->heroface;
	x = my_hero->getPositionX();
	y = my_hero->getPositionY();
	this->bulletsprite = Sprite::create("bullet1.png");
	this->addChild(bulletsprite);
	bulletsprite->setPosition(Vec2(x, y));

}

void Bullet::initBulletSprite(Vec2 pos,int face)  //��ʼ���ӵ�,����λ�ó���
{
	heroFaceinBullet = face;
	this->bulletsprite = Sprite::create("bullet1.png");
	this->addChild(bulletsprite);
	bulletsprite->setPosition(Vec2(x, y));
}
void Bullet::bulletMoveAnimation()  //����Ŀ�ĵ�����ʹ�ӵ��ƶ�
{

	float time = 500 / speed; //���е�Ŀ��ʱ��
	//if (distance<40)
	//	return;
	MoveBy* actionMove;
	if (heroFaceinBullet == 1)
	{
		actionMove = MoveBy::create(time, Vec2(-250, 0));
	}
	else if (heroFaceinBullet == 2)
	{
		actionMove = MoveBy::create(time, Vec2(250, 0));
	}
	else if (heroFaceinBullet == 3)
	{
		actionMove = MoveBy::create(time,Vec2(0, -250));
	}
	else if (heroFaceinBullet == 4)
	{
		actionMove = MoveBy::create(time, Vec2(0, 250));
	}
	this->bulletsprite->runAction(actionMove);

}



void Bullet::StartListen()
{
	bulletMoveAnimation();
	
	//this->schedule(schedule_selector(Bullet::cutMonsterBlood), 0.05f);
	this->schedule(schedule_selector(Bullet::removeBullet), 0.03f);

}

void Bullet::removeBullet(float delta)//�������˾��Ƴ��ӵ�
{
	if (ifexist == 1)
	{
		float x1 = x - bulletsprite->getPositionX();
		float y1 = y - bulletsprite->getPositionY();
	   //�����ӵ��Ӿ�����������
		distance = sqrt(pow(x1, 2) + pow(y1, 2));
		if (distance == 250 )
		{
			this->removeChild(bulletsprite, true);
			ifexist = 0;
		}
	}
	
}

void Bullet::removeBulletFromOutside()
{
	this->removeChild(bulletsprite, true);
	ifexist = 0;
}
