#include "includes.h"
#include "io.cpp"
#include "wm/window.cpp"

int main(int argc, char **argv) {

    window newWindow;

    newWindow.createWindow();

    /**
     * throw error if no rom is given
     */
    /* if (argc != 2) {
        std::cout << "Usage: emulator <ROM File>" << std::endl;
    }
    proc myProc;
    myProc.run();*/
    return 0;
}