// <3
// Tema: String / Remove Duplicate Letters
// Intento manual (greedy) de "Remove Duplicate Letters": busca construir el menor string
// lexicografico que contiene cada letra una sola vez, escogiendo la siguiente letra mas pequena
// posible que aun permita completar las letras restantes. Version explicativa de la idea greedy;
// la implementacion limpia con pila monotona esta en removeDuplicates1.cpp.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> nums(s.size());
        bool letras[26] = {false};
        int cont[26] = {0};
        for(char c : s)
        {
            nums.push_back(c - '0');
            cont[c-'a']++;
            letras[c - 'a'] = true;
        }

        int letmax = 0;
        for (int i = 0; i < 26; i++) 
        {
            letmax += letras[i];
        }

        char ini;
        for (int i = 0; i < 26; i++) 
        {
            if(cont[i] > 0)
            {
                ini = i + 'a';
                break;
            }
        }
        

        string god="";
        int idx = 0; 
        bool contGod[26] = {false};
        for(int i = 0 ; i < s.size() || god.size() < letmax; i++)
        {
            if(s[i] == ini && contGod[s[i]-'a'] == false)
            {
                idx = i + 1;
                for (int i = ini -'a' + 1; i < 26; i++) 
                {
                    if(cont[i] > 0 && contGod[i] == false)
                    {
                        ini = i + 'a';
                        break;
                    }
                }
                god+=s[i];
                contGod[s[i]-'a'] = true;
            }
            else if(cont[s[i]-'a']==1 && contGod[s[i]-'a'] == false)
            {
                char mini = s[i];
                int idxMini = i;
                while(idx < i)
                {
                    for(int j = idx; j < i; j++)
                    {
                        if(s[j] < mini && contGod[s[j]-'a'] == false)
                        {
                            mini = s[j];
                            idxMini = j;
                        }
                    }
                    if(mini != s[i])
                    {
                        god+= s[idxMini];
                        contGod[s[idxMini]-'a'] = true;

                        idx = idxMini + 1;
                        mini = s[i];
                        idxMini = i;

                    }
                    else
                    {
                        break;
                    }

                }

                for(int j = idx; j <= i; j++)
                {
                    if(s[j] == s[i])
                    {
                        god+=s[j];
                        idx = j + 1;
                        contGod[s[j]-'a']= true;
                        break;
                    }
                }
            }
            cont[s[i]-'a']--; 
        }
        
        return god;
    }
};