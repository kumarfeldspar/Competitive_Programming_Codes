/*
https://cses.fi/problemset/task/1753/
*/

#include <bits/stdc++.h>
using namespace std;
vector<int> kmp(string s)
{
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (s[i] != s[j] && j > 0)
        {
            j = pi[j - 1];
        }
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, t;
    cin >> s >> t;
    string newS = t + "#" + s;
    vector<int> ans = kmp(newS);
    int m = t.size(), cnt = 0;
    for (int i = m + 1; i < newS.size(); i++)
    {
        if (ans[i] == m)
            cnt++;
    }
    cout << cnt;
}
