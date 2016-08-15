class skeeball {

	
	unsigned char buttons[2];
	int score,
		highscore,
		balls;

	enum game_state
	{
		Play = 0, Attract,Post
	};

	enum Btn
	{
		B1000L = 0x0000,
		B1000R = 0x0001,
		B500   = 0x0002, 
		B400   = 0x0004, 
		B300   = 0x0008, 
		B200   = 0x0010,
		B100   = 0x0020,
		BRET   = 0x0040,
		SELECT = 0x0080,
		START  = 0x0100,
		SCORED = 0x003F,
		ANY    = 0xFFFF,

	};

	game_state state = game_state::Attract;

	public:
		skeeball () {


		}
		void run();
		void end();
	private:
		struct termios tio;
		int tty_fd;
		void initSerial();
		void updateButtons();
		void loadHighScore();
		void saveHighScore();
		void startPost();
		void startAttract();
};

