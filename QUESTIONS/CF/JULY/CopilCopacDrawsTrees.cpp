// Date: 13-07-2024
// Start Time: 13:15:14
// End Time  : 13:36:27
// Time Taken: 21 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1830/problem/A
// Rating: Medium
// Description: output the number of readings Copil Copac needs to draw the tree.
// Solved: Yes
// Learning: idea is to do dfs along with a helping array and using previously calcualted answers to get the answer for the next node.

/****************************************************Pre Processor***************************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

/****************************************************Definition***************************************************/
#define endl '\n'
#define pb push_back
#define F first
#define S second
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

/**************************************************Global Variables*************************************************/
const ll MAXM = 1e5;
int mod = 1e9 + 7;
int INF = 1e9 + 5;
long long INFF = 1000000000000000005LL;
double EPS = 1e-9;
double PI = acos(-1);
vector<long> factors[MAXM + 5];

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/**************************************************Utility Functions***********************************************/
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
/***************************************************Main Function**************************************************/

vector<vector<pair<int, int>>> edgelist;
vector<int> dp;
vector<int> id;
void dfs(int nn)
{
    for (auto v : edgelist[nn])
    {
        if (dp[v.F] == 0)
        {
            dp[v.F] = dp[nn] + (v.S < id[nn]);
            id[v.F] = v.S;
            dfs(v.F);
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    edgelist.clear();
    dp.clear();
    id.clear();
    edgelist.resize(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        edgelist[b].pb({a, i});
        edgelist[a].pb({b, i});
    }
    dp = vector<int>(n + 1, 0);
    id = vector<int>(n + 1, 0);
    dp[1] = 1;
    id[1] = 0;
    int ans = 0;
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}

signed main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    int t = 1;
    cin >> t;
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