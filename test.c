#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL_main.h>
#include <math.h>
#define SPEED 3
#define ESPEED 1.5
typedef struct vector {
    float speedx;
    float speedy;
} EnemySpeed;


void EventHandling(SDL_Event *event,int *run,const bool *KeyPress){
    switch(event->type){
            case SDL_EVENT_MOUSE_MOTION:
            SDL_Log("Motion event");
            break;
            case SDL_EVENT_QUIT:
            SDL_Log("Attempted quiting____________________");
            *run=0;
            break;
            case SDL_EVENT_KEY_UP:
             SDL_Log("Key Up");
            break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            SDL_Log("Mouse Key pressed");
            break;
            case SDL_EVENT_KEY_DOWN:
            SDL_Log("Pressed another button");
            break;
            case SDL_EVENT_TEXT_INPUT:
            SDL_Log("Input text");
            break;
            default:
            SDL_Log("Unhandled Event");
            
    }
}
void RestrictPosition(float *x, float *y){
    if (*x<0){
        *x=0;
    }
    else if (*x>=640){
        *x=639;
    }
    if (*y<0){
        *y=0;
    }
    else if (*y>=480){
        *y=479;
    }
    
}
void DrawGraphics(SDL_Renderer *renderer,SDL_FRect *rect,SDL_FRect *enemy){
    if(!SDL_SetRenderDrawColor(renderer,255,255,0,255)){
        fprintf(stderr,"Error:%s",SDL_GetError());
    }
    SDL_RenderClear(renderer);
    if(!SDL_SetRenderDrawColor(renderer,255,0,0,255)){
        fprintf(stderr,"Error:%s",SDL_GetError());
    }
    SDL_RenderFillRect(renderer,rect);
    if(!SDL_SetRenderDrawColor(renderer,0,0,255,255)){
        fprintf(stderr,"Error:%s",SDL_GetError());
    }
    SDL_RenderFillRect(renderer,enemy);
    SDL_RenderPresent(renderer);
}
void MovePlayer(float *x,float *y){
    const bool *KeyState=SDL_GetKeyboardState(NULL);
    if (KeyState[SDL_SCANCODE_W])
    *y-=SPEED;
    if (KeyState[SDL_SCANCODE_S])
    *y+=SPEED;
    if (KeyState[SDL_SCANCODE_A])
    *x-=SPEED;
    if (KeyState[SDL_SCANCODE_D])
    *x+=SPEED;
}
EnemySpeed CalcSpeed(float x,float y){
    float z=sqrt(x*x+y*y);
    EnemySpeed final;
    final.speedx=(x/z)*ESPEED;
    final.speedy=(y/z)*ESPEED;
    return final;
}
void EnemyMove(float tx,float ty,float *x,float *y){
float distx=fabs(tx-*x);
float disty=fabs(ty-*y);
EnemySpeed speed=CalcSpeed(distx,disty);
if(tx>*x){
    *x+=speed.speedx;
}
else {
    *x-=speed.speedx;
}
if(ty>*y){
   *y+=speed.speedy; 
}
else 
*y-=speed.speedy;
}
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
    SDL_FRect mainrect;
    mainrect.x=0;
    mainrect.y=0;
    mainrect.w=50;
    mainrect.h=50;
    SDL_FRect enemyrect;
    enemyrect.x=589;
    enemyrect.y=429;
    enemyrect.w=50;
    enemyrect.h=50;
    
    //make the main loop
    int running=1;
    SDL_Event event;
   
    while(running){

        while(SDL_PollEvent(&event)){
        //check for diffirent events
        EventHandling(&event,&running,SDL_GetKeyboardState(NULL));
        
    }
    MovePlayer(&mainrect.x,&mainrect.y);
    RestrictPosition(&mainrect.x,&mainrect.y);
    EnemyMove(mainrect.x,mainrect.y,&enemyrect.x,&enemyrect.y);
    DrawGraphics(renderer,&mainrect,&enemyrect);
    SDL_Delay(16);
}
SDL_DestroyWindow(window);
SDL_Quit();

    
    return 0;
}
