// <3
// Tema: Arrays / Brute Force
// Resumen: Cuenta subarreglos donde "target" es mayoria (aparece en mas de la mitad de las
// posiciones)
// Detalle: Cuenta subarreglos donde "target" es mayoria (aparece en mas de la mitad de las
// posiciones). Fuerza bruta O(n^2): para cada inicio i expande el final j acumulando cuantas
// veces aparece target en el subarreglo actual y compara el doble de esa cuenta contra el
// tamano del subarreglo.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int god = 0;
        for(int i = 0 ; i < nums.size(); i++)
        {
            vector<int> temp;
            int tempi = 0;
            for(int j = i ; j < nums.size(); j++)
            {
                temp.push_back(nums[j]);
                if(nums[j]==target)
                {
                    tempi++;
                }
                if(tempi*2 > temp.size())
                {
                    god++;
                }
            }
            
        }

        return god;
    }
};