/*
https://cses.fi/problemset/task/1753/
*/

#include <bits/stdc++.h>
using namespace std;
vector<int> z_function(string s)
{
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
    string newS = t + "#" + s;
    vector<int> ans = z_function(newS);
    int m = t.size(), cnt = 0;
    for (int i = m + 1; i < newS.size(); i++)
    {
        if (ans[i] == m)
            cnt++;
    }
    cout << cnt;
}
