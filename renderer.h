#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


//MESHS
#define cuboDestruir meshDestruir
#define piramideDestruir meshDestruir
#define esferaDestruir meshDestruir
//SCREEN
#define SCREEN_H 480
#define SCREEN_W 640
#define ESCALA SCREEN_H/2
#define centroZ 4.5
//RETURNS
#define TODO_OK 0
#define ERR_MEM -1
#define ERR_SDL -2


//COLORS
#define blanco 0xFFFFFFFF
#define negro 0x00000000
#define rojo 0xFF0000FF
#define verde 0x0FF000FF

//MATH
#define PI 3.14159265359
#define max(a,b,c) (a)>(b) && (a)>(c)?  a : (b)>(c) ? b : c 
#define min(a,b,c) (a)<(b) && (a)<(c)?  a : (b)<(c) ? b : c 

//TIPOS DE DATOS
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

typedef struct
{
   int indices[3];
} Triangulo;


typedef struct
{
    int cantV;
    int cantT;

    Punto3D *verticesR;
    Punto3D *vertices;
    Punto3D posicion;
    Triangulo *triangulos;

} Mesh;

typedef struct
{
    float m[3][3];
} matriz3;


typedef Mesh Cubo;
typedef Mesh Piramide;
typedef Mesh Esfera;
typedef Punto3D vec3D;
typedef Punto2D vec2D;



//ROTACIONES, ESCALAS Y MOVIMIENTOS
Punto3D rotarX(Punto3D* p, float angulo);
Punto3D rotarY(Punto3D* p, float angulo);
Punto3D rotarZ(Punto3D* p, float angulo);
void rotarMesh(Mesh *mesh, float angulo, bool x, bool y, bool z);


//DIBUJO
bool dibujarPixel(uint32_t* buffer, int x, int y, uint32_t color);
void dibujarLinea(uint32_t* buffer, Punto2D* p0, Punto2D* p1, uint32_t color);
void dibujarRectangulo(uint32_t* buffer, int alto, int ancho, uint32_t color, void* centro);
void dibujarTriangulo(uint32_t* buffer,float *zBuffer, Punto3D* v0 , Punto3D* v1, Punto3D* v2, uint32_t color, bool relleno);
void dibujarCirculo(uint32_t* buffer, int radio, uint32_t color, void* centro);
void limpiarBuffers(uint32_t* buffer, float* zBuffer);
void dibujarMesh(Punto3D* cam,  uint32_t* buffer, float* zBuffer, Mesh* mesh, uint32_t color);


//CREAR GEOMETRICAS
void trianguloCrear(Triangulo* triangulo, int i1, int i2, int i3);
int cuboCrear(Mesh *mesh, Punto3D centro, float alto, float ancho, float profundidad);
void punto2DCrear(Punto2D* p, int x, int y);
void punto3DCrear(Punto3D* p, float x, float y, float z);
void meshDestruir(Mesh *mesh);

//GEOMETRIA
matriz3 multiplicarMatrices(matriz3 a, matriz3 b);
void vectorObtenerDePuntos(Punto3D p1, Punto3D  p2, vec3D* vector);
void vector2DObtenerDePuntos(Punto2D p1, Punto2D p2, vec2D* vector);
Punto2D proyectarEn2D(Punto3D* p);
float normaVec(vec3D v1);
float normaVec2D(vec2D v1);
void productoVectorial(vec3D p1, vec3D p2, vec3D* ort);
float productoEscalar(vec3D v1, vec3D v2);
float area2D(Punto2D a,Punto2D b,Punto2D c);
float area3D(Punto3D a,Punto3D b,Punto3D c);
Punto3D sumarPuntos3D(Punto3D p1, Punto3D p2);
void construirMatrices(matriz3* id, matriz3* x, matriz3* y, matriz3* z, float angulo);

//por las dudas no se si me va a volver a servir
bool puntoDentroDeCara(Punto2D a, Punto2D b, Punto2D c, Punto2D p);



#endif //RENDERER_H