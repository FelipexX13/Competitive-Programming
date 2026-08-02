// <3
// Tema: Simulation / Brute Force
// Resuelve "LLMs" (Maratona SBC de Programacao 2025, Problem L): Bruno arma un predictor de
// palabras "SBC" a partir de un diccionario de palabras con vectores 2D, un texto base de
// conocimiento y consultas; para cada consulta, se buscan en el texto base todas las ocurrencias
// consecutivas de las ultimas K palabras (ventana de contexto), se toman las palabras
// siguientes como "candidatas" (si no hay ninguna, se baja K en 1 y se repite hasta K=0), y se
// elige la palabra del diccionario que maximiza el producto punto de su vector contra la suma de
// los vectores candidatos (empate: la mas comun, primera en el diccionario). El codigo hace esto
// de forma directa: busqueda por fuerza bruta de "ctx" dentro de "kb" con bucles anidados para
// armar "candidates", suma sus vectores en (sumX, sumY), y recorre linealmente las N palabras del
// diccionario para hallar el maximo "bestS" de dictVec[i].x*sumX + dictVec[i].y*sumY.

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> dictWord(N);
    vector<pair<long long,long long>> dictVec(N);
    unordered_map<string,int> firstIndex; // first occurrence of a word in the dictionary

    for(int i = 0; i < N; i++){
        string w; long long x, y;
        cin >> w >> x >> y;
        dictWord[i] = w;
        dictVec[i] = {x, y};
        if(firstIndex.find(w) == firstIndex.end())
            firstIndex[w] = i;
    }

    int M;
    cin >> M;
    vector<string> kb(M);
    for(int i = 0; i < M; i++)
        cin >> kb[i];

    int Q, K;
    cin >> Q >> K;

    for(int q = 0; q < Q; q++){
        int F;
        cin >> F;
        vector<string> query(F);
        for(int i = 0; i < F; i++)
            cin >> query[i];

        int curK = K;
        vector<string> candidates;

        while(curK >= 1){
            // last curK words of the ORIGINAL query
            vector<string> ctx(query.end() - curK, query.end());
            candidates.clear();

            // search knowledge base for consecutive occurrences of ctx
            for(int j = 0; j + curK - 1 < M; j++){
                bool match = true;
                for(int t = 0; t < curK; t++){
                    if(kb[j + t] != ctx[t]){ match = false; break; }
                }
                if(match){
                    int nextPos = j + curK;
                    if(nextPos < M){
                        candidates.push_back(kb[nextPos]);
                    }
                }
            }

            if(!candidates.empty()) break;
            curK--;
        }

        // print the query words
        for(int i = 0; i < F; i++){
            cout << query[i];
            cout << " ";
        }

        if(candidates.empty()){
            cout << "*\n";
            continue;
        }

        // Precompute candidate vectors (0,0) if word not in dictionary
        vector<pair<long long,long long>> candVecs;
        candVecs.reserve(candidates.size());
        for(auto &c : candidates){
            auto it = firstIndex.find(c);
            if(it != firstIndex.end())
                candVecs.push_back(dictVec[it->second]);
            else
                candVecs.push_back({0,0});
        }

        // sum of candidate vectors, so S(d) = d . sum(candidates)
        long long sumX = 0, sumY = 0;
        for(auto &cv : candVecs){
            sumX += cv.first;
            sumY += cv.second;
        }

        long long bestS = LLONG_MIN;
        int bestIdx = -1;

        for(int i = 0; i < N; i++){
            long long s = dictVec[i].first * sumX + dictVec[i].second * sumY;
            if(s > bestS){
                bestS = s;
                bestIdx = i;
            }
        }

        cout << dictWord[bestIdx] << "\n";
    }

    return 0;
}