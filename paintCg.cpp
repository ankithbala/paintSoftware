
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glx.h>
#include <GL/glut.h> 
#include<vector>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;

struct Color{ float r,g,b;};

struct Point{
    int mouseX, mouseY, brush;
    Color color;
    int size;
};
vector<Point> points;
Color color={1,1,1};
int size=1;
int num = 0;
bool leftClick = false;
void drawShape(int num)
{
    for (auto &x:points)
    {
        glColor3f(x.color.r, x.color.g, x.color.b);
        switch(x.brush){
        case 0:
            glBegin(GL_POLYGON);
            glVertex2f(x.mouseX - x.size, x.mouseY - x.size);
            glVertex2f(x.mouseX + x.size, x.mouseY - x.size);
            glVertex2f(x.mouseX + x.size, x.mouseY + x.size);
            glVertex2f(x.mouseX - x.size, x.mouseY + x.size);
            glEnd();
            break;
        case 1:
            glBegin(GL_TRIANGLES);
            glVertex2f(x.mouseX - x.size, x.mouseY - x.size);
            glVertex2f(x.mouseX + x.size, x.mouseY - x.size);
            glVertex2f(x.mouseX, x.mouseY + x.size);
            glEnd();
            break;
        case 2:
            glBegin(GL_LINES);
            glVertex2f(x.mouseX, x.mouseY - x.size);
            glVertex2f(x.mouseX, x.mouseY + x.size);
            glEnd();

        }
    }
    glFlush();
}

void display(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    drawShape(num);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        color={1,1,1};
        break;
    case '2':
        color={1,0,0};
        break;
    case '3':
        color={0,1,0};
        break;
    case '4':
        color={1, 1, 0};
        break;
    case '5':
        color={1, 0, 1};
        break;
    case '6':
        color={0, 1, 1};
        break;
    case '7':
        color={0, 0, 1};
        break;
    case '+':
        if (size < 65)
            size = size * 2;
        break;
    case '-':
        if (size > 1 )
            size = size / 2;
        break;
    case 's':
        num++;
        if (num > 2)
            num = 0;
        break;
    case 'c':
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        break;
    case 'e':
        color={0,0,0};
        break;

    }
    glutPostRedisplay();
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}
void mouse(int button, int action, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (action == GLUT_DOWN)
            leftClick = true;
        else
            leftClick = false;
    }
}


void mouseMove(int x, int y)
{
    if (leftClick)
    {
        points.push_back({x,y,num,color, size});
        glutPostRedisplay();
    }
}
void menufun1(int value)
{
    if(value==1)
    {
        //display();
        glutDisplayFunc(display);
        glutMotionFunc(mouseMove);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
    }
    if(value==9)
    {
        if (size < 65)
            size = size * 2;
        glutPostRedisplay();
    }
    if(value==10)
    {
        if (size > 1 )
            size = size / 2;
        glutPostRedisplay();
    }
    if(value==14)
    {
        color={0,0,0};
        glutPostRedisplay();
    }
}

void menufun2(int value)
{
    if(value==2)
    {
        color={1,1,1};
        glutPostRedisplay();
    }
    if(value==3)
    {
        color={1,0,0};
        glutPostRedisplay();

    }
    if(value==4)
    {
        color={0,1,0};
        glutPostRedisplay();
    }
    if(value==5)
    {
        color={1, 1, 0};
        glutPostRedisplay();
    }
    if(value==6)
    {
        color={0, 0, 1};
        glutPostRedisplay();
    }
    if(value==7)
    {
        color={1,0,1};
        glutPostRedisplay();
    }
    if(value==8)
    {
        color={0, 1, 1};
        glutPostRedisplay();
    }
    
}
void menufun3(int value)
{
    if(value==11)
    {
        num=0;
        glutDisplayFunc(display);
        glutMotionFunc(mouseMove);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
    }
    if(value==12)
    {
        num=1;
        glutDisplayFunc(display);
        glutMotionFunc(mouseMove);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
    }
    if(value==13)
    {
        num=2;
        glutDisplayFunc(display);
        glutMotionFunc(mouseMove);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
    }
    
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(500, 300);
    glutCreateWindow("Paint Software");
    int SubMenu=glutCreateMenu(menufun2);
    glutAddMenuEntry("White",2);
    glutAddMenuEntry("Red",3);
    glutAddMenuEntry("Green",4);
    glutAddMenuEntry("Yellow",5);
    glutAddMenuEntry("Blue",6);
    glutAddMenuEntry("Magenta",7);
    glutAddMenuEntry("Cyan",8);
    int SubMenu2=glutCreateMenu(menufun3);
    glutAddMenuEntry("Quad",11);
    glutAddMenuEntry("Triangle",12);
    glutAddMenuEntry("Line",13);
    int MainMenu=glutCreateMenu(menufun1);
    glutAddSubMenu("Draw",SubMenu2);
    glutAddMenuEntry("+",9);
    glutAddMenuEntry("-",10);
    glutAddMenuEntry("Eraser",14);
    glutAddSubMenu("Color",SubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
