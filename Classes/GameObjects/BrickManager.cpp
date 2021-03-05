#include "BrickManager.h"

static std::map<int, int> scores = {
	{ -2, 0 },
	{ 1, 10 },
	{ 2, 15 }
};

BrickManager:: BrickManager() {}

BrickManager::BrickManager(cocos2d::Scene* parent, const cocos2d::Size& winSize) {
	
	this->_winSize = winSize;
	LoadDefaultLevel(parent);
}

BrickManager::~BrickManager() {}

void BrickManager::LoadDefaultLevel(cocos2d::Scene* parent) {

	const int N_ROWS = 3;
	const int N_COLS = 4;

	activeBricks = 7;
	int hpValues[] = { -2, 1, 2, 1, 1, 2, 2, -2, -2, -2, 1, -2 };

	cocos2d::Vec2 initPos = cocos2d::Vec2(_winSize.width * 0.25f, _winSize.height * 0.75f);
	float yPosOffset = initPos.y;
	float xPosOffset = initPos.x;

	float brickSizeX = _winSize.width * 0.17f;
	float brickSizeY = _winSize.height * 0.03f;

	int z = 0;
	for (int i = 0; i < N_ROWS; i++) {
		
		xPosOffset = initPos.x;
		for (int j = 0; j < N_COLS; j++) {

			_bricks.push_back(Brick(parent, xPosOffset, yPosOffset, hpValues[z++]));
			xPosOffset += brickSizeX;
		}
		yPosOffset -= brickSizeY;
	}
	
	
}

void BrickManager::ResetLevel() {

	activeBricks = 7;
	int hpValues[] = { -2, 1, 2, 1, 1, 2, 2, -2, -2, -2, 1, -2 };

	for (int i = 0; i < _bricks.size(); i++) {
		_bricks[i].Show();
		_bricks[i].SetHP(hpValues[i]);
	}
}

int BrickManager::ApplyCollisionToBrickAtPos(const cocos2d::Vec2& pos) {

	for (int i = 0; i < _bricks.size(); i++) {
		
		if (_bricks[i].getPosition().equals(pos)) {
			
			int hp = 0;
			if (_bricks[i].ApplyCollisionLogic(hp))
				activeBricks--;
			
			return scores[hp];
		}
	}
}

bool BrickManager::CheckWinCond() {
	return (activeBricks <= 0);
}