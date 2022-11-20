#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits.h>
#include <ctime>

using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int mx = INT_MIN;

    unordered_map<int, int> mp;
    for (int i = 0; i < k; i++)
    {
        if (mp.find(arr[i]) == mp.end())
            mp[arr[i]] = 1;
        else
            mp[arr[i]]++;
    }
    mx = max(mx, (int)mp.size());
    for (int i = k; i < n; i++)
    {
        if (mp[arr[i - k]] == 1)
            mp.erase(arr[i - k]);
        else
            mp[arr[i - k]]--;
        if (mp.find(arr[i]) == mp.end())
            mp[arr[i]] = 1;
        else
            mp[arr[i]]++;
        mx = max(mx, int(mp.size()));
    }

    cout << mx << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}