/*
https://cses.fi/problemset/task/1190
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node
{
    int prefix;
    int suffix;
    int sum;
    int maxSum;
};
const int N = 2e5 + 5;
node sgt[4 * N];
node combine(node a, node b)
{
    node ans;
    ans.sum = a.sum + b.sum;
    ans.prefix = max(a.prefix, a.sum + b.prefix);
    ans.suffix = max(a.suffix + b.sum, b.suffix);
    ans.maxSum = max({a.maxSum, b.maxSum, a.suffix + b.prefix, ans.prefix, ans.suffix, ans.sum});
    return ans;
}
void update(int t, int tl, int tr, int i, int value)
{
    if (tl > i || tr < i)
        return;
    if (tl == tr)
    {
        sgt[t].maxSum = sgt[t].prefix = sgt[t].suffix = sgt[t].sum = value;
        return;
    }
    int mid = (tl + tr) / 2;
    update(2 * t + 1, tl, mid, i, value);
    update(2 * t + 2, mid + 1, tr, i, value);
    node temp = combine(sgt[2 * t + 1], sgt[2 * t + 2]);
    sgt[t] = temp;
}
node query(int t, int tl, int tr, int l, int r)
{
    if (tl > r || tr < l)
        return {0, 0, 0, 0};
    if (l <= tl && r >= tr)
        return sgt[t];
    int mid = (tl + tr) / 2;
    node temp = combine(query(2 * t + 1, tl, mid, l, r), query(2 * t + 2, mid + 1, tr, l, r));
    return temp;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i], update(0, 0, n - 1, i, a[i]);
    while (q--)
    {
        int k, x;
        cin >> k >> x;
        k--;
        update(0, 0, n - 1, k, x);
        node ans = query(0, 0, n - 1, 0, n - 1);
        cout << max(0LL, ans.maxSum) << '\n';
    }
}