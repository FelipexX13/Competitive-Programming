#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n; cin >> n;
    long long tot = 0;
    long long god = 0;
    vector<long long> nums1;
    for(long long i = 0 ; i < n ; i ++)
    {
        long long a; cin >>a;
        tot+= a;
        nums1.push_back(tot);
    }
    vector<long long> nums(10000000,0);
    for(long long i = 0 ; i < nums1.size() ; i++)
    {
        nums[nums1[i]]=1;
    }
    
    if(tot%3!=0)
    {
        cout<< 0 <<endl;
    }
    else
    {
        long long tri = tot/3;
        for(long long i = 0 ; i < (10000000) ; i++)
        {
            
            if(nums[i]==1 && nums[i]==nums[i+tri]&&nums[i]==nums[i+tri+tri]&&i<10000000&&i+tri<10000000&&i+tri+tri<10000000)
            {
               
                god++;
                nums[i]=0;
                nums[i+tri] = 0;
                nums[i+tri+tri] = 0;
            }
        }
        
        cout << god << endl;
    }
    return 0;
}