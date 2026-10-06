#include "renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{   
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        puts("ERROR AL INICIAR VIDEO SDL3");
        return ERR_SDL;
    }

    SDL_Window *window = SDL_CreateWindow("3D RENDERER", SCREEN_W, SCREEN_H, 0);
    
    if (!window)
        {
            printf("Error al crear ventana: %s\n", SDL_GetError());
            SDL_Quit();
            return ERR_SDL;
        }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, "software");
    
    if(!renderer)
    {
        printf("Error al crear renderer: %s\n", SDL_GetError());
        return ERR_SDL;
    }
    
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    
    if(!texture)
    {
        puts("ERROR AL INICIAR EL RENDERER");
        return ERR_SDL;
    }

    SDL_Event event;
    static uint32_t frameBuffer[SCREEN_H*SCREEN_W] = {0};
    static float zBuffer[SCREEN_H*SCREEN_W] = {-1};
    bool running = true;
    int tiempoAct;
    int tiempoAnt = 0;
    float tiempoTicks;
    float tiempoDelta;
    float angulo = 0.0;
    
    Punto3D cam;
    punto3DCrear(&cam, 0.0, 0.0, 0.0);
    Mesh cubo;
    cuboCrear(&cubo, cam, 2, 2, 2);

    while(running)
    {   
        //REVISAR EVENTOS
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            {
                running = false;
            }  
        }

        limpiarBuffers(frameBuffer, zBuffer);

        //Analizar ticks para regular los ticks por segundo al renderizar
        tiempoAct = SDL_GetPerformanceCounter();
        tiempoTicks = tiempoAct - tiempoAnt;
        tiempoDelta = tiempoTicks / SDL_GetPerformanceFrequency();
        tiempoAnt = SDL_GetPerformanceCounter();

        //PROCESAMIENTO
        
        dibujarMesh(frameBuffer, zBuffer, &cubo, blanco);
        rotarMesh(&cubo, angulo, true, true, true);
        angulo+=90*tiempoDelta;
        
        //RENDERIZADO
        SDL_UpdateTexture(texture, NULL, &frameBuffer, SCREEN_W*sizeof(uint32_t));
        SDL_RenderClear(renderer); 
        SDL_RenderTexture(renderer, texture, NULL, NULL); 
        SDL_RenderPresent(renderer);
        
    }
    //DESTRUIR Y LIBERAR MEMORIA
    cuboDestruir(&cubo);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
