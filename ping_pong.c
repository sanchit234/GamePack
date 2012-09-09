#include <allegro.h>
#include <time.h>

SAMPLE *samSong;

int ball_x = 320;
int ball_y = 240;

int ball_tempX = 320;
int ball_tempY = 240;

int p1_x = 20;
int p1_y = 210;

int p1_tempX = 20;
int p1_tempY = 210;

int p2_x = 620;
int p2_y = 210;

int p2_tempX = 620;
int p2_tempY = 210;

int for_scoring,scored; 
int count1=0,count2=0;

time_t secs; 
int dir;     

BITMAP *buffer; 

void moveBall()
{
    ball_tempX = ball_x;
    ball_tempY = ball_y;

    if (dir == 1 && ball_x > 5 && ball_y > 5)
    { 
         if( ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60)
         {
                  dir = rand()% 2 + 3;
         }
         else
         {    
                 --ball_x;
                 --ball_y;
         }    
              
    } 
    else if (dir == 2 && ball_x > 5 && ball_y < 475)
    {
         if( ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60)
         {
                  dir = rand()% 2 + 3;
         }
         else
         {    
                 --ball_x;
                 ++ball_y;
         }

    } 
    else if (dir == 3 && ball_x < 635 && ball_y > 5)
    {
         if( ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60)
         {
                  dir = rand()% 2 + 1;
         }
         else
         {    
                 ++ball_x;
                 --ball_y;
         }
    } 
    else if (dir == 4 && ball_x < 635 && ball_y < 475)
    {
         if( ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60)
         {
                  dir = rand()% 2 + 1;
         }
         else
         {    
                 ++ball_x;
                 ++ball_y;
         }

    } 
    else 
    { 
        if (dir == 1 || dir == 3)    
             ++dir;
        else if (dir == 2 || dir == 4)    
             --dir;
    }    
    acquire_screen();
  //  circlefill ( buffer, ball_tempX, ball_tempY, 5, makecol( 0, 0, 0));
    circlefill ( buffer, ball_x, ball_y, 5, makecol( 255, 255, 255));
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
    rest(5);
}    

void p1Move()
{ 
    p1_tempY = p1_y;

    if( key[KEY_W] && p1_y > 0)
    { 
        --p1_y;          
    } 
    else if( key[KEY_S] && p1_y < 420)
    { 
        ++p1_y;         
    }     
    acquire_screen();
   // rectfill( buffer, p1_tempX, p1_tempY, p1_tempX + 10, p1_tempY + 60, makecol ( 0, 0, 0));
    rectfill( buffer, p1_x, p1_y, p1_x + 5, p1_y + 60, makecol ( 255, 0, 0));
    rectfill( buffer, p1_x +5 , p1_y , p1_x + 10, p1_y + 60, makecol ( 0, 0, 0));
    release_screen();
}  

void p2Move()
{ 
    p2_tempY = p2_y;

    if( key[KEY_UP] && p2_y > 0)
    { 
        --p2_y;          
    }
    else if( key[KEY_DOWN] && p2_y < 420)
    {
        ++p2_y;         
    }     
    acquire_screen();
    //rectfill( buffer, p2_tempX, p2_tempY, p2_tempX + 10, p2_tempY + 60, makecol ( 0, 0, 0));
    rectfill( buffer, p2_x, p2_y, p2_x + 5, p2_y + 60, makecol ( 0, 0, 0));
    rectfill( buffer, p2_x+6, p2_y , p2_x + 10, p2_y + 60, makecol ( 255, 0, 0));
    release_screen();
}    

void startNew()
{
    clear_keybuf();
    readkey();
    clear_to_color( buffer, makecol( 0, 0, 0));
    ball_x = 320;
    ball_y = 240;

    p1_x = 20;
    p1_y = 210;

    p2_x = 620;
    p2_y = 210;
}    

void checkWin()
{
    if ( ball_x < p1_x)
    {
        for_scoring=2;
        scored=1;
    }
    else if ( ball_x > p2_x)
    {
        for_scoring=1;
        scored=1;
    }    
    else
        scored=0;
}    

void declare_winner()
{
    if(count1==5)
    {
          textout_ex( screen, font, "Player 1 Wins!", 280, 150, makecol( 255, 0, 0), makecol( 0, 0, 0)); 
          rest(2000);
          count1=0;
          count2=0;
          ball_x=320;
          ball_y=240;
          p1_x = 20;
          p1_y = 210;
          p2_x = 620;
          p2_y = 210;
    }
    else if(count2==5)
    {
          textout_ex( screen, font, "Player 2 Wins!", 280, 150, makecol( 255, 0, 0), makecol( 0, 0, 0));       
          rest(2000);
          count1=0;
          count2=0;
          ball_x=320;
          ball_y=240;
          p1_x = 20;
          p1_y = 210;
          p2_x = 620;
          p2_y = 210;
    }
}
void setupGame()
{ 
    acquire_screen();
    rectfill( buffer, p1_x, p1_y, p1_x + 10, p1_y + 60, makecol ( 0, 0, 255));
    rectfill( buffer, p2_x, p2_y, p2_x + 10, p2_y + 60, makecol ( 0, 0, 255));  
    circlefill ( buffer, ball_x, ball_y, 5, makecol( 128, 255, 0));
    draw_sprite( screen, buffer, 0, 0);
    release_screen();
    
    time(&secs);
    srand( (unsigned int)secs);
    dir = rand() % 4 + 1;           
}    

void pingpong_score()
{
     if(for_scoring==2)
           count2++;
     else if(for_scoring==1)
           count1++;   
     textprintf(screen,font,60,2,makecol(255,255,255), "P1=%d", count1);
     textprintf(screen,font,540,2,makecol(255,255,255), "P2=%d", count2);
     if(count1==5 || count2==5)
     {
           declare_winner();
           stop_sample(samSong);
           openscreen();
     }
     startNew();
}

int pingpong()
{
    buffer = create_bitmap( 640, 480); 
    BITMAP *BGpong = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\BGpong.bmp", NULL);
    
    
    samSong = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\pingpong.wav");
    play_sample(samSong, 128, 128, 1000, 1);
    setupGame();

    while( !key[KEY_ESC])
    {
        draw_sprite(buffer, BGpong, 0,0);
        textprintf(buffer,font,60,2,makecol(255,255,255), "P1=%d", count1);
        textprintf(buffer,font,540,2,makecol(255,255,255), "P2=%d", count2);        
        p1Move();
        p2Move();
        moveBall();
        
        checkWin();
        
        if(scored==1)
                pingpong_score();
        
        if(key[KEY_BACKSPACE])
        {
                      count1=0;
                      count2=0;
                      ball_x=320;
                      ball_y=240;
                      p1_x = 20;
                      p1_y = 210;
                      p2_x = 620;
                      p2_y = 210;
                      stop_sample(samSong);
                      openscreen();
        }              
    }    
    return 0;
}
