#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN = 110;
const ll oo = 1e16;
const ll ooo = 2e9+1;

ll a[maxN][maxN], accum[maxN][maxN], odd[maxN][maxN];
ll ST[maxN][maxN<<2];

void update(int tree, int id, int l, int r, int u, ll val) {
    if (u < l || u > r) return ;
    if (l == r) {
        ST[tree][id] = val;
        return ;
    }

    int mid = (l+r) >> 1;
    update(tree, id<<1, l , mid, u, val);
    update(tree, id<<1|1,  mid+1, r, u, val);

    ST[tree][id] = min(ST[tree][id<<1], ST[tree][id<<1|1]);
}

ll get(int tree, int id, int l, int r, int u, int v) {
    if (v < l || u > r) return oo;
    if (l <= u && v <= r) return ST[tree][id];

    int mid = (l+r) >> 1;
    ll left = get(tree, id<<1, l, mid, u, v);
    ll right = get(tree, id<<1|1, mid+1, r, u, v);
    return min(left, right);
} 

void reset() {
    for (int i = 0; i < maxN; ++i) {
        for (int j = 0; j < maxN; ++j) {
            a[i][j] = 0;
            accum[i][j] = 0;
            odd[i][j] = 0;
        }
    }
    for (int i = 0; i < maxN; ++i) {
        for (int j = 0; j < maxN*4; ++j) {
            ST[i][j] = 0;
        }
    }
}

int main() {
    int t;
    cin >> t;

    for (int i = 1; i<=t; ++i) {
        reset();
        int m, n;
        cin >> m >> n;

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> a[i][j];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                accum[i][j] = accum[i-1][j] + accum[i][j-1] -accum[i-1][j-1]+ a[i][j];
                odd[i][j] = odd[i-1][j] + odd[i][j-1] - odd[i-1][j-1];
                if (a[i][j]%2 == 1) odd[i][j]++;
            }
        }

        // for (int i = 1; i <= m; ++i) {
        //     for (int j = 1; j <= n; ++j) {
        //         cout << accum[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        ll result = -oo;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 1; k <= i; ++k) {
                    for (int t = 1; t <= j; ++t) {
                        if (k==i && t==j) continue;
                        ll tmp = accum[i][j] - accum[i][t] - accum[k][j] + accum[k][t]; 
                        if (odd[i][j] == odd[i][t] + odd[k][j] - odd[k][t]) result = max(result, tmp);
                    }
                }
            }
        }

        cout << "Test " << i << ": ";
        if (result < 0) cout << "impossible" << endl;
        else cout << result << endl;

    }

    return 0;
}