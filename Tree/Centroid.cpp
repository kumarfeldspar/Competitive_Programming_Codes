#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
#define f(i, x) for (int i = 0; i < x; i++)
#define bfor(i, a, b) for (int i = a; i >= b; i--)
#define rep(i, a, b) for (int i = a; i < b; i++)
/*
a node from which all subtrees have size at most n/2(<=n/2)
no subtree with size greater than n/2

A centroid of a tree
 is defined as a node such that when the tree is rooted
at it, no other nodes have a subtree of size greater than N/2
We can find a centroid in a tree by starting at the root. Each step, loop
through all of its children. If all of its children have subtree size less than or equal to N/2
, then it is a centroid. Otherwise, move to the child
with a subtree size that is more than N/2 and repeat until you find a centroid.
*/
const int N = 2e5 + 5;
int n, sz[N];
vector<int> adj[N];
void dfs(int v, int p)
{
    for (auto i : adj[v])
    {
        if (i == p)
            continue;
        dfs(i, v);
        sz[v] += sz[i];
    }
}
int get_centroid(int v, int p)
{
    for (auto i : adj[v])
    {
        if (i == p)
            continue;
        if (sz[i] * 2 > n)
            return get_centroid(i, v);
    }
    return v;
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, 1, n + 1) sz[i] = 1;
    f(i, n - 1)
    {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0);
    int centroid = get_centroid(1, 0);
    cout << centroid << '\n';
}