#pragma once

#include <sstream>
#include "cocos2d.h"

// Includes level physical limits and walls
class Background {
private:
	int currentScore;

	cocos2d::Size _winSize;
	cocos2d::Size _spriteSize;

	cocos2d::Sprite* _bgrSprite;
	cocos2d::Label* _gamePausedLabel;
	cocos2d::Label* _youWonLabel;
	cocos2d::Label* _scoreLabel;
	
	cocos2d::DrawNode* _topWall;
	cocos2d::DrawNode* _leftWall;
	cocos2d::DrawNode* _rightWall;
	cocos2d::DrawNode* _bottomWall;			// This one is a trigger

	void initWalls(cocos2d::Scene* parent);
	void initLabels(cocos2d::Scene* parent);
public:
	Background();
	Background(cocos2d::Scene* parent, const cocos2d::Size& winSize);
	~Background();

	void setLabelsVisible(bool gamePausedHidden, bool youWonHidden);
	void resetScore();
	void addScore(int score);
	void runGameWonAnimation();

};
