﻿#ifndef __MILITARY_H__
#define __MILITARY_H__

#include "cocos2d.h"
#include <iostream>
#include<string>
USING_NS_CC;
using std::string;

/*enum 
{
	//寰呭畬鍠?};*/

class Military : public Sprite
{
private:
	int health_point;
	int max_hp;
	Vec2 position;
	bool dead;

	Vec2  destination;
	bool Selected;
	string status;
	int country;

	static int power;
	static string name;
	static int speed;
	static int delay;
	static Action* move;
	static int money;

	//ValueVector data;

public:
	void sethp(int damage);
	void setDestination(Vec2 v);
	void setdead();
	void setPosition(Vec2 v);
	void Military::attack(Military* sprite);
	void setSelected(bool b);
	static void createBar(Military *a);
	Action* getMoveAction()
	{
		return move;
	}
	float getSpeed()
	{
		return speed;
	}
	Vec2 getDestination()
	{
		return destination;
	}
	Vec2 getPosition()
	{
		return position;
	}
	void setStatus(const char* str)
	{
		status = str;
	}
	string getStatus()
	{
		return status;
	}

	int getCountry()
	{
		return country;
	}
	

   int gethp()
	{
		return health_point;
	}


	static Military* create(string& filename);

	void init(int _health_point, bool _dead, bool _Selected, Vec2 _position,Vec2 _destination , Action* _move);
	/*static Military* create(string & filename);
	static Military* create(const std::string & filename, const Rect & rect);
	static Military* createWithTexture(Texture2D * texture);
	static Military* createwithTexture(Texture2D * texture, const Rect & rect, bool rotated = false);
	static Military* createWithSpritFrame(SpriteFrame* pSpriteFrame);
	static Military* createWithSpriteFrameName(const std::string & spriteFrameName);*/

	//virtual ValueVector& getValueVector() = 0;
};

#endif
