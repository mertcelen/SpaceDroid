//For drawing circle
void circle(int x, int y, int r){
#define PI 3.1415
	float angle;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

//For write string on screen
void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)

	{
		glutBitmapCharacter(font, string[i]);
	}
}

//For write formatted string on screen
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

//For getting keydown events and make it meaningful
void onKeyDown(unsigned char key, int x, int y){
	if (option_vis == true){
		if (key != 8){
		options.user_name[strlen(options.user_name)] = key;
		printf("%s\n", options.user_name);
		}
		else{
			char temp[10];
			strncpy(temp, options.user_name, strlen(options.user_name) - 2);
			printf("%s\n", options.user_name);
		}
		if (key == 'a'){//for some reason, esc key not working, so I decided to put a
			menu_vis = true;
			option_vis = false;
		}
	}
	if (menu_vis == false){
		switch (key) {
		case ' ': rocketCreate(); break;
		case 'w':
		case 'W': up = true; break;
		case 's':
		case 'S': down = true; break;
		case 'a':
		case 'A': left = true; break;
		case 'd':
		case 'D': right = true; break;
		case 27:
			menu_vis = true;
			pause = true;
			break;
		case 13:
			if (hs_vis == true){
				hs_vis = false;
				pause = false;
				menu_vis = true;
			}
			break;
		}
	}
	else{
		switch (key) {
		case 'W':
		case 'w':
			if (selection == 1)
				selection = 4;
			else if (selection == 2)
				selection = 1;
			else if (selection == 3)
				selection = 2;
			else
				selection = 3;
			break;
		case 's':
		case 'S':
			if (selection == 1)
				selection = 2;
			else if (selection == 2)
				selection = 3;
			else if (selection == 3)
				selection = 4;
			else
				selection = 1;
			break;
		case 13:
			if (selection == 4)
					exit(0);
			else if (selection == 1){
				if (!pause)
					reset();
					pause = false;
					menu_vis = false;
				}
			else if (selection == 3){
					hs_vis = true;
					pause = true;
					menu_vis = false;
				}
			else if(selection==2){
					option_vis = true;
					menu_vis = false;
					pause = true;
				}
			break;
		case 27:
			if (pause){
				menu_vis = false;
				pause = false;
			}break;
		}
	}
	glutPostRedisplay();
}

//Function when user unpressed any key
void onKeyUp(unsigned char key, int x, int y){
	switch (key){
	case 'w': up = false; break;
	case 'W': up = false; break;
	case 's': down = false; break;
	case 'S': down = false; break;
	case 'a': left = false; break;
	case 'A': left = false; break;
	case 'd': right = false; break;
	case 'D': right = false; break;
	}

	glutPostRedisplay();
}

//To resize window if user want to do
void onResize(int w, int h){
	// To setup coordinate system
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

//Main Timer loop of Glut
#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	if (menu_vis == false && pause == false){
		moveAndroid();
		if (rock_time%ROCK_FREQUENCY == 0)
			createRock();
		effect++;
		mana++;
		if (mana >= (cur_rocket)* 33) mana = (cur_rocket)* 33;
		if (cur_rocket == 0) mana = 33;
		if (effect > 1000) effect = 0;
		if (explosion_f == true)
			explo++;
	}
	glutPostRedisplay();
}
#endif

//For getting special keydown(like F1,F2) events and make it meaningful
void onSpecialKeyUp(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_UP:
		up = false; break;
	case GLUT_KEY_DOWN:
		down = false; break;
	case GLUT_KEY_LEFT:
		left = false; break;
	case GLUT_KEY_RIGHT:
		right = false; break;
	}
	glutPostRedisplay();
}

//Function when user unpressed special keys
void onSpecialKeyDown(int key, int x, int y)
{
	if (option_vis == true){
		switch (key) {
		case GLUT_KEY_LEFT:
			if (option_vis){
				if (options_selection != 1)
					options_selection--;
				else
					options_selection = 3;
			}break;
		case GLUT_KEY_RIGHT:
			if (option_vis){
				if (options_selection != 3)
					options_selection++;
				else
					options_selection = 1;
			}break;
		}
	}
	if (menu_vis == false){
		switch (key) {

		case GLUT_KEY_UP:
			up = true; break;
		case GLUT_KEY_DOWN:
			down = true; break;
		case GLUT_KEY_LEFT:
			left = true; break;
		case GLUT_KEY_RIGHT:
			right = true; break;
		case 27:
			menu_vis = true;
			pause = true;
			break;
		}
	}
	else{
		switch (key) {
		case GLUT_KEY_UP:
			if (selection == 1)
				selection = 4;
			else if (selection == 2)
				selection = 1;
			else if (selection == 3)
				selection = 2;
			else
				selection = 3;
			break;
		case GLUT_KEY_DOWN:
			if (selection == 1)
				selection = 2;
			else if (selection == 2)
				selection = 3;
			else if (selection == 3)
				selection = 4;
			else
				selection = 1;
			break;
		case 13:
			if (selection == 3)
				exit(0);
			else if (selection == 1){
				if (!pause)
					reset();
				pause = false;
				menu_vis = false;
			}
			break;
		case 27:
			if (pause){
				menu_vis = false;
				pause = false;
			}break;
		}
	}
	glutPostRedisplay();
}
