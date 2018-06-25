#include "hero.h"
#include "localPlayScene.h"

USING_NS_CC;

Hero::Hero()
{
	isMoving = false;
	isAttacking = false;
	attackPower = 1;
	heroDirection = 0;
	cHeroSprite = nullptr;
	moveSpeed = 1.6f;
	heroface = 1;
	attackMode = 0;
}

void Hero::initHeroSprite()
{
	this->cHeroSprite = Sprite::create("knight.png");
	this->addChild(cHeroSprite);
}

float Hero::getMoveSpeed()
{
	return moveSpeed;
}

void Hero::changeAttackMode()
{
	attackMode = !attackMode;
	//������ͼ
	this->removeChild(cHeroSprite, TRUE);//��ԭ���ľ���ɾ����  
	if (attackMode)
	{
		this->cHeroSprite = Sprite::create("knightWithGun.png");
		this->addChild(cHeroSprite);
		this->cHeroSprite->setFlippedX(heroDirection);
	}
	else
	{
		this->cHeroSprite = Sprite::create("knight.png");
		this->addChild(cHeroSprite);
		this->cHeroSprite->setFlippedX(heroDirection);
	}
}

void Hero::setRunAnimation(bool runDirection)
{
	//��ת������
	if (heroDirection != runDirection)
	{
		heroDirection = runDirection;
		cHeroSprite->setFlippedX(runDirection);
	}
	if (isMoving || cHeroSprite->getNumberOfRunningActions() > 0)
		return;
	Animation *animation = Animation::create();
	log("run move anime");
	for (int i = 1; i <= 4; i++)
	{
		__String *frameName;
		if(attackMode)
			frameName = __String::createWithFormat("knightAnime/runWithGun_%d.png", i);
		else
			frameName = __String::createWithFormat("knightAnime/run_%d.png", i);
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	Animate *action = Animate::create(animation);
	action->setTag(101);
	cHeroSprite->runAction(RepeatForever::create(action));

	isMoving = true;
}

void Hero::setAttackAnimation()
{
	if (isAttacking || cHeroSprite->getNumberOfRunningActions() > 0)
		return;
	Animation* animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "knightAnime/attackKnife_%d.png", i);
		animation->addSpriteFrameWithFile(szName); //���ض�����֡    
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //����ѭ��1��    
							//��������װ��һ������  
	Animate* act = Animate::create(animation);
	//�����ص��������������������AttackEnd()  
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	//������������  
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);

	cHeroSprite->runAction(attackact);
	isAttacking = true;

}
void Hero::AttackEnd()
{
	//�ָ�����ԭ���ĳ�ʼ����ͼ   
	this->removeChild(cHeroSprite, TRUE);//��ԭ���ľ���ɾ����  
	if (attackMode)
		cHeroSprite = Sprite::create("knightWithGun.png");
	else
		cHeroSprite = Sprite::create("knight.png");//�ָ�����ԭ������ͼ����    
	cHeroSprite->setFlippedX(heroDirection);  //���ӣ�
	this->addChild(cHeroSprite);
	isAttacking = false;
}

void Hero::setUpAnimation()
{
	if (isAttacking)
		return;
	isAttacking = true;
	Animation *animation = Animation::create();
	log("run up anime");
	for (int i = 1; i <= 5; i++)
	{
		__String *frameName = __String::createWithFormat("knightAnime/up_%d.png", i);
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	Animate *action = Animate::create(animation);
	action->setTag(103);
	cHeroSprite->runAction(action);
	isAttacking = false;
}
void Hero::stopAllAnimation()
{
	isAttacking = false;
	if (!isMoving)
		return;
	cHeroSprite->stopActionByTag(101);
	this->removeChild(cHeroSprite, TRUE);//��ԭ���ľ���ɾ����  
	if(attackMode)
		cHeroSprite = Sprite::create("knightWithGun.png");
	else
		cHeroSprite = Sprite::create("knight.png");//�ָ�����ԭ������ͼ����  
	cHeroSprite->setFlippedX(heroDirection);
	this->addChild(cHeroSprite);
	isMoving = false;
}

void Hero::addHeadProgress(char *xue_back, char* xue_fore, float totalPro)
{
	headProgress = new ProgressView();
	headProgress->setPosition(Vec2(cHeroSprite->getPositionX() + 10, cHeroSprite->getPositionY() + 50));//�����ڹ�����ͷ    																											  //Monster_xue->setScale(2.2f);    
	headProgress->initProgressView(xue_back, xue_fore);
	headProgress->setTotalProgress(totalPro);
	headProgress->setCurrentProgress(totalPro);
	this->addChild(headProgress);
}

void Hero::setMoveSpeed(float currentSpeed)
{
	moveSpeed = currentSpeed;
}

void Hero::setFlipp(bool direc)
{
	cHeroSprite->setFlippedX(direc);
}

bool Hero::getAttackMode()
{
	return attackMode;
}
