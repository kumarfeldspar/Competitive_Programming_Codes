// https://cses.fi/problemset/task/1137/
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct segtree {
    int size;
    vector<long long> sums;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        sums.assign(2 * size, 0LL);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                sums[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void build(vector<int> &a) {
        build(a, 0, 0, size);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            sums[x] = val;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) {
            set(i, val, 2 * x + 1, lx, m);
        } else {
            set(i, val, 2 * x + 2, m, rx);
        }
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void set(int i, int val) {
        set(i, val, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0;
        if (lx >= l && rx <= r) return sums[x];
        int m = (lx + rx) / 2;
        long long s1 = sum(l, r, 2 * x + 1, lx, m);
        long long s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }

    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

vector<vector<int>> adj;
vector<int> path;
vector<int> subtree_size;

void dfs(int v, int p) {
    path.push_back(v);
    for (auto &i : adj[v]) {
        if (i == p) continue;
        dfs(i, v);
        subtree_size[v] += subtree_size[i];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    adj.resize(n + 1);
    path.resize(0);
    subtree_size.resize(n + 1, 1);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, -1);
    unordered_map<int, int> mpp;
    vector<int> val(n, 0);
    for (int i = 0; i < n; i++) {
        mpp[path[i]] = i;
        val[i] = v[path[i]];
    }

    segtree st;
    st.init(n);
    st.build(val);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            int idx = mpp[s];
            st.set(idx, x);
        } else {
            int s;
            cin >> s;
            int idx = mpp[s];
            int ans = st.sum(idx, idx + subtree_size[s]);
            cout << ans << "\n";
        }
    }
}
