#include "Monster1.h"
#include "localPlayScene.h"


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
	this->addChild(monster1Sprite);
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
