#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include <curses.h>

/*funtions for plane*/
static void PlaneSetPosition(plane_t* this,unsigned int x,unsigned int y)
{
	this->x=x;
	this->y=y;
}

static void PlaneRefresh(plane_t* this)
{
	mvprintw(this->y,this->x-1,ICON_PLANE);
}

static void PlaneErasure(plane_t* this)
{
	mvprintw(this->y,this->x-1,ICON_PLANE_EMPTY);
}

 void InitPlane(plane_t* this,unsigned int x,unsigned int y)
{   
	this->x=x;
	this->y=y;
	this->SetPosition=PlaneSetPosition;
	this->Refresh=PlaneRefresh;
	this->Erasure=PlaneErasure;
}

/*funtions for bullet*/
static void BulletSetPosition(bullet_t* this,unsigned int x,unsigned int y)
{
	this->x=x;
	this->y=y;
}

static void BulletSetState(bullet_t* this,bool state)
{
	this->state=state;
}

static void BulletRefresh(bullet_t* this)
{
    if(this->state==APPEAR)
        mvprintw(this->y,this->x,ICON_BULLET);
    else 
        mvprintw(this->y,this->x,ICON_BULLET_EMPTY);

}

static void BulletErasure(bullet_t* this)
{
	mvprintw(this->y,this->x,ICON_BULLET_EMPTY);
}

void InitBullet(bullet_t* this,unsigned int x,unsigned int y)
{
    this->x=x;
	this->y=y;
	this->SetPosition=BulletSetPosition;
	this->Refresh=BulletRefresh;
	this->Erasure=BulletErasure;
    this->SetState=BulletSetState;
}

/*funtions for enemy*/
static void EnemySetPosition(enemy_t* this,unsigned int x,unsigned int y)
{
	this->x=x;
	this->y=y;
}

static void EnemySetState(enemy_t* this,bool state)
{
	this->state=state;
}

static void EnemyRefresh(enemy_t* this)
{
    if(this->state==APPEAR)
        mvprintw(this->y,this->x-1,ICON_ENEMY);
    else 
        mvprintw(this->y,this->x-1,ICON_ENEMY_EMPTY);

}

static void EnemyErasure(enemy_t* this)
{
	mvprintw(this->y,this->x-1,ICON_ENEMY_EMPTY);
}

void InitEnemy(enemy_t* this,unsigned int x,unsigned int y)
{
    this->x=x;
	this->y=y;
	this->SetPosition=EnemySetPosition;
	this->Refresh=EnemyRefresh;
	this->Erasure=EnemyErasure;
    this->SetState=EnemySetState;
}
