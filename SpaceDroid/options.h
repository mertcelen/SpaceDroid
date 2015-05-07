void optionsf();
void showoptions();
FILE *optionsp;
				//default settings
void writeOptions(){
	optionsp = fopen("options.bin", "wb");
	if (optionsp != NULL)
		fwrite(&options, sizeof(options), 1, optionsp);
}
void readOptions(){
	fread(&options, sizeof(options), 1, optionsp);
	fclose(optionsp);
}
void optionsf(){
	optionsp = fopen("options.bin", "rb");
	if (optionsp == NULL){
		printf("Options file not found,creating default one\n");
		writeOptions();
	}
	else
		readOptions();
	showoptions();
}
void showoptions(){
	print(-45, 220, "Difficulty", GLUT_BITMAP_TIMES_ROMAN_24);
		if (options_selection == 1){
			glColor3f(0.5, 0.5, 0.5);
			glRectf(-120, 150, -50, 90);
			glColor3f(0.1, 0.1, 0.1);
			glRectf(-40, 150, 30, 90);
			glRectf(40, 150, 110, 90);
		}
		else if (options_selection == 2){
			glColor3f(0.5, 0.5, 0.5);
			glRectf(-40, 150, 30, 90);
			glColor3f(0.1, 0.1, 0.1);
			glRectf(-120, 150, -50, 90);
			glRectf(40, 150, 110, 90);
		}
		else{
			glColor3f(0.5, 0.5, 0.5);
			glRectf(40, 150, 110, 90);
			glColor3f(0.1, 0.1, 0.1);
			glRectf(-120, 150, -50, 90);
			glRectf(-40, 150, 30, 90);
	}
	glColor3f(1, 1, 1);
	print(-90, 115, "1", GLUT_BITMAP_TIMES_ROMAN_24);
	print(-10, 115, "2", GLUT_BITMAP_TIMES_ROMAN_24);
	print(70, 115, "3", GLUT_BITMAP_TIMES_ROMAN_24);
	print(-80, 0, "PLAYER NAME", GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0.1, 0.1, 0.1);
	glRectf(-60,-40,60,-100);
	glColor3f(1, 1, 1);
	vprint(-40, -80, GLUT_BITMAP_TIMES_ROMAN_24, "%s", options.user_name);
	/*glColor3f(0.1, 0.1, 0.1);
	glRectf(-120, 30, 120, -30);
	glRectf(-120, -40, 120, -100);
	glRectf(-120, -110, 120, -170);*/
}
