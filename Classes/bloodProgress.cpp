#include "bloodProgress.h"  

ProgressView::ProgressView()
	: progressBackground(nullptr)
	, progressForeground(nullptr)
	, totalBlood(0)
	, currentBlood(0)
	, scale(1.0f)
{}

void ProgressView::initProgressView(const char* backName,const char* foreName)
{
	progressBackground = Sprite::create(backName);
	this->addChild(progressBackground);
	
	progressForeground = Sprite::create(foreName);
	progressForeground->setAnchorPoint(Vec2(0, 0.5));
	//设置位置
	progressForeground->setPosition(Vec2(-progressForeground->getContentSize().width / 2.0f, 0));
	this->addChild(progressForeground);
}

void ProgressView::setTotalProgress(float total)
{
	if (progressForeground == nullptr) 
		return;
	scale = progressForeground->getContentSize().width / total;
	totalBlood = total;
}

void ProgressView::setCurrentProgress(float progress)
{
	if (progressForeground == nullptr)
		return;
	if (progress > totalBlood) 
		progress = totalBlood;
	currentBlood = progress;
	//利用Rect显示一部分
	float rectWidth = progress * scale;
	const Vec2 pos = progressForeground->getTextureRect().origin;
	const Rect rect = Rect(pos.x, pos.y, rectWidth, progressForeground->getContentSize().height);
	setForegroundTextureRect(rect);
}

void ProgressView::setForegroundTextureRect(const Rect &rect)
{
	progressForeground->setTextureRect(rect);
}

float ProgressView::getCurrentProgress() const
{
	return currentBlood;
}

float ProgressView::getTotalProgress() const
{
	return totalBlood;
}

bool ProgressView::cutBlood(float cutAmount)
{
	if (currentBlood - cutAmount < 0)
	{
		currentBlood = 0;
		setCurrentProgress(currentBlood);
		return true;
	}
	else
	{
		currentBlood -= cutAmount;
		setCurrentProgress(currentBlood);
		return false;
	}
}

void ProgressView::addBlood(float amount)
{
	setCurrentProgress(currentBlood + amount);
}