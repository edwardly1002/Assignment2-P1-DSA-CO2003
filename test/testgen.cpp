#include <bits/stdc++.h>
using namespace std;

string name[] = {"tcAVL", "tcSplay", "tcBKU"};

int avl[] = {100,300,500};
int splay[] = {200, 500, 1000};
int bku[] = {500, 2000, 5000};

ifstream ifile;
ofstream ofile;

void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++)  
    {  
        int k = rand()%2;
        if (arr[j] < pivot && k==0)   
        {  
            i++; 
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        int pi = partition(arr, low, high);   
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}

// bool comp(int a, int b) {
//     int n = rand()%2;
//     if (n==0) return a > b;
//     else return a < b;
// }

void makeACase(int a, int i, int nodes) {
    int arr[1000];
    for (int j = 0; j < 101; ++j) arr[j] = j;
    quickSort(arr, 0, nodes-1);

    string path = "test/" + name[a] + "/test" + to_string(i) + ".txt";
    freopen(path.c_str(), "w", stdout);

    cout << a << " " << nodes << endl;

    //TRUELY INSERT
    for (int j = 0; j < nodes; ++j) {
        cout << arr[j] << " " << arr[j] << endl;
    }
    //DUPLICATEKEY
    for (int j = 0; j < nodes/4; ++j) {
        int k = rand()%nodes;
        cout << k << " " << k << endl;
    }
    //SEARCH
    for (int j = 0; j < nodes/2; ++j) {
        int k = rand()%nodes;
        cout << k << endl;
    }
    //SEARCH NOT FOUND
    for (int j = 0; j < nodes/4; ++j) {
        int k = rand()%nodes+nodes;
        cout << k << endl;
    }
    //DELETE NOT FOUND
    for (int j = 0; j < nodes/4; ++j) {
        int k = rand()%nodes+nodes;
        cout << k << endl;
    }
    //DELETE 
    for (int j = 0; j < nodes; ++j) {
        cout << j << endl;
    }
}

int main() {
    srand(time(NULL));

    ///AVL
    for (int i = 1; i <= avl[0]; ++i) makeACase(0, i, 10);
    for (int i = avl[0]+1; i <= avl[1]; ++i) makeACase(0, i, 20);
    for (int i = avl[1]+1; i <= avl[2]; ++i) makeACase(0, i, 100);

    ///Splay
    // for (int i = 1; i <= splay[0]; ++i) makeACase(1, i, 10);
    // for (int i = splay[0]+1; i <= splay[1]; ++i) makeACase(1, i, 20);
    // for (int i = splay[1]+1; i <= splay[2]; ++i) makeACase(1, i, 100);

    ///BKU
    for (int i = 1; i <= bku[0]; ++i) makeACase(2, i, 10);
    for (int i = bku[0]+1; i <= bku[1]; ++i) makeACase(2, i, 20);
    for (int i = bku[1]+1; i <= bku[2]; ++i) makeACase(2, i, 100);

    return 0;
}