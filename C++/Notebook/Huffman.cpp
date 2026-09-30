// <3
// Tema: Greedy / Huffman
// O: (n log n) con priority_queue
// Uso: lee frecuencias por stdin; el costo es la suma de las fusiones
// Costo minimo para combinar N elementos de a dos, donde cada combinacion cuesta la suma de
// los dos elementos y el resultado vuelve a la mesa. Aparece disfrazado como "unir cuerdas",
// "mezclar archivos ordenados" o "juntar montones de piedras".
// El greedy correcto es siempre combinar los dos MAS PEQUENOS disponibles, porque cada
// elemento paga su valor una vez por cada combinacion en la que participa, y los mas grandes
// deben participar en la menor cantidad posible. Un priority_queue de minimo lo resuelve en
// O(n log n). Cuidado: el acumulador debe ser long long, la suma crece rapido.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        pq.push(x);
    }

    long long cost = 0;
    while (pq.size() > 1)
    {
        long long x = pq.top(); pq.pop();
        long long y = pq.top(); pq.pop();
        cost += x + y;
        pq.push(x + y);
    }

    cout << cost << "\n";
    return 0;
}
