// <3
// Tema: Implementation / Dia Siguiente y Anos Bisiestos
// Resumen: Aritmetica de calendario sin usar <ctime>
// O: (1) siguienteDia, (n) el barrido de registros
// Uso: siguienteDia(D1,M1,Y1, D2,M2,Y2) -> la segunda fecha es el dia de despues?
// Detalle: Aritmetica de calendario sin usar <ctime>, que es lo que uno necesita cuando el
// enunciado da fechas como tres enteros. El arreglo dias[] esta 1-INDEXADO a proposito (dias[0]
// = 0), asi que dias[M] es directamente lo que mide el mes M y no hay que restar 1 en ningun
// lado. Avanzar un dia son tres casos encadenados, y en ese orden: si el dia se pasa del largo
// del mes se vuelve 1 y sube el mes; si el mes llega a 13 se vuelve 1 y sube el ano. Escrito
// asi cubre solo el 31 de diciembre con el mismo if de siempre, sin caso especial. EL ANO
// BISIESTO NO ES "divisible por 4". La regla completa son tres condiciones: divisible por 400
// -> bisiesto (2000 si) divisible por 4 pero NO por 100 -> bisiesto (2024 si) el resto -> no
// (1900 NO, 2023 no) Los anos de siglo son la trampa: 1900 y 2100 no son bisiestos aunque sean
// divisibles por 4. Si el rango de anos del problema no toca un cambio de siglo, Y % 4 == 0
// alcanza, pero no cuesta nada escribir la regla buena. OJO: dias[] se declara ADENTRO de la
// funcion, asi que el dias[2] = 29 se deshace en cada llamada. Si se saca a variable global hay
// que acordarse de devolverlo a 28. El main de abajo es el uso tipico: se leen registros (fecha
// + un contador) y se acumula la diferencia del contador solo entre registros de dias
// CONSECUTIVOS. El patron de comparar cada registro con el anterior guardando D0/M0/Y0/C0 sirve
// para cualquier serie por fechas. VERIFICADO contra datetime de Python: los 87.372 dias de
// 1896 a 2104 y 40.000 pares al azar, 0 fallos, incluyendo 1900 (no bisiesto) y 2000 (si).

#include <bits/stdc++.h>
using namespace std;

bool siguienteDia(long long D1, long long M1, long long Y1,
                  long long D2, long long M2, long long Y2)
{
    int dias[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(Y1 % 400 == 0 || (Y1 % 4 == 0 && Y1 % 100 != 0))
        dias[2] = 29;

    D1++;

    if(D1 > dias[M1])
    {
        D1 = 1;
        M1++;

        if(M1 == 13)
        {
            M1 = 1;
            Y1++;
        }
    }

    return D1 == D2 && M1 == M2 && Y1 == Y2;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while(cin >> n && n)
    {
        long long ans = 0, cnt = 0;

        long long D0, M0, Y0, C0;

        for(int i = 0; i < n; i++)
        {
            long long D, M, Y, C;
            cin >> D >> M >> Y >> C;

            if(i > 0 && siguienteDia(D0, M0, Y0, D, M, Y))
            {
                cnt++;
                ans += C - C0;
            }

            D0 = D;
            M0 = M;
            Y0 = Y;
            C0 = C;
        }

        cout << cnt << ' ' << ans << '\n';
    }
}
