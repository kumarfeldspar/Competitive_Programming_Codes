#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int depth[N];
vector<int> adj[N];
int up[N][20];
void dfs(int v, int p)
{
    up[v][0] = p;
    for (int i = 1; i < 20; i++)
    {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto i : adj[v])
    {
        if (i == p)
            continue;
        depth[i] = depth[v] + 1;
        dfs(i, v);
    }
}
int Kth(int v, int k)
{
    for (int i = 19; i >= 0; i--)
    {
        if (k & (1 << i))
            v = up[v][i];
    }
    return v;
}
int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b); // depth[a]>=depth[b]
    int climb = depth[a] - depth[b];
    a = Kth(a, climb); // now a and b are at same depth
    if (a == b)
        return a;
    for (int i = 19; i >= 0; i--)
    {
        if (up[a][i] != up[b][i])
        {
            // if 2^ith par of a !=2^th ith par of b
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}
int distance(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}
int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 1);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << distance(a, b) << '\n';
    }
}
