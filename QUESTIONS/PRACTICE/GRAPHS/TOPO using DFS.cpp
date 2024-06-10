// Date: 05-06-2024
// Start Time: 22:13:29
// End Time  : 22:21:18
// Time Taken: 7 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Easy
// Description: Topological sorting using dfs
// Solved: Yes
// Learning: if length of topo array is not equal to number of nodes then there is a cycle in the graph

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
vpii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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
vi topo;
void dfs(int node, vvi &adj)
{
    vis[node] = 1;
    for (auto nn : adj[node])
    {
        if (!vis[nn])
        {
            dfs(nn, adj);
        }
    }
    topo.pb(node);
}

void solve()
{
    memset(vis, 0, sizeof(vis));
    // directed graph
    int n, m;
    cin >> n >> m;
    vvi v(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            dfs(i, v);
        }
    }

    reverse(topo.begin(), topo.end());
    for (auto it : topo)
    {
        cout << it << " ";
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