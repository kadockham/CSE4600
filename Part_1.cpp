#include <iostream>

using namespace std;

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
        if(arr[i] % 2 == 0 && arr[i] % 5 == 0)
        {
            cout << "CSUSB" << " ";
        }
        else if(arr[i] % 2 == 0)
        {
            cout << "CSU" << " ";
        }
        else if(arr[i] % 5 == 0)
        {
            cout << "SB" << " ";
        }
        else
        {
            cout << arr[i] << " ";
        }
        
    }

    cout << endl;
    
    return 0;

}