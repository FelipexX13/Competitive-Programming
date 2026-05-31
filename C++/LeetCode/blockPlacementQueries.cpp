// <3
// Tema: Data Structures / Segment Tree
// Resuelve "Block Placement Queries": usa un segment tree de maximos y un set de obstaculos
// para determinar si un bloque de tamano sz cabe en algun hueco del rango [0, x].

#include <bits/stdc++.h>
using namespace std;

typedef int T; // tipo de dato del segtree
struct segtree {
    vector<T> st; //, lazy;
    int n;
    T neutro = 0; // neutro para MAX (los huecos son >= 0)

    segtree(const vector<T> &v) {
        n = v.size();
        st.assign(n*4, 0);
        //lazy.assign(n*4, neutro);
        build(1, 0, n-1, v);
    }

    void build(int p, int L, int R, const vector<T> &v) {
        if (L == R) st[p] = v[L];
        else {
            int m=(L+R)/2, l=p*2, r=l+1;
            build(l,L,m,v); build(r,m+1,R,v);
            st[p] = max(st[l], st[r]);   // <- max
        }
    }

    /*
    void propagate(int p, int L, int R, T val) {
        if (val == neutro) return;
        st[p] = val;
        lazy[p] = neutro;
        if (L == R) return;
        int l = p*2, r = l+1;
        lazy[l] = lazy[r] = val;
    }
    */

    T query(int i, int j) { return query(1, 0, n-1, i, j); }
    void upd(int i, int j, T val) { upd(1, 0, n-1, i, j, val); }

    T query(int p, int L, int R, int i, int j) {
        //propagate(p, L, R, lazy[p]);
        if (i > R || j < L) return neutro;
        if (i <= L && R <= j) return st[p];
        int m=(L+R)/2, l=p*2, r=l+1;
        T lf = query(l, L, m, i, j);
        T rg = query(r, m+1, R, i, j);
        return max(lf, rg);          // <- max
    }

    void upd(int p, int L, int R, int i, int j, T val) {
        //propagate(p, L, R, lazy[p]);
        if (i > R || j < L) return;
        if (i <= L && R <= j) st[p] = val; // cambiar por propagate(p,L,R,val);
        else {
            int m=(L+R)/2, l=p*2, r=l+1;
            upd(l, L, m, i, j, val);
            upd(r, m+1, R, i, j, val);
            st[p] = max(st[l], st[r]);    // <- max
        }
    }
};

class Solution {
public:
    


    vector<bool> getResults(vector<vector<int>>& queries) {
        int MAX = 0;
        for (auto &q : queries) MAX = max(MAX, q[1]);

        vector<T> base(MAX + 1, 0);    // árbol de huecos, todo en 0
        segtree seg(base);

        set<int> obs = {0};            // 0 es la pared izquierda
        vector<bool> res;

        for (auto &q : queries) {
            if (q[0] == 1) {                        // colocar obstáculo en x
                int x = q[1];
                auto it = obs.lower_bound(x);       // primer elemento > x
                int prev = *std::prev(it);
                seg.upd(x, x, x - prev);            // hueco que termina en x
                if (it != obs.end()) {
                    int next = *it;
                    seg.upd(next, next, next - x);  // el hueco viejo se acorta
                }
                obs.insert(x);
            } else {                                // consulta [2, x, sz]
                int x = q[1], sz = q[2];
                auto it = obs.upper_bound(x);       // primer elemento > x
                int prev = *std::prev(it);          // mayor obstáculo <= x
                bool ok = (x - prev >= sz) || (seg.query(0, x) >= sz);
                res.push_back(ok);
            }
        }
        return res;


    }
};