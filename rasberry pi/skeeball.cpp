#include <termios.h>
#include <stdout>
#include "skeeball.h"

#define isPressed(x,y) ((1>>x)&y)


void skeeball::start()
{
   score = 0;
   balls = 6;
   state = game_state::Play;
   // Send "start" command to Arduino
   // Will triger ball release and resets as need on arduino
   write(tty_fd,"S",1);
   cout << "Game Start!\n";
}


void skeeball::run()
{
   updateButtons();
   if (state == game_state::Play) 
   {
   	if (isPressed(Btn::B1000L|Btn::B1000R,(unsigned int)buttons))
   		score += 1000;
   	else if (isPressed(Btn::B500,(unsigned int)buttons))
   		score += 500;
   	else if (isPressed(Btn::B400,(unsigned int)buttons))
   		score += 400;
   	else if (isPressed(Btn::B300,(unsigned int)buttons))
   		score += 300;
   	else if (isPressed(Btn::B200,(unsigned int)buttons))
   		score += 200;
   	else if (isPressed(Btn::B100,(unsigned int)buttons))
   		score += 100;

   	// Ball returned to ramp, -1 ball
   	// Return 
   	if (isPressed(Btn::BRET,(unsigned int)buttons)) 
   	{
   		// Oh man, out of balls, change mode
   		if (--balls == 0)
   			startPost();
   	}
   }
   else if (state == game_state::Attract) 
   {

   }
   else if (state == game_state::Post) 
   {
   
   }
}

void skeeball::startPost() {
	state = game_state::Post;
	//play music
	//display score
	//set timer
}


void skeeball::updateButtons() {
	unsigned char c = 'B';

	write(tty_fd,&c,1);
	read(tty_fd,buttons,2);

	cout << (unsigned int)buttons << "\n";
}


void skeeball::end()
{
  close(tty_fd);
}

void skeeball::initSerial() {
        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;
        tty_fd=open("/dev/arduino", O_RDWR | O_NONBLOCK);      
        cfsetospeed(&tio,B9600);            
        cfsetispeed(&tio,B9600);           
        tcsetattr(tty_fd,TCSANOW,&tio);
}

