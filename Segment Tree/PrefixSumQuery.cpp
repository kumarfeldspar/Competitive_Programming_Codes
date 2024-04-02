/*
https://cses.fi/problemset/task/2166
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e18;
const int N = 2e5 + 5;
struct node
{
    int prefix;
    int sum;
};
node sgt[4 * N];
node merge(node a, node b)
{
    node ans;
    ans.prefix = max(a.prefix, a.sum + b.prefix);
    ans.sum = a.sum + b.sum;
    return ans;
}
void update(int t, int tl, int tr, int i, int value)
{
    if (tl > i || tr < i)
        return;
    if (tl == tr)
    {
        sgt[t].prefix = sgt[t].sum = value;
        return;
    }
    int mid = (tl + tr) / 2;
    update(2 * t + 1, tl, mid, i, value);
    update(2 * t + 2, mid + 1, tr, i, value);
    int left = 2 * t + 1, right = 2 * t + 2;
    sgt[t].prefix = max(sgt[left].prefix, sgt[left].sum + sgt[right].prefix);
    sgt[t].sum = sgt[left].sum + sgt[right].sum;
}
node query(int t, int tl, int tr, int l, int r)
{
    if (tl > r || tr < l)
        return {0, 0};
    if (l <= tl && r >= tr)
        return sgt[t];
    int mid = (tl + tr) / 2;
    int left = 2 * t + 1, right = 2 * t + 2;
    return merge(query(left, tl, mid, l, r), query(right, mid + 1, tr, l, r));
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i], update(0, 0, n - 1, i, v[i]);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int k, u;
            cin >> k >> u;
            k--;
            update(0, 0, n - 1, k, u);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            node ans = query(0, 0, n - 1, a, b);
            cout << max(0LL, ans.prefix) << '\n';
        }
    }
}
