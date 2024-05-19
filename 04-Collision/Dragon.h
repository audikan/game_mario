#pragma once
#include "GameObject.h"

#define DRAGON_GRAVITY 0.002f
#define DRAGON_WALKING_SPEED 0.05f


#define DRAGON_BBOX_WIDTH 18
#define DRAGON_BBOX_HEIGHT 18
#define DRAGON_BBOX_HEIGHT_DIE 12

#define DRAGON_DIE_TIMEOUT 5000

#define DRAGON_STATE_WALKING 823
#define DRAGON_STATE_DIE 923

#define ID_ANI_DRAGON_WALKING 8000
#define ID_ANI_DRAGON_DIE 8001

class CDragon : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CDragon(float x, float y);
	virtual void SetState(int state);
};