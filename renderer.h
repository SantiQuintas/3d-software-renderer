#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


//SCREEN
#define SCREEN_H 480
#define SCREEN_W 640
#define ESCALA SCREEN_H/2

//RETURNS
#define TODO_OK 0
#define ERR_MEM -1
#define ERR_SDL -2


//COLORS
#define blanco 0xFFFFFFFF
#define negro 0x00000000
#define rojo 0xFF0000FF
#define verde 0x0FF000FF

#define PI 3.14159265359
typedef struct
{
    int x;
    int y;
} Punto2D;

typedef struct
{
    float x;
    float y;
    float z;
} Punto3D;

typedef Punto3D vec3D;
void puntoCrear(Punto2D* p, int x, int y);
void punto3DCrear(Punto3D* p, float x, float y, float z);
#endif //RENDERER_H