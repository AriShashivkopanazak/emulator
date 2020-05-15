#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "time.h"
#include "emulation.h"

/**
 * file : emulation.cpp
 * 
 * Holds all processes pertaining to the emulator
 */
class chip8
{
public:
	/**
	 * Load ROM file into memory
	 * 
	 * Initialize()
	 * Opens ROM file
	 * Gets the file size
	 * Allocate memory to store ROM
	 * Copy ROM into Buffer
	 * Copy Buffer into memory
	 * 
	 * make sure this works before cleanup
	 */
	bool load(const char *file_path)
	{
		initialize();

		// open rom file
		FILE *rom = fopen(file_path, "rb");
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
		char *rom_buffer = (char *)malloc(sizeof(char) * rom_size);
		if (rom_buffer == NULL)
		{
			std::cerr << "failed to allocate memory for ROM" << std::endl;
			return false;
		}

		// Copy ROM into Buffer
		size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, rom);
		if (result != rom_size)
		{
			std::cerr << "failed to read ROM" << std::endl;
			return false;
		}

		// Copy buffer into memory
		if ((4096 - 512) > rom_size)
		{
			for (int i = 0; i < rom_size; ++i)
			{
				// Load into memory starting at 0x200 (=512)
				e.memory[i + 512] = (uint8_t)rom_buffer[i];
			}
		} else {
			std::cerr << "ROM too large to fit in memory" << std::endl;
			return false;
		}

		// Clean up
		fclose(rom);
		free(rom_buffer);
		std::cout << "loaded successfully";
		return true;
	}


	/**
	 * A MESS
	 */
	void emulate_cycle()
	{
		// Fetch Opcode
		e.opcode = e.memory[e.program_counter] << 9 | e.memory[e.program_counter + 1]; //opcode is two bytes


		// Decode Opcode
		// Execute Opcode
		// Update timers
		switch (e.opcode & 0xF000)
		{
		case 0x0000:
			switch (e.opcode & 0x000f)
			{
			case 0x0000:
				for (int i = 0; i < 2048; ++i)
				{
					e.graphics[i] = 0;
				}
				e.draw_flag = true;
				e.program_counter += 2;
				break;

			case 0x000e:
				--e.stack_pointer;
				e.program_counter = e.stack[e.stack_pointer];
				e.program_counter += 2;
				break;
			
			default:
				printf("\nUnknown op code: %.4X\n", e.opcode);
					exit(3);
				}
				break;

		case 0x1000:
			e.program_counter = e.opcode & 0x000f;
			break;

		case 0x2000:
			e.stack[e.stack_pointer] = e.program_counter;
			++e.stack_pointer;
			e.program_counter = e.opcode & 0x0fff;
			break;
		
		case 0x3000:
			if (e.V[(e.opcode & 0X0F00) >> 8] == (e.opcode & 0x00FF))
			{
				e.program_counter += 4;
			} else {
				e.program_counter += 2;
			}
			break;
		
		case 0x4000:
			if (e.V[(e.opcode & 0X0F00) >> 8] != (e.opcode & 0x00FF))
			{
				e.program_counter += 4;
			} else {
				e.program_counter += 2;
			}
			break;

		case 0x5000:
			if (e.V[(e.opcode & 0x0F00) >> 8] == e.V[(e.opcode & 0x00F0) >> 4])
			{
				e.program_counter += 4;
			} else {
				e.program_counter += 2;
			}
			break;

		case 0x6000:
			e.V[(e.opcode & 0x0F00) >> 8] = e.opcode & 0x00FF;
				e.program_counter= 2;
			break;

		case 0x7000:
			e.V[(e.opcode & 0x0F00) >> 8] += e.opcode & 0x00FF;
				e.program_counter= 2;
			break;

		case 0x8000:
			switch (e.opcode & 0x000f)
			{
			case 0x0000:
				e.V[(e.opcode & 0x0F00) >> 8] = e.V[(e.opcode & 0x00F0) >> 4];
				e.program_counter += 2;
				break;

			case 0x0001:
				e.V[(e.opcode & 0x0F00) >> 8] |= e.V[(e.opcode & 0x00F0) >> 4];
				e.program_counter += 2;
				break;

			case 0x0002:
				e.V[(e.opcode & 0x0F00) >> 8] &= e.V[(e.opcode & 0x00F0) >> 4];
				e.program_counter += 2;
				break;

		        case 0x0003:
            			e.V[(e.opcode & 0x0F00) >> 8] ^= e.V[(e.opcode & 0x00F0) >> 4];
				e.program_counter += 2;
				break;

			case 0x0004:
				e.V[(e.opcode & 0x0F00) >> 8] += e.V[(e.opcode & 0x00F0) >> 4];
				if (e.V[(e.opcode & 0x00F0) >> 4] > (0xFF - e.V[(e.opcode & 0x0F00) >> 8]))
					e.V[0xF] = 1; //carry
				else
					e.V[0xF] = 0;
					e.program_counter += 2;
				break;

			case 0x0005:
				if (e.V[(e.opcode & 0x00F0) >> 4] > e.V[(e.opcode & 0x0F00) >> 8])
					e.V[0xF] = 0; // there is a borrow
				else
					e.V[0xF] = 1;
				e.V[(e.opcode & 0x0F00) >> 8] -= e.V[(e.opcode & 0x00F0) >> 4];
				e.pc += 2;
				break;

			case 0x0006:
				e.V[0xF] = e.V[(e.opcode & 0x0F00) >> 8] & 0x1;
				e.V[(e.opcode & 0x0F00) >> 8] >>= 1;
				e.program_counter += 2;
				break;

			case 0x0007:
				if (e.V[(e.opcode & 0x0F00) >> 8] > e.V[(e.opcode & 0x00F0) >> 4]) // VY-VX
					e.V[0xF] = 0;                                            // there is a borrow
				else
					e.V[0xF] = 1;
				e.V[(e.opcode & 0x0F00) >> 8] = e.V[(e.opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
				e.program_counter += 2;
				break;

			case 0x000E:
				e.V[0xF] = e.V[(opcode & 0x0F00) >> 8] >> 7;
				e.V[(e.opcode & 0x0F00) >> 8] <<= 1;
				e.program_counter += 2;
				break;

			default:
				printf("\nUnknown op code: %.4X\n", opcode);
				exit(3);
			}
			break;


		case 0x9000:
        		if (e.V[(e.opcode & 0x0F00) >> 8] != e.V[(e.opcode & 0x00F0) >> 4])
			{
				e.program_counter += 4;
			} else {
				e.program_counter += 2;
			}
			break;
			
		case 0xa000:
			e.index_register = e.opcode & 0x0FFF;
			e.program_counter += 2;
			break;

		case 0xb000:
			e.program_counter = (e.opcode & 0x0FFF) + e.V[0];
			break;

		case 0xc000:
			e.V[(e.opcode & 0x0F00) >> 8] = (rand() % (0xFF + 1)) & (e.opcode & 0x00FF);
			e.program_counter += 2;
			break;

		case 0xd000:
			{
				unsigned short x = e.V[(e.opcode & 0x0F00) >> 8];
				unsigned short y = e.V[(e.opcode & 0x00F0) >> 4];
				unsigned short height = e.opcode & 0x000F;
				unsigned short pixel;

				e.V[0xF] = 0;
				for (int yline = 0; yline < height; yline++)
				{
					pixel = e.memory[e.index_register + yline];
					for(int xline = 0; xline < 8; xline++)
					{
					if((pixel & (0x80 >> xline)) != 0)
					{
						if(e.graphics[(x + xline + ((y + yline) * 64))] == 1)
						{
						e.V[0xF] = 1;
						}
						e.graphics[x + xline + ((y + yline) * 64)] ^= 1;
					}
					}
				}

				e.draw_flag = true;
				e.program_counter += 2;
			}
			break;

		case 0xe000:
			switch (e.opcode & 0x00FF)
			{
			case 0x009E:
				if (e.keypad[e.V[(e.opcode & 0x0F00) >> 8]] != 0)
					e.program_counter += 4;
				else
					e.program_counter += 2;
				break;

			case 0x00A1:
				if (e.keypad[e.V[(e.opcode & 0x0F00) >> 8]] == 0)
					e.program_counter += 4;
				else
					e.program_counter += 2;
				break;

			default:
			printf("\nUnknown op code: %.4X\n", e.opcode);
			exit(3);
			}
			break;

		case 0xf000:
			switch(e.opcode & 0x00FF)
			{
				// FX07 - Sets VX to the value of the delay timer
				case 0x0007:
				e.V[(e.opcode & 0x0F00) >> 8] = e.delay_timer;
				e.program_counter += 2;
				break;

				// FX0A - A key press is awaited, and then stored in VX
				case 0x000A:
				{
					bool key_pressed = false;

					for(int i = 0; i < 16; ++i)
					{
						if(e.keypad[i] != 0)
						{
						e.V[(e.opcode & 0x0F00) >> 8] = i;
						key_pressed = true;
						}
				}

				// If no key is pressed, return and try again.
				if(!key_pressed)
					return;

				e.program_counter += 2;
				}
				break;

				case 0x0015:
					e.delay_timer = e.V[(e.opcode & 0x0F00) >> 8];
					e.program_counter += 2;
					break;

				case 0x0018:
					e.sound_timer = e.V[(e.opcode & 0x0F00) >> 8];
					e.program_counter += 2;
					break;

				case 0x001E:
					if(e.index_register + e.V[(e.opcode & 0x0F00) >> 8] > 0xFFF)
						e.V[0xF] = 1;
					else
						e.V[0xF] = 0;
					e.index_register += e.V[(e.opcode & 0x0F00) >> 8];
					e.program_counter += 2;
					break;

				case 0x0029:
					e.index_register = e.V[(e.opcode & 0x0F00) >> 8] * 0x5;
					e.program_counter += 2;
					break;

				case 0x0033:
					e.memory[e.index_register]     = e.V[(e.opcode & 0x0F00) >> 8] / 100;
					e.memory[e.index_register + 1] = (e.V[(e.opcode & 0x0F00) >> 8] / 10) % 10;
					e.memory[e.index_register + 2] = e.V[(e.opcode & 0x0F00) >> 8] % 10;
					e.program_counter += 2;
					break;

				case 0x0055:
					for (int i = 0; i <= ((e.opcode & 0x0F00) >> 8); ++i)
						e.memory[e.index_register + i] = e.V[i];
					// On the original interpreter, when the
					// operation is done, I = I + X + 1.
					e.index_register += ((e.opcode & 0x0F00) >> 8) + 1;
					e.program_counter += 2;
					break;

				case 0x0065:
					for (int i = 0; i <= ((e.opcode & 0x0F00) >> 8); ++i)
						e.V[i] = e.memory[e.index_register + i];

					// On the original interpreter,
					// when the operation is done, I = I + X + 1.
					e.index_register += ((e.opcode & 0x0F00) >> 8) + 1;
					e.program_counter += 2;
					break;

				default:
				printf ("Unknown opcode [0xF000]: 0x%X\n", e.opcode);
			}
			break;

    		default:
        		printf("\nUnimplemented op code: %.4X\n", e.opcode);
        		exit(3);
		}
	}
private:

	emulation_specs e;

	/**
	 * Initialize the emulator
	 * 
	 * Reset counters and registers
	 * Clear display
	 * Clear memory
	 */
	void initialize()
	{
		// Reset
		e.program_counter = 0x200; // 512
		e.opcode = 0;
		e.index_register = 0;
		e.stack_pointer = 0;

		// Clear Display
		for (int i = 0; i < 2048; ++i)
		{
			e.stack[i] = 0;
			e.keypad[i] = 0;
			e.V[i] = 0;
		}

		// Clear Memory
		for (int i = 0; i < 4096; ++i)
		{
			e.memory[i] = 0;
		}

		// Reset timers
		e.delay_timer = 0;
		e.sound_timer = 0;

		// Seed rng
		srand(time(NULL));
	}
};