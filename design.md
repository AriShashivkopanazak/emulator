# Human Readable Design For the Chip8 Emulator

## Inputs

Keyboard
8 Bit Roms

## Outputs

Screen
Audio

## Actions

Executes 8 bit games

## Constraints

## Design

* throw error if no rom is given
* Create window using SDL library
  * give window height and width
  * give a window to render to
  * initialize SDL
  * create a window and renderer
  * create textures that store frame buffer
  * add temporary pixel buffer
* instantiate chip8
* load rom
* run a infinate loop that emulates the behavior of chip 8
