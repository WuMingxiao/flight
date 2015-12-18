#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdbool.h>

#define ICON_PLANE        "<^>"
#define ICON_PLANE_EMPTY  "   " //for erasure 
#define ICON_BULLET       "|"
#define ICON_BULLET_EMPTY " "   //for erasure
#define ICON_ENEMY        "<v>"
#define ICON_ENEMY_EMPTY  "   " //for ereaure

#define APPEAR true
#define DISAPPEAR false 

/*define the prototype of plane*/
typedef struct plane_s
{
	unsigned int x;
	unsigned int y;
	void (*SetPosition)(struct plane_s* this, unsigned int x, unsigned int y);
	void (*Refresh)(struct plane_s* this);
	void (*Erasure)(struct plane_s* this);
}plane_t;

/*define the prototype of bullet*/
typedef struct bullet_s
{
	unsigned int x;
	unsigned int y;
    bool state;
	void (*SetPosition)(struct bullet_s* this, unsigned int x, unsigned int y);
	void (*Refresh)(struct bullet_s* this);
	void (*Erasure)(struct bullet_s* this);
	void (*SetState)(struct bullet_s* this, bool state);
}bullet_t;

/*define the prototype of enemy*/
typedef struct enemy_s
{
	unsigned int x;
	unsigned int y;
    bool state;
	void (*SetPosition)(struct enemy_s* this, unsigned int x, unsigned int y);
	void (*Refresh)(struct enemy_s* this);
	void (*Erasure)(struct enemy_s* this);
	void (*SetState)(struct enemy_s* this, bool state);
}enemy_t;

void InitPlane(plane_t*,unsigned int,unsigned int);

void InitBullet(bullet_t*,unsigned int,unsigned int);

void InitEnemy(enemy_t*,unsigned int,unsigned int);

#endif
