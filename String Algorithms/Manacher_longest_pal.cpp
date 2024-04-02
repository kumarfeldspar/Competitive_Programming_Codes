/*
https://cses.fi/problemset/task/1111
*/
#include <bits/stdc++.h>
using namespace std;
#define all(x) x.begin(), x.end()
#define f(i, x) for (int i = 0; i < x; i++)
#define bfor(i, a, b) for (int i = a; i >= b; i--)
#define rep(i, a, b) for (int i = a; i < b; i++)
string t;
vector<int> manacher_odd(string s)
{
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]])
        {
            p[i]++;
        }
        if (i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s)
{
    for (auto c : s)
    {
        t += string("#") + c;
    }
    t += string("#");
    auto res = manacher_odd(t);
    return res;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    vector<int> ans = manacher(s);
    int id = 0, mx = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        if (mx < ans[i])
        {
            mx = ans[i];
            id = i;
        }
    }
    int start = id - mx + 1, end = id + mx - 1;
    string pr = "";
    for (int i = start; i <= end; i++)
    {
        if (t[i] != '#')
            pr.push_back(t[i]);
    }
    cout << pr;
}