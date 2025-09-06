#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL_main.h>
int main(int argc,char* argv[]){
    //initialize the video subsystem, and print out error if there is one
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr,"Error:%s",SDL_GetError());
        return 1;
    }
    //create window and check for errors during that process
    SDL_Window* window=SDL_CreateWindow("SDL3 Window",640,480,SDL_WINDOW_RESIZABLE);
    if(window==NULL){
        fprintf(stderr,"Error:%s",SDL_GetError());
        SDL_Quit();
        return 1;
    }
    //Initialize the renderer and check for errors
    SDL_Renderer *renderer=SDL_CreateRenderer(window,NULL);
    if(renderer==NULL){
        fprintf(stderr,"Error:%s",SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //make the main loop
    int running=1;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event)){
        //check for diffirent events
        SDL_StartTextInput(window);    
        switch(event.type){
            case SDL_EVENT_MOUSE_MOTION:
            SDL_Log("Motion event");
            break;
            case SDL_EVENT_QUIT:
            SDL_Log("Attempted quiting____________________");
            running=0;
            break;
            case SDL_EVENT_KEY_UP:
             SDL_Log("Key Up");
            break;
            case SDL_EVENT_KEY_DOWN:
            SDL_Log("Key Down");
            break;
            case SDL_EVENT_TEXT_INPUT:
            SDL_Log("Input text");
            break;
            default:
            SDL_Log("Unhandled Event");
            
        }
    }
SDL_StopTextInput(window);
SDL_Delay(16);
}
SDL_DestroyWindow(window);
SDL_Quit();

    
    return 0;
}
