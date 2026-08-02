// <3
// Tema: Simulation / Greedy
// Resuelve "Escalator" (Training Camp 2026, Day 4 problema C): una escalera doble tarda 10
// segundos en cruzar a cualquier persona, arranca en la direccion del primero que llega estando
// detenida, y si alguien llega en direccion contraria a la que se mueve debe esperar a que pare;
// hay que hallar el momento en que la escalera se detiene por ultima vez.
// Simula el estado de la escalera con variables busy_until (cuando quedaria libre), dir (direccion
// actual) y waiting (si hay alguien esperando un cambio de sentido), resolviendo en O(N) los
// cambios de direccion pendientes antes de procesar la llegada de cada persona.

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    scanf("%d", &n);
 
    long long busy_until = 0; // tiempo en que la escalera dejaria de moverse (si nadie mas entra)
    int dir = -1;             // -1 = sin direccion asignada aun (detenida)
    bool waiting = false;     // hay alguien esperando para cambiar de direccion cuando pare
 
    for (int i = 0; i < n; i++){
        long long t; int d;
        scanf("%lld %d", &t, &d);
 
        // Resolver switches pendientes que ya deberian haber ocurrido antes de t
        while (waiting && t >= busy_until){
            dir = 1 - dir;
            busy_until = busy_until + 10;
            waiting = false;
        }
 
        if (busy_until <= t){
            // la escalera esta detenida, arranca en la direccion de esta persona
            dir = d;
            busy_until = t + 10;
        } else {
            // la escalera esta en movimiento
            if (d == dir){
                // misma direccion: entra ya, puede extender el tiempo de parada
                busy_until = max(busy_until, t + 10);
            } else {
                // direccion opuesta: debe esperar a que pare
                waiting = true;
            }
        }
    }
 
    // Si queda alguien esperando al final, ese grupo entra cuando la escalera
    // finalmente se detiene, y sale 10 segundos despues.
    if (waiting){
        busy_until = busy_until + 10;
    }
 
    printf("%lld\n", busy_until);
    return 0;
}