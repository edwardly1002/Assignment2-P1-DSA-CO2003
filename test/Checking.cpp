#include <bits/stdc++.h>
using namespace std;


string out_name[] = {"outAVL", "outSplay", "outBKU"};

int num_test[] = {500, 1000, 5000};

int main()
{
    string path_myOutput = "D:/Duy/HCMUT/Assignment/DSA/Assignment 2/Duy_test/";            //your output path
    string path_FriendOutput = "D:/Duy/Github/DSA_Assignment2-P1/test/Duy_test/";           //your friend output path
    for (int t = 0; t < 3; ++t) {                                                           
        for (int iTest = 1; iTest <= num_test[t]; ++iTest) {                                
            string myOut = path_myOutput + out_name[t] + "/test" + to_string(iTest) + ".txt";
            string friendOut = path_FriendOutput + out_name[t] + "/test" + to_string(iTest) + ".txt";
            // string myOut = "D:/Duy/HCMUT/Assignment/DSA/Assignment 2/myans.txt";         //your output of unit_test
            // string friendOut = "D:/Duy/HCMUT/Assignment/DSA/Assignment 2/ans.txt";       
            ifstream myF;
            ifstream friendF;
            myF.open(myOut);
            friendF.open(friendOut);
            if (!myF.is_open()){
                cout << "Cant find output " << iTest << " of type " << t << " in my output" << endl;
                return 0;
            }
            if (!friendF.is_open()){
                cout << "Cant find output " << iTest << " of type " << t << " in friend output" << endl;
                return 0;
            }
            string s1, s2;
            int cnt = 0;
            while(getline(myF, s1) && getline(friendF, s2)){
                ++cnt;
                if (s1 != s2) {
                    cout << "Type: " << t << "  Test: " << iTest << ": WRONG!\n" << "Line: " << cnt << '\n';
                    return 0;
                }
            }
            if (!getline(myF, s1) && !getline(friendF, s2))
                cout << "Type: " << t << "  Test: " << iTest << ": CORRECT!\n";
            else{
                cout << "Type: " << t << "  Test: " << iTest << ": Missing output\n";
                return 0;
            }
        }
    }
    return 0;
}