#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n; cin >> n; 
    int m; cin >> m;
    
    vector<vector<int>> clases;
    long long maxi = 0;
    
    for(int i = 0 ; i < n; i++)
    {
        vector<int> pp;
        for(int j = 0 ; j < m; j++)
        {
            int a; cin>>a;
            pp.push_back(a);
        }
        clases.push_back(pp);
    }
    for(int i = 0 ; i < m; i++)
    {
        long long maxxx = 0;
        for(int j = 0 ; j < n; j++)
        {
            if(clases[j][i] >= maxxx)
            {
                maxxx = clases[j][i];
            }
        }
        maxi += maxxx;
    }
    
    cout << maxi<< endl;

    return 0;
}