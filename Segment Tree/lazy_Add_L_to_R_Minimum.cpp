#include <bits/stdc++.h>
using namespace std;
//https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/A

class SegmentTree
{
    int n;
    vector<long long> tree, lazy;

public:
    SegmentTree(int size) : n(size), tree(4 * size, 0), lazy(4 * size, 0) {}

    void propagate(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node];
            if (start != end)
            {
                lazy[node * 2 + 1] += lazy[node];
                lazy[node * 2 + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int l, int r, int value, int start, int end, int node)
    {
        propagate(node, start, end);

        if (start > end || start > r || end < l)
            return;

        if (start >= l && end <= r)
        {
            tree[node] += value;
            if (start != end)
            {
                lazy[node * 2 + 1] += value;
                lazy[node * 2 + 2] += value;
            }
            return;
        }

        int mid = (start + end) / 2;
        update_range(l, r, value, start, mid, node * 2 + 1);
        update_range(l, r, value, mid + 1, end, node * 2 + 2);
        tree[node] = min(tree[node * 2 + 1], tree[node * 2 + 2]);
    }

    long long query_range(int l, int r, int start, int end, int node)
    {
        propagate(node, start, end);

        if (start > end || start > r || end < l)
            return LLONG_MAX;

        if (start >= l && end <= r)
            return tree[node];

        int mid = (start + end) / 2;
        long long left = query_range(l, r, start, mid, node * 2 + 1);
        long long right = query_range(l, r, mid + 1, end, node * 2 + 2);
        return min(left, right);
    }

    void update_range(int l, int r, int value)
    {
        update_range(l, r, value, 0, n - 1, 0);
    }

    long long query_range(int l, int r)
    {
        return query_range(l, r, 0, n - 1, 0);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTree st(n);

    for (int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;
            st.update_range(l, r - 1, v);
        }
        else if (type == 2)
        {
            int l, r;
            cin >> l >> r;
            cout << st.query_range(l, r - 1) << "\n";
        }
    }

    return 0;
}
