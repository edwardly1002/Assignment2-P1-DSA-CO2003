#include <bits/stdc++.h>
using namespace std;

#include "myBKU.cpp"

ifstream ifile;
ofstream ofile;

string in_name[] = {"tcAVL", "tcSplay", "tcBKU"};
string out_name[] = {"outAVL", "outSplay", "outBKU"};

int num_test[] = {500, 1000, 5000};

void func(int key, int val) {
    ofile << key << " ";
}

void run_test() {
    int a, b;
    ifile >> a >> b;
    
    BKUTree<int,int> *tree = new BKUTree<int,int>();

    ///TEST ADD
    for (int i = 0; i < b; ++i) { 
        int k, v; 
        ifile >> k >> v; 
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);   
    }
    for (int i = 0; i < b/4; ++i) { 
        int k, v; 
        ifile >> k >> v; 
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
    }
    
    ///TEST SEARCH
    for (int i = 0; i < b/2; ++i) { 
        int k; 
        ifile >> k; 
        vector<int> traversed;
        try {
            tree->search(k, traversed); 
            ofile << "TRAVERSED LIST: " << endl;
            for (int i : traversed) ofile << i << " ";
            ofile << endl;
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
    }
    for (int i = 0; i < b/4; ++i) { 
        int k; 
        ifile >> k; 
        vector<int> traversed;
        try {
            tree->search(k, traversed); 
            ofile << "TRAVERSED LIST: " << endl;
            for (int i : traversed) ofile << i << " ";
            ofile << endl;
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
    }
    

    ///TEST DELETE
    for (int i = 0; i < b/4; ++i) { 
        int k; 
        ifile >> k; 
        try {
            tree->remove(k); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
    }

    for (int i = 0; i < b; ++i) {
        int k;
        ifile >> k;
        try {
            tree->remove(k);
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);
    }

    delete tree;
}

int main() {

    string path = "Github/test/";

    ///TEST AVL | Splay | BKU = 0 | 1 | 2
    int t = 2;
    for (int t = 0; t < 3; ++t) {
        for (int i = 1; i <= num_test[t]; ++i) {
            string in_path = path + in_name[t] + "/test" + to_string(i) + ".txt";
            string out_path = path + out_name[t] + "/test" + to_string(i) + ".txt";

            ifile.close();
            ofile.close();
            ifile.open(in_path);
            ofile.open(out_path);

            run_test();

        }

    }

    return 0;
}