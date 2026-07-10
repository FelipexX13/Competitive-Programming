#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double n; cin >>n;
    double prob = 1;
    double persons = 2;
    prob *= (n-1)/n;
    
    if(n==1)
    {
        cout << 2 << endl;
        return 0;
    }
    

        while(true)
        {
            prob *= (n-persons)/n;
            
            persons++;
            if(1-prob>0.5)
            {
                cout<< persons << endl;
                return 0;
            }
            
        }
        
        
        
    

    return 0;
}