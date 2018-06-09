#pragma once  
#include "cocos2d.h"  
#include "bloodProgress.h"

USING_NS_CC;

class localStatus : public cocos2d::Layer
{
private:
	ProgressView* cBloodProgress;
	Label* pointLabel;
	int playerPoint;
public:
	virtual bool init();

	bool cutHeroBlood(float amount);
	void addHeroBlood(float amount);

	void addPoint(int add);//���ӵ÷�

	//��NPC�Ի���ͼ��
	void showOldNPCDialog();
	void removeOldNPCDialog();
	void showPaojieDialog();
	void removePaoNPCDialog();

	CREATE_FUNC(localStatus);
};  
