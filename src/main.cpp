#include "io.cpp"

/**
 * --------------------------------
 * A Cross Platform chip-8 Emulator
 * --------------------------------
 */
int main(int argc, char** argv)
{
    proc tasks;
    tasks.run(argc, argv);
    return 0;
}
