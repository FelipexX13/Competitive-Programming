// <3
// Tema: CSES / Dijkstra sobre Grafo de Capas
// Resumen: Dijkstra donde el estado no es solo la ciudad sino el par (ciudad, ya use el
// descuento)
// Detalle: Dijkstra donde el estado no es solo la ciudad sino el par (ciudad, ya use el
// descuento). Es la tecnica de GRAFO DE CAPAS o grafo producto: se duplica el grafo, en la capa
// 0 nada esta usado y en la capa 1 el descuento ya se gasto, y las aristas que aplican el
// descuento son las unicas que cruzan de una capa a la otra. Un Dijkstra normal sobre ese grafo
// mas grande resuelve todo. POR QUE NO SE PUEDE MAS BARATO: la respuesta no es "el camino
// minimo y despues descuento la arista mas cara", porque el mejor camino con descuento puede
// ser otro camino completamente distinto. Hay que decidir los dos a la vez, y para eso se mete
// la decision dentro del estado. CUANDO USAR: cada vez que al camino minimo se le agrega un
// recurso limitado. "Puedes usar k teletransportes", "puedes hacer una arista gratis", "hay que
// llegar con tanque suficiente". La regla es multiplicar los nodos por los estados del recurso:
// n*(k+1) nodos, mismo Dijkstra. Si el recurso tiene muchos valores el estado explota; ahi ya
// toca pensar en otra cosa.

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <climits>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    
    cin >> n >> m;
    
    vector<vector<pair<long long, long long>>> vuelos(n);
    
    long long a,b,c;
    
    while(m--)
    {
        cin >> a >> b >> c;
        
        vuelos[--a].push_back({--b,c});
    }
    
    //Estados
    long long USADO = 1, NO_USADO = 0;
    
    vector<vector<long long>> costoMinimo(n, vector<long long>(2, LLONG_MAX));
    
    priority_queue<array<long long, 3>,
                   vector<array<long long, 3>>,
                   greater<array<long long, 3>>> cola;
  
    costoMinimo[0][NO_USADO] = 0;
    
    cola.push({0,0,NO_USADO});
    
    while(!cola.empty())
    {
        long long costo, ciudad, estado;
        
        costo = cola.top()[0];
        ciudad = cola.top()[1];
        estado = cola.top()[2];
        
        cola.pop();
        
        if(costoMinimo[ciudad][estado] < costo) continue;
        
        for(pair<long long, long long> vuelo : vuelos[ciudad])
        {
            long long adonde = vuelo.first;
            long long cuanto = vuelo.second;
            
            if(costoMinimo[adonde][estado] > costo + cuanto)
            {
                costoMinimo[adonde][estado] = costo + cuanto;
                
                cola.push({costo+cuanto,adonde,estado});
            }
            
            if(estado == NO_USADO)
            {
                if(costoMinimo[adonde][USADO] > costo + cuanto/2)
                {
                    costoMinimo[adonde][USADO] = costo + cuanto/2;
                    
                    cola.push({costo+cuanto/2,adonde,USADO});
                }
            }
        }
    }
    
    cout << min(costoMinimo[n-1][NO_USADO], costoMinimo[n-1][USADO]) << endl;

    return 0;
}