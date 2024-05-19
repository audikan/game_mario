#include "Dragon.h"

CDragon::CDragon(float x, float y):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = DRAGON_GRAVITY;
	die_start = -1;
	SetState(DRAGON_STATE_WALKING);
}

void CDragon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == DRAGON_STATE_DIE)
	{
		left = x - DRAGON_BBOX_WIDTH / 2;
		top = y - DRAGON_BBOX_HEIGHT_DIE / 2;
		right = left + DRAGON_BBOX_WIDTH;
		bottom = top + DRAGON_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - DRAGON_BBOX_WIDTH / 2;
		top = y - DRAGON_BBOX_HEIGHT / 2;
		right = left + DRAGON_BBOX_WIDTH;
		bottom = top + DRAGON_BBOX_HEIGHT;
	}
}

void CDragon::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CDragon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CDragon*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CDragon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == DRAGON_STATE_DIE) && (GetTickCount64() - die_start > DRAGON_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CDragon::Render()
{
	int aniId = ID_ANI_DRAGON_WALKING;
	if (state == DRAGON_STATE_DIE)
	{
		aniId = ID_ANI_DRAGON_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CDragon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DRAGON_STATE_DIE:
		die_start = GetTickCount64();
		y += (DRAGON_BBOX_HEIGHT - DRAGON_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case DRAGON_STATE_WALKING:
		vx = -DRAGON_WALKING_SPEED;
		break;
	}
}
