#include <SDL2/SDL.h>

class window {
    public:
        /**
         * Creates a window
         */
        void createWindow() {

            // Give window height and width
            int width  = 1024;
            int height =  512;

            // Window to render to
            SDL_Window* emulator = NULL;

            // Initialize SDL
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
                exit(1);
            }

            // Create Window
            emulator = SDL_CreateWindow(
                "CHIP-8 Emulator",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width, height, SDL_WINDOW_SHOWN
            );

            if (emulator == NULL) {
                    printf("Window could not be created! SDL_ERROR %s\n",
                    SDL_GetError()
                );
            }

            // Create Renderer
            SDL_Renderer *renderer = SDL_CreateRenderer(emulator, -1, 0);
            SDL_RenderSetLogicalSize(renderer, width, height);

            // Create Texture That Stores Frame Buffer
            SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
                SDL_PIXELFORMAT_ARGB8888,
                SDL_TEXTUREACCESS_STREAMING,
                64, 32);

            // Temporary pixel buffer
            uint32_t pixels[2048];
        }   
};
