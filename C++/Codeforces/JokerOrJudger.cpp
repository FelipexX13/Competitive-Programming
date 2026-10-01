// <3
// Tema: Implementation / Clasificacion de Cadenas por Prefijo
// Resumen: Cada reporte que llega es una cadena de una lista fija y vale cierto puntaje
// O: (n) por cadena
// Detalle: Cada reporte que llega es una cadena de una lista fija y vale cierto puntaje:
// UnreasonableProblemArrangement vale 10, WrongProblemX vale 100, SameProblemX vale 30,
// UnreasonableLimitForProblemX vale 5, WeakTestsForProblemX vale 3 y BadProblemX vale 1, donde
// X es una letra de la A a la L (los 12 problemas del contest). Cualquier otra cosa vale 0. Se
// suman los n reportes del caso y se responde Joker si el total pasa de P, y Judger si no. De
// algoritmo no tiene nada: es lectura cuidadosa. Lo unico que decide si pasa o no es no
// equivocarse contando caracteres, y por eso vale la pena tener la plantilla lista. LA CLAVE:
// validar s.size() ANTES de comparar el prefijo, y ese size() no es decorativo. s.substr(0, 12)
// sobre una cadena mas corta NO lanza excepcion, simplemente devuelve lo que alcance, asi que
// comparar solo el prefijo dejaria pasar "BadProblemAA" o "BadProblemABC". Fijar el largo
// exacto es lo que obliga a que haya EXACTAMENTE una letra despues del prefijo, y por eso
// s.back() de una vez es la letra del problema. Las seis ramas son mutuamente excluyentes
// porque cada una fija un largo distinto: 11, 12, 13, 20, 28 y 30. O sea que el orden de los if
// da igual, no hay una que tape a otra. Vale la pena revisarlo cuando se escribe algo asi,
// porque si dos plantillas compartieran largo Y prefijo, el orden si mandaria y el bug seria
// invisible. Verificado que los seis largos cuadran con sus prefijos (len(prefijo) + 1 ==
// size), que es justo el off-by-one que se cuela solo en este tipo de problema. Alternativas
// para comparar prefijos, por si el largo no se puede fijar: s.rfind(prefijo, 0) == 0 // busca
// el prefijo solo en la posicion 0 s.compare(0, k, prefijo) == 0 // sin crear el substring
// temporal Y ojo con el comparador final: es total > P estricto, empatar con P es Judger.

#include <bits/stdc++.h>
using namespace std;

int score(string s) {
    if (s == "UnreasonableProblemArrangement")
        return 10;

    if (s.size() == 13 && s.substr(0, 12) == "WrongProblem" &&
        s.back() >= 'A' && s.back() <= 'L')
        return 100;

    if (s.size() == 12 && s.substr(0, 11) == "SameProblem" &&
        s.back() >= 'A' && s.back() <= 'L')
        return 30;

    if (s.size() == 28 && s.substr(0, 27) == "UnreasonableLimitForProblem" &&
        s.back() >= 'A' && s.back() <= 'L')
        return 5;

    if (s.size() == 20 && s.substr(0, 19) == "WeakTestsForProblem" &&
        s.back() >= 'A' && s.back() <= 'L')
        return 3;

    if (s.size() == 11 && s.substr(0, 10) == "BadProblem" &&
        s.back() >= 'A' && s.back() <= 'L')
        return 1;

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, P;
        cin >> n >> P;

        int total = 0;

        while (n--) {
            string s;
            cin >> s;
            total += score(s);
        }

        cout << (total > P ? "Joker" : "Judger") << '\n';
    }
}
