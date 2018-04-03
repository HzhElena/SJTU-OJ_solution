#include <iostream>

using namespace std;

int main()
{
    int N;
    cin>>N;
    int result = 1;
    int *num = new int[N-1];
    for(int i=0;i<N-1;++i)
        cin>>num[i];
    for(int i=2;i<=N;++i)
    {
        result = ((result + num[N-i]-1)% i) +1;
    }
    cout<<result;
    return 0;
}
