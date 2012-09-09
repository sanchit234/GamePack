#include <allegro.h>

#define MODE GFX_AUTODETECT
#define WIDTH 640
#define HEIGHT 480
#define MAXSPEED 2
#define BULLETSPEED 6

SAMPLE *samSong;

#define TAN makecol(255,242,169)
#define BURST makecol(255,189,73)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)

struct tagTank
{
    int x,y;
    int dir,speed;
    int score;

} tanks[2];
 
struct tagBullet
{
    int x,y;
    int alive;
    int xspd,yspd;

} bullets[2];

int gameover = 0;

BITMAP *tank_bmp[2][8];
BITMAP *bullet_bmp;
BITMAP *explode_bmp;

void drawtank(int num);
void erasetank(int num);
void movetank(int num);
void explode(int num, int x, int y);
void updatebullet(int num);
void fireweapon(int num);
void forward(int num);
void backward(int num);
void turnleft(int num);
void turnright(int num);
void getinput();
void setuptanks();
void score_tank(int);
void setupscreen();

void drawtank(int num)
{
    int dir = tanks[num].dir;
    int x = tanks[num].x-15;
    int y = tanks[num].y-15;

    draw_sprite(screen, tank_bmp[num][dir], x, y);
}

void erasetank(int num)
{
    int x = tanks[num].x-17;
    int y = tanks[num].y-17;

    rectfill(screen, x, y, x+33, y+33, BLACK);
}

void movetank(int num)
{
    int dir = tanks[num].dir;
    int speed = tanks[num].speed;

    switch(dir)
    {
        case 0:
            tanks[num].y -= speed;
            break;
        case 2:
            tanks[num].x += speed;
            break;
        case 4:
            tanks[num].y += speed;
            break;
        case 6:
            tanks[num].x -= speed;
            break;
    }

    if (tanks[num].x > SCREEN_W-22)
    {
        tanks[num].x = SCREEN_W-22;
        tanks[num].speed = MAXSPEED;
    }
    if (tanks[num].x < 22)
    {
        tanks[num].x = 22;
        tanks[num].speed = MAXSPEED;
    }
    if (tanks[num].y > SCREEN_H-22)
    {
        tanks[num].y = SCREEN_H-22;
        tanks[num].speed = MAXSPEED;
    }
    if (tanks[num].y < 32)
    {
        tanks[num].y = 32;
        tanks[num].speed = MAXSPEED;
    }
}

void explode(int num, int x, int y)
{
    int n;

    if (explode_bmp == NULL)
    {
        explode_bmp = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\explode.bmp", NULL);
    }
    
    for (n = 0; n < 5; n++)
    {
        rotate_sprite(screen, explode_bmp, 
            x + rand()%10 - 20, y + rand()%10 - 20, 
            itofix(rand()%255));

        rest(30);
    }

    circlefill(screen, x, y, 50, BLACK);   
}

void updatebullet(int num)
{
    int x = bullets[num].x;
    int y = bullets[num].y;

    if (!bullets[num].alive) return;
    
    rectfill(screen, x, y, x+10, y+10, BLACK);        

    bullets[num].x += bullets[num].xspd;
    bullets[num].y += bullets[num].yspd;
    x = bullets[num].x;
    y = bullets[num].y;

    if (x < 6 || x > SCREEN_W-6 || y < 20 || y > SCREEN_H-6)
    {
        bullets[num].alive = 0;
        return;
    }

    int tx = tanks[!num].x;
    int ty = tanks[!num].y;
    if (x > tx-16 && x < tx+16 && y > ty-16 && y < ty+16)
    {
        bullets[num].alive = 0;
            
        explode(num, x, y);
        score_tank(num);
    }
    else
    {
        draw_sprite(screen, bullet_bmp, x, y);

        textprintf(screen, font, SCREEN_W/2-50, 1, TAN, "B1 %-3dx%-3d  B2 %-3dx%-3d", bullets[0].x, bullets[0].y, bullets[1].x, bullets[1].y);
    }
}


void fireweapon(int num)
{
    int x = tanks[num].x;
    int y = tanks[num].y;

    bullet_bmp = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\bullet.bmp", NULL);

    if (!bullets[num].alive)
    {
        bullets[num].alive = 1;
        switch (tanks[num].dir)
        {
            case 0:
                bullets[num].x = x-2;
                bullets[num].y = y-22;
                bullets[num].xspd = 0;
                bullets[num].yspd = -BULLETSPEED;
                break;
            
            case 2:
                bullets[num].x = x+22;
                bullets[num].y = y-2;
                bullets[num].xspd = BULLETSPEED;
                bullets[num].yspd = 0;
                break;
            
            case 4:
                bullets[num].x = x-2;
                bullets[num].y = y+22;
                bullets[num].xspd = 0;
                bullets[num].yspd = BULLETSPEED;
                break;
            
            case 6:
                bullets[num].x = x-22;
                bullets[num].y = y-2;
                bullets[num].xspd = -BULLETSPEED;
                bullets[num].yspd = 0;
                break;
        }
    }
}

void forward(int num)
{
        tanks[num].dir = 0;
}

void backward(int num)
{
        tanks[num].dir = 4;
}

void turnleft(int num)
{
        tanks[num].dir = 6;
}

void turnright(int num)
{
        tanks[num].dir = 2;
}

void getinput()
{
    if (key[KEY_ESC])   
          gameover = 1;
    
    if (key[KEY_W])     
          forward(0);
    if (key[KEY_D])     
          turnright(0);
    if (key[KEY_A])     
          turnleft(0);
    if (key[KEY_S])     
          backward(0);
    if (key[KEY_SPACE]) 
          fireweapon(0);
            
    if (key[KEY_UP])    
          forward(1);
    if (key[KEY_RIGHT]) 
          turnright(1);
    if (key[KEY_DOWN])  
          backward(1);
    if (key[KEY_LEFT])  
          turnleft(1);
    if (key[KEY_ENTER]) 
          fireweapon(1);
   
    rest(30);
}

void score_tank(int player)
{
    int points = ++tanks[player].score;
    textprintf(screen, font, SCREEN_W-70*(player+1), 1, BURST, "P%d: %d", player+1, points);
}

void setuptanks()
{
    int n;
    
    tanks[0].x = 30;
    tanks[0].y = 40;
    tanks[0].speed = MAXSPEED;
    tanks[0].score = 0;
    tanks[0].dir = 4;

    tank_bmp[0][0] = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\tank1.bmp", NULL);
    
    for (n=1; n<8; n++)
    {
        tank_bmp[0][n] = create_bitmap(32, 32);
        clear_bitmap(tank_bmp[0][n]);
        rotate_sprite(tank_bmp[0][n], tank_bmp[0][0],0, 0, itofix(n*32));
    }

    tanks[1].x = SCREEN_W-30;
    tanks[1].y = SCREEN_H-30;
    tanks[1].speed = MAXSPEED;
    tanks[1].score = 0;
    tanks[1].dir = 0;
    
    tank_bmp[1][0] = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\tank2.bmp", NULL);    
    
    for (n=1; n<8; n++)
    {
        tank_bmp[1][n] = create_bitmap(32, 32);
        clear_bitmap(tank_bmp[1][n]);

        rotate_sprite(tank_bmp[1][n], tank_bmp[1][0], 0, 0, itofix(n*32));
    }
}


void setupscreen()
{
    /*set_color_depth(32);
    int ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }*/

    textprintf(screen, font, 1, 1, BURST, "Tank War - %dx%d", SCREEN_W, SCREEN_H);

  //  rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, TAN);
  //  rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, TAN);
   
}

void declare_winner_tanks()
{
     if(tanks[0].score==10)
     {
          tanks[0].score==0;
          textout_ex( screen, font, "Player 1 Wins!", 300, 230, makecol( 255, 0, 0), makecol( 0, 0, 0));       
          rest(2000);
          destroy_bitmap(tank_bmp[2][8]);
          destroy_bitmap(bullet_bmp);
          destroy_bitmap(explode_bmp);
          openscreen();
     }
     else if(tanks[1].score==10)
     {
          tanks[1].score==0;
          textout_ex( screen, font, "Player 2 Wins!", 300, 230, makecol( 255, 0, 0), makecol( 0, 0, 0));       
          rest(2000);
          destroy_bitmap(tank_bmp[2][8]);
          destroy_bitmap(bullet_bmp);
          destroy_bitmap(explode_bmp);
          stop_sample(samSong);
          openscreen();
     }
}

int tankwars()
{
    BITMAP *buffer = create_bitmap(640,480);
    rectfill(screen, 2, 14, SCREEN_W-3, SCREEN_H-3, BLACK);
    
    setupscreen();
    setuptanks();
    
    BITMAP *BGpong = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\BGpong.bmp", NULL);
    
    samSong = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\tankwars.wav");
    play_sample(samSong, 255, 128, 1000, 1);
    //game loop
    while(!gameover)
    {
        rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, TAN);
        rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, TAN);
   
        textprintf(screen, font, 0, SCREEN_H-10, WHITE, "DIRS %d , %d", tanks[0].dir, tanks[1].dir);
        
        erasetank(0);
        erasetank(1);
        
        movetank(0);
        movetank(1);

        drawtank(0);
        drawtank(1);

        updatebullet(0);
        updatebullet(1);
        
        if (keypressed())
            getinput();
        
        declare_winner_tanks();
        
        if(key[KEY_BACKSPACE])
        {
                      tanks[1].score=0;
                      tanks[0].score=0;
                      stop_sample(samSong);
                      openscreen();
        }
        
        if(key[KEY_ESC])
        {
                        exit(1);
        }
        
        rest(10);
    }
    return 0;
}
