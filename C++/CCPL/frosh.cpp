// <3
// Tema: Data Structures / Conteo de Inversiones con Fenwick
// Resumen: Hay n estudiantes en fila y solo se pueden intercambiar PARES CONSECUTIVOS
// O: (n log n), inversiones con Fenwick
// Detalle: Resuelve "Frosh Week" (problema F, CCPL): hay n estudiantes en fila y solo se pueden
// intercambiar PARES CONSECUTIVOS; se pide el minimo de intercambios para dejarlos ordenados.
// LO QUE HAY QUE VER ES LA EQUIVALENCIA, porque el resto es una plantilla: cada intercambio de
// vecinos cambia el orden relativo de UNA sola pareja, asi que arreglar la fila cuesta
// exactamente tantos intercambios como PAREJAS DESORDENADAS haya, o sea el numero de
// INVERSIONES (pares i < j con a[i] > a[j]). No es una cota, es una igualdad: cada inversion
// hay que deshacerla y cada swap deshace una. COMO SE CUENTAN AQUI: se recorre de izquierda a
// derecha metiendo cada elemento en un Fenwick indexado por VALOR. Al llegar a a[i] ya hay i
// elementos adentro; de esos, fw.sum(pos) son los menores o iguales, asi que i - fw.sum(pos)
// son los MAYORES, y esos son justo los que quedaron a la izquierda siendo mas grandes: las
// inversiones que aporta a[i]. Se acumula y se inserta. La compresion de coordenadas (el
// lower_bound sobre el arreglo ordenado) no es opcional: los numeros de estudiante son
// arbitrarios y el Fenwick se indexa por posicion, no por valor. El +1 es porque un Fenwick es
// 1-indexado a la fuerza (con i = 0, i & -i vale 0 y el for no avanza nunca). El acumulador va
// en long long y eso TAMPOCO es opcional: con n = 10^6 al reves el total es n*(n-1)/2, casi
// 5*10^11, que revienta un int sin avisar. HAY OTRA FORMA, con merge sort, que esta en
// "froshMergeSort" en este mismo cuaderno. Medido con n = 10^6 en esta maquina, las dos ya
// arregladas: Fenwick 477 ms aleatorio, 335 invertido, 337 ordenado, ~16 MB merge sort con
// buffer unico 360 ms aleatorio, 311 invertido, 293 ordenado, ~8 MB O sea que para ESTE
// problema el merge sort gana, porque el Fenwick paga un sort y ademas guarda tres arreglos (a,
// el ordenado y el bit de long long) contra dos del merge. La razon para quedarse igual con la
// version de Fenwick es que se GENERALIZA: el mismo codigo, cambiando que se pregunta, cuenta
// cuantos hay menores que x, responde por rangos, o soporta actualizaciones. El merge sort solo
// sabe contar inversiones y se acabo. Verificado contra el sample y contra la version de merge
// sort sobre n = 10^6 en los tres casos (aleatorio, invertido y ya ordenado): mismo resultado,
// 250188280112 en el aleatorio.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    long long sum(int idx) {
        long long res = 0;

        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while (cin >> n) {

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<int> sorted = a;
        sort(sorted.begin(), sorted.end());

        Fenwick fw(n);

        long long god = 0;

        for (int i = 0; i < n; i++) {

            int pos = lower_bound(
                sorted.begin(),
                sorted.end(),
                a[i]
            ) - sorted.begin() + 1;

            god += i - fw.sum(pos);

            fw.add(pos, 1);
        }

        cout << god << '\n';
    }

    return 0;
}
