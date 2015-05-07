//Displaying high scores
void displayScores(){
	if (scores[0].count != 0){
		print(-75, 300, "HIGHSCORES", GLUT_BITMAP_TIMES_ROMAN_24);
		for (int i = 0; i < scores[0].count; i++)
			vprint(-75, 150 + -1 * i * 40, GLUT_BITMAP_TIMES_ROMAN_24, "%s %d", scores[i].name, scores[i].score);
	}
	else
		print(0, 110, "No Highscore found!", GLUT_BITMAP_HELVETICA_12);
	print(-145, -325, "PRESS ENTER TO RETURN", GLUT_BITMAP_TIMES_ROMAN_24);
	fclose(highscore);
}

//Write scores to file
void writeScore(int score){
	highscore = fopen("score.bin", "wb");
	if (highscore != NULL){
		fwrite(&scores[0].score, sizeof(scores[0].score), 1, highscore);
		fwrite(&scores, sizeof(scores), 1, highscore);
	}
	fclose(highscore);
}

//Recursive Bubble sort algorithm and it's swap function
void swap(highscores_t *x, highscores_t *y) {
	int score;
	char name[10] = { "" };
	strcpy(name, x->name);
	strcpy(x->name, y->name);
	strcpy(y->name, name);
	score = x->score;
	x->score = y->score;
	y->score = score;
}
void bubble_sort(int n){
	if (n == 0)
		return;
	for (int i = 0; i <n - 1; i++) {
		if (scores[i + 1].score > scores[i].score)
			swap(&scores[i], &scores[i + 1]);
	}
	bubble_sort(n - 1);
}

//Read scores from file and store them into array
void readScores(){
	fread(&scores[0].score, sizeof(scores[0].score), 1, highscore);
	fread(&scores, sizeof(scores), 1, highscore);
	bubble_sort(scores[0].count);
	fclose(highscore);
}

//Open file, if file not exist create one
void fileOpen(){
	highscore = fopen("score.bin", "rb");
	if (highscore == NULL)
		highscore = fopen("score.bin", "wb");
	else
		readScores();
}

//Main function of highscores
void highScore(int score){
	fileOpen();
	scores[scores[0].count].score = score;
	strcpy(scores[scores[0].count].name, options.user_name);
	scores[0].count++;
	bubble_sort(scores[0].count);
	writeScore(score);
}