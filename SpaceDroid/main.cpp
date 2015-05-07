#define _CRT_SECURE_NO_WARNINGS												//To disable warnings
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")		//To hide terminal

//Default Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <GL/glut.h>
#include "queue.h"

//Custom Libraries
#include "definitions.h"
#include "glutfunctions.h"
#include "options.h"
#include "background.h"
#include "objects.h"
#include "highscores.h"

//Reset everything in order to restart game
void reset(){
	for (int i = 0; i<MAX_ROCKET; i++){
		rocket[i].flag = false;
		rocket[i].x = 0;
		rocket[i].y = 0;
	}
	for (int i = 0; i<ROCK_COUNT; i++){
		rock[i].flag = false;
		rock[i].x = 0;
		rock[i].y = 0;
	}
	android.center.x = 0;
	android.center.y = -WINDOW_HEIGHT / 4;
	rem_life = ANDROID_LIFE_COUNT;
	score = 0;
	cur_rocket = MAX_ROCKET;
	mana = cur_rocket * 33;

}

//Main Display Loop
void display(){
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	star(false);
	if (!menu_vis && !hs_vis &&!option_vis){
		drawAndroid();
		drawRocks();
		rocketFire();
		rocketHitCheck();
		checkAndroidHit();
		stats();
	}
	else if (!option_vis && !hs_vis){
		menu_vis = true;
		menu();
		welcomeMesg();
	}
	if (option_vis==true){
		menu_vis = false;
		hs_vis = false;
		optionsf();
	}
	if (hs_vis)
		displayScores();
	if (rem_life != 0)
		rock_time++;
	else if(!hs_vis){
		glColor3f(1, 1, 1);
		vprint(-140, 120, GLUT_BITMAP_HELVETICA_18, "GAME OVER! YOUR SCORE IS %d", score);
		if (score_flag){
			highScore(score);
			score_flag = false;
		}
		menu_vis = true;
	}
	glutSwapBuffers();

}

//Basic glut functions definitions, main loop starter
int  main(int argc, char *argv[]){
	reset();
	initialize_q(&starqueue);
	star(true);
	fileOpen();
	optionsf();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("SpaceDroid v1.0 by Mert CELEN");
	glutDisplayFunc(display);
	glutReshapeFunc(onResize);
	welcomeMesg();
	glutSpecialUpFunc(onSpecialKeyUp);
	glutSpecialFunc(onSpecialKeyDown);
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif
	glutMainLoop();
	return(0);
}
