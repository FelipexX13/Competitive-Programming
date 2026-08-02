// <3
// Tema: Data Structures / Fenwick Tree (Consultas offline)
// Resuelve "D-query" (problema H; el nombre de archivo conserva el guion del nombre original
// "D-query"): dada una secuencia a_1..a_n y q consultas (i, j), para cada una hay que responder
// cuantos elementos distintos hay en la subsecuencia a_i..a_j.
// Ordena las consultas por su extremo derecho j (vector order) y las procesa offline avanzando
// un puntero curJ de izquierda a derecha: por cada nueva posicion, si el valor ya aparecio antes
// (lastPos) le resta 1 en el BIT a su ocurrencia previa y suma 1 en la posicion actual, de modo
// que el BIT siempre cuenta, para cada valor, solo su ultima ocurrencia hasta curJ; la respuesta
// de cada consulta es query(j) - query(i-1).

#include <bits/stdc++.h>
using namespace std;

int bit_tree[30005];
int n;

void update(int pos, int val){
    for(; pos <= n; pos += pos & (-pos))
        bit_tree[pos] += val;
}

int query(int pos){
    int res = 0;
    for(; pos > 0; pos -= pos & (-pos))
        res += bit_tree[pos];
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    int q;
    cin >> q;

    vector<int> qi(q), qj(q);
    vector<int> order(q);
    for(int k = 0; k < q; k++){
        cin >> qi[k] >> qj[k];
        order[k] = k;
    }

    // sort query indices by right endpoint j
    sort(order.begin(), order.end(), [&](int x, int y){
        return qj[x] < qj[y];
    });

    vector<int> answer(q);
    unordered_map<int,int> lastPos; // value -> last position it was seen
    lastPos.reserve(1 << 20);

    int curJ = 0; // how far we've processed (1-indexed)
    for(int idx : order){
        int j = qj[idx];
        // advance pointer up to j, updating BIT
        while(curJ < j){
            curJ++;
            int val = a[curJ];
            auto it = lastPos.find(val);
            if(it != lastPos.end()){
                update(it->second, -1); // remove old occurrence's contribution
            }
            update(curJ, 1);
            lastPos[val] = curJ;
        }
        answer[idx] = query(j) - query(qi[idx] - 1);
    }

    for(int k = 0; k < q; k++)
        cout << answer[k] << "\n";

    return 0;
}