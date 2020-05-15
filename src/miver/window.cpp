#include <GL/glut.h>

/**
 * file : window.cpp
 * 
 * renders the window
 */
class the_window
{
    public:
        int createWindow(int argc, char** argv)
        {
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE);
            glutInitWindowSize(720, 450);
            glutInitWindowPosition(100, 100);
            glutCreateWindow("Test");
            glutDisplayFunc(render);
            glutMainLoop();
            return 0;
        }
    private:
        static void render(void)
        {
            
        }
};