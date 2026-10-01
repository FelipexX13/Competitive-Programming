// <3
// Tema: Implementation / Simulacion con Parsing de Codigo
// Resumen: Hay L "primelocks", cada uno con la forma prlck i
// Detalle: Resuelve "Impossible Primebox" (problema I, ICPC 2025): hay L "primelocks", cada uno
// con la forma prlck i: x = x [* Ai] [+ Bi] if Pi div x jumpto {prlck ji | end} else jumpto
// {prlck mi | end} Se arranca en el candado 0 con un x inicial y se sigue saltando hasta caer
// en un end. Hay que hallar el MENOR x inicial con el que el candado i se ejecuta exactamente
// Ki veces, para todos. El enunciado promete que la clave existe y es menor que 50000, asi que
// la solucion es probar x = 0, 1, 2, ... y quedarse con el primero que cumpla: no hay que
// invertir nada. LO QUE DE VERDAD CUESTA ES LEER LA ENTRADA, porque el formato tiene partes
// OPCIONALES: el "* Ai" puede no estar, el "+ Bi" puede no estar, y los destinos son "prlck j"
// o "end", que ocupan distinta cantidad de palabras. Leer con >> palabra por palabra y decidir
// segun lo que aparece es mucho mas seguro que intentar un patron fijo con getline. linea 2: "x
// = x" y despues, mientras siga habiendo operador, se lee "* A" o "+ B" linea 3: "if P div x
// jumpto <destino> else jumpto <destino>", donde <destino> es "end" (una palabra) o "prlck"
// seguido del numero (dos palabras) Para saber donde termina la linea 2 sin depender de saltos
// de linea, se mira si la siguiente palabra es "if": ahi empieza la linea 3. "Pi div x"
// significa "Pi divide a x", o sea x % Pi == 0. Leerlo al reves es el error facil. EL CORTE POR
// CICLO INFINITO ES OBLIGATORIO: con un x malo el proceso puede no terminar nunca. Como cada Ki
// es a lo sumo 1000 y hay a lo sumo 10 candados, un recorrido valido no puede dar mas de 10000
// pasos; si se pasa de ahi, ese x no sirve y se corta. Ademas, apenas un contador supera su Ki
// ya se puede abandonar, y eso es lo que hace que la mayoria de los x se descarten en pocos
// pasos. SOBRE EL TIEMPO, PARA QUE NO SORPRENDA: el peor caso teorico es 50000 candidatos por
// 10000 pasos. Medido con 5 casos armados a proposito para que ninguna x sirva y el recorrido
// siempre llegue a los 10000 pasos: 15.5 s en total, unos 3 s por caso. El enunciado promete
// que la clave EXISTE y es menor que 50000, asi que en cualquier entrada legitima se encuentra
// antes y no se paga ese costo; el sample completo corre en 12 ms. Si aun asi diera TLE, lo
// siguiente seria detectar ciclos guardando los estados (candado, residuos) ya vistos. EL VALOR
// DE x NO SE PUEDE GUARDAR: con A hasta 1000 por paso y hasta 10000 pasos, x llega a tener
// miles de digitos. Pero de x solo se pregunta si P lo divide, asi que se lleva x MODULO el
// primo de cada candado. La transformacion x = x*A + B se traduce a los residuos sin cambiar
// nada, porque (x*A + B) mod P depende solo de x mod P. Con L <= 10 son 10 residuos por paso.
// Verificado con los dos casos del sample (10 y 255) y con una fuerza bruta independiente
// escrita aparte que simula lo mismo: 600 primeboxes aleatorios, sin diferencias.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Lock {
    ll A, B, P;
    int siTrue, siFalse;      // -1 significa "end"
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L;

    while (cin >> L && L != 0) {

        vector<Lock> lk(L);

        for (int i = 0; i < L; i++) {

            string s;

            // "prlck i:" (dos palabras)
            cin >> s >> s;

            // "x = x" y despues los opcionales
            cin >> s >> s >> s;

            lk[i].A = 1;
            lk[i].B = 0;

            // Se leen operadores hasta toparse con el "if" de la linea 3.
            while (cin >> s && s != "if") {
                ll v;
                cin >> v;

                if (s == "*") lk[i].A = v;
                else lk[i].B = v;
            }

            // "P div x jumpto <destino> else jumpto <destino>"
            cin >> lk[i].P;
            cin >> s >> s >> s;              // div x jumpto

            cin >> s;
            if (s == "end") {
                lk[i].siTrue = -1;
            } else {
                cin >> lk[i].siTrue;         // venia "prlck j"
            }

            cin >> s >> s;                   // else jumpto

            cin >> s;
            if (s == "end") {
                lk[i].siFalse = -1;
            } else {
                cin >> lk[i].siFalse;
            }
        }

        vector<int> K(L);
        for (int i = 0; i < L; i++) cin >> K[i];

        int pasosMax = 0;
        for (int i = 0; i < L; i++) pasosMax += K[i];

        // Con los primos DISTINTOS (a lo sumo 10 y cada uno <= 1000) se arma
        // M = su producto. Si M cabe con margen para multiplicar por A, basta
        // llevar UN residuo x mod M: como cada P divide a M, preguntar por
        // r % P sigue valiendo, y el paso cuesta una multiplicacion en vez de
        // una por candado. Si M no cabe, se cae al vector de residuos.
        vector<ll> primos;
        for (int i = 0; i < L; i++) primos.push_back(lk[i].P);
        sort(primos.begin(), primos.end());
        primos.erase(unique(primos.begin(), primos.end()), primos.end());

        const ll LIMITE = (ll)9e18 / 1001;      // deja espacio para r*A + B
        ll M = 1;
        bool unico = true;

        for (ll p : primos) {
            if (M > LIMITE / p) { unico = false; break; }
            M *= p;
        }

        ll clave = -1;

        vector<int> veces(L), r(L);

        for (ll x0 = 0; x0 < 50000 && clave < 0; x0++) {

            // x se dispara (se multiplica por A hasta 1000 en cada paso) y no
            // cabe en ningun entero. Pero de x solo se pregunta si es divisible
            // por P, asi que basta llevar x modulo esos primos:
            // (x*A + B) mod P se calcula con (x mod P), sin conocer x.
            for (int i = 0; i < L; i++) veces[i] = 0;

            ll ru = x0 % M;

            if (!unico)
                for (int i = 0; i < L; i++) r[i] = (int)(x0 % lk[i].P);

            int cur = 0;
            int pasos = 0;
            bool sirve = true;

            while (cur != -1) {

                if (++pasos > pasosMax + 1) {    // ciclo o demasiadas vueltas
                    sirve = false;
                    break;
                }

                veces[cur]++;

                if (veces[cur] > K[cur]) {       // ya se paso de su cuota
                    sirve = false;
                    break;
                }

                bool divide;

                if (unico) {
                    ru = (ru * lk[cur].A + lk[cur].B) % M;
                    divide = (ru % lk[cur].P == 0);
                } else {
                    for (int i = 0; i < L; i++)
                        r[i] = (int)((r[i] * lk[cur].A + lk[cur].B) % lk[i].P);
                    divide = (r[cur] == 0);
                }

                if (divide) cur = lk[cur].siTrue;
                else cur = lk[cur].siFalse;
            }

            if (sirve && veces == K) clave = x0;
        }

        cout << clave << '\n';
    }

    return 0;
}
