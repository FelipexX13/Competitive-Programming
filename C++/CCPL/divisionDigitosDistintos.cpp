// <3
// Tema: Implementation / Generacion de Numeros con Digitos Distintos
// Resumen: Para cada N del caso de prueba, busca todos los pares (s1, s2) con s1 / s2 = N donde
// s1 y s2 tienen
// O: (cantidad de numeros con digitos distintos), generados una vez
// Detalle: Para cada N del caso de prueba, busca todos los pares (s1, s2) con s1 / s2 = N donde
// s1 y s2 tienen, cada uno por su lado, TODOS sus digitos distintos, y los imprime como "s1 /
// s2 = N". La idea es precalcular UNA SOLA VEZ la lista de todos los numeros con digitos
// distintos, y despues cada consulta solo recorre esa lista probando s1 = s2 * N. CUANTOS SON:
// el primer digito tiene 9 opciones (1-9, el 0 no abre), el segundo vuelve a tener 9 (los diez
// menos el ya usado, y ahi el 0 si vale), el tercero 8, y asi bajando. Sumando los largos de 1
// a 10 digitos: 9 + 81 + 648 + 4536 + 27216 + 136080 + 544320 + 1632960 + 3265920 + 3265920 =
// 8877690 Los de 9 y 10 digitos son la misma cantidad porque al decimo ya solo queda una
// opcion, y entre esos dos largos esta el 73% del total. Son ~68 MB de vector, asi que el
// reserve no es adorno: sin el, el vector duplica capacidad hasta 128 MB y puede costar el
// limite de memoria. LA GENERACION es backtracking puro con el esqueleto de siempre: marcar el
// digito, recursar, desmarcar. Se usa un bool usado[10] en vez de una mascara de bits a
// proposito, porque usado[d] se lee de una y mask & (1 << d) hay que decodificarlo. El
// desmarcado explicito es lo que deja ver que la rama del 2 puede volver a usar el 1. No hace
// falta comparar contra MAX_NUM al generar: el mayor numero con 10 digitos distintos ES
// 9876543210, asi que la recursion nunca se pasa sola. EL CORTE DE LA CONSULTA: como la lista
// esta ordenada, apenas s2 > MAX_NUM / N el producto ya se sale y todos los siguientes tambien,
// asi que se rompe el ciclo. Con N grande eso deja el recorrido en nada; con N = 2 todavia
// visita 7 millones, que es el peor caso. OJO CON DOS COSAS QUE CUESTAN TIEMPO Y NO SE VEN: -
// Imprimir con endl hace flush en CADA linea. Con N = 2 salen 680425 lineas y ahi se va la
// mayor parte del tiempo. Con '\n' la salida es identica y el caso completo baja de 2084 ms a
// 1390 ms (medido). - Si a la funcion de generar se le pone un tercer parametro y se llama
// generate(0, 0, 0), choca con std::generate de <algorithm> por el using namespace std y NO
// compila. Por eso aqui se llama armar. Es el mismo problema que tiene llamar remove a una
// funcion propia. Verificado: la salida es identica, linea por linea, a la version original que
// paso el juez, sobre 709320 lineas incluyendo el peor caso N = 2.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MAX_NUM = 9876543210LL;

vector<ll> nums;

// usado[d] = true si el digito d ya esta puesto en el numero que armamos.
bool usado[10];

// Arma numeros digito por digito, probando todas las opciones.
//   numero  = lo que llevamos armado hasta ahora
//   cuantos = cuantos digitos tiene ese numero
// Cada llamada decide CUAL es el siguiente digito que se pega al final.
void armar(ll numero, int cuantos) {
    // Si ya pusimos por lo menos un digito, lo que llevamos YA es un numero
    // valido (todos sus digitos son distintos), asi que se guarda.
    if (cuantos > 0) {
        nums.push_back(numero);
    }

    // Con 10 digitos distintos ya se usaron todos, no hay mas que pegar.
    if (cuantos == 10) {
        return;
    }

    // Se prueba cada digito que todavia no hayamos usado.
    for (int d = 0; d <= 9; d++) {
        if (usado[d]) {
            continue;
        }

        // El 0 no puede ir de primero (021 no es un numero de 3 digitos).
        if (cuantos == 0 && d == 0) {
            continue;
        }

        usado[d] = true;                        // se marca: ya lo usamos

        armar(numero * 10 + d, cuantos + 1);    // se pega al final y se sigue

        usado[d] = false;                       // se libera para la otra rama
    }
}

// Revisa si x tiene todos sus digitos distintos, sacandolos uno por uno.
bool distinctDigits(ll x) {
    int mask = 0;

    while (x > 0) {
        int d = x % 10;
        x /= 10;

        if (mask & (1 << d))
            return false;

        mask |= (1 << d);
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    nums.reserve(9000000);      // el total es 8877690, sin realocar

    armar(0, 0);

    sort(nums.begin(), nums.end());

    int T;
    cin >> T;

    while (T--) {
        ll N;
        cin >> N;

        for (ll s2 : nums) {
            // Si s2 * N se pasa del maximo, los siguientes tambien: corta.
            if (s2 > MAX_NUM / N)
                break;

            ll s1 = s2 * N;

            if (!distinctDigits(s1))
                continue;

            cout << s1 << " / " << s2 << " = " << N << '\n';
        }

        if (T)
            cout << '\n';
    }

    return 0;
}
