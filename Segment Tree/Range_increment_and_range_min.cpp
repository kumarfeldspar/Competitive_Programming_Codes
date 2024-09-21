#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200000 +2329;
const int inf=1e18;
//when we arrive at a node we update its contents and 
//propogate its updates to its children
int sgt[4 * N],lazy[4 * N],arr[N];
void push(int t, int tl, int tr)
{
	sgt[t] += lazy[t];
	// since we are doing it for minm
	// if we did if for sum we would have to (tr-tl+1)*lazy[t]
	if (tl != tr)
	{
		lazy[2 * t + 1] += lazy[t];
		lazy[2 * t + 2] += lazy[t];
	}
	lazy[t] = 0;
}

void update(int t,int tl,int tr,int l,int r,int inc){
	push(t, tl, tr);
	if (l > tr || tl > r)
		return ;
	if(l==tl&&r==tr){//this is important 
		lazy[t]+=inc;
		push(t,tl,tr);
		return ;
	}
	int mid=(tl+tr)/2;
	update(2*t+1,tl,mid,l,min(r,mid),inc);
	update(2*t+2,mid+1,tr,max(l,mid+1),r,inc);
	sgt[t]=min(sgt[2*t+1],sgt[2*t+2]);
}
int query(int t,int tl,int tr,int l,int r){
	push(t, tl, tr);
	if (l > tr || tl > r)
		return inf;
	if (tl >= l && tr <= r)
	{
		return sgt[t];
	}
	int mid=(tl+tr)/2;
	return min(query(2*t+1,tl,mid,l,min(r,mid)),query(2*t+2,mid+1,tr,max(l,mid+1),r));
}

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		update(0,0,n-1,i,i,arr[i]);
	}

	int m;
	cin >> m;
	cin.ignore();
	for (int i = 0; i < m; i++)
	{
		string s;
		getline(cin, s);
		stringstream ss(s);
		vector<int> v;
		int a;
		while (ss >> a)
		{
			v.push_back(a);
		}
		int l=v[0],r=v[1];
		if (v.size() == 3)
		{	
			int d=v[2];
			if (l <= r)
				update(0, 0, n - 1, l, r, d);
			else
			{
				update(0, 0, n - 1, l, n - 1, d);
				update(0, 0, n - 1, 0, r, d);
			}
		}
		else
		{
			if (l <= r)
				cout << query(0, 0, n - 1, l, r);
			else
			{
				cout << min(query(0, 0, n - 1, l, n - 1), query(0, 0, n - 1, 0, r));
			}
			cout << '\n';
		}
	}
}
