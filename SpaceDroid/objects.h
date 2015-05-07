//Explosion effect, x y is given and explosion will pop up
void explosion(int x, int y){
	explosion_f = true;
	while (explo != 500){
		glColor3f(1, 0, 0);
		circle(x, y, explo / 10);
		explo++;
	}
	explosion_f = false;
	explo = 0;
}

//Rocket functions for and move rocket and destroy if out of boundries
void rocketFire(){
	for (int i = 0; i < MAX_ROCKET; i++){
		if (rocket[i].flag && mana >= 33){
			glColor3f(1, 0, 0);
			glRectf(rocket[i].x - 2, rocket[i].y, rocket[i].x + 2, rocket[i].y + 20);
			rocket[i].y += 10;
			if (rocket[i].y >= WINDOW_HEIGHT / 2 && rocket[i].flag != false){
				rocket[i].flag = false;
				cur_rocket++;
			}

		}
	}
}

//For creating rocket
void rocketCreate(){
	for (int i = 0; i < MAX_ROCKET; i++){
		if (rocket[i].flag == false){
			rocket[i].x = android.center.x;
			rocket[i].y = android.center.y + 50;
			rocket[i].flag = true;
			cur_rocket--;
			break;
		}
	}
}

//For creating rock
void createRock(){
	int x, rotate;
	for (int i = 0; i < ROCK_COUNT; i++){
		if (rock[i].flag == false){
			x = rand() % WINDOW_WIDTH / 2;
			rotate = rand() % 2;
			if (rotate == 0) rotate = -1;
			x *= rotate;
			x += (rotate * -1 * 40);
			rock[i].x = rotate*x;
			rock[i].y = WINDOW_HEIGHT / 2;
			rock[i].flag = true;
			break;
		}
	}
}

//Drawing its basics and effects of character
void drawAndroid(){
	glColor3f(1, 1, 0);
	circle(android.center.x, android.center.y + 20, 20); //head
	glColor3f(1, 0, 0);
	glRectf(android.center.x - 20, android.center.y + 20, android.center.x + 20, android.center.y - 15);//body
	glColor3f(0, 0, 0);
	glRectf(android.center.x + 20, android.center.y + 21, android.center.x - 20, android.center.y + 19);//space between head and body
	glColor3f(0, 0, 0.7);
	circle(android.center.x - 8, android.center.y + 27, 3);//left eye
	circle(android.center.x + 8, android.center.y + 27, 3);//right eye
	glColor3f(1, 0, 0);
	//Ears Begin
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(android.center.x - 8, android.center.y + 38);
	glVertex2f(android.center.x - 13, android.center.y + 43);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(android.center.x + 8, android.center.y + 38);
	glVertex2f(android.center.x + 13, android.center.y + 43);
	glEnd();
	//Ears End

	//Hand
	glColor3f(1, 1, 0);
	circle(android.center.x - 28, android.center.y + 18, 4);//up
	glRectf(android.center.x - 32, android.center.y + (18), android.center.x - 24, android.center.y);//hand
	circle(android.center.x - 28, android.center.y, 4);//down
	circle(android.center.x + 28, android.center.y + 18, 4);//up
	glRectf(android.center.x + 32, android.center.y + 18, android.center.x + 24, android.center.y);//normal hand
	circle(android.center.x + 28, android.center.y, 4);//down

	//Foot
	glRectf(android.center.x + 10, android.center.y - 15, android.center.x + 2, android.center.y - 25);//hand
	glRectf(android.center.x - 10, android.center.y - 15, android.center.x - 2, android.center.y - 25);//hand
	circle(android.center.x + 6, android.center.y - 25, 4);
	circle(android.center.x - 6, android.center.y - 25, 4);
	glColor3f(1, 0, 0);
	if (effect % 10){
		circle(android.center.x + 6, android.center.y - 32, 5);
		circle(android.center.x - 6, android.center.y - 32, 5);
	}
	else{
		circle(android.center.x + 6, android.center.y - 35, 8);
		circle(android.center.x - 6, android.center.y - 35, 8);
	}

}

//Moving object
void moveAndroid(){

	if (left && android.center.x >= -WINDOW_WIDTH / 2 + 50)
		android.center.x -= ANDROID_SPEED;
	if (right && android.center.x <= WINDOW_WIDTH / 2 - 50)
		android.center.x += ANDROID_SPEED;
	if (up && android.center.y <= WINDOW_HEIGHT / 2 - 60)
		android.center.y += ANDROID_SPEED;
	if (down && android.center.y >= -WINDOW_HEIGHT / 2 + 60)
		android.center.y -= ANDROID_SPEED;
}

//Draw specific rock
void rocks(int x, int y){
	glColor3f(0.8, 0.8, 0.8);
	circle(x, y, 30);
}

//Drawing Rocks main function
void drawRocks(){
	for (int i = 0; i < ROCK_COUNT; i++){
		if (rock[i].flag == true){
			rocks(rock[i].x, rock[i].y);

			if (rock[i].y<-WINDOW_HEIGHT / 2 - 20){
				rock[i].flag = false;
				if (score != 0)
					score--;
				if (rem_life >= 0)
					rem_life--;
				else
					break;
			}
			else
				rock[i].y -= rock_speed;
		}
	}
}

//Check if any of rockets if any one of rocks
void rocketHitCheck(){
	for (int k = 0; k < ROCK_COUNT; k++){
		for (int i = 0; i < MAX_ROCKET; i++) {
			if (rocket[i].flag == true && rock[k].flag == true){
				if (rocket[i].x - 30 < rock[k].x && rocket[i].x + 30 > rock[k].x && rocket[i].y - 50 < rock[k].y && rocket[i].y + 50 > rock[k].y){
					rocket[i].flag = false;
					explosion(rock[k].x, rock[k].y);
					rock[k].flag = false;
					score++;
					cur_rocket++;
				}

			}
		}
	}
}

//Check if android hit any rock
void checkAndroidHit(){
	for (int i = 0; i<ROCK_COUNT; i++){
		if (rock[i].flag == true && rock[i].y > android.center.y - 70 && rock[i].y < android.center.y + 70 && rock[i].x + 30 > android.center.x - 20 && rock[i].x - 30 < android.center.x + 20){
			rem_life--;
			explosion(android.center.x, android.center.y);
			rock[i].flag = false;
		}
	}
}
