#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

//these are the set dimensions of the two matricies A and B from which we wwill build our Resulting matracies
#define AROW 4
#define ACOL 3
#define BROW 3
#define BCOL 4

//Here we define the sizes of the matracies given the defined values above
//also rownum is used to keep track of what row we are on when multiplying rows and columns
int matA[AROW][ACOL];
int matB[BROW][BCOL];
int matC[AROW][BCOL];

//This function multiply the values in row m column k of matrix a by values of row k column n in matrix b
//we add the resulting values and that gives us the value at row m column n for the Matrix c
//one run of this function will give us one value matrix c
//we will later use 16 threads to call this function
void *dotProduct(void* arg)
{
    //takes the values out of the void pointer;
    int sum = 0;
    int m =((int*)arg)[0];
    int n =((int*)arg)[1];
    //was using this code to trouble shoot where the thread was at
        //cout << m << n;
        //cout << "row " << m << "column " << n << endl;
    //this multipies the values in matA row m by matB column n
    for(int k = 0; k < 3; k++)
    {
        sum += matA[m][k] * matB[k][n];
    }
    //store the value into matC
    matC[m][n] = sum;
}

int main()
{
    //number of threads
    int count = (AROW * BCOL);
    //initialize the values inside of matrix C to 0
    for(int i = 0; i < AROW; i++)
    {
        for (int j = 0; j < BCOL; j++)
        {
            matC[i][j] = 0;
        }
    }
    //asks the user to enter values for the matracies
    cout << "This program multiplies two matracies." << endl;
    cout << "One 4X3 Matrix and one 4X3 Matrix" << endl;
    cout << "now enter the values for matrix A." << endl;
    for(int i = 0; i < AROW; i++)
    {
        for(int j = 0; j < ACOL; j++)
        {
            cout << "row " << i << " column " << j << ": ";
            cin  >> matA[i][j];
        }
    }
    cout << "Matrix B" << endl;
    for(int i = 0; i < BROW; i++)
    {
        for(int j = 0; j < BCOL; j++)
        {
            cout << "row " << i << " column " << j << "; ";
            cin  >> matB[i][j];
        }
    }
    
    //prints the values of the matracies
    //each print statement goes row by row printing out the item of each column in the row
    cout << "Matrix A is: " << endl;
    for(int i = 0; i < AROW; i++)
    {
        for(int j = 0; j < ACOL; j++)
        {
            cout << matA[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix B: " << endl;
    for(int i = 0; i < BROW; i++)
    {
        for(int j = 0; j < BCOL; j++)
        {
            cout << matB[i][j] << " ";
        }
        cout << endl;
    }

    //This constructs the number of threads we will need for this program being the number of rows in the matrix C
    //it puts them into an array with location 0 to 15
    pthread_t threads[count];
    int threadcnt = 0;

    int *p;
    int buffer[2];
    p = buffer;
    for(int i = 0; i < AROW; i++)
    {
        for(int j = 0; j < BCOL; j++)
        {
            //passes the values of i and j to the function in order to track rows and columns
            p[0] = i;
            p[1] = j;
            //creates a thread initialized in pthread_t and sends it to do work on dotproduct
            pthread_create(&threads[threadcnt], NULL, dotProduct, (void*)(p));
            //this code was used for troubleshooting
                //cout << "creating thread " << threadcnt << endl;

            //tell program to wait for the thread to finish before moving to the next thread
            //this is necessary or else the values being passed to the process can get confused.
            pthread_join(threads[threadcnt], NULL);

            threadcnt ++;
        }
    }
    //prints the out put of the multiplied matrix.
    cout << "Multiplication of A and B" << endl;

    for(int i = 0; i < AROW; i++)
    {
        for(int j = 0; j < BCOL; j++)
        {
            cout << matC[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}