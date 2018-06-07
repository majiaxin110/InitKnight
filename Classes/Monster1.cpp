#include "Monster1.h"
#include "localPlayScene.h"
#include "cocos2d.h"


USING_NS_CC;

Monster1::Monster1()
{

	isMoving = false;
	isAttacking = false;
	attackPower = 1;
	blood = 100;
	monster1Direction = 0;
	monster1Sprite = nullptr;
	moveSpeed = 2.5f;
}

void Monster1::initMonster1Sprite()  //创建怪物
{
	this->monster1Sprite = Sprite::create("carman1.png");
	monster1Sprite->setScale(0.6, 0.6);
	this->addChild(monster1Sprite);
}

void Monster1::startAnimation()  //开始播放动画
{
	Animation *animation = Animation::create();
	for (int i = 1; i <= 5; i++)
	{
		__String *frameName = __String::createWithFormat("carMan/carman%d.png", i);
		//log("frameName=%s", frameName->getCString());
		//SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrameWithFile(frameName->getCString());
	}

	animation->setDelayPerUnit(0.15f);  //设置两个帧播放时间;
	animation->setRestoreOriginalFrame(true);//动画执行后还原初始状态

	Animate *action = Animate::create(animation);
	monster1Sprite->runAction(RepeatForever::create(action));
	//动画结束

}

void Monster1::patrol()  //常态怪物巡逻
{
	
	//this->SetAnimation("monster_run", 6, MonsterDirecton);//播放动画  
	/*CCMoveBy *moveby1;
	if (monster1Direction == true)
		moveby1 = CCMoveBy::create(2, ccp(-100, 0));
	else
		moveby1 = CCMoveBy::create(2, ccp(100, 0));
	//创建回调动作，巡逻路线完后  
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::StopAnimation));
	//创建连续动作  
	CCActionInterval* xunluo = CCSequence::create(moveby1, callFunc, NULL);
	this->runAction(xunluo);*/
	
	
	//Action* action1=monster1Sprite->runAction(MoveBy::create(4, Vec2(-200, 0)));
	//Action* action2=monster1Sprite->runAction(MoveBy::create(4, Vec2(0, 200)));
	
		//auto action = Sequence::create(MoveBy::create(4, Vec2(-200, 0)), MoveBy::create(4, Vec2(200, 0)), nullptr);
		//auto action2 = monster1Sprite->runAction(FlipX::create(false));
		//auto action3= Sequence::create(action, action2, nullptr);
		
			/*auto repeat = Repeat::create(action, 1);
			runAction(repeat);
			monster1Sprite->setFlippedX(true);*/
			auto action = Sequence::create(MoveBy::create(4, Vec2(-200, 0)), MoveBy::create(4, Vec2(200, 0)), NULL);
			auto repeat = RepeatForever::create(action);
			runAction(repeat);
    
}

float Monster1::getMoveSpeed()
{
	return moveSpeed;
}



/*void Monster::setRunAnimation(bool runDriection)
{

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

void Hero::setAttackAnimation()
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
*/
