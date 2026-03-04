/* Prototipo minimo para desarrollo de juegos
Objetivos:
- Mostrar un mapa fijo en consola por medio de ASCII
- Dibujar la posicion del jugador en el mapa (x,y)
- Leer comandos wasd para mover al jugador
- Evitar que el jugador atraviese paredes
*/

#include <stdio.h>
#include <string.h>

#define ALTO 10
#define ANCHO 20

/* 
Mapa fijo: cada cadena representa una fila del nivel
'#' representa una pared
'.' representa el piso
'*' representa la moneda
*/
static const char *mapa_fijo[ALTO] = {
    "####################",
    "#.............*....#",
    "#.######.########..#",
    "#.#....#.#......#..#",
    "#.#.##.#.#.####.#..#",
    "#...#...#....#....#",
    "#####.#########.####",
    "#.....#.......#....#",
    "#.#####.#####.###..#",
    "####################"
};

/* Limpia la consola de forma simple */
static void consola_limpiar_simple(void){
    //modelo simple para imprimir saltos de linea y separar
    //el cuadro (frame) anterior
    for(int i = 0; i < 40; i++){
        printf("\n");
    }
}

// Verifica si una posición es pared 
static int es_pared(const char mapa[ALTO][ANCHO+1], int x, int y){
    // Si se sale del mapa, lo tratamos como pared
    if(x < 0 || x >= ANCHO || y < 0 || y >= ALTO){
        return 1;
    }

    return mapa[y][x] == '#'; //es pared
}

//Dibuja el mapa y el jugador 
static void renderizar(const char mapa[ALTO][ANCHO+1], 
                       int jugador_x, 
                       int jugador_y, 
                       int pasos){

    consola_limpiar_simple();
     //encabezado del frame
    printf("SESION 1 | Pasos: %d\n\n", pasos);

    for(int y = 0; y < ALTO; y++){
        for(int x = 0; x < ANCHO; x++){
         //dubujar al Jugador por encima del mapa
            if(x == jugador_x && y == jugador_y){
                putchar('@'); 
            }
            else{
                putchar(mapa[y][x]);
            }
        }
        putchar('\n');
    }

    puts("\nControles: W A S D + Enter | Q salir");
}

int main(){

    /* Copiamos el mapa fijo a una matriz editable */
    //estoprepara el camino para renderizar monedas y otros cambios del mapa
    char mapa[ALTO][ANCHO+1];//para el caracter nulo de filas

    for(int y = 0; y < ALTO; y++){
        strncpy(mapa[y], mapa_fijo[y], ANCHO);
        mapa[y][ANCHO] = '\0';//asegurar el fin de cadena
    }

    int xJugador = 1;   // Posición inicial del jugador
    int yJugador = 1;
    int pasos = 0;//contador de pasos

    char tecla;

    while(1){// bucle principal del juego 
        //primer paso: Renderizamosel mapa en pantalla

        renderizar(mapa, xJugador, yJugador, pasos);

        printf(">");
        //*C ingora saltos de linea anteriores
        //SEgundos paso: leemos el comando del usuario
        if(scanf(" %c", &tecla) != 1)
            break;

        if(tecla == 'q' || tecla == 'Q')
            break;

        int dx = 0;
        int dy = 0;

        // Interpretar la tecla como un vector de movimiento
        if(tecla == 'w' || tecla == 'W') dy = -1;      // Arriba
        else if(tecla == 's' || tecla == 'S') dy = 1;  // Abajo
        else if(tecla == 'a' || tecla == 'A') dx = -1; // Izquierda
        else if(tecla == 'd' || tecla == 'D') dx = 1;  // Derecha

        int nx = xJugador + dx;
        int ny = yJugador + dy;

        //Solo mover si NO es pared en nuestra posicion
        if(!es_pared(mapa, nx, ny)){
            xJugador = nx;
            yJugador = ny;
            pasos++;
        }
    }

    puts("\nFin del prototipo. Gracias por jugar.");
    return 0;
}
