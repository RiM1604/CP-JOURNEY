// Date: 02-06-2024
// Start Time: 09:47:34
// End Time  : 10:07:24
// Time Taken: 19 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://atcoder.jp/contests/abc356/tasks/abc356_d
// Rating: Hard
// Description: find the sum of set bits in (i & m) for all i <= n
// Solved: ofc not
// Learning: counting the number of set bits in i-th index for all numbers <= N

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
#define pb push_back
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

/*********************************************Definition*************************************************/
const ll MAXM = 1e5;
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
int mod = 1e9 + 7;
int INF = 1e9 + 5;
long long INFF = 1000000000000000005LL;
double EPS = 1e-9;
double PI = acos(-1);
vector<long> factors[MAXM + 5];

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/*********************************************Utility Functions******************************************/
void init()
{
    for (ll i = 1; i <= MAXM; i++)
    {
        for (ll j = i; j <= MAXM; j += i)
        {
            factors[j].pb(i);
        }
    }
}

int bin_pow(int base, int pow)
{
    int ans = 1;
    while (pow)
    {
        if (pow & 1)
        {
            ans = 1LL * ans * base % mod;
        }
        base = 1LL * base * base % mod;
        pow /= 2;
    }
    return ans;
}
/*********************************************Main Function***********************************************/

// counts the number of elements <= n whose idx bit is set
ll count(ll n, ll idx)
{
    ll p = (1LL << idx);
    ll cycles = n / (2 * p);
    ll res = cycles * p;
    ll l = n % (2 * p);
    if (l >= p)
    {
        res += (l - p + 1);
    }
    // debug(res,p, n,cycles,l);
    return res;
}

void solve()
{
    ll n, m;
    cin >> n >> m;
    ll res = 0;
    int new_mod = 998244353;
    for (ll i = 0; i < 60; i++)
    {
        if (m & (1LL << i))
        {
            // the i-th bit of m is set

            res += count(n, i);
            res %= new_mod;
        }
    }
    cout << res;
}

signed main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++)
    {
#ifdef LOCAL
        std::cerr << "Case # " << i << endl;
        std::cout << "Case #" << i << endl;
#endif
        solve();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}