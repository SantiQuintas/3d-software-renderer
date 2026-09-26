#include "renderer.h"
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>



bool dibujarPixel(uint32_t* buffer, int x, int y, uint32_t color);
void dibujarLinea(uint32_t* buffer, Punto2D* p0, Punto2D* p1, uint32_t color);
void dibujarRectangulo(uint32_t* buffer, int alto, int ancho, uint32_t color, void* centro);
void dibujarTriangulo(uint32_t* buffer, Punto2D* v0 , Punto2D* v1, Punto2D* v2, uint32_t color);
void dibujarCirculo(uint32_t* buffer, int radio, uint32_t color, void* centro);
void limpiarBuffer(uint32_t* buffer);
void vectorObtenerDePuntos(vec3D p1, vec3D p2, vec3D* vector);
Punto3D rotarY(Punto3D* p, float angulo);
Punto2D proyectarEn2D(Punto3D* p);
void productoVectorial(vec3D p1, vec3D p2, vec3D* ort);
float productoEscalar(vec3D v1, vec3D v2);
float normaVec(vec3D v1);

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
    Punto3D p0,p1,p2,p3,p4,p5,p6,p7;
    Punto3D p0R,p1R,p2R,p3R,p4R,p5R,p6R,p7R;
    Punto2D v0,v1,v2,v3,v4,v5,v6,v7;
    p0.x = -1;
    p0.y = 1;
    p0.z = 6;
    v0 = proyectarEn2D(&p0);
      
    p1.x = 1;
    p1.y = 1;
    p1.z = 6;
    v1 = proyectarEn2D(&p1);

    p2.x = 1;
    p2.y = 1;
    p2.z = 3;
    v2 = proyectarEn2D(&p2);
        
    p3.x = -1;
    p3.y = 1;
    p3.z = 3;
    v3 = proyectarEn2D(&p3);

    p4.x = -1;
    p4.y = -1;
    p4.z = 6;
    v4 = proyectarEn2D(&p4);

    p5.x = 1;
    p5.y = -1;
    p5.z = 6;
    v5 = proyectarEn2D(&p5);

    p6.x = 1;
    p6.y = -1;
    p6.z = 3;
    v6 = proyectarEn2D(&p6);

    p7.x = -1;
    p7.y = -1;
    p7.z = 3;
    v7 = proyectarEn2D(&p7);
    int tiempoAct;
    int tiempoAnt = 0;
    float tiempoTicks;
    float tiempoDelta;
    float angulo = 0.0;
    vec3D ortogonalCamara;
    Punto3D cam;
    cam.x=0;
    cam.y=0;
    cam.z=0;
    Punto3D pA;
    pA.x=0;
    pA.y=0;
    pA.z=5;

    vec3D vec1;
    vec3D vec2;
    vec3D ort;
    vectorObtenerDePuntos(cam, pA, &ortogonalCamara);
    float direccion;

    while(running)
    {   
        tiempoAct = SDL_GetPerformanceCounter();
        tiempoTicks = tiempoAct - tiempoAnt;
    
        tiempoDelta = tiempoTicks / SDL_GetPerformanceFrequency();

        tiempoAnt = SDL_GetPerformanceCounter();

        
        
        //REVISAR EVENTOS
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            {
                running = false;
            }  
        }
        limpiarBuffer(frameBuffer);

        //PROCESAR
        
            p0R = rotarY(&p0, angulo);
            v0 = proyectarEn2D(&p0R); 

            p1R = rotarY(&p1, angulo);
            v1 = proyectarEn2D(&p1R); 

            p2R = rotarY(&p2, angulo);
            v2 = proyectarEn2D(&p2R); 

            p3R = rotarY(&p3, angulo);
            v3 = proyectarEn2D(&p3R); 

            p4R = rotarY(&p4, angulo);
            v4 = proyectarEn2D(&p4R); 

            p5R = rotarY(&p5, angulo);
            v5 = proyectarEn2D(&p5R); 

            p6R = rotarY(&p6, angulo);
            v6 = proyectarEn2D(&p6R); 

            p7R = rotarY(&p7, angulo);
            v7 = proyectarEn2D(&p7R); 

            angulo+=90*tiempoDelta;
        //RENDERIZAR
        //CARA SUPERIOR
        vectorObtenerDePuntos(p0R, p1R, &vec1);
        vectorObtenerDePuntos(p0R, p2R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion < 0)
        {
            dibujarTriangulo(frameBuffer, &v0, &v1, &v2, blanco);
            dibujarTriangulo(frameBuffer, &v0, &v2, &v3, blanco);
        }

        
        //CARAS LATERAL
        vectorObtenerDePuntos(p0R, p4R, &vec1);
        vectorObtenerDePuntos(p0R, p5R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion > 0)
        {
            dibujarTriangulo(frameBuffer, &v0, &v4, &v5, blanco);
            dibujarTriangulo(frameBuffer, &v0, &v1, &v5, blanco);
        }


        //CARAS LATERAL
        vectorObtenerDePuntos(p0R, p4R, &vec1);
        vectorObtenerDePuntos(p0R, p7R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion < 0)
        {   
            dibujarTriangulo(frameBuffer, &v0, &v4, &v7, blanco);
            dibujarTriangulo(frameBuffer, &v7, &v3, &v0, blanco);
        }


        //CARAS LATERAL
        vectorObtenerDePuntos(p6R, p5R, &vec1);
        vectorObtenerDePuntos(p6R, p2R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion > 0)
        {
            dibujarTriangulo(frameBuffer, &v6, &v5, &v2, blanco);
            dibujarTriangulo(frameBuffer, &v5, &v2, &v1, blanco);
        }


        //CARAS LATERAL
        vectorObtenerDePuntos(p7R, p6R, &vec1);
        vectorObtenerDePuntos(p7R, p2R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion > 0)
        {
            dibujarTriangulo(frameBuffer, &v7, &v6, &v2, blanco);
            dibujarTriangulo(frameBuffer, &v7, &v2, &v3, blanco);
        }


        //CARA INFERIOR
        vectorObtenerDePuntos(p7R, p4R, &vec1);
        vectorObtenerDePuntos(p7R, p6R, &vec2);
        productoVectorial(vec1, vec2, &ort);
        direccion = productoEscalar(ort, ortogonalCamara)/ (normaVec(ort) * normaVec(ortogonalCamara));
        if(direccion < 0)
        {
            dibujarTriangulo(frameBuffer, &v7, &v4, &v6, blanco);
            dibujarTriangulo(frameBuffer, &v4, &v5, &v6, blanco);
        }


        SDL_UpdateTexture(texture, NULL, &frameBuffer, SCREEN_W*sizeof(uint32_t));
        SDL_RenderClear(renderer); 
        SDL_RenderTexture(renderer, texture, NULL, NULL); 
        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
float normaVec(vec3D v1)
{
    return sqrt((v1.x * v1.x) + (v1.y * v1.y)+ (v1.z * v1.z));
}
float productoEscalar(vec3D v1, vec3D v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
void vectorObtenerDePuntos(vec3D p1, vec3D p2, vec3D* vector)
{
    vector->x = p2.x - p1.x;
    vector->y = p2.y - p1.y;
    vector->z = p2.z - p1.z;
}
void productoVectorial(vec3D p1, vec3D p2, vec3D* ort)
{
    ort->x =  p1.y * p2.z + p1.z * p2.y;
    ort->y =  p1.z * p2.x + p1.x * p2.z;
    ort->z =  p1.x * p2.y + p1.y * p2.x;
}

void limpiarBuffer(uint32_t* buffer)
{
    memset(buffer, 0, SCREEN_H*SCREEN_W * sizeof(uint32_t));
}

void dibujarTriangulo(uint32_t* buffer, Punto2D* v0 , Punto2D* v1, Punto2D* v2, uint32_t color)
{
    dibujarLinea(buffer, v0, v1, color);
    dibujarLinea(buffer, v1, v2, color);
    dibujarLinea(buffer, v2, v0, color);
}
Punto3D rotarY(Punto3D* p, float angulo)
{   
    float a = angulo * (PI/180);
    float zLocal = p->z-4.5;

    Punto3D pNuevo;
    pNuevo.x = p->x * cos(a) - zLocal * sin(a);
    pNuevo.y = p->y;
    pNuevo.z = p->x * sin(a) + zLocal * cos(a);
    pNuevo.z+=4.5;

    return pNuevo;
}

Punto2D proyectarEn2D(Punto3D* p)
{   
    Punto2D pantalla;
    pantalla.x = SCREEN_W/2;
    pantalla.y = SCREEN_H/2;
    

    float xProyectada = p->z ? p->x/ p->z * ESCALA : 0;
    float yProyectada = p->z ? p->y/ p->z * ESCALA : 0;

    pantalla.x += xProyectada;
    pantalla.y -= yProyectada;
    
    return pantalla;
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

void dibujarRectangulo(uint32_t* buffer, int alto, int ancho, uint32_t color, void* centro)
{

    int x = SCREEN_W/2;
    int y = SCREEN_H/2;

    //SI NO SE ESTABLECE UN CENTRO (RECIBIMOS NULL) EL CENTRO SERA EL MDIO DE LA PANTALLA
    if(centro)
    {
        Punto2D* punto = (Punto2D*) centro;
        x = punto->x;
        y = punto->y;
    }
 

    for(int i=x-ancho/2; i < x+ancho/2 ; i++)
    {   
        for(int j=y-ancho/2; j < y+alto/2 ; j++)
        {   
            if(j && i)
                dibujarPixel(buffer, i, j, color);
        }
    }
}

void dibujarCirculo(uint32_t* buffer, int radio, uint32_t color, void* centro)
{
    
    int x = SCREEN_W/2;
    int y = SCREEN_H/2;

    //SI NO SE ESTABLECE UN CENTRO (RECIBIMOS NULL) EL CENTRO SERA EL MDIO DE LA PANTALLA
    if(centro)
    {
        Punto2D* punto = (Punto2D*) centro;
        x = punto->x;
        y = punto->y;
    }
   
    for(int i=-radio; i<=radio; i++)
        for(int j=-radio; j<=radio; j++)
            if(i*i+j*j <= radio*radio) // evita dibujar fuera del radio
                dibujarPixel(buffer, x+i, y+j, color);
}

void dibujarLinea(uint32_t* buffer, Punto2D* p0, Punto2D* p1, uint32_t color)
{   
    int x0 = p0->x;
    int x1 = p1->x;
    int y0 = p0->y;
    int y1 = p1->y;

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