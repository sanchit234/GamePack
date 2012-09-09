#include <allegro.h>

SAMPLE *samSong;

void init();
void deinit();

void init() 
{
	int depth, res;
	allegro_init();
	set_color_depth(32);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) 
    {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
}

void deinit() 
{
	clear_keybuf();
}

void openscreen()
{
    samSong = load_sample("C:\\Sanchit\\Game Pack\\Sprites\\openscreen.wav");
    play_sample(samSong, 255, 128, 1000, 1);
    
    int gameover=0;
    BITMAP *openscreen = load_bitmap("C:\\Sanchit\\Game Pack\\Sprites\\BG.bmp", NULL);
    
    draw_sprite(screen, openscreen, 0,0);
    textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
    textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
    textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
    textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
    textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
    	
    int j=1;
    
    while (!gameover) 
    {
          if(key[KEY_UP])
          {
                        if(j==1)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=1;                                 
                        }
                        else if(j==2)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=1;
                        }
                        else if(j==3)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=2;
                        }
                        else if(j==4)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=3;
                        }
                        else if(j==5)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 255, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=4;
                        }                             
                        rest(200);
          }
          if(key[KEY_DOWN])
          {
                        if(j==1)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));                                 
                                 j=2;
                        }
                        else if(j==2)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 255, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=3;
                        }
                        else if(j==3)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 255, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 j=4;
                        }
                        else if(j==4)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 255, 0, 0));
                                 j=5;
                        }
                        else if(j==5)
                        {
                                 textout_ex( screen, font, "Ping Pong", 280, 230, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Plkachu's Stick", 280, 240, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Save City", 280, 250, makecol( 255, 255, 255), makecol( 0, 0, 0)); 
                                 textout_ex( screen, font, "Tank Fighters", 280, 260, makecol( 255, 255, 255), makecol( 0, 0, 0));
                                 textout_ex( screen, font, "Exit", 280, 280, makecol( 255, 255, 255), makecol( 255, 0, 0));
                                 j=5;
                        }
                        rest(200);
          }                        
          
          if(key[KEY_ESC]|| key[KEY_F4])
          {
                exit(1);
          }
          if(key[KEY_ENTER])
          {
               if(j==1)
               {
                   stop_sample(samSong);    
                   pingpong();
               }
               else if(j==2)
               {
                   stop_sample(samSong);                    
                   pikachu_sticks();
               }
               else if(j==3)
               {
                   stop_sample(samSong);
                   savecity();
               }
               else if(j==4)
               {
                   stop_sample(samSong);                     
                   tankwars();     
               }
               else if(j==5)
                   exit(1);
         }
	}
}
