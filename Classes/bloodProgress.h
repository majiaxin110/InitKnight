#ifndef __PROGRESSVIEW_H__  
#define __PROGRESSVIEW_H__  

#include "cocos2d.h"  
using namespace cocos2d;

class ProgressView : public Node
{
public:
	ProgressView();

public:
	void initProgressView(const char* backName,const char* foreName);//�������飬��ʼ��
	//������Ѫ��  
	void setTotalProgress(float total);
	//���õ�ǰѪ��  
	void setCurrentProgress(float progress);
	//�õ���ǰѪ��  
	float getCurrentProgress() const;
	//�õ���Ѫ��  
	float getTotalProgress() const;
	//����Ѫ��,�����Ƿ��ɫ����
	bool cutBlood(float cutAmount);
	//����Ѫ��
	void addBlood(float addAmount);
private:
	//����ǰ��Ѫ����ʾ�ĳ���  
	void setForegroundTextureRect(const Rect &rect);

private:
	Sprite *progressBackground;//����
	Sprite *progressForeground;//ǰ��
	float totalBlood;//��Ѫ��  
	float currentBlood;//��ǰѪ��  
	float scale;//�Ŵ���  
};

#endif  