#include <iostream>
using namespace std;
int n;
void counts(int nums[],int res[]) {
    int t[n];
    int cur = 0;
    for (int i = n - 1; i >= 0; --i) {
        int left = 0, right = cur;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (t[mid] >= nums[i]) right = mid;
            else left = mid + 1;
        }
            res[i] = right;
            for(int i=cur;i>=right;--i)
                t[i+1] = t[i];
            ++cur;
            t[right] = nums[i];
        }
    for(int i=0;i<n;++i)
        cout<<res[i]<<" ";
}
int main()
{
    cin>>n;
    int x;
    int *nums = new int [n];
    int *res = new int [n];
    for(int i=0;i<n;++i)
        {
            cin>>x;
            nums[i] = x;
        }
    counts(nums,res);
    return 0;
}
