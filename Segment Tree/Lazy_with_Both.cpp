/*
https://cses.fi/problemset/task/1735/
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200000 + 5;
const int inf = 1e18;
/*
1)Increase each value in range [a,b] by x.
2)Set each value in range [a,b] to x.
3)Calculate the sum of values in range [a,b].
*/
// when we arrive at a node we update its contents and
// propogate its updates to its children
int sgt[4 * N], arr[N];
struct lazy
{
    int lazy_sum;
    bool is_pending;
    int change_to;
} lazy[4 * N];
void push(int t, int tl, int tr)
{
    if (lazy[t].is_pending)
    {
        sgt[t] = (tr - tl + 1) * lazy[t].change_to; // here also (tr-tl+1)
    }
    sgt[t] += (tr - tl + 1) * lazy[t].lazy_sum;
    // if we did if for sum we would have to (tr-tl+1)*lazy[t]
    if (tl != tr)
    {
        if (lazy[t].is_pending)
        {
            lazy[2 * t + 1].is_pending = 1;
            lazy[2 * t + 1].change_to = lazy[t].change_to;
            lazy[2 * t + 1].lazy_sum = 0;
            lazy[2 * t + 2].is_pending = 1;
            lazy[2 * t + 2].change_to = lazy[t].change_to;
            lazy[2 * t + 2].lazy_sum = 0;
        }
        lazy[2 * t + 1].lazy_sum += lazy[t].lazy_sum;
        lazy[2 * t + 2].lazy_sum += lazy[t].lazy_sum;
    }
    lazy[t].change_to = 0;
    lazy[t].is_pending = 0;
    lazy[t].lazy_sum = 0;
}

void update(int t, int tl, int tr, int l, int r, int val)
{ // change l to r to val
    push(t, tl, tr);
    if (l > tr || tl > r)
        return;
    if (l == tl && r == tr)
    { // this is important
        lazy[t].is_pending = 1;
        lazy[t].change_to = val;
        lazy[t].lazy_sum = 0;
        push(t, tl, tr);
        return;
    }
    int mid = (tl + tr) / 2;
    update(2 * t + 1, tl, mid, l, min(r, mid), val);
    update(2 * t + 2, mid + 1, tr, max(l, mid + 1), r, val);
    sgt[t] = sgt[2 * t + 1] + sgt[2 * t + 2];
}
void update2(int t, int tl, int tr, int l, int r, int inc)
{ // increment l to r by inc
    push(t, tl, tr);
    if (l > tr || tl > r)
        return;
    if (l == tl && r == tr)
    { // this is important
        lazy[t].lazy_sum += inc;
        push(t, tl, tr);
        return;
    }
    int mid = (tl + tr) / 2;
    update2(2 * t + 1, tl, mid, l, min(r, mid), inc);
    update2(2 * t + 2, mid + 1, tr, max(l, mid + 1), r, inc);
    sgt[t] = sgt[2 * t + 1] + sgt[2 * t + 2];
}
int query(int t, int tl, int tr, int l, int r)
{
    push(t, tl, tr);
    if (l > tr || tl > r)
        return 0;
    if (tl >= l && tr <= r)
    {
        return sgt[t];
    }
    int mid = (tl + tr) / 2;
    return query(2 * t + 1, tl, mid, l, min(r, mid)) + query(2 * t + 2, mid + 1, tr, max(l, mid + 1), r);
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        update(0, 0, n - 1, i, i, arr[i]);
    }
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int a, b, inc;
            cin >> a >> b >> inc;
            // increment [a,b] by x
            a--, b--;
            update2(0, 0, n - 1, a, b, inc);
        }
        else if (type == 2)
        {
            int a, b, x;
            cin >> a >> b >> x;
            // set [a,b] to x
            a--, b--;
            update(0, 0, n - 1, a, b, x);
        }
        else if (type == 3)
        {
            int a, b;
            cin >> a >> b;
            // sum [a,b]
            a--, b--;
            int ans = query(0, 0, n - 1, a, b);
            cout << ans << '\n';
        }
    }
}
SHARE CODE TO OTHERS
    Test details