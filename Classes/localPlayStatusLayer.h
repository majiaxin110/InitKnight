#pragma once  
#include "cocos2d.h"  
#include "bloodProgress.h"

USING_NS_CC;
class localStatus : public cocos2d::Layer
{
private:
	ProgressView* cBloodProgress;
public:
	virtual bool init();

	bool cutHeroBlood(float amount);
	void addHeroBlood(float amount);
	CREATE_FUNC(localStatus);
};  
