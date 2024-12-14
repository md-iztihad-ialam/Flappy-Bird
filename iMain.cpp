# include "iGraphics.h"
#include <GL/glut.h>
# include <Windows.h>
#include<time.h>
#include<stdlib.h>



int screenX=1000, screenY=555;

int gameState=0;

int difficulty=0;

int score=0;

int mainScore = 0;

static int highScore=0;

int birdX=100;
int birdY=400; 
int birdSize=40;
int birdGravity=4;
int birdJump=90;
int bird=0;
char birdImage[10][20]={"tile000.bmp", "tile001.bmp", "tile002.bmp", "tile003.bmp", "tile004.bmp", "tile005.bmp", "tile006.bmp", "tile007.bmp", "tile008.bmp", "tile009.bmp"};


int pipeGap = 180;
int pipeWidth = 80;
int pipeSpeed = 10;
int pipeX[3] = {800, 1100, 1400};
int pipeY_height_down[3] = {50, 250, 100};





void homePage(){
	iShowBMP(0, 0, "HomePage.bmp");
}

void difficultyPage(){
	iShowBMP(0, 0, "DifficultyPage.bmp");
}

void creditPage(){
	iShowBMP(0, 0, "CreditPage.bmp");
}

void instructionPage(){
	iShowBMP(0, 0, "InstructionPage.bmp");
}

void leaderboardPage(){
	iShowBMP(0, 0, "LeaderboardPage.bmp");
	
	FILE *hScore = fopen("highScore.txt", "r");
	char points[200];

	int y = 350;
	while(fgets(points, 200, hScore) != NULL){
		iSetColor(255, 255, 255);
		iText(500, y, points, GLUT_BITMAP_TIMES_ROMAN_24);
		y = y - 50;
	}

	fclose(hScore);
}

void restart(){
	gameState = 0;
	score = 0;
	birdY = 400;
	birdGravity = 4;
	pipeX[0] = 800; pipeX[1] = 1100; pipeX[2] = 1400;
	pipeY_height_down[0] = 50; pipeY_height_down[1] = 250; pipeY_height_down[2] = 100;
}

void easyPage(){
	iShowBMP(0, 0, "mainBackground.bmp");
	iShowBMP2(birdX, birdY, birdImage[bird], 0);
	iSetColor(255, 0, 0);
	char scoreString[4];
	sprintf(scoreString, "Score: %d", score/7);
	iText(100, 500, scoreString);

	for(int i=0; i<3; i++){
		iSetColor(58, 126, 59);
		iFilledRectangle(pipeX[i], 0, pipeWidth, pipeY_height_down[i]);	
		iFilledRectangle(pipeX[i], pipeY_height_down[i]+pipeGap, pipeWidth, 560-(pipeY_height_down[i]+pipeGap));
	}
}

void hardPage(){
	iShowBMP(0, 0, "HardPage.bmp");
	iShowBMP2(birdX, birdY, birdImage[bird], 0);
	iSetColor(255, 255, 255);
	char scoreString[4];
	sprintf(scoreString, "Score: %d", score/3);
	iText(100, 500, scoreString);

	for(int i=0; i<3; i++){
		iSetColor(137, 12, 23);
		iFilledRectangle(pipeX[i], 0, pipeWidth, pipeY_height_down[i]);	
		iFilledRectangle(pipeX[i], pipeY_height_down[i]+pipeGap, pipeWidth, 560-(pipeY_height_down[i]+pipeGap));
	}
}

void mediumPage(){
	iShowBMP(0, 0, "MediumPage.bmp");
	iShowBMP2(birdX, birdY, birdImage[bird], 0);
	iSetColor(255, 255, 255);
	char scoreString[4];
	sprintf(scoreString, "Score: %d", score/5);
	iText(100, 500, scoreString);

	for(int i=0; i<3; i++){
		iSetColor(29, 5, 149);
		iFilledRectangle(pipeX[i], 0, pipeWidth, pipeY_height_down[i]);	
		iFilledRectangle(pipeX[i], pipeY_height_down[i]+pipeGap, pipeWidth, 560-(pipeY_height_down[i]+pipeGap));
	}
}

void gameOverPage(){
	iShowBMP(0, 0, "EndPage.bmp");
	iSetColor(0, 0, 255);
	char scoreString[4];

	if(difficulty == 0){
		mainScore = score/7;
	}else if(difficulty == 1){
		mainScore = score/5;
	}else if(difficulty == 2){
		mainScore = score/3;
	}

	sprintf(scoreString, "%d", mainScore);
	iText(400, 280, scoreString);


	FILE *hScore = fopen("highScore.txt", "r");
	int scores[5] = {0, 0, 0, 0, 0};
	int i = 0;
	char str[100];

	while(fgets(str, 100, hScore) != NULL  &&  i<5){
		scores[i] = atoi(str);
		i++;
	}

	int flag = 1;
	for(int i=0; i<5; i++){
		if(mainScore == scores[i]){
			flag = 0;
		}
	}


	if(flag){
		int flag2 = 1;
		for(int i=0; i<5; i++){
			if(flag2){
				if(mainScore > scores[i]){
					for(int j=4; j>i; j--){
						scores[j] = scores[j-1];
					}
					scores[i] = mainScore;
					break;
				}
			}
		}
	}

	fclose(hScore);


	hScore = fopen("highScore.txt", "w");

	for(int i=0; i<5; i++){
		fprintf(hScore, "%d\n", scores[i]);
	}

	fclose(hScore);




	hScore = fopen("highScore.txt", "r");

	char highScoreString[3];

	if(fgets(highScoreString, 3, hScore) != NULL){
		iSetColor(0, 0, 255);
		iText(475, 230, highScoreString);
	}

	fclose(hScore);
}

void iDraw() {
	

	iClear();

	if(gameState==0){
		homePage();
	}else if(gameState==1){
		difficultyPage();
	}else if(gameState==2){
		creditPage();
	}else if(gameState==3){
		instructionPage();
	}else if(gameState==5){
		gameOverPage();
	}else if(gameState == 6){
		leaderboardPage();
	}

	if(gameState==4 && difficulty==0){
		pipeGap=180;
		birdGravity=4;
		pipeSpeed=10;
		easyPage();
	}else if(gameState==4 && difficulty==1){
		pipeGap=180;
		birdGravity=4;
		pipeSpeed=15;
		mediumPage();
	}else if(gameState==4 && difficulty==2){
		pipeGap=180;
		birdGravity=4;
		pipeSpeed=20;
		hardPage();
	}
}





void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	
}





void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Handle clicks on the main menu

        if (gameState == 0) {
            if (mx >= 375 && mx <= 625 && my >= 325 && my <= 385) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                gameState = 1;
            } else if (mx >= 375 && mx <= 625 && my >= 245 && my <= 310) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                gameState = 6;
            } else if (mx >= 375 && mx <= 625 && my >= 165 && my <= 230) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                gameState = 2;
            }else if(mx >= 375 && mx <= 625 && my >= 85 && my<= 150){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				gameState = 3;
			}else if(mx >= 375 && mx<= 625 && my >= 5 && my<= 70){
				exit(0);
			}
        }else if (gameState == 1) {
            if (mx >= 375 && mx <= 625 && my >= 245 && my <= 305) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                difficulty = 0;
                gameState = 4;
            } else if (mx >= 375 && mx <= 625 && my >= 165 && my <= 225) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                difficulty = 1;
                gameState = 4;
            } else if (mx >= 375 && mx <= 625 && my >= 85 && my <= 150) {
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
                difficulty = 2;
                gameState = 4;
            }else if(mx >= 375 && mx <= 625 && my >= 10 && my<= 70){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				gameState = 0;
			}
        }else if(gameState == 6){
			if(mx >= 375 && mx<= 625 && my >= 5 && my<= 80){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				gameState = 0;
			}

		}else if(gameState == 2){
			if(mx >= 370 && mx<= 630 && my >= 55 && my<= 110){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				gameState = 0;
			}
		}else if(gameState == 3){
			if(mx >= 370 && mx<= 625 && my >= 20 && my<= 75){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				gameState = 0;
			}
		}else if(gameState == 5){
			if(mx >= 375 && mx<= 630 && my >= 5 && my<= 70){
				PlaySound(TEXT("Music\\swoosh.wav"), NULL, SND_ASYNC);
				restart();
			}
		}
    }
}






void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}else if(key == ' '){
		birdY += birdJump;
		if(gameState == 4){
			PlaySound(TEXT("Music\\flap.wav"), NULL, SND_ASYNC);
		}
	} 
	
	if(key == 'r'){
		if(gameState == 5){
			restart();
		}
	}
	
}



void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}else if (key == GLUT_KEY_UP) {

	}else if (key == GLUT_KEY_DOWN) {

	}else if (key == GLUT_KEY_RIGHT) {

	}else if (key == GLUT_KEY_LEFT) {

	}

}


void change(){
	if(gameState == 4){
		bird++;
		if(bird>=10){
			bird=0;
		}

		if(gameState==5){
			gameOverPage();
		}

		int i = 0;
		int k = 0;

		while(i != 3){

			pipeX[i] -= pipeSpeed;

			if(pipeX[i]+pipeWidth < 0){

				pipeX[i] = screenX-200;

				int height[3] = {50, 150, 300};

				int k=rand()%3;

				pipeY_height_down[i] = height[k];
			}

			birdY -= birdGravity;

			if (birdX > pipeX[i] && birdX < pipeX[i] + pipeWidth) {
				score += 1;
			}
			

			if ((birdX + birdSize >= pipeX[i] && birdX  <= pipeX[i] + pipeWidth && 
			(birdY <= pipeY_height_down[i] || birdY + birdSize >= pipeY_height_down[i] + pipeGap)) || 
			birdY <= 0 || birdY + birdSize >= screenY) {
				PlaySound(TEXT("Music\\hit.wav"), NULL, SND_ASYNC);
				gameState = 5;
				return;
			}

			if((birdY+birdSize) >= 560 || birdY <= 0){
				PlaySound(TEXT("Music\\hit.wav"), NULL, SND_ASYNC);
				gameState = 5;
				return;
			}

			i++;
		}
	}

}

int main() {

	srand(time(NULL));
	iSetTimer(50, change);
	iInitialize(screenX, screenY, "FLAPPY BIRD");
	return 0;

}