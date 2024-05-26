#include <bits/stdc++.h>
//https://www.thejoboverflow.com/problem/350/
using namespace std;
const long long mod = 1000000000000037;
const int N=1e5+5;
vector<long long> pre(N, 0), rev(N, 0);
long long n;
long long modmul(long long val, long long n, long long m)
{
	long long q = ((double)val * (double)n / (double)m);
	long long res = val * n - m * q;
	res = (res % m + m) % m;
	return res;
}
long long bpow(long long a, long long b, long long m)
{
	a %= m;
	unsigned long long res = 1;
	while (b > 0)
	{
		if (b & 1)
			res = modmul(res, a, m);
		a = modmul(a, a, m);
		b /= 2;
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
		inv[i] = modmul(inv[i - 1], init, mod);
		inv[i] %= mod;
	}
}
long long sub(int i,int j){//0 based indexes
  long long curr=pre[i+1]-pre[j]+mod;
  curr%=mod;
  curr=modmul(curr,inv[j+1],mod);
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
			long long h_front = sub(id + mid - (id+1));
			long long rid = n - id + 1;
			long long h_back = rev[rid + mid] - rev[rid] + mod;
			if (h_back > mod)
				h_back %= mod;
			h_back = modmul(h_back, inv[rid + 1], mod);
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
