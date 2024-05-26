#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
vector<vector<int>> sgt(4 * N + 5);
vector<int> merge(vector<int> &left, vector<int> &right)
{
    vector<int> merged;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
            merged.push_back(left[i]), i++;
        else
            merged.push_back(right[j]), j++;
    }
    while (i < left.size())
        merged.push_back(left[i]), i++;
    while (j < right.size())
        merged.push_back(right[j]), j++;
    return merged;
}

void build(int t, int tl, int tr, vector<int> &a)
{
    if (tl == tr)
    {
        sgt[t].push_back(a[tl]);
        return;
    }
    int mid = (tl + tr) / 2;
    build(2 * t + 1, tl, mid, a);
    build(2 * t + 2, mid + 1, tr, a);
    sgt[t] = merge(sgt[2 * t + 1], sgt[2 * t + 2]);
}
int query(int t, int tl, int tr, int l, int r, int k)
{
    if (l > tr || r < tl)
        return 0;
    if (tl >= l && tr <= r)
    {
        return lower_bound(sgt[t].begin(), sgt[t].end(), k) - sgt[t].begin();
    }
    int mid = (tl + tr) / 2;
    return query(2 * t + 1, tl, mid, l, r, k) + query(2 * t + 2, mid + 1, tr, l, r, k);
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(__null);
    cout.tie(__null);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(0, 0, n - 1, a);
    while (q--)
    {
        int l, r, k;
        cin >> l >> r >> k; // kth no between l to r
        int hi = 1e9, lo = -1e9, ans = 0;
        while (hi >= lo)
        {
            int mid = (lo + hi) / 2;
            int less = query(0, 0, n - 1, l - 1, r - 1, mid);
            if (less < k)
            {
                ans = mid;
                lo = mid + 1;
            }
            else
                hi = mid - 1;
        }
        cout << ans << '\n';

        /*
        >greater than -> R-L+1-(upper_bound)
        >less than    -> lower_bound
        >less equal   -> upper_bound
        greater equal ->R-L+1-(lower_bound)
        >for less than K in L to R just replace upper_bound by
        lower_bound
        */
    }
}
