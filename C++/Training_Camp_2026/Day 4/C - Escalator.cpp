// <3
// Tema: Simulation / Greedy
// Resuelve "Escalator" (Day 4, problema C - Contest 04 [Avanzados]): una escalera doble tarda 10
// segundos en cruzar a cualquier persona, arranca en la direccion del primero que llega estando
// detenida, y si alguien llega en direccion contraria a la que se mueve debe esperar a que pare;
// hay que hallar el momento en que la escalera se detiene por ultima vez. Simula el estado de la
// escalera con variables busy_until (cuando quedaria libre), dir (direccion actual) y waiting (si
// hay alguien esperando un cambio de sentido), resolviendo en O(N) los cambios de direccion
// pendientes antes de procesar la llegada de cada persona.

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    long long busy_until = 0;
    int dir = -1;
    bool waiting = false;

    for (int i = 0; i < n; i++){
        long long t; int d;
        cin >> t >> d;

        while (waiting && t >= busy_until){
            dir = 1 - dir;
            busy_until = busy_until + 10;
            waiting = false;
        }

        if (busy_until <= t){
            dir = d;
            busy_until = t + 10;
        } else {
            if (d == dir){
                busy_until = max(busy_until, t + 10);
            } else {
                waiting = true;
            }
        }
    }

    if (waiting){
        busy_until = busy_until + 10;
    }

    cout << busy_until << "\n";
    return 0;
}