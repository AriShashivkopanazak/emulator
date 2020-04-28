// #include "includes.h"
// #include "io.cpp"
// #include "wm/window.cpp"
#include <GL/glut.h>

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
	

    // window newWindow;

    // newWindow.createWindow();


    // newWindow
    // /**
    //  * throw error if no rom is given
    //  */
    // /* if (argc != 2) {
    //     std::cout << "Usage: emulator <ROM File>" << std::endl;
    // }
    // proc myProc;
    // myProc.run();*/
