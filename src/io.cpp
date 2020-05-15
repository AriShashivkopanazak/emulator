#include "miver/window.cpp"
#include "miver/emulation.cpp"

/**
 * file : io.cpp
 * 
 * Manages all processes
 */
class proc {
    public:
        int run(int argc, char** argv) {
            // place all tasks here
            // initialize and load game
            if (!chip.load(argv[1]))
            {
                return 2;
            }


            // emulation loop
            while (true)
            {
                // emulate one cycle
                chip.emulate_cycle();
                // if the "draw" is set, update screen

                // store key press state (press and release)


            }

            // create a window
            window.createWindow(argc, argv);

            return 0;
        }

    private:
        // give each class a instance here
        the_window window;
        chip8 chip;
};