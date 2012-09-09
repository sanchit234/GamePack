#include <allegro.h>
#include <time.h>

BITMAP *buffer;
BITMAP *bmpGameBg;
BITMAP *bmpPlayer;
BITMAP *bmpStick;

SAMPLE *samSong;
SAMPLE *samScore;
  
int m = 32, n = 32; 

int M() 
{
     return m; 
}

int N() 
{ 
     return n; 
}

void generateNewCoordinates()
{
  int tempM;
  int tempN;

  tempM = ( (int)rand() % 18 + 1 ) * 32;
  tempN = ( (int)rand() % 14 + 1 ) * 32;

  m = tempM;
  n = tempN;

}

int speed = 1.0, direction = 2, iTotalPicked = 0, x = 640/2 - 32/2, y = 480/2 - 32/2; 
int prev_x, prev_y, prev_dir;

int X() 
{ 
    return x; 
}

int Y() 
{ 
    return y; 
}

int Direction() 
{ 
    return direction; 
}

void update_prev() 
{ 
     prev_x = x; 
     prev_y = y; 
     prev_dir = direction; 
}

float Speed() 
{ 
      return speed; 
}

int TotalPicked() 
{ 
    return iTotalPicked; 
}

void incrementTotalPicked() 
{ 
     iTotalPicked++; 
}

void move(int dir)
{
  if (dir == 2) 
  {
    if (y < 448) { y += speed; }
    direction = 2;
  }
  else if (dir == 4)
  {
    if (x > 0) { x -= speed; }
    direction = 4;
  }
  else if (dir == 6)
  {
    if (x < 608) { x += speed; }
    direction = 6;
  }
  else if (dir == 8)
  {
    if (y > 10) { y -= speed; }
    direction = 8;
  }
}

void increaseSpeed()
{
    if ( speed < 100 ) 
         speed += 1.0; 
}

void draw(BITMAP *buffer, BITMAP *bmpAlec)
{
        int tx = x;
        int ty = y;
        int tx2 = x;
        int ty2 = y;
        int tx3 = x;
        int ty3 = y;
        BITMAP *temp = create_bitmap(64, 64);
        rectfill(temp, 0, 0, 64, 64, makecol(255, 0, 255));
            int i=speed;
            if (Direction() == 2)
            {
                    ty -= speed*i*2;
                    ty2 -= speed*i*4;
                    ty3 -= speed*i*6;
                masked_blit(bmpPlayer, temp, 0,0, 0, 0,64,64);
            }
            else if (Direction() == 4)
            {
                    tx += speed*i*2;
                    tx2 += speed*i*4;
                    tx3 += speed*i*6;
                masked_blit(bmpPlayer, temp, 32*2,0, 0, 0,64,64);
            }
            else if (Direction() == 6)
            {
                    tx -= speed*i*2;
                    tx2 -= speed*i*4;
                    tx3 -= speed*i*6;
                masked_blit(bmpPlayer, temp, 64*2,0, 0, 0,64,64);
            }
            else if (Direction() == 8)
            {
                    ty += speed*i*2;
                    ty2 += speed*i*4;
                    ty3 += speed*i*6;
                masked_blit(bmpPlayer, temp, 96*2,0, 0, 0,64,64);
            }
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            set_trans_blender(0, 0, 0, 128);
            if ( speed > 6 ) { draw_trans_sprite(buffer, temp, tx3, ty3); }
            if ( speed > 4 ) { draw_trans_sprite(buffer, temp, tx2, ty2); }
            if ( speed > 2 ) { draw_trans_sprite(buffer, temp, tx, ty); }
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

    if (Direction() == 2)      { masked_blit(bmpPlayer, buffer, 0,0, x, y,64,64); }
    else if (Direction() == 4) { masked_blit(bmpPlayer, buffer, 32*2,0, x, y,64,64); }
    else if (Direction() == 6) { masked_blit(bmpPlayer, buffer, 64*2,0, x, y,64,64); }
    else if (Direction() == 8) { masked_blit(bmpPlayer, buffer, 96*2,0, x, y,64,64); }
}

volatile long speed_counter = 0;

void increment_speed_counter()
{
    speed_counter++;
}


void initializePikachuSticks()
{
  LOCK_VARIABLE(speed_counter);
  LOCK_FUNCTION(increment_speed_counter);
  install_int_ex(increment_speed_counter,BPS_TO_TIMER(120));
  srand((unsigned)time(NULL));   
}

int thereIsCollision()
{
  if (!( (Y()+56 >  N()+2 ) && (Y()+35 < N()+28 ) && (X()+43 > M()+2 ) && (X()+20 < M()+28 )))
  {
       return 0;
  }
  else 
  { 
       return 1; 
  }
}

int pikachu_sticks()
{
  initializePikachuSticks();
  
  buffer = create_bitmap(640,480);
  bmpGameBg = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\grass.bmp",NULL);
  bmpPlayer = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\player.bmp",NULL);
  bmpStick = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\stick.bmp",NULL);

  samSong = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\BGpikachu.wav");
  samScore = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\stick.wav");
  int song_frequency = 1000;

  generateNewCoordinates();

  play_sample(samSong, 255, 128, song_frequency, 1);

  while (!key[KEY_ESC])  
  {
      draw_sprite(buffer, bmpGameBg, 0, 0);
      textprintf(buffer,font,2,2,makecol(255,255,255), "Sticks Collected: %i", TotalPicked() );
      if ( Speed() == 1 )
      {
          textprintf(buffer,font,200,2,makecol(255,255,255), "Speed: %0.0f mph", Speed() );
      }
      else
      {
          textprintf(buffer,font,200,2,makecol(255,255,255), "Speed: %0.0f mph", Speed()*7 );
      }
      textprintf(buffer,font,408,2,makecol(255,255,255), "Rank: ");
      if (TotalPicked() < 10) 
      { 
           textprintf(buffer,font,452,2,makecol(255,255,255), "Nubsaws"); 
      }
      else if (TotalPicked() >= 10 && TotalPicked() < 20) 
      { 
           textprintf(buffer,font,452,2,makecol(255,255,255), "Amateur"); 
      }
      else if (TotalPicked() >= 20 && TotalPicked() < 30) 
      { 
           textprintf(buffer,font,452,2,makecol(255,200,0), "Stick Picker"); 
      }
      else if (TotalPicked() >= 30 && TotalPicked() < 40) 
      { 
           textprintf(buffer,font,452,2,makecol(0,200,255), "Mr. Awesome"); 
      }
      else if (TotalPicked() >= 40 && TotalPicked() < 50) 
      { 
           textprintf(buffer,font,452,2,makecol(175,130,0), "Over the Hill"); 
      }
      else if (TotalPicked() >= 50) 
      { 
           textprintf(buffer,font,452,2,makecol(255,0,0), "No life"); 
      }

      draw_sprite(buffer, bmpStick, M(), N() );

      draw(buffer, bmpPlayer);

      if (TotalPicked() == 10) 
      { 
           textprintf(buffer, font, X() - 110, Y() - 10,makecol(255,255,255), "Yay! Just infinite more to go!" ); 
      }
      else if (TotalPicked() == 50)
      {
           textprintf(buffer, font, X() - 110, Y() - 17,makecol(255,0,0), "You should probably stop now." );
           textprintf(buffer, font, X() - 100, Y() - 10,makecol(255,0,0), "This game never ends." );
      }
    
    {
         
        
        if (key[KEY_DOWN] || key[KEY_S])
        {
                    move(2);
                    update_prev();
        }               //the integer is which direction to move.  Look at the numpad to figure out.
        else if (key[KEY_LEFT] || key[KEY_A])
        {
                    move(4);
                    update_prev();
        }
        else if (key[KEY_RIGHT] || key[KEY_D])
        {
                    move(6);
                    update_prev();
        }
        else if (key[KEY_UP] || key[KEY_W])
        {
                    move(8);
                    update_prev();
        }
        
        else if (key[KEY_Z]) 
        { 
             generateNewCoordinates(); 
             rest(100);
        }
        else if (key[KEY_X]) 
        { 
             incrementTotalPicked(); 
             rest(100);
        }
        else if (key[KEY_C]) 
        { 
             increaseSpeed();
             rest(100);
        }
        else if (key[KEY_ESC]) 
             exit(0); 
        else if (key[KEY_BACKSPACE])
        {
             stop_sample(samSong);
             speed=1.0;
             iTotalPicked = 0;
             openscreen();
        }
             
        if (thereIsCollision())
        {
          play_sample(samScore, 255, 128, 1000, 0);
          generateNewCoordinates();
          incrementTotalPicked();
          if ( TotalPicked() % 10 == 0 )
          {
              song_frequency += 25;
              stop_sample(samSong);
              play_sample(samSong, 255, 128, song_frequency, 1);
              increaseSpeed();
          }
        }
      }
    
    acquire_screen();
    blit(buffer, screen, 0, 0, 0, 0, 640, 480);
    clear_bitmap(buffer);
    release_screen();
  }
  destroy_sample(samSong);
  destroy_sample(samScore);
  destroy_bitmap(buffer);

  return 0;
}
