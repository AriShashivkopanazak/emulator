#include "features/window.cpp"

/**
 * run io.cpp in main, acts as a taskmgr for main
 * instantiate classes
 */

class proc {
    public:
        void run(int argc, char** argv) {
            // place all tasks here
            
            // create a window
            newWindow.createWindow(argc, argv);

        }

    private:
        // give each thing a instance here
        window newWindow;
};