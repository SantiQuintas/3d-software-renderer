# SOFTWARE DE RENDERIZADO 3D EN C (wip)
Software de renderizado 3D programado en el lenguaje de C, el fin del proyecto es aprender tecnicas
y el funcionamiento del renderizado 3D por medio de algebra y geometria analitica. Hasta ahora 
se implemento la creacion de mesh, cubo como tambien el dibujo y rotacion de mesh.

## Requisitos
### GCC
Necesario para poder compilar el programa
### SDL3
Necesario para poder crear la ventana del renderer, uso de timers para limitar frames por segundo, dibujar los pixeles ubicados en el buffer del frame y detectar eventos de teclado.

## Compilacion
Para compilar se puede ejecutar el comando
```
gcc main.c renderer.c -o renderer.exe -lSDL3 -lm
```
## Ejecucion
Para ejecutar el programa compilado por terminal, utilice el siguiente comando
```
.\renderer.exe  
```
## Controles de Teclado
Con W, A, S, D, SPACE Y LCTRL se controla el movimiento de la camara

## Caracteristicas Implementadas
- Estructura Mesh
    - Los mesh se crean con tipoCrear, actualmente solo implemente
        el tipo de mesh Cubo, por lo que su funcion se llama cuboCrear
    - Los mesh tienen la funcion de rotar llamada rotarMesh, donde se
        pasa por parametro 3 bools para rotar en X, Y o Z
- Dibujo, todas las funciones se llaman dibujarX
    - 2D (Pixel, Linea, Triangulo, Circulo, Rectangulo)
    - 3D (dibujarMesh)
- Funciones relacionadas a algebra lineal y geometria
    - Vectores 2D, 3D
    - Producto Vectorial
    - Producto Escalar
    - Norma
    - Suma
    - Crear vector con 2 puntos
    - Proyectar un vector 3D en 2D
        - Esta funcion se encarga de transformar un vector
            en 3D dimensiones a 2D, traduciendo el entendimiento
            del eje Z a Proyectar mas grande la x e y del objeto