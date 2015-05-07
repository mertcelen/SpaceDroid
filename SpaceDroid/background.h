//Stars in the background
void star(bool flag){
	int rotate;
	for (int i = 0; i<options.star_count; i++){
		if (stars[i].y <= -1 * WINDOW_HEIGHT / 2)
			stars[i].flag = false;
		if (flag == true){
			rotate = rand() % 2;
			if (rotate == 0) rotate = -1;
			stars[i].x = rand() % WINDOW_HEIGHT*rotate;
			rotate = rand() % 2;
			if (rotate == 0) rotate = -1;
			stars[i].y = rand() % WINDOW_WIDTH*rotate;
			stars[i].flag = true;
		}
		else if (stars[i].flag == false){
			rotate = rand() % 2;
			if (rotate == 0) rotate = -1;
			stars[i].x = rand() % WINDOW_HEIGHT*rotate;
			int random = rand() % 25;
			stars[i].y = WINDOW_WIDTH + random;
			stars[i].flag = true;
		}
		glBegin(GL_POINTS);
		glVertex2f(stars[i].x, stars[i].y);
		glEnd();
		stars[i].y--;
	}
}

//Displaying Health and mana bars, scores.
void stats(){
	glColor3f(1, 0, 0);
	glRectf(-200, 320, -200 + rem_life * 20, 350);
	glColor3f(0, 0, 1);
	glRectf(-200, 290, -200 + mana, 320);
	glColor3f(1, 1, 1);
	vprint(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 30, GLUT_BITMAP_HELVETICA_18, "SCORE : %d", score);
}

//Displaying menu, buttons, details etc.
void menu(){
	glColor3f(1, 1, 1);
	print(-75, 150, "SPACEDROID", GLUT_BITMAP_TIMES_ROMAN_24);
	if (selection == 1){
		glColor3f(0.5, 0.5, 0.5);
		glRectf(-120, 100, 120, 40);
		glColor3f(0.1, 0.1, 0.1);
		glRectf(-120, 30, 120, -30);
		glRectf(-120, -40, 120, -100);
		glRectf(-120,-110,120,-170);
	}
	else if (selection == 2){
		glColor3f(0.5, 0.5, 0.5);
		glRectf(-120, 30, 120, -30);
		glColor3f(0.1, 0.1, 0.1);
		glRectf(-120, 100, 120, 40);
		glRectf(-120, -40, 120, -100);
		glRectf(-120,-110,120,-170);
	}
	else if (selection == 3){
		glColor3f(0.5, 0.5, 0.5);
		glRectf(-120, -40, 120, -100);
		glColor3f(0.1, 0.1, 0.1);
		glRectf(-120, 100, 120, 40);
		glRectf(-120, 30, 120, -30);
		glRectf(-120,-110,120,-170);
	}
	else{
		glColor3f(0.5, 0.5, 0.5);
		glRectf(-120,-110,120,-170);
		glColor3f(0.1, 0.1, 0.1);
		glRectf(-120, 100, 120, 40);
		glRectf(-120, 30, 120, -30);
		glRectf(-120, -40, 120, -100);
	}
	glColor3f(0.5, 0.5, 0.5);
	glRectf(-1 * WINDOW_WIDTH / 2, -1 * WINDOW_HEIGHT / 2 + 30, WINDOW_WIDTH / 2, -1 * WINDOW_HEIGHT / 2);
	glColor3f(0, 0, 0);
	print(-1 * WINDOW_WIDTH / 2, -1 * WINDOW_HEIGHT / 2 + 10, " PRESS W/A/S/D TO NAVIGATE,SPACE KEY TO FIRE", GLUT_BITMAP_9_BY_15);


	glColor3f(1, 1, 1);
	if (pause){
		print(-90, 200, "GAME PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);
		print(-65, 60, "CONTINUE", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
		print(-65, 60, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);
	print(-50, -10, "OPTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
	print(-75, -77, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
	print(-28, -147, "EXIT", GLUT_BITMAP_TIMES_ROMAN_24);
}

//Basic Welcome Message
void welcomeMesg(){
	glColor3f(1,1,1);
	if(menu_vis){
		if(strcmp("Player",options.user_name)!=1){
			vprint(-75,300,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome %s!",options.user_name);
		}
		else{
				print(-150,300,"Please change your name in options",GLUT_BITMAP_HELVETICA_18);
		}
	}
}
