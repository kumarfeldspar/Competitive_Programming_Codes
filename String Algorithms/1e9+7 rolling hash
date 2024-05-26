
#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
long long n;
const int N=1e5+5;
vector<long long> pre(N + 1, 0), rev(N + 1, 0);
long long bpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
long long MI(long long a, long long m) { return bpow(a, m - 2, m); }
void compute_hash(string s, vector<long long> &prefix_hash)
{
    long long p = 1;
    for (long long i = 0; i < s.size(); i++)
    {
        long long curr = (s[i] - 'a' + 1) * p;
        if (curr > mod)
            curr %= mod;
        p *= 29;
        if (p > mod)
            p %= mod;
        prefix_hash[i + 1] = prefix_hash[i] + curr;
        if (prefix_hash[i + 1] > mod)
            prefix_hash[i + 1] %= mod;
    }
}
void compute_inv(vector<long long> &inv)
{
    long long init = MI(29, mod);
    inv[0] = inv[1] = 1;
    for (long long i = 2; i <= n; i++)
    {
        inv[i] = inv[i - 1] * init;
        inv[i] %= mod;
    }
}
long long pre(int i,int j){
  long long curr=pre[i+1]-pre[j]+mod;
  curr%=mod;
  curr*=inv[j+1];
  curr%=mod;
  return curr;
}
int32_t main()
{
    string s;
    cin >> s;
    n = s.size();
    
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    compute_hash(s, pre);
    compute_hash(rev_s, rev);
    vector<long long> inv(n + 1, 1);
    compute_inv(inv);
    long long q;
    cin >> q;
    while (q--)
    {
        long long id;
        cin >> id;
        long long hi = min(id - 1, n - id);
        long long lo = 0;
        long long ans = 0;
        while (hi >= lo)
        {
            long long mid = (lo + hi) / 2;
            long long h_front = (pre[id + mid] - pre[id] + mod);
            if (h_front > mod)
                h_front %= mod;
            h_front = h_front * inv[id + 1];
            h_front %= mod;
            long long rid = n - id + 1;
            long long h_back = rev[rid + mid] - rev[rid] + mod;
            if (h_back > mod)
                h_back %= mod;
            h_back = h_back * inv[rid + 1], mod;
            h_back%=mod;
            if (h_back == h_front)
            {
                lo = mid + 1;
                ans = mid;
            }
            else
                hi = mid - 1;
        }
        long long pr = 0;
        if (ans != 0)
            pr = 1 + 2 * ans;
        cout << pr << " ";
    }
}
