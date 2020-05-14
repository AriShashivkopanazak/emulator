#include "features/window.cpp"
#include "features/emulation.cpp"

/**
 * file : io.cpp
 * 
 * Manages all processes
 */
class proc {
    public:
        void run(int argc, char** argv) {
            // place all tasks here
            // create a window
            newWindow.createWindow(argc, argv);
            // initialize and load game

            // emulation loop
            while (true)
            {
                // emulate one cycle

                // if the "draw" is set, update screen

                // store key press state (press and release)


            }
        }

    private:
        // give each class a instance here
        window newWindow;
};