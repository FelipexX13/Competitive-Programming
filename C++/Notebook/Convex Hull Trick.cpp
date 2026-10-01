// <3
// Tema: Dynamic Programming / Convex Hull Trick
// Resumen: Optimiza DPs de la forma dp[i] = min sobre j de (m[j]*x[i] + b[j]), es decir
// O: (n) amortizado, add y query juntos
// Uso: cht.add(m,b) con m DECRECIENTE; cht.query(x) con x CRECIENTE
// Detalle: Optimiza DPs de la forma dp[i] = min sobre j de (m[j]*x[i] + b[j]), es decir, cuando
// cada estado anterior aporta una recta y hay que evaluar la envolvente inferior en x[i]. Baja
// de O(n^2) a O(n) amortizado. Mantiene un deque con solo las rectas que llegan a ser minimas
// en algun punto: al insertar una recta nueva se descartan por atras las que quedaron "tapadas"
// (su punto de corte ya no aporta), y al consultar se descartan por adelante las que ya
// quedaron atras del x pedido. Requiere que las pendientes se inserten monotonas (decrecientes
// para minimo) y que las x de consulta vengan crecientes; si no se cumple, hay que usar Li Chao
// Tree o CHT dinamico.

#include <bits/stdc++.h>

using namespace std;

struct CHT
{
    struct L { long long m, b; double x; };
    deque<L> dq;

    double inter(const L &a, const L &c)
    {
        return double(c.b - a.b) / double(a.m - c.m);
    }

    void add(long long m, long long b)
    {
        L l = {m, b, 0};
        while (dq.size() >= 2 && inter(dq[dq.size() - 2], dq.back()) >= inter(dq.back(), l))
        {
            dq.pop_back();
        }
        if (dq.empty()) l.x = -1e300;
        else l.x = inter(dq.back(), l);
        dq.push_back(l);
    }

    long long query(long long x)
    {
        while (dq.size() >= 2 && dq[1].x <= x)
        {
            dq.pop_front();
        }
        return dq.front().m * x + dq.front().b;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
