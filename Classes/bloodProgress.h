#ifndef __PROGRESSVIEW_H__  
#define __PROGRESSVIEW_H__  

#include "cocos2d.h"  
using namespace cocos2d;

class ProgressView : public Node
{
public:
	ProgressView();

public:
	void initProgressView(const char* backName,const char* foreName);//创建精灵，初始化
	//设置总血量  
	void setTotalProgress(float total);
	//设置当前血量  
	void setCurrentProgress(float progress);
	//得到当前血量  
	float getCurrentProgress() const;
	//得到总血量  
	float getTotalProgress() const;
	//减少血量,返回是否角色死亡
	bool cutBlood(float cutAmount);
	//增加血量
	void addBlood(float addAmount);
private:
	//设置前景血条显示的长度  
	void setForegroundTextureRect(const Rect &rect);

private:
	Sprite *progressBackground;//背景
	Sprite *progressForeground;//前景
	float totalBlood;//总血量  
	float currentBlood;//当前血量  
	float scale;//放大倍数  
};

#endif  