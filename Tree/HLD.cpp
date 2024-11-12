//https://codeforces.com/gym/565994/problem/B1
#include "bits/stdc++.h"

using namespace std;

#define ios ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define int            long long
#define double         long double
#define endl           "\n"
#define all(x)         x.begin(), x.end()
// #define v              vector
#define vi             vector<int>
#define vvi            vector<vector<int>>
#define pii            pair<int, int>
#define mpci           map<char, int>
#define mpii           map<int, int>
#define pb             emplace_back
#define mp             make_pair
#define F              first
#define S              second
#define si             set<int>
#define msi            multiset<int>
#define maxn           1000005

int gcd(int a, int b) { if (b == 0) return a; return gcd(b, a % b);}
int power(int a, int b, int m) { int ans = 1; while (b) { if (b & 1) ans = (ans * a) % m; b /= 2; a = (a * a) % m; } return ans; }
int lcm(int a, int b) { return (a * b) / gcd(a, b); }
int modInverse(int a, int m) { return power(a, m - 2, m); }
int modAdd(int a, int b, int m) { return ((a % m) + (b % m)) % m; }
int modMul(int a, int b, int m) { return ((a % m) * (b % m)) % m; }
int modSub(int a, int b, int m) { return ((a % m) - (b % m) + m) % m; }
int modDiv(int a, int b, int m) { return (modMul(a, modInverse(b, m), m) + m) % m; }
bool isPrime(int n) { if (n <= 1) return false; if (n <= 3) return true; if (n % 2 == 0 || n % 3 == 0) return false; for (int i = 5; i * i <= n; i = i + 6) if (n % i == 0 || n % (i + 2) == 0) return false; return true; }
int nCr(int n, int r) { if (r > n - r) r = n - r; int ans = 1; for (int i = 0; i < r; i++) { ans *= (n - i); ans /= (i + 1); } return ans; }
int nCrModP(int n, int r, int p) { if (r > n - r) r = n - r; int C[r + 1]; memset(C, 0, sizeof(C)); C[0] = 1; for (int i = 1; i <= n; i++) { for (int j = min(i, r); j > 0; j--) C[j] = (C[j] + C[j - 1]) % p; } return C[r]; }
int nPr(int n, int r) { int ans = 1; for (int i = 0; i < r; i++) ans *= (n - i); return ans; }
int nPrModP(int n, int r, int p) { int ans = 1; for (int i = 0; i < r; i++) ans = (ans * (n - i)) % p; return ans; }
int log(int num , int base){int ans = 0; while(num){num /= base;ans++;} return ans;}
int countSetBits(int x){int ans = 0;while(x){ans += (x&1);x >>= 1;}return ans;}

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

bool testcases = 1;

const int MOD = 1e9 + 7;
const int mod = 998244353;

struct SegmentTree {
    int n;
    vector<vector<int>> tree;

    SegmentTree(int sz) {
        n = sz;
        tree.assign(4 * n, vector<int>());
    }

    void build_tree(const vector<int> &arr, int node, int l, int r){
        if(l == r){
            tree[node].push_back(arr[l]);
            return;
        }
        int mid = (l + r) / 2;
        build_tree(arr, 2*node, l, mid);
        build_tree(arr, 2*node+1, mid+1, r);
        const vector<int> &left = tree[2*node];
        const vector<int> &right = tree[2*node+1];
        tree[node].reserve(left.size() + right.size());
        int i = 0, j = 0;
        while(i < left.size() && j < right.size()){
            if(left[i] < right[j]){
                tree[node].push_back(left[i++]);
            }
            else{
                tree[node].push_back(right[j++]);
            }
        }
        while(i < left.size()){
            tree[node].push_back(left[i++]);
        }
        while(j < right.size()){
            tree[node].push_back(right[j++]);
        }
    }

    void build(const vector<int> &arr){
        build_tree(arr, 1, 0, n-1);
    }

    void query_range(int node, int l, int r, int ql, int qr, int x, vector<int> &candidates){
        if(ql > r || qr < l){
            return;
        }
        if(ql <= l && r <= qr){
            const vector<int> &vec = tree[node];
            if(vec.empty()) return;
            int pos_ = lower_bound(vec.begin(), vec.end(), x) - vec.begin();
            int left = pos_ -1;
            int right = pos_;
            int k = 2;
            while(k > 0 && (left >=0 || right < vec.size())){
                if(left >=0 && right < vec.size()){
                    if(abs(vec[left] - x) <= abs(vec[right] - x)){
                        candidates.push_back(vec[left]);
                        left--;
                    }
                    else{
                        candidates.push_back(vec[right]);
                        right++;
                    }
                }
                else if(left >=0 ){
                    candidates.push_back(vec[left]);
                    left--;
                }
                else{
                    candidates.push_back(vec[right]);
                    right++;
                }
                k--;
            }
            return;
        }
        int mid = (l + r) / 2;
        query_range(2*node, l, mid, ql, qr, x, candidates);
        query_range(2*node+1, mid+1, r, ql, qr, x, candidates);
    }
};

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> size;
    vector<int> depth;
    vector<int> parent;
    vector<int> heavy;
    vector<int> head;
    vector<int> pos;
    int current_pos;
    vector<int> arr; 
    vector<int> a;

    HLD(int n_) {
        n = n_;
        adj.assign(n+1, vector<int>());
        size.assign(n+1, 0);
        depth.assign(n+1, 0);
        parent.assign(n+1, 0);
        heavy.assign(n+1, -1);
        head.assign(n+1, 0);
        pos.assign(n+1, 0);
        current_pos = 0;
        arr.assign(n, 0);
        a.assign(n+1, 0); 
    }

    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs_size_calc(int u, int p_){
        parent[u] = p_;
        size[u] = 1;
        int max_size = 0;
        heavy[u] = -1;
        for(auto &v: adj[u]){
            if(v != p_){
                depth[v] = depth[u] +1;
                int sz = dfs_size_calc(v, u);
                size[u] += sz;
                if(sz > max_size){
                    max_size = sz;
                    heavy[u] = v;
                }
            }
        }
        return size[u];
    }

    void dfs_hld(int u, int h){
        head[u] = h;
        pos[u] = current_pos;
        arr[current_pos] = a[u];
        current_pos++;
        if(heavy[u] != -1){
            dfs_hld(heavy[u], h);
            for(auto &v: adj[u]){
                if(v != parent[u] && v != heavy[u]){
                    dfs_hld(v, v);
                }
            }
        }
    }

    void build(){
        dfs_size_calc(1, -1);
        dfs_hld(1, 1);
    }

    void query_path(int u, int v, int x, SegmentTree &st, vi &candidates){
        while (head[u] != head[v]){
            if(depth[head[u]] > depth[head[v]]){
                swap(u, v);
            }
            st.query_range(1, 0, st.n -1, pos[head[v]], pos[v], x, candidates);
            v = parent[head[v]];
        }
        if(depth[u] > depth[v]){
            swap(u, v);
        }
        st.query_range(1, 0, st.n -1, pos[u], pos[v], x, candidates);
    }
};

void solve()
{
    int n; cin >> n;
    HLD hld(n);
    for(int i = 1; i <= n; i++) cin >> hld.a[i];
    for(int i = 0; i < n - 1; i++){
        int x , y; cin >> x >> y;
        hld.add_edge(x , y);
    }

    hld.build();
    SegmentTree st(n);
    st.build(hld.arr);
    int q;
    cin >> q;
    while(q--){
        int l, r, x; cin >> l >> r >> x;
        vector<int> candidates;
        hld.query_path(l, r, x, st, candidates);
        int min1 = LLONG_MAX, min2 = LLONG_MAX;
        for(auto &val : candidates){
            int diff = abs(val - x);
            if(diff < min1){
                min2 = min1;
                min1 = diff;
            }
            else if(diff < min2){
                min2 = diff;
            }
        }
        cout << min1 + min2 << endl;
    }
}


int32_t main()
{
    ios 
    int t = 1;
    testcases and cin >> t;
    while(t--) solve();
}
