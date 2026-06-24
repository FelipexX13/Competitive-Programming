// <3
// Tema: Graph / BFS Backtracking
// Resuelve "Word Ladder II": encuentra TODAS las secuencias de transformacion mas cortas de
// beginWord a endWord cambiando una letra a la vez. BFS por niveles guardando los padres de cada
// palabra, y luego backtracking desde endWord para reconstruir todos los caminos minimos.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> ans;
    unordered_map<string, vector<string>> parents;

    void buildPaths(string word,
                    string beginWord,
                    vector<string>& path) {

        if (word == beginWord) {
            vector<string> cur = path;
            reverse(cur.begin(), cur.end());
            ans.push_back(cur);
            return;
        }

        for (auto& p : parents[word]) {
            path.push_back(p);
            buildPaths(p, beginWord, path);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord,
                                       string endWord,
                                       vector<string>& wordList) {

        unordered_set<string> words(wordList.begin(), wordList.end());

        if (!words.count(endWord))
            return {};

        queue<string> q;
        q.push(beginWord);

        unordered_set<string> visited;
        visited.insert(beginWord);

        bool found = false;

        while (!q.empty() && !found) {

            int sz = q.size();

            unordered_set<string> levelVisited;

            while (sz--) {

                string word = q.front();
                q.pop();

                string original = word;

                for (int i = 0; i < word.size(); i++) {

                    char old = word[i];

                    for (char c = 'a'; c <= 'z'; c++) {

                        if (c == old) continue;

                        word[i] = c;

                        if (!words.count(word))
                            continue;

                        if (!visited.count(word)) {

                            if (!levelVisited.count(word)) {
                                q.push(word);
                                levelVisited.insert(word);
                            }

                            parents[word].push_back(original);

                            if (word == endWord)
                                found = true;
                        }
                    }

                    word[i] = old;
                }
            }

            for (auto& w : levelVisited)
                visited.insert(w);
        }

        if (!found)
            return {};

        vector<string> path = {endWord};
        buildPaths(endWord, beginWord, path);

        return ans;
    }
};