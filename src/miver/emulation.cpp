#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "time.h"

/**
 * file : emulation.cpp
 * 
 * Holds all processes pertaining to the emulator
 */
class emulation_specs {
    //figure out what needs to be private
public:
    // chip 8 has 32 opcodes, each 2 bytes long
    unsigned short opcode;

    // the allowed memory
    unsigned char memory[4096];

    // cpu registers 15 8-bit registers
    unsigned char V[16];

    // There is an Index register I and a program counter (pc) which can have a value from 0x000 to 0xFFF
    unsigned short index_register;
    unsigned short program_counter;

    /**
     * memory map
     * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
     * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
     * 0x200-0xFFF - Program ROM and work RAM
     * 
     * The graphics system: 
     * The chip 8 has one instruction that draws sprite to the screen. 
     * Drawing is done in XOR mode and if a pixel is turned off as a result of drawing, 
     * the VF register is set. This is used for collision detection.
     * The graphics of the Chip 8 are black and white and the screen has a 
     * total of 2048 pixels (64 x 32). This can easily be implemented 
     * using an array that hold the pixel state (1 or 0)
     */
    unsigned char graphics[64 * 32];

    // Interrupts and hardware registers. The Chip 8 has none, but there are two
    // timer registers that count at 60 Hz. When set above zero they will count down to zero.

    unsigned char delay_timer;
    unsigned char sound_timer;

    /**
     * It is important to know that the 
     * Chip 8 instruction set has opcodes that allow the program 
     * to jump to a certain address or call a subroutine. 
     * While the specification don’t mention a stack,
     *  you will need to implement one as part of the interpreter yourself. 
     * The stack is used to remember the current location before a jump is performed.
     *  So anytime you perform a jump or call a subroutine, store the program counter in the stack 
     * before proceeding. The system has 16 levels of stack and
     *  in order to remember which level of the stack is used, you need to 
     * implement a stack pointer (sp).
     */
    unsigned short stack[16];
    unsigned short stack_pointer;

    /**
     * Finally, the Chip 8 has a HEX based keypad (0x0-0xF), 
     * you can use an array to store the current state of the key.
     */
    unsigned char keypad[16];
    
    void initialize()
    {
      // Reset
      program_counter = 0x200; // 512
      opcode          = 0;
      index_register  = 0;
      stack_pointer   = 0;
      
      // Clear Display
      for (int i =0 ; i < 2048 ; ++i) {
        stack[i] = 0;
        keypad[i] = 0;
        V[i] = 0;
      }

      // Clear Memory
      for (int i = 0 ; i < 4096 ; ++i) {
        memory[i] = 0;
      }

      // Reset timers
      delay_timer = 0;
      sound_timer = 0;

      // Seed rng
      srand (time(NULL));
    }

    bool load(const char* file_path)
    {
      initialize();

      // open rom file
      FILE* rom = fopen(file_path, "rb");
      if (rom == NULL)
      {
        std::cerr << "failed to open rom" << std::endl;
        return false;
      }

      // get file size
      fseek(rom, 0, SEEK_END);
      long rom_size = ftell(rom);
      rewind(rom);

      // allocate memory to store rom
      char* rom_buffer = (char*) malloc(sizeof(char) * rom_size);
      if (rom_buffer == NULL) {
        std::cerr << "failed to allocate memory for ROM" << std::endl;
        return false;
      }

      // Copy ROM into Buffer
      size_t result = fread(rom_buffer, sizeof(char), (size_t) rom_size, rom);
      if (result != rom_size)
      {
        std::cerr << "failed to read ROM" << std::endl;
        return false;
      }

      // Copy buffer into memory
      if ((4096-512) > rom_size)
      {
        for (int i = 0 ; i < rom_size ; ++i)
        {
          // Load into memory starting at 0x200 (=512)
          memory [i + 512] = (uint8_t)rom_buffer[i];
        }
      } else
      {
        std::cerr << "ROM too large to fit in memory" << std::endl;
        return false;
      }
      
      // Clean up
      fclose(rom);
      free(rom_buffer);
      std::cout << "loaded successfully";
      return true;
    }

    void emulate_cycle()
    {
      // Fetch Opcode
      // Decode Opcode
      // Execute Opcode
      // Update timers
    }
};

