#include "miver/window.cpp"
#include "miver/emulation.cpp"

/**
 * file : io.cpp
 * 
 * Manages all processes
 */
class proc {
    public:
        void run(int argc, const char* argv) {
            // place all tasks here
            // initialize and load game
            chip.initialize();
            chip.load(argv);


            // emulation loop
            while (true)
            {
                // emulate one cycle
                chip.emulate_cycle();
                // if the "draw" is set, update screen

                // store key press state (press and release)


            }
            // create a window
            newWindow.createWindow(argc, (char**)argv);
        }

    private:
        // give each class a instance here
        window newWindow;
        emulation_specs chip;
};