#pragma once

#include "cocos2d.h"

class Brick
{
private:
	int hp;
	cocos2d::Size _spriteSize;

	cocos2d::Sprite* _sprite;
	cocos2d::Vec2 _position;

	void HideSelf();
	void ShowSelf();
public:

	Brick();		// Default constructor necessary
	Brick(cocos2d::Scene* parent, float offsetX, float offsetY, int hp);
	~Brick();

	void SetBrick(float offsetX, float offsetY, int hp);
	void SetPosition(float offsetX, float offsetY);
	void SetHP(int hp);
	bool ApplyCollisionLogic(int& hitHp);
	void Dispose();
	void Show();

	cocos2d::Vec2 getPosition();
};