#include <bits/stdc++.h>
using namespace std;
struct sparseTable
{
	vector<long long> lg;
	vector<vector<long long>> st1, st2;
	sparseTable(vector<long long> &a)
	{
		int n = a.size();
		lg.resize(n + 1);
		st1.resize(n + 1, vector<long long>(21, 0LL));
		st2.resize(n + 1, vector<long long>(21, 0LL));
		lg[1] = 0;
		for (int i = 2; i <= n; i++)
		{
			lg[i] = lg[(i / 2)] + 1;
		}
		for (int i = 0; i < n; i++)
			st1[i][0] = st2[i][0] = a[i];
		for (int len = 1; len <= lg[n]; len++)
		{

			for (int i = 0; i + (1ll << len) - 1 < n; i++)
			{

				st1[i][len] = min(st1[i][len - 1], st1[i + (1ll << (len - 1))][len - 1]);
				st2[i][len] = max(st2[i][len - 1], st2[i + (1ll << (len - 1))][len - 1]);
			}
		}
	}
	pair<long long , long long> query(int l, int r)
	{
		int len = r - l + 1;
		long long j = lg[len];
		long long mn = min(st1[l][j], st1[r - (1ll << j) + 1][j]);
		long long mx = max(st2[l][j], st2[r - (1ll << j) + 1][j]);
		pair<long long, long long> ans = {mn, mx};
		return ans;
	}
};

int32_t main()
{
	int n;
	cin >> n;
	vector<long long> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	sparseTable st1(a);
	pair<long long,long long>x=st1.query(1,4);
	cout <<x.first<<" "<<x.second; // all values are 0-based indexing
}
