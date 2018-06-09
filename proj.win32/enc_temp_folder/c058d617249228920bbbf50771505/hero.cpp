#include "hero.h"
#include "localPlayScene.h"

USING_NS_CC;

Hero::Hero()
{
	isMoving = false;
	isAttacking = false;
	attackPower = 1;
	blood = 100;
	heroDirection = 0;
	cHeroSprite = nullptr;
	moveSpeed = 1.5f;
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

void Hero::setRunAnimation(bool runDirection)
{
	//翻转吧朋友
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
		__String *frameName = __String::createWithFormat("knightAnime/run_%d.png", i);
		//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	Animate *action = Animate::create(animation);
	action->setTag(101);
	cHeroSprite->runAction(RepeatForever::create(action));

	isMoving = true;
}

/*void Hero::setAttackAnimation()
{
	if (isAttacking || cHeroSprite->getNumberOfRunningActions() > 0)
		return;
	isAttacking = true;
	Animation *animation = Animation::create();
	log("run attack anime");
	for (int i = 1; i <= 4; i++)
	{
		__String *frameName = __String::createWithFormat("knightAnime/attackKnife_%d.png", i);
		//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrameWithFile(frameName->getCString());
	}
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);
	Animate *action = Animate::create(animation);
	action->setTag(102);
	cHeroSprite->runAction(action);
	isAttacking = false;
}*/
void  Hero::setAttackAnimation()
{
	if (isAttacking || cHeroSprite->getNumberOfRunningActions() > 0)
		return;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= 4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName,"knightAnime/attackKnife_%d.png", i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧    
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环1次    
							//将动画包装成一个动作  
	CCAnimate* act = CCAnimate::create(animation);
	//创建回调动作，攻击结束后调用AttackEnd()  
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	//创建连续动作  
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);

	cHeroSprite->runAction(attackact);
	isAttacking = true;

}
void Hero::AttackEnd()
{
	//恢复精灵原来的初始化贴图   
	this->removeChild(cHeroSprite, TRUE);//把原来的精灵删除掉  
	cHeroSprite = CCSprite::create("knight.png");//恢复精灵原来的贴图样子  
	cHeroSprite->setFlipX(heroDirection);  //增加！
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
		//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
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
	if (!isMoving)
		return;
	cHeroSprite->stopActionByTag(101);
	this->removeChild(cHeroSprite, TRUE);//把原来的精灵删除掉  
	cHeroSprite = Sprite::create("knight.png");//恢复精灵原来的贴图样子  
	cHeroSprite->setFlippedX(heroDirection);
	this->addChild(cHeroSprite);
	isMoving = false;
}