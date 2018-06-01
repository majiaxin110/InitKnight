#ifndef __HERO_H__  
#define __HERO_H__  

#include "cocos2d.h"  

class Hero :public cocos2d::Node
{
private:
	cocos2d::Sprite* cHeroSprite;
public:
	bool isMoving;//�Ƿ������ƶ�
	bool heroDirection;//���ҳ���0���ң�1����
	Hero();
	void initHeroSprite();
	void keyPressedDo(cocos2d::EventKeyboard::KeyCode keyCode);
	CREATE_FUNC(Hero);
};

#endif // __HERO_H__  
