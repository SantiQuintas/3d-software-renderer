#include "renderer.h"

//MESHS
int cuboCrear(Mesh *mesh, Punto3D centro, float alto, float ancho, float profundidad)
{
    mesh->posicion = centro;
    mesh->posicion.z += centroZ;
    mesh->cantT = 12;
    mesh->cantV = 8;
    mesh->triangulos = malloc(mesh->cantT*sizeof(Triangulo));
    if(!mesh->triangulos)
        return ERR_MEM;

    mesh->vertices = malloc(mesh->cantV*sizeof(Punto3D));
    if(!mesh->vertices)
    {
         free(mesh->triangulos);
         return ERR_MEM;
     }
    mesh->verticesR = malloc(mesh->cantV*sizeof(Punto3D));
    if(!mesh->verticesR)
    {
        free(mesh->triangulos);
         free(mesh->vertices);
        return ERR_MEM;
    }

    //CARA TRASERA
    punto3DCrear(mesh->vertices, centro.x- ancho/2, centro.y - alto/2 , centro.z + profundidad/2);
    punto3DCrear(mesh->vertices+1, centro.x + ancho/2, centro.y - alto/2 , centro.z + profundidad/2);
    punto3DCrear(mesh->vertices+2, centro.x +  ancho/2, centro.y + alto/2 , centro.z + profundidad/2);
    punto3DCrear(mesh->vertices+3, centro.x - ancho/2, centro.y +  alto/2 , centro.z + profundidad/2);

    //CARA FRONTAL
    punto3DCrear(mesh->vertices+4, centro.x- ancho/2, centro.y - alto/2 , centro.z - profundidad/2);
    punto3DCrear(mesh->vertices+5, centro.x + ancho/2, centro.y - alto/2 , centro.z - profundidad/2);
    punto3DCrear(mesh->vertices+6, centro.x +  ancho/2, centro.y + alto/2 , centro.z - profundidad/2);
    punto3DCrear(mesh->vertices+7, centro.x - ancho/2, centro.y +  alto/2 , centro.z -  profundidad/2);

    //VerticesR
    *mesh->verticesR = *mesh->vertices;
    *(mesh->verticesR+1) = *(mesh->vertices+1);
    *(mesh->verticesR+2) = *(mesh->vertices+2);
    *(mesh->verticesR+3) = *(mesh->vertices+3);
    *(mesh->verticesR+4) = *(mesh->vertices+4);
    *(mesh->verticesR+5) = *(mesh->vertices+5);
    *(mesh->verticesR+6) = *(mesh->vertices+6);
    *(mesh->verticesR+7) = *(mesh->vertices+7);

    //cara trasera
    trianguloCrear(mesh->triangulos, 0,1,2); 
    trianguloCrear(mesh->triangulos+1, 0, 2, 3); 

    //cara frontal
    trianguloCrear(mesh->triangulos+2, 4, 5, 6); 
    trianguloCrear(mesh->triangulos+3, 4, 6, 7); 

    //base superior
    trianguloCrear(mesh->triangulos+4, 0,1, 5); 
    trianguloCrear(mesh->triangulos+5, 0, 5, 4); 

    //base inferior
    trianguloCrear(mesh->triangulos+6, 2, 6, 3); 
    trianguloCrear(mesh->triangulos+7, 3 ,7 , 6); 

    
    //cara izquierda
    trianguloCrear(mesh->triangulos+8, 0, 4, 3); 
    trianguloCrear(mesh->triangulos+9, 4, 7, 3); 

    //cara derecha
    trianguloCrear(mesh->triangulos+10, 1, 5, 2); 
    trianguloCrear(mesh->triangulos+11, 5, 6, 2); 

    return TODO_OK;
}

void meshDestruir(Mesh *mesh)
{
    mesh->cantT=0;
    mesh->cantV=0;
    free(mesh->triangulos);
    free(mesh->vertices);
    free(mesh->verticesR);
}

void dibujarMesh(uint32_t* buffer, float* zBuffer, Mesh* mesh, uint32_t color )
{
    for(int i=0; i < mesh->cantT ; i++)
    {   
        Triangulo* triangulo = mesh->triangulos + i;
        Punto3D v1Real = sumarPuntos3D(*(mesh->verticesR + triangulo->indices[0]), mesh->posicion);
        Punto3D v2Real = sumarPuntos3D(*(mesh->verticesR + triangulo->indices[1]), mesh->posicion);
        Punto3D v3Real = sumarPuntos3D(*(mesh->verticesR + triangulo->indices[2]), mesh->posicion);
        dibujarTriangulo(buffer, zBuffer, &v1Real, &v2Real, &v3Real, color, true);
    }
    
}
Punto3D sumarPuntos3D(Punto3D p1, Punto3D p2)
{
    Punto3D suma;
    suma.x = p1.x + p2.x;
    suma.y = p1.y + p2.y;
    suma.z = p1.z + p2.z;
    return suma;
}
void rotarMesh(Mesh *mesh, float angulo, bool x, bool y, bool z)
{
    for(int i=0; i < mesh->cantV ; i++)
    {   
        Punto3D* vertice = mesh->verticesR+i;
        Punto3D resultado = *(mesh->vertices+i);
        if(x)
           resultado = rotarX(&resultado, angulo);
        if(y)
           resultado = rotarY(&resultado, angulo);
        if(z)
           resultado = rotarZ(&resultado, angulo);

       *vertice = resultado;
    }
}


//ROTACIONES, ESCALAS Y MOVIMIENTO
Punto3D rotarY(Punto3D* p, float angulo)
{   
    float a = angulo * (PI/180);
    float zLocal = p->z;

    Punto3D pNuevo;
    pNuevo.x = p->x * cos(a) - zLocal * sin(a);
    pNuevo.y = p->y;
    pNuevo.z = p->x * sin(a) + zLocal * cos(a);
    return pNuevo;
}

Punto3D rotarX(Punto3D* p, float angulo)
{   
    float a = angulo * (PI/180);
    float zLocal = p->z;

    Punto3D pNuevo;
    pNuevo.x = p->x;
    pNuevo.y = p->y * cos(a) - zLocal * sin(a);
    pNuevo.z = p->y * sin(a) + zLocal * cos(a);

    return pNuevo;
}

Punto3D rotarZ(Punto3D* p, float angulo)
{   
    float a = angulo * (PI/180);
    float zLocal = p->z;

    Punto3D pNuevo;
    pNuevo.x = p->x * cos(a) +  p->y * sin(a) ;
    pNuevo.y = p->x * sin(a) -  p->y * cos(a) ;
    pNuevo.z = zLocal;

    return pNuevo;
}

void trianguloCrear(Triangulo* triangulo, int i1, int i2, int i3)
{
    triangulo->indices[0] = i1;
    triangulo->indices[1] = i2;
    triangulo->indices[2] = i3;
}

void punto3DCrear(Punto3D* p, float x, float y, float z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

void punto2DCrear(Punto2D* p, int x, int y)
{
    p->x = x;
    p->y = y;
}

void vector2DObtenerDePuntos(Punto2D p1, Punto2D p2, vec2D* vector)
{
    vector->x = p2.x - p1.x;
    vector->y = p2.y - p1.y;
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
    ort->x =  p1.y * p2.z - p1.z * p2.y;
    ort->y =  p1.z * p2.x - p1.x * p2.z;
    ort->z =  p1.x * p2.y - p1.y * p2.x;
}

void limpiarBuffers(uint32_t* buffer, float* zBuffer)
{
    memset(buffer, 0, SCREEN_H*SCREEN_W * sizeof(uint32_t));
    for (int i = 0; i < SCREEN_H * SCREEN_W; i++)
        zBuffer[i] = -1.0f;
}

float area2D(Punto2D a,Punto2D b,Punto2D c)
{
    return (b.x- a.x)*(c.y - a.y)- (b.y - a.y) *(c.x-a.x);
}

float area3D(Punto3D a,Punto3D b,Punto3D c)
{
        float abx = b.x - a.x;
    float aby = b.y - a.y;
    float abz = b.z - a.z;

    float acx = c.x - a.x;
    float acy = c.y - a.y;
    float acz = c.z - a.z;

    float nx = aby * acz - abz * acy;
    float ny = abz * acx - abx * acz;
    float nz = abx * acy - aby * acx;

    return sqrtf(nx*nx + ny*ny + nz*nz) / 2.0f;
}

float normaVec2D(vec2D v1)
{
    return sqrt(v1.x*v1.x + v1.y+v1.y);
}

void dibujarTriangulo(uint32_t* buffer, float *zBuffer, Punto3D* p0 , Punto3D* p1, Punto3D* p2, uint32_t color, bool relleno)
{
     Punto2D v0 = proyectarEn2D(p0);
     Punto2D v1 = proyectarEn2D(p1); 
     Punto2D v2 = proyectarEn2D(p2);
    if(relleno)
    {
        float z0 = p0->z;
        float z1 = p1->z;
        float z2 = p2->z;
        float a,b,c;
        float zP;

        float area = area2D(v0,v1,v2);
        if(area == 0)
            return;


    
        int minX = min(v0.x,v1.x,v2.x) >=0 ? min(v0.x,v1.x,v2.x) : 0;
        int maxX = max(v0.x,v1.x,v2.x) <= SCREEN_W ?  max(v0.x,v1.x,v2.x) : SCREEN_W;
        int minY = min(v0.y,v1.y,v2.y) >=0 ? min(v0.y,v1.y,v2.y) : 0;
        int maxY = max(v0.y,v1.y,v2.y)<= SCREEN_H? max(v0.y,v1.y,v2.y) : SCREEN_H ;
        
            for(int i = minY; i < maxY; i++)
            {
                Punto2D p;
                p.y = i;
                for(int j = minX ; j < maxX ; j++)
                {   
                    p.x = j;
                    //obtener coordenadas baricentricas
                    a =  area2D(p,v1,v2) / area;
                    b =  area2D(v0,p,v2) / area;
                    c =  area2D(v0,v1,p) / area;
                    zP = 1.0f/((1/z0)*a +(1/ z1) * b + (1/z2) * c);
                    bool puntoDentroDeCara = a >= 0 && b >= 0 && c >= 0;
                    if((*(zBuffer+(SCREEN_W*i+j))== -1  && puntoDentroDeCara ) || (*(zBuffer+(SCREEN_W*i+j)) > zP && puntoDentroDeCara))
                    {
                        *(zBuffer+(SCREEN_W*i+j)) = zP;
                        dibujarPixel(buffer, p.x, p.y, blanco);
                    }
                    
                }
                    
            }
    }
    else
    {
        dibujarLinea(buffer, &v0, &v1, color);
        dibujarLinea(buffer, &v1, &v2, color);
        dibujarLinea(buffer, &v2, &v0, color);
    }

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

bool puntoDentroDeCara(Punto2D a, Punto2D b, Punto2D c, Punto2D p)
{
    Punto2D ab, ac, ap;
    Punto2D ba, bc, bp;
    Punto2D ca, cb, cp;

    float z1, z2;
    float z3, z4;
    float z5, z6;
    bool cond1=false, cond2=false, cond3=false;
    vector2DObtenerDePuntos(a, b, &ab);
    vector2DObtenerDePuntos(a, c, &ac);
    vector2DObtenerDePuntos(a, p, &ap);

    vector2DObtenerDePuntos(b, a, &ba);
    vector2DObtenerDePuntos(b, c, &bc);
    vector2DObtenerDePuntos(b, p, &bp);

    vector2DObtenerDePuntos(c, a, &ca);
    vector2DObtenerDePuntos(c, b, &cb);
    vector2DObtenerDePuntos(c, p, &cp);

    // AB X AC
    z1 = ab.x * ac.y - ab.y * ac.x;
    // AB X AP
    z2 = ab.x * ap.y - ab.y * ap.x;

    // BC X BA
    z3 = bc.x * ba.y - bc.y * ba.x;
    // BC X BP
    z4 = bc.x * bp.y - bc.y * bp.x;

    // CA X CB
    z5 = ca.x * cb.y - ca.y * cb.x;
    // CA X CP
    z6 = ca.x * cp.y - ca.y * cp.x;

    cond1 = (z1 > 0 && z2 > 0) || (z1 < 0 && z2 < 0);
    cond2 = (z3 > 0 && z4 > 0) || (z3 < 0 && z4 < 0);
    cond3 = (z5 > 0 && z6 > 0) || (z5 < 0 && z6 < 0);    

    return cond1 && cond2 && cond3;
}
