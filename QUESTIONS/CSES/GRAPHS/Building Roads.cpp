// Date: 05-06-2024
// Start Time: 09:26:28
// End Time  : 09:43:36
// Time Taken: 17 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1666/
// Rating: Easy
// Description: Find the number of components
// Solved: Yes
// Learning: How to print the edges required to connect the components

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
int vis[MAXM + 5];
void dfs(int node, int comp, vvi &v)
{
    vis[node] = comp;
    for (auto nn : v[node])
    {
        if (!vis[nn])
        {
            dfs(nn, comp, v);
        }
    }
}

void solve()
{
    // find the number of componnents and report ans - 1
    int n, m;
    cin >> n >> m;
    vvi v(n + 1);
    memset(vis, 0, sizeof(vis));
    for (int j = 1; j <= m; j++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    // using dfs to count the number of components
    int comp = 0;
    vpii ans;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            if (i != 1)
                ans.pb({i - 1, i});
            comp++;
            dfs(i, comp, v);
        }
    }
    cout << comp - 1 << endl;
    for (auto p : ans)
    {
        cout << p.first << " " << p.second << endl;
    }
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