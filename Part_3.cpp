#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <stdlib.h>

using namespace std;

const int Arows = 4;
const int Acols = 3;
const int Brows = 3;
const int Bcols = 4;

vector <int> row[Arows];
vector <int> col[Bcols];
int C[Arows][Bcols];

int dotProduct(void* data)
{
    int i, j;
    sscanf((char *) data, "%d %d", &i, &j);

    int len, na, nb;
    na = row[i].size();
    nb = col[i].size();

    if (na > nb)
    {
        len = nb;
    }
    else
    {
        len = na;
    }
    int sum = 0;
    for(int k = 0; k < len; k++)
    {
        sum += row[i][k] * col[j][k];
    }
    C[i][j] = sum;

    return 0;
}
void printMat(int *m, int nRows, int nCols)
{
    for(int i = 0; i < nRows; i++)
    {
        printf("\n");
        for(int j = 0; j < nCols; j++)
        {
            printf("%3f\t", *(m+i*nCols+j));
        }
    }
}
int main()
{
    SDL_Thread *sumThread;
    int matA[][Acols] = {{5,2,3},{4,5,7},{6,3,7},{1,3,4}};
    int matB[][Brows] = {{4,5,6,1},{3,2,3,5},{2,8,7,7}};

    for(int i = 0; i < Arows; i++)
    {
        for(int j = 0; j < Acols; j++)
        {
            row[i].push_back (matA[i][j]);
        }
    }
    for(int j = 0; j < Bcols; j++)
    {
        for(int i = 0; i < Brows; i++)
        {
            col[j].push_back(matB[i][j]);
        }
    }
    char buffer[100];
    for(int i = 0; i < Arows; i++)
    {
        for(int j = 0; j < Brows; j++)
        {
            sprintf(buffer, "%d %d", i, j);
            sumThread = SDL_CreateThread(dotProduct, (void *)buffer);

            if(sumThread == NULL)
            {
                cout << "\nFailed" << SDL_GetError() << endl;
            }
            else
            {
                SDL_WaitThread(sumThread, NULL);
            }
        }
    }
    printMat(&matA[0][0], Arows, Acols);
    cout << endl << endl;
    printMat(&matB[0][0], Brows, Bcols);
    cout << endl << endl;
    printMat(&C[0][0], Arows, Bcols);

    return 0;

}