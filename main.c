#include "renderer.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>

bool dibujarPixel(uint32_t* buffer, int x, int y, uint32_t color);
void dibujarLinea(uint32_t* buffer, int x0, int x1, int y0, int y1, uint32_t color);
int main()
{   
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        puts("ERROR AL INICIAR VIDEO SDL3");
        return ERR_SDL;
    }

        

    SDL_Window *window = SDL_CreateWindow("3D RENDERER", SCREEN_W, SCREEN_H, SDL_WINDOW_EXTERNAL);
    
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
    uint32_t frameBuffer[SCREEN_H*SCREEN_W] = {0};
    bool running = true;
    dibujarLinea(frameBuffer, 0, 10, 0, 7, 0xAAAAAAAA);
    dibujarLinea(frameBuffer, 10, 0, 7, 0,  0xBBBBBBBB);
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

        //PROCESAR

        

        //RENDERIZAR
        SDL_UpdateTexture(texture, NULL, &frameBuffer, SCREEN_W*sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();


}


bool dibujarPixel(uint32_t* buffer, int x, int y, uint32_t color)
{
    if((x >= 0 && x <= SCREEN_W-1) && (y >= 0 && y <= SCREEN_H-1))
    {
        buffer[y * SCREEN_W + x] = color ; 
        return true;
    }

    return false;
}


void dibujarLinea(uint32_t* buffer, int x0, int x1, int y0, int y1, uint32_t color)
{   

    int distanciax = x1-x0;
    int distanciay = y1-y0;
    if(!distanciax && !distanciay)
    {
        dibujarPixel(buffer, x0, y0, color);
        return;
    }

    int acum=0;
    int dep;

    if(abs(distanciax) > abs(distanciay))
    {
        dep = y0;
        if(distanciax > 0)
        {
            for(int i = x0; i <= x1 ; i++)
            {   
            
                dibujarPixel(buffer, i, dep, color); 
                if(distanciay != 0)
                {
                    acum+=abs(distanciay);
                    if(acum >= abs(distanciax))
                    {
                        dep+= distanciay> 0 ? 1 : -1; 
                        acum -= abs(distanciax);
                    } 
                }

                
            }
        }
        else
        {
            for(int i = x0; i >= x1 ; i--)
            {   
            
                dibujarPixel(buffer, i, dep, color); 
                if(distanciay != 0)
                {
                    acum+=abs(distanciay);
                    if(acum >= abs(distanciax))
                    {
                        dep+= distanciay> 0 ? 1 : -1; 
                        acum -= abs(distanciax);
                    } 
                }

                
            }
        }
        
    }
    else
    {
        dep=x0;
        if(distanciay > 0)
        {
            for(int i = y0; i <= y1 ; i++)
                {   
                
                    dibujarPixel(buffer, dep, i, color); 
                    if(distanciax != 0)
                    {
                        acum+=abs(distanciax);
                        if(acum >= abs(distanciay))
                        {
                            dep+= distanciax> 0 ? 1 : -1; 
                            acum -= abs(distanciay);
                        } 
                    }

                }
        }
        else
        {
            for(int i = y0; i >= y1 ; i--)
                {   
                
                    dibujarPixel(buffer, dep, i, color); 
                    if(distanciax != 0)
                    {
                        acum+=abs(distanciax);
                        if(acum >= abs(distanciay))
                        {
                            dep+= distanciax> 0 ? 1 : -1; 
                            acum -= abs(distanciay);
                        } 
                    }

                }
        }
    }
 
    

  
        
}