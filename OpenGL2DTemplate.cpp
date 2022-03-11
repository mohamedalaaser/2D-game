//  Includes

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>






//-----------------

//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawCircle(int x, int y, float r);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Display();
//-----------------

//  Global Variables
int windowWidth = 600;
int windowHeight = 770;
double gameSpeed = 1;
int animationlimit = 0;
int carPosition = 1;
int score = 0;
int lives = 3;
int gameOver = 0;

int timeMin = 0;
int timeSec = 0;

const int coinsPerMin = 2;
const int obstaclesPerMin = coinsPerMin * 6;

int coinsEveryMinute[coinsPerMin];
int coinsLanePos[coinsPerMin] = { -1 };
int coinsDraw[coinsPerMin] = { -1 };
int coinsAnim[coinsPerMin] = { -1 };

int obstaclesEveryMinute[obstaclesPerMin];
int obstaclesLanePos[obstaclesPerMin] = {-1};
int obstaclesDraw[obstaclesPerMin] = { -1 };
int obstaclesAnim[obstaclesPerMin] = { -1 };


double colAnim = 0.8;

//-----------------

void print(int x, int y, char* string)
{
    int len, i;

    //set the position of the text in the window using the x and y coordinates
    glRasterPos2f(x, y);

    //get the length of the string to display
    len = (int)strlen(string);

    //loop to display character by character
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}



// draws rectangles using the (x,y) of the bottom left vertex, width (w) and height (h)
void drawRect(int x, int y, int w, int h) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

// draws a circle using OpenGL's gluDisk, given (x,y) of its center and tis radius
void drawCircle(int x, int y, float r) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    GLUquadric* quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}


void Key(unsigned char key, int x, int y) {

    if (key == 'a')
        carPosition--;
    if (key == 'd')
        carPosition++;

    if (carPosition < 0)
        carPosition = 0;
    else if (carPosition > 2)
        carPosition = 2;

    // ask OpenGL to recall the display function to reflect the changes on the window
    glutPostRedisplay();
}






void TimerSecond(int value) {


    //every second we check if we have to spawn a coin and give it a lane
    for (int i = 0; i < coinsPerMin; i++) {
        if (coinsEveryMinute[i] == timeSec) {
            coinsLanePos[i] = rand() % 3;
            coinsAnim[i] = 770;
        }
        else {
            coinsLanePos[i] = -1;
        }
    }

    //same for obstacles
    for (int i = 0; i < obstaclesPerMin; i++) {
        if (obstaclesEveryMinute[i] == timeSec) {
            obstaclesLanePos[i] = rand() % 3;
            obstaclesAnim[i] = 770;
        }
        else {
            obstaclesLanePos[i] = -1;
        }
    }

    timeSec++;
    if (timeSec > 60) {
        timeSec = 0;
        timeMin++;

        //every minute we want coinsPerMin coins  in  random times
                for (int i = 0; i < coinsPerMin; i++) {
                    coinsEveryMinute[i] = rand() % 60;
            
                }
                //and 6 obstacles
                for (int i = 0; i < obstaclesPerMin; i++) {
                    obstaclesEveryMinute[i] = rand() % 60;

                }

    }
       


   
    glutPostRedisplay();
    glutTimerFunc(1 * 1000/gameSpeed, TimerSecond, 0);
}

void DrawBackGround() {
    //draw grey road
    glColor3f(0.5, 0.5, 0.5);
    drawRect(windowWidth * 0.15 / 2, 0, windowWidth * 0.85, 2000);

    //draw white sidestripes
    glColor3f(1, 1, 1);
    drawRect(10, 0, 35, 110);
    drawRect(10, 110 * 2, 35, 110);
    drawRect(10, 110 * 4, 35, 110);
    drawRect(10, 110 * 6, 35, 110);
    drawRect(10, 110 * 8, 35, 110);
    drawRect(10, 110 * 10, 35, 110);
    drawRect(10, 110 * 12, 35, 110);
    drawRect(10, 110 * 14, 35, 110);
    drawRect(10, 110 * 16, 35, 110);

    drawRect(555, 0, 35, 120);
    drawRect(555, 110 * 2, 35, 110);
    drawRect(555, 110 * 4, 35, 110);
    drawRect(555, 110 * 6, 35, 110);
    drawRect(555, 110 * 8, 35, 110);
    drawRect(555, 110 * 10, 35, 110);
    drawRect(555, 110 * 12, 35, 110);
    drawRect(555, 110 * 14, 35, 110);
    drawRect(555, 110 * 16, 35, 110);


    //draw black sidestripes
    glColor3f(0, 0, 0);
    drawRect(10, 110 * 1, 35, 110);
    drawRect(10, 110 * 3, 35, 110);
    drawRect(10, 110 * 5, 35, 110);
    drawRect(10, 110 * 7, 35, 110);
    drawRect(10, 110 * 9, 35, 110);
    drawRect(10, 110 * 11, 35, 110);
    drawRect(10, 110 * 13, 35, 110);
    drawRect(10, 110 * 15, 35, 110);

    drawRect(555, 110 * 1, 35, 110);
    drawRect(555, 110 * 3, 35, 110);
    drawRect(555, 110 * 5, 35, 110);
    drawRect(555, 110 * 7, 35, 110);
    drawRect(555, 110 * 9, 35, 110);
    drawRect(555, 110 * 11, 35, 110);
    drawRect(555, 110 * 13, 35, 110);
    drawRect(555, 110 * 15, 35, 110);


    //draw middle stripes
    glColor3f(1, 1, 1);
    drawRect(210, 0, 10, 130);
    drawRect(210, 130 * 2, 10, 130);
    drawRect(210, 130 * 4, 10, 130);
    drawRect(210, 130 * 6, 10, 130);
    drawRect(210, 130 * 8, 10, 130);
    drawRect(210, 130 * 10, 10, 130);
    drawRect(210, 130 * 12, 10, 130);
    drawRect(210, 130 * 14, 10, 130);

    drawRect(380, 0, 10, 130);
    drawRect(380, 130 * 2, 10, 130);
    drawRect(380, 130 * 4, 10, 130);
    drawRect(380, 130 * 6, 10, 130);
    drawRect(380, 130 * 8, 10, 130);
    drawRect(380, 130 * 10, 10, 130);
    drawRect(380, 130 * 12, 10, 130);
    drawRect(380, 130 * 14, 10, 130);
}


void DrawCharacter() {

    // MAIN car
        //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0, 50);
    glVertex2f(0, 70);
    glVertex2f(80, 70);
    glVertex2f(80, 50);
    glEnd();
    //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0, 10);
    glVertex2f(0, 30);
    glVertex2f(80, 30);
    glVertex2f(80, 10);
    glEnd();
    //Car Body
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(20, 10);
    glVertex2f(20, 80);
    glColor3f(1, 0.3, 0.3);

    glVertex2f(40, 100);
    glVertex2f(60, 80);
    glVertex2f(60, 10);
    glEnd();

}


void DrawCoin() {
    glColor3f(0, 0, 0);
    drawCircle(0, 0, 24);
    glColor3f(1, 0.8, 0.4);
    drawCircle(0, 0, 23);
    glColor3f(0, 0, 0);
    drawRect(-7, -13, 14, 26);
    glColor3f(1, 0.8, 0.4);
    drawRect(-6, -12, 12, 24);

}


void DrawObstacle() {
   
    drawRect(0, 30, 170, 30);
    drawRect(0, 0, 30, 80);
    drawRect(140, 0, 30, 80);


}


void Display() {



    if (gameOver == 1) {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 0, 0);
        char* p0s[20];
        sprintf((char*)p0s, "GameOver, Score: %d", score);
        print(100, 500, (char*)p0s);
        glFlush();

    }
    else {


        glClear(GL_COLOR_BUFFER_BIT);


        //everyRender we check if a new coin has a lane to be spawned, we put it in coinsdraw queue
        for (int i = 0; i < coinsPerMin; i++) {
            if (coinsLanePos[i] != -1) {
                coinsDraw[i] = coinsLanePos[i];
                coinsAnim[i] = 770;
                coinsLanePos[i] = -1;
            }
        }

        for (int i = 0; i < obstaclesPerMin; i++) {
            if (obstaclesLanePos[i] != -1) {
                obstaclesDraw[i] = obstaclesLanePos[i];
                obstaclesAnim[i] = 770;
                obstaclesLanePos[i] = -1;
            }
        }


        glPushMatrix();


        glPushMatrix();
        glTranslated(0, -animationlimit, 0); //draw and animate background
        DrawBackGround();
        glPopMatrix();



        glPushMatrix(); //draw car
        glTranslated(45 + (170 * carPosition) + 85 - 40, 20, 0);
        DrawCharacter();
        glPopMatrix();


        for (int i = 0; i < coinsPerMin; i++) { //draw and move coins
            glPushMatrix();
            glTranslated(45 + 170 * coinsDraw[i] + 85, coinsAnim[i], 0);
            DrawCoin();
            glPopMatrix();
        }

        
        for (int i = 0; i < obstaclesPerMin; i++) {//draw and move obstacles
            glPushMatrix();
            glColor3f(colAnim, colAnim, 0);
            glTranslated(170 * obstaclesDraw[i] + 45, obstaclesAnim[i], 0);
            DrawObstacle();
            glPopMatrix();
        }
        



        glColor3f(1, 0, 0);
        char* p0s[20];
        sprintf((char*)p0s, "Time: %d : %d", timeMin, timeSec);
        print(200, windowHeight - 20, (char*)p0s);

        sprintf((char*)p0s, "lives: %d", lives);
        print(0, windowHeight - 20, (char*)p0s);

        sprintf((char*)p0s, "Score: %d", score);
        print(100, windowHeight - 20, (char*)p0s);

        sprintf((char*)p0s, "Speed: %f", gameSpeed);
        print(400, windowHeight - 20, (char*)p0s);


        glPopMatrix();
        glFlush();
    }
}

void Anim()
{
    if (animationlimit < 770) {
        animationlimit += gameSpeed;
    }
    else {
        animationlimit = 0;
    }

    for (int i = 0; i < coinsPerMin; i++) {
        if (coinsAnim[i] > 100) {
            coinsAnim[i] -= gameSpeed;
        }
        else {
            if (carPosition == coinsDraw[i]) {
                score++;
                if (score%5 == 0) {
                    gameSpeed *= 1.5;
                    lives++;
                }
            }

            coinsAnim[i] = -1;
            coinsDraw[i] = -1;
        }
    }

    for (int i = 0; i < obstaclesPerMin; i++) {
        if (obstaclesAnim[i] > 100) {
            obstaclesAnim[i] -= gameSpeed;
        }
        else {
            if (carPosition == obstaclesDraw[i]) {
                lives--;
                if (lives == 0) {
                    gameOver = 1;
                }
               
            }

            obstaclesAnim[i] = -1;
            obstaclesDraw[i] = -1;
        }
    }
    colAnim -= 0.004;
    if (colAnim < 0)
        colAnim = 0.8;

    for (int i = 0; i < 8000000; i++);
    glutPostRedisplay();
}




void main(int argc, char** argr) {
    glutInit(&argc, argr);


    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(350, 0);

    glutCreateWindow("Robotic Arm");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed



    for (int i = 0; i < coinsPerMin; i++) {
        coinsEveryMinute[i] = rand() % 60;

    }
    for (int i = 0; i <obstaclesPerMin; i++) {
        obstaclesEveryMinute[i] = rand() % 60;

    }


    glutTimerFunc(0, TimerSecond, 0);
    glutIdleFunc(Anim);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0, 1, 0, 0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glutMainLoop();
}