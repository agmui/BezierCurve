#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "LTimer.cpp"
#include "LTexture.cpp"
#include "BezierCurve.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

using namespace std;

bool mouseClick;
int mouseX, mouseY;

// struct point
// {
//     float x;
//     float y;
// };

int main(int argc, char *argv[])
{
    SDL_Window *win = SDL_CreateWindow("Bezier Curve Demo", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *gRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_PRESENTVSYNC);
    // SDL_SetWindowPosition(win, 194, 403);
    BezierCurve *bezierCurve = new BezierCurve(gRenderer);
    // BezierCurve *bezierCurve = new BezierCurve(gRenderer,100);

    // Main loop flag
    bool quit = false;
    bool pause = false;

    // Event handler
    SDL_Event e;

    // Set text color as black
    SDL_Color textColor = {0, 0, 0, 255};

    // The frames per second timer
    LTimer fpsTimer;

    // The frames per second cap timer
    LTimer capTimer;

    // In memory text stream
    std::stringstream timeText;

    // Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

    uint degree = 4;
    SDL_FPoint cords[degree] = {
        {100.0, 100.0},
        {150.0, 400.0},
        {200.0, 220.0},
        {500.0, 100.0}};
    while (!quit)
    {
        // Start cap timer
        capTimer.start();

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseClick = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseClick = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;
                else if (e.key.keysym.sym == SDLK_SPACE)
                    pause = !pause;
                break;
            // better way to do it
            // bool KEYS[322]; // 322 is the number of SDLK_DOWN events
            // for (int i = 0; i < 322; i++)
            // { // init them all to false
            //     KEYS[i] = false;
            // }
            // SDL_EnableKeyRepeat(0, 0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down
            // case SDL_KEYDOWN:
            //     keys[ev.key.keysym.scancode] = true;
            //     break;
            // case SDL_KEYUP:
            //     keys[ev.key.keysym.scancode] = false;
            //     break;
            default:
                break;
            }
        }
        if (!pause)
        {

            // the screen gets cleared with the last color that was set
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            SDL_GetMouseState(&mouseX, &mouseY);

            // ==========================================================================================

            countedFrames %= 100;
            float p = (float)countedFrames / 100.0;

            // set draw color to red
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
            bezierCurve->nDegreeCurve(degree, cords, p, false);

            SDL_SetRenderDrawColor(gRenderer, 0x0F, 0x00, 0x00, 0xFF);
            bezierCurve->drawHelpers(cords, degree, mouseClick, mouseX, mouseY);

            // ==========================================================================================
            // update screen
            SDL_RenderPresent(gRenderer);

            ++countedFrames;
        }
        // If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME)
        {
            // Wait remaining time
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        }
    }
}
