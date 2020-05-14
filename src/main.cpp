#include "io.cpp"

/**
 * --------------------------------
 * CHIP-8 Emulator with sound
 * --------------------------------
 */
int main(int argc, char** argv)
{
    proc tasks;
    tasks.run(argc, (const char *)argv);
    return 0;
}
