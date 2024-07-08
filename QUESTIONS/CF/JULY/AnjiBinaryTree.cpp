// Date: 08-07-2024
// Start Time: 16:34:37
// End Time  : 17:59:20
// Time Taken: 84 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1900/problem/C
// Rating: 1300
// Description: Find the min cost required to make sure you atleast reach a leaf node.
// Solved: Yes
// Learning: A good idea to take edge weights with 0 and 1 when the travel to that node does not require any cost and when the travel requires a cost.

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

vector<vector<pair<int, int>>> g;
// vi ans;
string s;
// void dfs(int node, vvi &g)
// {
//     cout << "node" << node << endl;
//     if (node == 0)
//     {
//         return;
//     }
//     int l = g[node][0];
//     int r = g[node][1];
//     dfs(l, g);
//     dfs(r, g);

//     if ((!g[node][0]) && (!g[node][1]))
//     {
//         ans[node] = 0;
//         // return;
//     }
//     else if (!g[node][1])

//     {
//         ans[node] = ans[g[node][0]];
//         if (s[node - 1] != 'L')
//         {
//             ans[node] += 1;
//         }
//     }
//     else if (!g[node][0])
//     {
//         ans[node] = ans[g[node][1]];
//         if (s[node - 1] != 'R')
//         {
//             ans[node] += 1;
//         }
//     }
//     else
//     {
//         if (ans[g[node][0]] == ans[g[node][1]])
//         {
//             ans[node] = ans[g[node][0]];
//             if (s[node - 1] == 'U')
//             {
//                 ans[node] += 1;
//             }
//         }
//         else if (ans[g[node][0]] > ans[g[node][1]])
//         {
//             ans[node] = ans[g[node][1]];
//             ans[node] += (s[node - 1] == 'R') ? 0 : 1;
//         }
//         else if (ans[g[node][0]] < ans[g[node][1]])
//         {
//             ans[node] = ans[g[node][0]];
//             ans[node] += (s[node - 1] == 'L') ? 0 : 1;
//         }
//     }
//     return;
// }

int dfs(int nn, int dd)
{
    if (g[nn][0].F == 0 && g[nn][1].F == 0)
    {
        return dd;
    }
    int ans = INT_MAX;
    for (auto v : g[nn])
    {
        if (v.F != 0)
        {
            ans = min(ans, dfs(v.F, dd + v.S));
        }
    }
    return ans;
};
void solve()
{
    int n;
    cin >> n;
    cin >> s;
    // cout << (s[0] == 'L') << endl;
    g.clear();
    g.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        if (s[i - 1] == 'L')
        {
            g[i].pb({l, 0});
            g[i].pb({r, 1});
        }
        else if (s[i - 1] == 'R')
        {
            g[i].pb({l, 1});
            g[i].pb({r, 0});
        }
        else
        {
            g[i].pb({l, 1});
            g[i].pb({r, 1});
        }
        // g[i].pb(l);
        // g[i].pb(r);
        // cout << l << r << i << endl;
        // cout << g[i][0] << g[i][1] << endl;
    }
    cout << dfs(1, 0) << endl;
    // cout << ans[1] << endl;
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