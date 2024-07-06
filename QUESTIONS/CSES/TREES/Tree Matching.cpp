// Date: 05-07-2024
// Start Time: 22:45:37
// End Time  : 23:48:23
// Time Taken: 62 minutes
// Author: RiM1604
// QUESTION LINK: https://cses.fi/problemset/task/1130
// Rating: Easy
// Description: Find the matching i.e the edges give a tree.
// Solved: Yes
// Learning: Simple observation that do matching starting from the leaf nodes which is always optimal. Forgot to do g[a].pb(b) and g[b].pb(a) and did g[a].pb(b) but its wrong as it is undirected.

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
#define int long long
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

vvi g;
int ans = 0;
vi visited;
int dfs(int node, int pp, vvi &g)
{
    int val = 0;
    visited[node] = 1;
    for (auto v : g[node])
    {
        if (v != pp)
        {
            val += dfs(v, node, g);
        }
    }
    if (val == 0)
    {
        // cout << "ans" << ans << "node" << node << endl;
        return 1;
    }
    ans += 1;
    // cout << "ans" << ans << "node" << node << endl;
    return 0;
}

void solve()
{
    int n;
    cin >> n;
    g.resize(n + 1);
    visited = vi(n + 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        // cout << a << b << endl;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            // cout << "notvisited" << i << endl;
            dfs(i, -1, g);
        }
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