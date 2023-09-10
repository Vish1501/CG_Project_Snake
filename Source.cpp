#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
//#include <string.h>
#include "game.h"
#include<tchar.h>

#define ROWS 30.0
#define COLUMNS 30.0

std::ofstream ofile;
std::ifstream ifile;
bool game_over = false;
extern int sDirection;
int score = 0;
clock_t start_time, end_time;
double cpu_time_used;

//start_time = clock();

void init();
void display_callback();
void input_callback(int, int, int);
void reshape_callback(int, int);
void timer_callback(int);

int main(int argc, char** argv)
{
    start_time = clock();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(600, 600);
    glutCreateWindow("SNAKE GAME");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(100, timer_callback, 0);
    init();
    glutMainLoop();
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(COLUMNS, ROWS);
}

//Callbacks
void display_callback()
{
    if (game_over)
    {
        end_time = clock();
        cpu_time_used = end_time - start_time;
        char text[50];
        sprintf(text, "%d", score);
        char msg[100] = "Your score is: ";
        strcat(msg, text);
        MessageBox(NULL, (LPCSTR)msg, (LPCSTR)"Game Over!", 0);
        printf("\n\n\nYour score is: %d", score);
        printf("\nYour timing is %lf seconds", (cpu_time_used/1000.0));
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    draw_grid();
    draw_food();
    draw_snake();
    glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLfloat)w, GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int)
{
    glutPostRedisplay();
    glutTimerFunc(100, timer_callback, 0);
}
void input_callback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    }
}
