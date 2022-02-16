/*
 * Created on Tue Nov 02 2021
 *
 * Copyright (c) 2021 Peterson Yuhala, IIUN
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

//screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void create_sdl_window()
{
    SDL_Window *window = NULL;

    //the surface contained by the window
    SDL_Surface *screenSurface = NULL;

    //Initialize sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL count not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window cannot be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Wait two seconds
            SDL_Delay(2000);
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *args[])
{

    create_sdl_window();
    return 0;
}