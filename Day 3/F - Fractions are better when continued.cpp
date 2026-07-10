
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n ; cin >> n;
    
    if(n==1)
    {
        cout<<1<<endl;
    }
    else if(n == 2)
    {
        cout<<2<<endl;
    }
    else
    {
        long long num = 1;
        long long dem = 2;
        long long temp = 0;
        long long temp2 = 0;
        while(n>1)
        {
            temp2 = num + dem;
            num = temp2;
            
            temp = num;
            num = dem;
            dem = temp;
            
            n--;
        }
        
        cout<<num<<endl;
    }

    return 0;
}