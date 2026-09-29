// <3
// Tema: Formulario / Trampas de C++
// Los errores que compilan sin una sola advertencia y dan respuesta equivocada: division
// entera con negativos, overflow porque int*int se calcula en int antes de guardarse en
// long long, pow devolviendo 999999999999999 en vez de 10^15, y comparadores de sort que
// rompen el programa por usar <= en vez de <.
// Todos los valores de aqui estan verificados corriendo el codigo en este mismo equipo.

// =============== TRAMPAS DE C++ ===============
//
// Division y modulo con negativos  (verificado)
//     -7 / 2 = -3     la division trunca HACIA CERO, no hacia abajo
//     -7 % 2 = -1     el resto se lleva el signo del dividendo
//      7 / -2 = -3     7 % -2 = 1
//     floor(-7.0/2) = -4   -> distinto de -7/2
//     modulo siempre positivo : ((a % m) + m) % m
//     division hacia abajo    : (a - ((a % m) + m) % m) / m
//     Esto rompe hashing, indices circulares y aritmetica modular.
//
// Overflow silencioso  (verificado)
//     int a = 100000, b = 100000;
//     long long x = a * b;              -> 1410065408   MAL
//     long long x = (long long)a * b;   -> 10000000000  bien
//     La conversion ocurre DESPUES de multiplicar: castea un operando.
//     1 << 40   -> 0              1LL << 40 -> 1099511627776
//     accumulate(v.begin(), v.end(), 0)   suma en int, desborda
//     accumulate(v.begin(), v.end(), 0LL) suma en long long
//     Regla: si el resultado pasa de 2*10^9, todo el camino en ll.
//
// pow y sqrt son de punto flotante  (verificado que falla)
//     (long long)pow(10,15) = 999999999999999   le falta 1
//     (long long)pow(5,15)  = 30517578124       le falta 1
//     Para enteros usa exponenciacion binaria propia.
//     Para raiz entera, redondea y ajusta:
//         long long r = sqrtl(n);
//         while (r*r > n) r--;
//         while ((r+1)*(r+1) <= n) r++;
//
// Comparadores de sort
//     Tiene que ser ESTRICTO: return a < b;   nunca a <= b
//     Con <= el sort puede salirse del arreglo y tumbar el programa.
//     Descendente: return a > b;
//     Por varios campos:
//         if (a.x != b.x) return a.x < b.x;
//         return a.y < b.y;
//
// Contenedores
//     m[k] CREA la clave con valor por defecto si no existe.
//         Para solo consultar: m.count(k) o m.find(k).
//     unique() exige el vector ORDENADO y no borra por si solo:
//         sort(all(v)); v.erase(unique(all(v)), v.end());
//     En set y map usa el miembro s.lower_bound(x): es O(log n).
//         std::lower_bound(s.begin(), s.end(), x) recorre en O(n).
//     priority_queue es MAXIMO por defecto. Para minimo:
//         priority_queue<int, vector<int>, greater<int>> pq;
//     Borrar de un vector mientras lo recorres invalida iteradores.
//
// Entrada y salida
//     cin >> x  salta espacios y DEJA el '\n' pendiente. Si despues
//     usas getline, lees una linea vacia: consume el salto primero.
//     endl hace flush cada vez; dentro de un bucle usa '\n'.
//     Al inicio del main:
//         ios::sync_with_stdio(false); cin.tie(nullptr);
//     printf de long long es %lld, no %d.
//     Si mezclas printf y cout con sync desactivado, el orden se rompe.
//
// Punto flotante
//     Nunca compares con ==. Usa fabs(a-b) < 1e-9.
//     double guarda ~15-16 digitos; por encima de 2^53 pierde enteros.
//     Imprimir con decimales: cout << fixed << setprecision(k)
//     Si el problema es de enteros, resuelvelo con enteros.
