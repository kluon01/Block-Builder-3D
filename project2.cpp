//---------------------------------------
// Program: Project 2 | Block World
// Purpose: A simple block building game in 3D with camera controls
// Author:  Karshin Luong, John Gauch
// Date:    02/18/2019
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MAX_CUBE_COUNT 500

// Global variables
int xangle = 0;
int yangle = 0;
int zangle = 0;
float xpos = 0.0;
float ypos = 0.0;
float zpos = 0.0;
int type = 0;
int count = 0;
float centers [MAX_CUBE_COUNT][6];

GLenum mode = GL_LINE_LOOP;

using namespace std;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//---------------------------------------
// Function to draw 3D cube
//---------------------------------------
void cube(float midx, float midy, float midz, float size, float red, float green, float blue)
{
    // Define 8 vertices
    float ax = midx - size / 2;
    float ay = midy - size / 2;
    float az = midz + size / 2;
    float bx = midx + size / 2;
    float by = midy - size / 2;
    float bz = midz + size / 2;
    float cx = midx + size / 2;
    float cy = midy + size / 2;
    float cz = midz + size / 2;
    float dx = midx - size / 2;
    float dy = midy + size / 2;
    float dz = midz + size / 2;
    float ex = midx - size / 2;
    float ey = midy - size / 2;
    float ez = midz - size / 2;
    float fx = midx + size / 2;
    float fy = midy - size / 2;
    float fz = midz - size / 2;
    float gx = midx + size / 2;
    float gy = midy + size / 2;
    float gz = midz - size / 2;
    float hx = midx - size / 2;
    float hy = midy + size / 2;
    float hz = midz - size / 2;

    // Draw 6 faces
    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(ax, ay, az);
    glVertex3f(bx, by, bz);
    glVertex3f(cx, cy, cz);
    glVertex3f(dx, dy, dz);
    glEnd();

    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(ax, ay, az);
    glVertex3f(dx, dy, dz);
    glVertex3f(hx, hy, hz);
    glVertex3f(ex, ey, ez);
    glEnd();

    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(ax, ay, az);
    glVertex3f(ex, ey, ez);
    glVertex3f(fx, fy, fz);
    glVertex3f(bx, by, bz);
    glEnd();

    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(gx, gy, gz);
    glVertex3f(fx, fy, fz);
    glVertex3f(ex, ey, ez);
    glVertex3f(hx, hy, hz);
    glEnd();

    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(gx, gy, gz);
    glVertex3f(cx, cy, cz);
    glVertex3f(bx, by, bz);
    glVertex3f(fx, fy, fz);
    glEnd();

    glBegin(mode);
    glColor3f(red, green, blue);
    glVertex3f(gx, gy, gz);
    glVertex3f(hx, hy, hz);
    glVertex3f(dx, dy, dz);
    glVertex3f(cx, cy, cz);
    glEnd();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    // Fly mode keyboard controls 
    if (key == 'F')
        type = 0;
    else if (key == 'x' && type == 0)
        xpos -= 0.04;
    else if (key == 'y' && type == 0)
        ypos -= 0.04;
    else if (key == 'z' && type == 0)
        zpos -= 0.04;
    else if (key == 'X' && type == 0)
        xpos += 0.04;
    else if (key == 'Y' && type == 0)
        ypos += 0.04;
    else if (key == 'Z' && type == 0)
        zpos += 0.04;
    // Rotate mode keyboard controls
    else if (key == 'R')
        type = 1;
    else if (key == 'x' && type == 1)
        xangle -= 5;
    else if (key == 'y' && type == 1)
        yangle -= 5;
    else if (key == 'z' && type == 1)
        zangle -= 5;
    else if (key == 'X' && type == 1)
        xangle += 5;
    else if (key == 'Y' && type == 1)
        yangle += 5;
    else if (key == 'Z' && type == 1)
        zangle += 5;
    // Add a cube to current position and save the center point to a 2D array
    else if (key == '+' && type == 0)
    {
        centers[count][0] = xpos;
        centers[count][1] = ypos;
        centers[count][2] = zpos;
        count++; // increment cube count
        glutPostRedisplay();
    }
    // Decrement cube count when player types - in order to delete last cube placed
    else if (key == '-' && type == 0)
    {
        count--;
    }
    // Redraw objects
    glutPostRedisplay();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set boundary so cube doesnt go out of bounds
    if (xpos >= 0.45)
        xpos = 0.45;
    else if(ypos >= 0.45)
        ypos = 0.45;
    else if(zpos >= 0.45)
        zpos = 0.45;
    else if (xpos <= -0.45)
        xpos = -0.45;
    else if(ypos < -0.45)
        ypos = -0.45;
    else if(zpos <= -0.45)
        zpos = -0.45;
    // Camera roation
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    glRotatef(zangle, 0.0, 0.0, 1.0);
    cube(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0); // Draw boundary cube
    cube(0.0+xpos, 0.0+ypos, 0.0+zpos, 0.05, 1.0, 0.0, 0.0); // Draw drawing cube
    // Display the placed cubes using the center locations stored in the 2D array
    for (int i = count - 1; i >= 0; i--)
        if(count > 0) // Only draw the cubes when the player places the first cube
            cube(centers[i][0], centers[i][1], centers[i][2], 0.04, 0.0, 1.0, 1.0);
    glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Cube World");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
