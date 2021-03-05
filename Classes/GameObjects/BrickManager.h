#pragma once

#include <vector>
#include <map>
#include "Brick.h"
#include "cocos2d.h"

class BrickManager {
private:
	int activeBricks;
	std::vector<Brick> _bricks;
	cocos2d::Size _winSize;
public:
	BrickManager();
	BrickManager(cocos2d::Scene* parent, const cocos2d::Size& winSize);
	~BrickManager();

	void LoadDefaultLevel(cocos2d::Scene* parent);
	void ResetLevel();
	int ApplyCollisionToBrickAtPos(const cocos2d::Vec2& pos);
	bool CheckWinCond();
};