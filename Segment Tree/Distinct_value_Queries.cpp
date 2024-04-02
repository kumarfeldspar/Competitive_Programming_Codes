/* https://cses.fi/problemset/task/1734/ */

#include <bits/stdc++.h>
using namespace std;
/*
    we process the queries by their R value
    and maintain a bit from o to R
    we only keep the rightmost occurence of each element
    as we would always query from Lx to R so righmost occurence
    will always come if it has to
*/
struct bit
{
    vector<int> BIT;
    int N;
    bit(int n)
    {
        N = n;
        BIT.resize(n + 1, 0);
    }
    int query(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += BIT[i];
            i -= (i & (-i));
        }
        return sum;
    }
    void update(int i, int val)
    {
        while (i <= N)
        {
            BIT[i] += val;
            i += (i & (-i));
        }
    }
};
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1);
    map<int, int> prev;
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    vector<vector<pair<int, int>>> queries(n + 1);
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        queries[r].push_back({l, i});
    }
    bit BIT(n + 1);
    vector<int> ans(q);
    for (int i = 1; i <= n; i++)
    {
        if (prev.find(v[i]) != prev.end())
        {
            int last = prev[v[i]];
            BIT.update(last, -1); // made the contribution of last element zero
        }
        BIT.update(i, 1);
        // keeping only the lastest element active
        prev[v[i]] = i;
        for (auto &j : queries[i])
        {
            int l = j.first, r = i;
            int distinct = BIT.query(r) - BIT.query(l - 1);
            ans[j.second] = distinct;
        }
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}