#include <iostream>
using namespace std;
int main()
{
    int n; cin >> n;
    int sum = 0;
    while(n--)
    {
        int a; cin >>a;
        if(a==3 or a==2)
        {
            sum++;
        }
    }
    cout << sum << endl;
  //a
    return 0;
}