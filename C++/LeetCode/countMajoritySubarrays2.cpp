// <3
// Tema: Arrays / Prefix Sums
// Resumen: Misma idea que countMajoritySubarrays.cpp pero en O(n)
// Detalle: Misma idea que countMajoritySubarrays.cpp pero en O(n): transforma el arreglo a +1
// (target) / -1 (cualquier otro valor) y cuenta subarreglos con suma positiva. Como el balance
// (prefijo acumulado desplazado por n) cambia en +-1 en cada paso, usa un arreglo pre[]
// indexado por ese balance para llevar, sin necesitar un Fenwick tree, cuantos prefijos
// anteriores tuvieron un balance menor al actual, actualizando presum incrementalmente en O(1)
// por posicion.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> pre(2 * n + 1, 0);

        pre[n] = 1;

        int cnt = n;
        long long presum = 0;
        long long ans = 0;

        for (int x : nums) {
            if (x == target) {
                presum += pre[cnt];

                ++cnt;
                ++pre[cnt];
            } else {
                --cnt;

                presum -= pre[cnt];
                ++pre[cnt];
            }

            ans += presum;
        }

        return ans;
    }
};