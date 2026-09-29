// <3
// Tema: Graph / BFS
// Resuelve "Word Ladder": halla la longitud de la transformacion mas corta de beginWord a endWord
// cambiando una letra a la vez, usando solo palabras de wordList. BFS por niveles donde cada
// palabra es un nodo y dos palabras se conectan si difieren en exactamente una letra.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());

        if (!words.count(endWord))
            return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        while (!q.empty()) {
            auto [word, dist] = q.front(); 
            q.pop();

            if (word == endWord)
                return dist;

            for (int i = 0; i < word.size(); i++) {
                char original = word[i];

                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == original) continue;

                    word[i] = c;

                    if (words.count(word)) {
                        q.push({word, dist + 1});
                        words.erase(word); // mark as visited
                    }
                }

                word[i] = original;
            }
        }

        return 0;
    }
};