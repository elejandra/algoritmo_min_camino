#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define limite_inferior 1
#define limite_superior 11
#define CENTRO matriz[i][j]
#define ARRIBA matriz[i-1][j]
#define ABAJO matriz[i+1][j]
#define DERECHA matriz[i][j+1]
#define IZQUIERDA matriz[i][j-1]

using namespace std;

class Tablero{
    public:
        int matriz[100][100];   // se declara la matriz para representar el tablero de números
        bool matriz_historial[100][100];
        int altura_ancho;  //atributo que indica el largo y ancho de la matriz
        int costo_maximo=10000;
        int costo_actual=0;
        LONG64 cantidad_de_pasos=0;
        string matriz_camino[100][100];
    public:
        Tablero(int);
        void mostrarTablero();
        int obtenerLargoMatriz();
        void mostrarCostoMinimo();
        bool estaDentro(int,int);
        bool llegoFinal(int,int);
        void avanzar(int,int,int,int,int);
        bool estuvo(int,int);
        void mostrarTableroHistorial();
        void mostrarCamino();
        void llenarMatrizCamino();
};
Tablero::Tablero(int _altura_ancho){
    int i,j;
    altura_ancho = _altura_ancho;
    // Ahora se procede a inicializar los números aleatoreos del tablero desde este constructor
    srand(time(NULL));
    for(i=0;i<altura_ancho;i++){
        for(j=0;j<altura_ancho;j++){
            matriz[i][j]=limite_inferior+rand()%(limite_superior-limite_inferior);
        }
    }

    for(i=0;i<altura_ancho;i++){
        for(j=0;j<altura_ancho;j++){
            matriz_historial[i][j]=false;
        }
    }


}

void Tablero::mostrarTablero(){
    int i,j;
    for(i=0;i<altura_ancho;i++){
        for(j=0;j<altura_ancho;j++){
            cout << matriz[i][j] << "\t";
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

void Tablero::mostrarTableroHistorial(){
    int i,j;
    for(i=0;i<altura_ancho;i++){
        for(j=0;j<altura_ancho;j++){
            cout << matriz_historial[i][j] << "\t";
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

void Tablero::mostrarCamino(){
    int i,j;
    for(i=0;i<altura_ancho;i++){
        for(j=0;j<altura_ancho;j++){
            cout << matriz_camino[i][j] << "\t";
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

int Tablero::obtenerLargoMatriz(){
    return altura_ancho;
}

bool Tablero::estaDentro(int i,int j){
    if(i >= 0 && j >= 0){
        if(i < altura_ancho && j < altura_ancho){
            return true;
        }
    }
    return false;
}

bool Tablero::llegoFinal(int i,int j){
    if(i == altura_ancho-1 && j == altura_ancho-1){
        return true;
    }
    return false;
}

bool Tablero::estuvo(int i,int j){
    if(matriz_historial[i][j]){
        return true;
    }
    return false;
}

void Tablero::llenarMatrizCamino(){
    int n,m;
    for(n=0;n<altura_ancho;n++){
        for(m=0;m<altura_ancho;m++){
            if(matriz_historial[n][m]){
                matriz_camino[n][m]="|*|";
            }
            else if(!matriz_historial[n][m]){
                matriz_camino[n][m]='-';
            }
        }
    }
}

void Tablero::avanzar(int i, int j,int costo,int valor_posicion,int desicion){
    if (estaDentro(i, j)) {
            cantidad_de_pasos=cantidad_de_pasos+1;
            matriz_historial[i][j]=true;
            if (llegoFinal(i, j)) {
                    cout << "Costo actual: " << costo << endl;
                if(costo<costo_maximo){
                    costo_maximo=costo;
                    llenarMatrizCamino();
                }
            }

            if(desicion==1){
                if(estaDentro(i+1,j) && !estuvo(i+1,j) && ((costo + abs(CENTRO-matriz[i+1][j]))<costo_maximo)){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i+1  ,  j  ,  costo + abs(CENTRO-matriz[i+1][j])  ,  matriz[i+1][j] , 0);
                }
                if(estaDentro(i,j+1) && !estuvo(i,j+1) && (costo + abs(CENTRO-matriz[i][j+1]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i  ,  j+1  ,  costo + abs(CENTRO-matriz[i][j+1])  ,  matriz[i][j+1] , 0);
                }
                if(estaDentro(i,j-1) && !estuvo(i,j-1) && (costo + abs(CENTRO-matriz[i][j-1]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i  ,  j-1  ,  costo + abs(CENTRO-matriz[i][j-1])  ,  matriz[i][j-1] , 0);
                }
                if(estaDentro(i-1,j) && !estuvo(i-1,j) && (costo + abs(CENTRO-matriz[i-1][j]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i-1  ,  j  ,  costo + abs(CENTRO-matriz[i-1][j])  ,  matriz[i-1][j] , 0);
                }
            }
            if(desicion==0){
                if(estaDentro(i+1,j) && !estuvo(i+1,j) && ((costo + abs(CENTRO-matriz[i+1][j]))<costo_maximo)){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i+1  ,  j  ,  costo + abs(CENTRO-matriz[i+1][j])  ,  matriz[i+1][j] , 1);
                }
                if(estaDentro(i,j+1) && !estuvo(i,j+1) && (costo + abs(CENTRO-matriz[i][j+1]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i  ,  j+1  ,  costo + abs(CENTRO-matriz[i][j+1])  ,  matriz[i][j+1] , 1);
                }
                if(estaDentro(i,j-1) && !estuvo(i,j-1) && (costo + abs(CENTRO-matriz[i][j-1]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i  ,  j-1  ,  costo + abs(CENTRO-matriz[i][j-1])  ,  matriz[i][j-1] , 1);
                }
                if(estaDentro(i-1,j) && !estuvo(i-1,j) && (costo + abs(CENTRO-matriz[i-1][j]))<costo_maximo){ // SE PREGUNTA SI LA POSICIÓN A LA QUE SE QUIERE AVANZAR ESTÁ ADENTRO DE LA MATRIZ
                    avanzar(  i-1  ,  j  ,  costo + abs(CENTRO-matriz[i-1][j])  ,  matriz[i-1][j] , 1);
                }
            }
            matriz_historial[i][j]=false;
        }
}

void Tablero::mostrarCostoMinimo(){
    cout << "El camino mas optimo cuesta: " << costo_maximo << endl;
}

int main()
{

    Tablero tablero(3);
    tablero.avanzar(0,0,0,tablero.matriz[0][0],1);
    tablero.mostrarCostoMinimo();
    cout << "Cantidad de pasos: " << tablero.cantidad_de_pasos << endl;
    tablero.mostrarTablero();
    tablero.mostrarCamino();
    return 0;
}
