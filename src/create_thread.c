#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <pthread.h>
#include <unistd.h>
#include "create_thread.h"
#include "event.h"
#include <time.h>

extern unsigned int left_limit;
extern unsigned int right_limit;
extern unsigned int up_limit;
extern unsigned int down_limit;

extern plane_t planeMaster;
extern unsigned int bulletShootedNum;
unsigned int enemyGenerateNum;
unsigned int score;


#define PLANENUM 1
#define SPACE_GAP 2 //spaceGapBullet=spaceGapEnemy=SPACE_GAP
#define TIME_GAP  100000 //timeGapBullet=TIME_GAP
#define TIMES 10 //timeGapEnemy=TIME_GAP*TIMES

void DisplayEnemyGenerateNum(void)
{
    char str[10];
    sprintf(str,"<v> %3d",enemyGenerateNum);
    mvprintw(up_limit+1,right_limit-9,str);
}
void DisplayBulletShootedNum(void)
{
    char str[10];
    sprintf(str,"|  %3d",bulletShootedNum);
    mvprintw(up_limit+2,right_limit-8,str);
}
void DisplayPlaneNum(void)
{
    char str[10];
    sprintf(str,"<^> %3d",PLANENUM);
    mvprintw(up_limit+3,right_limit-9,str);
}
void DisplayScore(void)
{
    char str[10];
    sprintf(str,"SCR %3d",score);
    mvprintw(up_limit+4,right_limit-9,str);
}
void DisplayInfo(void)
{
    DisplayEnemyGenerateNum();	
    DisplayBulletShootedNum();
    DisplayPlaneNum();
    DisplayScore();     
}
void DisplayGameOver(void)
{
    clear();
    mvprintw(down_limit/2,right_limit/2-5,"GAME OVER");
    DisplayInfo();
}

void *Thread(void* arg)
{
    unsigned int i,j;
    unsigned int oddEven=0;
    bullet_t* bullets;
    enemy_t* enemys;
    
	/* calculate the number and the position of bullets and enemys according to the size of terminal */
    unsigned int bullet_enemy_top=((down_limit-2)-(up_limit+1))%SPACE_GAP+(up_limit+1);
    unsigned int bullet_enemy_bottom=down_limit-2;
	unsigned int bulletNum=((down_limit-2)-(up_limit+1))/SPACE_GAP+1;
    unsigned int enemyNum=bulletNum;

    unsigned int bulletShootedNum_temp=bulletShootedNum;
    unsigned int randEnemy_x;

	srand((unsigned int)time(NULL));
    
    bullets=(bullet_t*)malloc(sizeof(bullet_t)*bulletNum); //create all instances of the bullets
	enemys=(enemy_t*)malloc(sizeof(enemy_t)*enemyNum); //create all instances of the enemys
   
	for(i=0;i<bulletNum;i++)
    {
        InitBullet(&bullets[i],left_limit-1,bullet_enemy_bottom-SPACE_GAP*i);//Init invisible bullets out of the box 
        bullets[i].SetState(&bullets[i],DISAPPEAR);  
    }
	
	for(i=0;i<enemyNum;i++)
    {
        InitEnemy(&enemys[i],left_limit-1,bullet_enemy_bottom-SPACE_GAP*i);//Init invisible enemys out 0f the box
        enemys[i].SetState(&enemys[i],DISAPPEAR);  
    }
	
	while(1)
    {

        for(i=0;i<bulletNum;i++) //all bullets move a step every loop
        {
            bullets[i].y-=SPACE_GAP; 
            if(bullets[i].y<bullet_enemy_top||bullets[i].y>bullet_enemy_bottom)
            {
                bullets[i].SetPosition(&bullets[i],planeMaster.x,bullet_enemy_bottom);
                
                if(bulletShootedNum==bulletShootedNum_temp) //new bullet generating only if the KEY_UP is pushing down 
                    bullets[i].SetState(&bullets[i],DISAPPEAR);  
                else
                    bullets[i].SetState(&bullets[i],APPEAR);
                bulletShootedNum_temp=bulletShootedNum;
            }
            else
            {
                bullets[i].SetPosition(&bullets[i],bullets[i].x,bullets[i].y);
            }
            bullets[i].Refresh(&bullets[i]);
        }

        if(oddEven%TIMES==0) //all enemys move a step every TIMES loops 
        {
            for(i=0;i<enemyNum;i++)
            {
                enemys[i].y+=SPACE_GAP;
                if(enemys[i].y<bullet_enemy_top||enemys[i].y>bullet_enemy_bottom)
                {
                    if(enemys[i].state==APPEAR) //enemy reach the bottom of the terminal 
                        {
                            DisplayGameOver();
                            refresh();
                            while(1); //game over
                        }
                    
                    randEnemy_x=rand()%((right_limit-2)-(left_limit+2)+1)+(left_limit+2);//randEnemy_x in [(left_limit+2),(right_limit-2)]
                    enemys[i].SetPosition(&enemys[i],randEnemy_x,bullet_enemy_top);
                    
                    enemys[i].SetState(&enemys[i],APPEAR);
                }
                else
                {
                    enemys[i].SetPosition(&enemys[i],enemys[i].x,enemys[i].y);
                }
                enemys[i].Refresh(&enemys[i]);

            }

        }
        else
        {
            for(i=0;i<enemyNum;i++)
                {
                    enemys[i].Refresh(&enemys[i]);
                }
        }

        for(i=0;i<bulletNum;i++) //when bullet shoot enemy   
        {
            for(j=0;j<enemyNum;j++)
            {
                if(bullets[i].state==APPEAR && enemys[j].state==APPEAR && (bullets[i].x>=enemys[j].x-1 && bullets[i].x<=enemys[j].x+1) && bullets[i].y==enemys[j].y)
                {
                    bullets[i].SetState(&bullets[i],DISAPPEAR);
                    enemys[j].SetState(&enemys[j],DISAPPEAR);
                    bullets[i].Refresh(&bullets[i]);
                    enemys[j].Refresh(&enemys[j]);
                    score++;
                }
            }
            
        }

        DisplayInfo(); //display information at top right corner
        refresh();
         
        if(oddEven%TIMES==0)
        {
            enemyGenerateNum++;
        }
        
        oddEven++;

        usleep(TIME_GAP); //determine the speed of bullets and enemys

        for(i=0;i<enemyNum;i++)
        {
          enemys[i].Erasure(&enemys[i]);
        }


        for(i=0;i<bulletNum;i++)
        {
            bullets[i].Erasure(&bullets[i]);
        }

    }

    free(bullets);
    free(enemys);
}




void InitThread(void)
{
	pthread_t id;
    int ret;


    ret=pthread_create(&id,NULL,Thread,NULL);
 
    if(ret!=0)
	{
        printf ("Create pthread error!\n");
        exit (1);
    }

    return;
}

