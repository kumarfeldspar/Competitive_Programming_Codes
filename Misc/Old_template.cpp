#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_pair_set;
/*==============================================MACROS=================================================*/
#define forder(x) find_by_order(x)
#define okey(x) order_of_key(x)
#define sqrt sqrtl
#define pok(ok) (ok) ? cout << "YES" << nl : cout << "NO" << nl;
#define nl '\n'
#define F first
#define S second
#define __builtin_popcount __builtin_popcountll
#define vvi vector<vector<int>>
#define ld long double
#define pb push_back
#define mp make_pair
#define precision(i) cout << fixed << setprecision(i)
#define vpii vector<pair<int, int>>
#define pii pair<int, int>
#define vi vector<int>
#define stoi stoll
#define all(x) x.begin(), x.end()
#define mii map<int, int>
#define pqb priority_queue<int>
#define sz(a) (ll) a.size()
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define pqs priority_queue<int, vi, greater<int>>
#define rsort(a) sort(a.rbegin(), a.rend())
#define get_sum(a) accumulate(a.begin(), a.end(), 0LL)
#define get_max(a) *max_element(a.begin(), a.end())
#define get_min(a) *min_element(a.begin(), a.end())
#define uniq(s) s.resize(unique(s.begin(), s.end()) - s.begin())
#define setbits(x) __builtin_popcountll(x)
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());
#define SHUF(v) shuffle(all(v), RNG);
long long rnd(long long x, long long y)
{
    return uniform_int_distribution<long long>(x, y)(RNG);
}
// Use mt19937_64 for 64 bit random numbers
#define print(x) cout << x << nl
#define inf 1e18
#define ld long double
#define w(t)  \
    int t;    \
    cin >> t; \
    while (t--)
#define in(k) \
    int k;    \
    cin >> k;
#define f(i, x) for (int i = 0; i < x; i++)
#define bfor(i, a, b) for (int i = a; i >= b; i--)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define trav(a, x) for (auto &a : x)
/*===============================================DEBUG===================================================*/
#define dbg1(x) cout << #x << " " << x << endl
#define dbg2(x, y) cout << #x << " " << x << " " << #y << " " << y << endl
#define dbg3(x, y, z) cout << #x << " " << x << " " << #y << " " << y << " " << #z << " " << z << endl
#define dbg4(x, y, z, w) cout << #x << " " << x << " " << #y << " " << y << " " << #z << " " << z << " " #w << " " << w << endl
#define dbg5(x, y, z, w, a) cout << #x << " " << x << " " << #y << " " << y << " " << #z << " " << z << " " #w << " " << w << " " << #a << " " << a << endl
template <typename T>
void _print1(T i) { cout << i; };
template <typename x, typename... y>
void _print1(x a, y... b)
{
    _print1(a);
    if (sizeof...(b))
        cout << ", ";
    _print1(b...);
}
#define dbg(x...)         \
    cout << #x << " => "; \
    _print1(x);           \
    cout << "\n";
void _print(ll t) { cerr << t; }
void _print(int t) { cerr << t; }
void _print(string t) { cerr << t; }
void _print(char t) { cerr << t; }
void _print(ld t) { cerr << t; }
void _print(double t) { cerr << t; }
template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);
template <class T, class V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.first);
    cerr << ",";
    _print(p.second);
    cerr << "}";
}
template <class T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
/*=============================================FUNCTIONS=================================================*/
string tobin(ll x)
{
    // shows from left
    string res;
    while (x > 0)
    {
        if (x % 2 == 0)
            res += '0';
        else
            res += '1';
        x /= 2;
    }
    reverse(all(res));
    return res;
}
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define MAX 500007
vector<int> primes;
bool isprime[MAX];
int spf[MAX];
void sieve()
{
    f(i, MAX) spf[i] = i;
    for (ll i = 2; i < MAX; i++)
    {
        if (spf[i] == i)
        {
            for (ll j = i * i; j < MAX; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
    f(i, MAX) isprime[i] = true;
    isprime[1] = false;
    for (ll i = 2; i < MAX; i++)
    {
        if (isprime[i])
        {
            for (ll j = i * i; j < MAX; j += i)
                isprime[j] = false;
        }
    }

    // for (ll p = 2; p < MAX; p++)
    // 	if (isprime[p])
    // 		primes.push_back(p);
}
ll bpow(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll dx[] = {0, 1, -1, 0};
ll dy[] = {1, 0, 0, -1};
ll nCr(ll n, ll r)
{
    if (n < r)
        return 0;
    if (r > n - r)
        r = n - r;
    ll ans = 1;
    ll i;
    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / __gcd(a, b) * b; }
ll MI(ll a, ll m) { return bpow(a, m - 2, m); }
void meta(int x) { cout << "Case #" << x << ": "; }
/*
order_of_key (val): returns the no. of values less than val
find_by_order (k): returns the iterator to kth largest element.(0-based)
memory taken by int of 1e6 is 4 mbs
*/
#define int long long int
#define mod 1000000007
const int N = 4e5 + 5;

void solve(){

}

int32_t main()
{
    fastio;

    //  #ifndef ONLINE_JUDGE
    //      freopen("input.txt", "r", stdin);
    //      freopen("output.txt", "w", stdout);
    //  #endif

    int t = 1;
    cin >> t;
    int tc = 1;
    while (t--){
        // meta(tc++);
        solve();
    }

    // ends
}