#include <iostream>
#include <thread>

using namespace std;

void csu(int);
void sb(int);
void csusb(int);
void number(int);

int main()
{
    int size = 0;
    int value = 0;

    cout << "This program will take an array of size n and determine an output based on the value at each index of the array." << endl;
    cout << "It will output: " << endl
         << "CSU when the value is divisable by 2" << endl
         << "SB when the value is divisable by 5" << endl
         << "CSUSB when the value is divisable by both" << endl
         << "the value when the value is divisable by none" << endl;
    cout << "What would you like the size of the array to be?" << endl;
    cin  >> size;

    int arr[size];
    cout << "Now enter " << size << " values for the array." << endl;
    for(int i = 0; i < size; i++)
    {
        cin >> value;
        arr[i] = value;
    }
    cout << "The array is full." << endl;
    cout << "Here's the output of the array." << endl;

    for(int i = 0; i < size; i++)
    {
        thread first (csu, arr[i]);
        thread second (sb, arr[i]);
        thread third (csusb, arr[i]);
        thread forth (number, arr[i]);

        first.join();
        second.join();
        third.join();
        forth.join();

    }

    cout << endl << endl;

    return 0;
}
void csu(int num)
{
    if(num % 2 == 0 && num % 5 != 0)
    {
        cout << "CSU" << " ";
    }
}
void sb(int num)
{
    if(num % 5 == 0 && num % 2 != 0)
    {
        cout << "SB" << " ";
    }
}
void csusb(int num)
{
    if(num % 2 == 0 && num % 5 == 0)
    {
        cout << "CSUSB" << " ";
    }
}
void number(int num)
{
    if(num % 2 != 0 && num % 5 != 0)
    {
        cout << num << " ";
    }
}