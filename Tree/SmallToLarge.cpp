/*
https://cses.fi/problemset/task/1139/
*/

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 69;
set<int> st[N];
vector<int> adj[N];
int color[N];
int distinct[N];
void merge(set<int> &a, set<int> &b)
{
    if ((int)a.size() > (int)b.size())
        swap(a, b); // a<b in O(1)
    for (auto &i : a)
        b.insert(i);
}
void dfs(int v, int p)
{
    for (auto i : adj[v])
    {
        if (i == p)
            continue;
        dfs(i, v);
        merge(st[i], st[v]);
    }
    distinct[v] = st[v].size();
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> color[i], st[i].insert(color[i]);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++)
        cout << distinct[i] << " ";
}