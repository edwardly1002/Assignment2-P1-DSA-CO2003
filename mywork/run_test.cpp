#include <bits/stdc++.h>
using namespace std;

#include "BKUTree_imp.cpp"                      //include your BKUTree.cpp

ifstream ifile;
ofstream ofile;

string in_name[] = {"tcAVL", "tcSplay", "tcBKU"};
string out_name[] = {"outAVL", "outSplay", "outBKU"};

int num_test[] = {500, 1000, 5000};

void func(int key, int val) {
    ofile << key << " ";
}

void run_test_debug() {
    int a, b;
    ifile >> a >> b;
    
    BKUTree<int,int> *tree = new BKUTree<int,int>();

    ///TEST ADD
    cerr << "__________START_ADD________" << endl;
    int cnt_line = 1;
    for (int i = 0; i < b; ++i) { 
        cerr << "Line: " << ++cnt_line << " --- ";
        int k, v; 
        ifile >> k >> v; 
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);   
        cerr << "SUCCESS" << '\n';
    }
    for (int i = 0; i < b/4; ++i) { 
        cerr << "Line: " << ++cnt_line << " --- ";
        int k, v; 
        ifile >> k >> v; 
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
        cerr << "SUCCESS" << '\n';
    }

    cerr << "__________DONE_ADD________" << endl;
    cerr << "__________START_SEARCH________" << endl;
    ///TEST SEARCH
    for (int i = 0; i < b/2; ++i) { 
        cerr << "Line: " << ++cnt_line << " --- ";
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
        cerr << "SUCCESS" << '\n';
    }
    for (int i = 0; i < b/4; ++i) { 
        cerr << "Line: " << ++cnt_line << " --- ";
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
        cerr << "SUCCESS" << '\n';
    }
    
    cerr << "__________DONE_SEARCH________" << endl;
    cerr << "__________START_DELETE________" << endl;
    ///TEST DELETE
    for (int i = 0; i < b/4; ++i) { 
        cerr << "Line: " << ++cnt_line << " --- ";
        int k; 
        ifile >> k; 
        try {
            tree->remove(k); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
        cerr << "SUCCESS" << '\n';
    }

    for (int i = 0; i < b; ++i) {
        cerr << "Line: " << ++cnt_line << " --- ";
        int k;
        ifile >> k;
        try {
            tree->remove(k);
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);
        cerr << "SUCCESS" << '\n';
    }
    cerr << "__________DONE_DELETE________" << endl;
    delete tree;
}

void run_test() {
    int a, b;
    ifile >> a >> b;
    
    BKUTree<int,int> *tree = new BKUTree<int,int>();

    ///TEST ADD
    int cnt_line = 1;
    for (int i = 0; i < b; ++i) { 
        int k, v; 
        ifile >> k >> v; 
        ofile << "Input line: " << ++cnt_line << " /  ADD: " << k << ' ' << v << endl;
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);   
        ofile << "----------------------------------------------------" << endl;
    }
    for (int i = 0; i < b/4; ++i) { 
        int k, v; 
        ifile >> k >> v; 
        ofile << "Input line: " << ++cnt_line << " /  ADD: " << k << ' ' << v << endl;
        try {
            tree->add(k, v); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
        ofile << "----------------------------------------------------" << endl;
    }

    ///TEST SEARCH
    for (int i = 0; i < b/2; ++i) { 
        int k; 
        ifile >> k; 
        ofile << "Input line: " << ++cnt_line << " /  SEARCH: " << k  << endl;
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
        ofile << "----------------------------------------------------" << endl;
    }
    for (int i = 0; i < b/4; ++i) { 
        int k; 
        ifile >> k; 
        ofile << "Input line: " << ++cnt_line << " /  SEARCH: " << k  << endl;
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
        ofile << "----------------------------------------------------" << endl;
    }
    
    ///TEST DELETE
    for (int i = 0; i < b/4; ++i) { 
        int k; 
        ifile >> k; 
        ofile << "Input line: " << ++cnt_line << " /  DEL: " << k  << endl;
        try {
            tree->remove(k); 
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);  
        ofile << "----------------------------------------------------" << endl;
    }

    for (int i = 0; i < b; ++i) {
        int k;
        ifile >> k;
        ofile << "Input line: " << ++cnt_line << " /  DEL: " << k  << endl;
        try {
            tree->remove(k);
        }
        catch (const char* e) {
            ofile << e << endl;
        }
        tree->displayTrees(func, ofile);
        ofile << "----------------------------------------------------" << endl;
    }
    delete tree;
}

int main() {

    string path_input = "D:/Duy/Github/DSA_Assignment2-P1/test/";                    //input path
    string path_output = "D:/Duy/HCMUT/Assignment/DSA/Assignment 2/Duy_test/";       //output path, remember to create outAVL, outBKU, outSplay folders

    ///TEST AVL | Splay | BKU = 0 | 1 | 2
    for (int t = 0; t < 3; ++t) {
        for (int i = 1; i <= num_test[t]; ++i) {
            cerr << "Type: " << t << "   " << "Test: " << i << '\n';        //look at your terminal to see which test you are running
                                                                            //you can comment this line to run faster
            string in_path = path_input + in_name[t] + "/test" + to_string(i) + ".txt";
            string out_path = path_output + out_name[t] + "/test" + to_string(i) + ".txt";

            ifile.close();
            ofile.close();
            ifile.open(in_path);
            ofile.open(out_path);

            // run_test_debug();                    //run_test_debug shows which line is executing in your terminal
            run_test();

        }

    }

    return 0;
}