#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a[8];

void resetA(ll *a) {
    for (int i = 0; i < 7; ++i) a[i] = 0;
}

void assign(ll *a, ll *a1) {
    for (int i = 0;i < 7; ++i) a[i] = a1[i];
}

bool sol(ll *a, ll *a1) {
    ll accum = 0;
    ll same_type = 0;
    for (int i = 0; i < 7; ++i) {
        if (a[i] > 0 && a1[i] >0) same_type++;
        accum+=a[i];
    }
    return same_type >= accum/2;
}

int main() {
    int n;
    cin >> n;

    int m; 
    cin >> m; 

    resetA(a);
    for (int i = 0; i < m; ++i) {
        ll tmp;
        cin >> tmp;
        a[tmp%7]++;
    }

    bool flag = "true";
    for (int i = 1; i<n; ++i) {
        cin >> m; 
        ll a1[8];
        resetA(a1);
        for (int i = 0; i < m; ++i) {
            ll tmp;
            cin >> tmp;
            a1[tmp%7]++;
        }

        if (!sol(a, a1)) flag = false;
        assign(a, a1);
    }

    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}