// Date: 04-06-2024
// Start Time: 16:09:12
// End Time  : 17:48:34
// Time Taken: 99 minutes
// Author: Shashwat Kumar
// QUESTION LINK:
// Rating: Medium
// Description: Find a cycle and print the nodes in it
// Solved: No
// Learning: This code worked because there were no back links in the graph so there will always be a case that when a cycle exists then there are at least 3 nodes in the cycle

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

vi ans;

bool dfs(int node, vvi &adj, vi &vis, int parent)
{
    vis[node] = 1;
    for (auto nn : adj[node])
    {
        debug(nn, vis[nn], node, parent);
        if (!vis[nn])
        {
            if (dfs(nn, adj, vis, node))
            {
                debug(node);
                ans.pb(node);
                return true;
            }
        }
        else if (nn != parent)
        {
            ans.pb(nn);
            ans.pb(node);
            cout << nn << " " << node << " " << parent << endl;
            return true;
        }
    }
    return false;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi adj(n + 1);
    vi vis(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    // using dfs to find a cycle
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            if (dfs(i, adj, vis, -1))
            {
                int i = 1, cnt = 2;
                while (i < ans.size() && ans[i] != ans[0])
                {
                    i++;
                    cnt++;
                }
                debug(cnt);
                cout << cnt << endl;
                for (int i = 0; i < cnt && i < ans.size(); i++)
                {
                    cout << ans[i] << " ";
                }
                return;
            }
    }
    cout << "IMPOSSIBLE";
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