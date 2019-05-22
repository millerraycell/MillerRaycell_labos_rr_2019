#include<iostream>
#include <stdlib.h>

using namespace std;

// Quantidade de processos
const int P = 5;

// Quantidade de recursos
const int R = 3;

// Função que calcula quantos recursos cada processo precisa
int** calculateNeed(int maximo[P][R], int alocado[P][R])
{
    // Matriz da necessidade de recursos
    int **necessita = (int**)malloc(P*sizeof(int*));
    for(int i = 0; i < P ; i++)
    {
    	necessita[i] = (int*) malloc (R*sizeof(int));
    }

    for (int i = 0 ; i < P ; i++)
    {
    	for (int j = 0 ; j < R ; j++)
    	{
    		//Quantidade necessária é a quantidade máxima menos a
    		//Quantidade disponível
    		necessita[i][j] = maximo[i][j] - alocado[i][j];
    	}
    }
    return necessita;
}

// Function to find the system is in safe state or not
bool isSafe(int processos[], int disponivel[], int maximo[][R], int alocado[][R])
{
    int **necessita = calculateNeed(maximo, alocado);

    // Indica que todos os processos ainda não foram finalizados
    bool terminado[P] = {0};

    // Salva a sequência dos processos
    int sequencia[P];

    // Cópia dos recursos
    int recursos[R];

    for (int i = 0; i < R ; i++)
    {
        recursos[i] = disponivel[i];
    }


    int cont = 0;
    while (cont < P)
    {
    	//encontra processo que ainda não foi finalizado e dá recursos a ele
        bool encontrado = false;
        for (int p = 0; p < P; p++)
        {
            if (terminado[p] == 0)
            {
            	int j;
                for (j = 0; j < R; j++)
                {
                	//Se a quantidade de recursos que o processo necessita for maior do que a
                	//quantidade disponível, o laço irá parar pois esse é o processo que precisa
                	//de mais recursos
                    if (necessita[p][j] > recursos[j])
                    {
                        break;
                    }
                }

                //Se o processo

                if (j == R)
                {
                    for (int k = 0 ; k < R ; k++)
                    {
                        recursos[k] += alocado[p][k];
                    }

                    sequencia[cont++] = p;

                    terminado[p] = 1;

                    encontrado = true;
                }
            }
        }

        if (encontrado == false)
        {
            cout << "System is not in safe state" << endl;
            return false;
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < P ; i++)
    {
        cout << sequencia[i] << " ";
    }
    cout << endl;

    return true;
}

int main()
{
    int processos[] = {0, 1, 2, 3, 4};


    int disponivel[] = {3, 3, 2};


    int maximo[][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    int alocado[][R] = {{0, 1, 0},
                      {2, 0, 0},
                      {3, 0, 2},
                      {2, 1, 1},
                      {0, 0, 2}};

    isSafe(processos, disponivel, maximo, alocado);

    return 0;
}
