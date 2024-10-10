#include <iostream>
#include <vector>
using namespace std;
int bs (vector<int>arr, int x, int s, int e)
{
    int mid = s + (e-s)/2;
    while (s<=e)
    {
        if (arr[mid] == x)
        {
            return mid;
        }
        else if (arr[mid] > x)
        {
            e = mid - 1;
        }
        else
        s = mid + 1;

        mid = s + (e-s)/2;
    }
    return -1;
}
int main ()
{
    vector<int>arr = {3,4,5,6,11,13,14,15,56,70};  
    int size = arr.size();
    int n = 13;
    if (arr[0] == n)
    {
        cout << "0"<<endl;
    }
    int i = 1;
    while (i < arr.size() && arr[i] < n) 
    {
        i*=2;
    } 
    int ans = bs(arr, n, i/2, min(i,size-1));
    cout << ans;
return 0;
}