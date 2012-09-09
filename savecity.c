#include <conio.h>
#include <stdlib.h>
#include <allegro.h>

#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)
#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define SMOKE makecol(140,130,120)

typedef struct POINT
{
        int x,y;
}POINT;

POINT points[2000];

int curpoint,totalpoints;

BITMAP *buffer;
BITMAP *crosshair;
BITMAP *city;

SAMPLE *samSong;
SAMPLE *samExplosion2;
SAMPLE *samExplosion1;

int x1,y1,x2,y2;
int done=0;int destroyed=1;
int n;
int mx,my,mb;
int score = -1;

void updatescore()
{
         score++;
         textprintf_right(buffer,font,SCREEN_W-5,1,WHITE, "SCORE: %d   ", score);
}

void explosion1(BITMAP *bmp, int x,int y,int finalcolor)
{
     int color,size;
     for (n=0; n<20; n++)
     {
                color = makecol(rand()%255,rand()%255,rand()%255);
                size = 20+rand()%20;
                circlefill(bmp, x, y, size, color);
                rest(2);
     }
     circlefill(bmp, x, y, 40, finalcolor);
}

void explosion2(BITMAP *bmp, int x,int y,int finalcolor)
{
     int color,size;
     for (n=0; n<20; n++)
     {
                color = makecol(rand()%255,rand()%255,rand()%255);
                size = 20+rand()%20;
                circlefill(bmp, x, y, 350, color);
                rest(2);
     }
     circlefill(bmp, x, y, 350, finalcolor);
}

void doline(BITMAP *bmp, int x, int y, int d)
{
     points[totalpoints].x = x;
     points[totalpoints].y = y;
     totalpoints++;
}

void firenewmissile()
{
     destroyed=0;
     totalpoints = 0;
     curpoint = 0;

     x1 = rand() % (SCREEN_W-1);
     y1 = 20;

     x2 = rand() % (SCREEN_W-1);
     y2 = SCREEN_H-50;

     do_line(buffer,x1,y1,x2,y2,0,&doline);
}

void movemissile()
{     
     samExplosion2 = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\explosion2.wav");
 
     int x = points[curpoint].x ;
     int y = points[curpoint].y ;
 
     scare_mouse();

     rectfill(buffer,x-6,y-3,x+6,y+1,BLACK);

     if (getpixel(screen,x,y) == GREEN)
     {  
            destroyed++;
            updatescore();
            rectfill(buffer, 2, 14, 636, 352, BLACK);
     }
     else
     {
          putpixel(buffer,x,y-3,SMOKE);
          circlefill(buffer,x,y,2,BLUE);
     }
         
     unscare_mouse();
     
     curpoint++;
     if (curpoint >= totalpoints)
     {        
          play_sample(samExplosion2, 128, 128, 1000, 0);
          destroyed++;

          explosion2(screen, x, y, BLACK);

          textout_ex( screen, font, "Game Over", 300, 230, makecol( 255, 0, 0), makecol( 0, 0, 0));       
          rest(2000);
          textprintf(screen,font,300,245,makecol(255,255,255), "Final Score=%d", score);
          rest(2000);
          
          stop_sample(samSong);
          stop_sample(samExplosion2);
          
          score=-1;
          
          openscreen();
     }
}

int savecity()
{
     buffer = create_bitmap(640,480);
     
     samSong = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\savecity.wav");
     samExplosion1 = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\explosion1.wav");

     textout(buffer,font,"Save City (ESC to quit)",0,1,WHITE);

     updatescore();

//     rect(buffer, 0, 12, SCREEN_W-2, SCREEN_H-2, RED);

     city = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\city.bmp", NULL);
     for (n = 0; n < 5; n++)
         masked_blit(city, buffer, 0, 0, 20+n*120, SCREEN_H-city->h-2, city->w, city->h);

     crosshair = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\crosshair.bmp", NULL); 
     set_mouse_sprite(crosshair);
     set_mouse_sprite_focus(15,15);
     show_mouse(buffer); 
     
     play_sample(samSong, 128, 128, 1000, 1);
     
     while (!key[KEY_ESC])
     {
           //above the red was border get destroyed
           rect(buffer, 0, 12, SCREEN_W-2, SCREEN_H-2, RED);
           
           mx = mouse_x;
           my = mouse_y;
           mb = (mouse_b & 1);
     
           if (destroyed)
                firenewmissile();
     
           if (mb)
           {
                explosion1(screen,mx,my,GREEN);
                play_sample(samExplosion1, 40, 128, 1000, 0);
           }
           
           movemissile();
           
           blit(buffer,screen,0,0,0,0,640,480);
           
           if(key[KEY_BACKSPACE])
           {    
                 score=-1;        
                 firenewmissile();
                 stop_sample(samSong);

                 openscreen();        
           }
              
           if(key[KEY_ESC])
           {
                           exit(1);
           }
           
                         
           if(score>=0 && score <5)
                 rest(10);
           else if(score>=5 && score<10)
                 rest(9);            
           else if(score>=10 && score<15)
                 rest(8);            
           else if(score>=15 && score<20)
                 rest(7);            
           else if(score>=20 && score<25)
                 rest(6);            
           else if(score>=25 && score<30)
                 rest(5);            
           else if(score>=30 && score<35)
                 rest(4);            
           else if(score>=35 && score<40)
                 rest(3);
           else if(score>=40 && score<45)
                 rest(2);
           else if(score>=45)
                 rest(1);            
                                   
     }
     
     set_mouse_sprite(NULL);
     destroy_bitmap(city);
     destroy_bitmap(crosshair);
    // openscreen();
     return 0;
}
