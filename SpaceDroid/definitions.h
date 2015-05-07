//some function definitions
void moveAndroid();
void rocketCreate();
void createRock();
void reset();

//Definitions
#define WINDOW_WIDTH  400		// window width
#define WINDOW_HEIGHT 700		// window height
#define TIMER_PERIOD   16		// 16 for 60 FPS
#define TIMER_ON      1     	// 0:disable timer, 1:enable timer
#define ANDROID_SPEED 15		// speed of android
#define ROCK_COUNT 10			// max rock amount in a scene
#define ROCK_FREQUENCY 75		// less = higher
#define STAR_COUNT 1024			// stars in the scene
#define ROCK_START_SPEED 5		// default rock speed
#define ROCKET_SPEED 50			// speed of rocket
#define MAX_ROCKET 3			// max rocket amount in a scene,
#define ANDROID_LIFE_COUNT 5	// android life count

//Structures

	//Basic point structure
typedef struct {
	int x, y;
	bool flag;
}point_t;

	//Basic option structure for settings
typedef struct {
	int star_count,difficulty;
	char user_name[10];
}options_t;

	//Android structure
typedef struct {
	point_t center;
	int speed, check;
}android_t;

	//Highscores structure
typedef struct {
	int score, count;
	char name[10];
}highscores_t;



FILE *highscore;				//File for highscores
highscores_t scores[10];		//In order to fast response, highscores will be kept in array
android_t android;				//Basic character definition
point_t rocket[MAX_ROCKET],		//Rockers position, status array.
rock[ROCK_COUNT],				//Rocks position, status array.
stars[STAR_COUNT];				//Status position, status array.
queue_t starqueue;				//Stars qeueu
options_t options = { 1000, 1, "Player" };

bool left, right, up, down,		// default booleans for moving character
menu_vis = true,				//Is menu visibility on or off boolean
pause,							//Is game paused or not
explosion_f,					//Basic explosion effect
option_vis = false,				//Check if user opened options
score_flag = true,				//flag for update score only once
hs_vis = false;					//Is high scores is shown or not

int rock_time = 0,				//Basic variable that helps rocks spawn rate. Basicly rocks spawn if rock_time % ROCK_FREQUENCY=0
rock_speed = ROCK_START_SPEED,	//Rock start speed defined before, but this variable helps level system by changing its speed
score = 0,						//Score definition, it should be 0 at start
explo = 0,						//It's explosion timeout, work in progress
mana,							//Variable to store mana as variable
effect = 0,						//It's effect of android's rocket, whenever effect reachs %10, effect shown up.
rem_life = ANDROID_LIFE_COUNT,	//Remaning life variable, it's redefine because it had to.
selection = 1,					//To deciding which button chosed in menu
cur_rocket = MAX_ROCKET,		//How many rockets fired
options_selection = 1;			//options selection counter