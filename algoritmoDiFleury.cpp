// algoritmoDiFleury.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
using namespace std;
#define N 5

int nodoPartenza(int g[])
{
    int toReturn = 0;
    for (int i = 0; i < N; i++) {
        if (g[i] % 2 != 0) {
            toReturn = i;
            break;
        }
    }
    return toReturn;
}

void stampaMatrice(int matrice[][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}

void trovaGradoNodi(int grafo[][N], int array[N]) {
    for (int i = 0; i < N; i++) {
        int somma = 0;
        for (int j = 0; j < N; j++) {
            somma += grafo[i][j];
        }
        array[i] = somma;
    }
}

bool isAurealian(int grafoModificato[][N]) {
    int arrayGradi[N];
    trovaGradoNodi(grafoModificato, arrayGradi);
    int dispari = 0;
    bool toReturn = true;
    for (int i = 0; i < N; i++) {
        if (arrayGradi[i] % 2 == 1) {
            dispari++;
        }
    }
    if (dispari > 2 or dispari == 1) {
        toReturn = false;
    }
    return toReturn;
}

int trovaGradoGrafo(int grafo[][N]) {
    int toReturn = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grafo[i][j] == 1) {
                toReturn++;
            }

        }
    }
    return toReturn/2;
}

void riempiMatrice(int matrice[2][N], int grafo[][N]) {
    int arrayGradi[N];
    trovaGradoNodi(grafo, arrayGradi);

    for (int j = 0; j < N; j++) {
        matrice[0][j] = arrayGradi[j];
    }
    for (int j = 0; j < N; j++) {
        matrice[1][j] = j;
    }
}

void ordinaMatrice(int matrice[2][N]) {
    int appoggioGrado = 0;
    int appoggioNumeroNodo = 0;
    for (int j = 0; j < N - 1; j++) {
        for (int i = 0; i < N - 1; i++) {
            if (matrice[0][i] < matrice[0][i + 1]) {
                appoggioGrado = matrice[0][i];
                appoggioNumeroNodo = matrice[1][i];
                matrice[0][i] = matrice[0][i + 1];
                matrice[1][i] = matrice[1][i + 1];
                matrice[0][i + 1] = appoggioGrado;
                matrice[1][i + 1] = appoggioNumeroNodo;
            }
        }
    }
}

void trovaPercorso(int grafo[][N],int nodoPartenza,int gradoGrafo) {
    int nodoAttuale = nodoPartenza;
    int sequensLength = gradoGrafo+1;
    int nodiCollegamenti[2][N];
    int* sequenza = new int [sequensLength];
    sequenza[0] = nodoAttuale;
    int contatore = 0;

    for (int j = 0; j <sequensLength ; j++){
        riempiMatrice(nodiCollegamenti, grafo);
        ordinaMatrice(nodiCollegamenti);
        for (int i = 0; i < N; i++) {
            int colonna = nodiCollegamenti[1][i];
            if (grafo[nodoAttuale][colonna] == 1) {
                grafo[nodoAttuale][colonna] = 0;
                grafo[colonna][nodoAttuale] = 0;
                
                if (isAurealian(grafo)) {
                    nodoAttuale = colonna;
                    contatore++;
                    sequenza[contatore] = colonna;
                    break;
                }
                else {
                    grafo[nodoAttuale][colonna] = 1;
                    grafo[colonna][nodoAttuale] = 1;
                }
            }
        }
    }

    cout << "Sequenza: ";
    for (int i = 0; i < sequensLength; i++)
    {
        cout << sequenza[i] << " ";
    }
}


int main(){ 
    bool exit = 0;
    while (exit == 0) {
        int grafo[N][N] = { {0,1,1,1,1},
                           {1,0,1,1,1},
                           {1,1,0,1,1},
                           {1,1,1,0,1},
                           {1,1,1,1,0}
        };

        int arrayGradi[N];

        trovaGradoNodi(grafo, arrayGradi);
        stampaMatrice(grafo);

        for (int i = 0; i < N; i++) {
            cout << "Grado nodo " << i << " :" << arrayGradi[i] << endl;
        }

        cout << "Aureliano: " << isAurealian(grafo) << endl;

        cout << "Nodo di partenza: " << nodoPartenza(arrayGradi) << endl;

        cout << "Grado del grafo: " << trovaGradoGrafo(grafo) << endl;

        trovaPercorso(grafo, nodoPartenza(arrayGradi), trovaGradoGrafo(grafo));
        
        cout << endl << "Uscire dal programma(1) ripetere il programma(0)";
        cin >> exit;
        


    }
    return 0;
}


