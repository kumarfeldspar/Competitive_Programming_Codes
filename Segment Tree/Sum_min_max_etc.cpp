#include <bits/stdc++.h>
using namespace std;
#define int long long 
vector<long long> segtree;
void update(int t, int tl, int tr, int i, int value)
{
    if (tl > i || tr < i)
        return;
    if (tl == tr)
    {
        segtree[t] = value;
        return;
    }
    int mid = (tl + tr) / 2;
    update(2 * t + 1, tl, mid, i, value);
    update(2 * t + 2, mid + 1, tr, i, value);
    segtree[t] = segtree[2 * t + 1] + segtree[2 * t + 2];
}
long long query(int t, int tl, int tr, int l, int r)
{
    if (tl > r || tr < l)
        return 0;
    if (l <= tl && r >= tr)
        return segtree[t];
    int mid = (tl + tr) / 2;
    return query(2 * t + 1, tl, mid, l, r) + query(2 * t + 2, mid + 1, tr, l, r);
}
int32_t main()
{
    int n, q;
    cin >> n >> q;
    segtree.resize(4 * n + 1);
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        update(0, 0, n - 1, i, v[i]);
    }
    while (q--)
    {
        int k;
        cin >> k;
        if (k == 1)
        {
            int i, val;
            cin >> i >> val;
            i--;
            update(0, 0, n - 1, i, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--, r--;
            long long ans = query(0, 0, n - 1, l, r);
            cout << ans << '\n';
        }
    }
}