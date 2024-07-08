// Date: 07-07-2024
// Start Time: 18:23:09
// End Time  : 10:53:40
// Time Taken: -449 minutes
// Author: RiM1604
// QUESTION LINK:
// Rating: Easy
// Description: Find the min no of flips where when you flip the node which you take its child flips but the child's child does not and the child's child's child flips.
// Solved: Yes
// Learning: Did mistake of understanding the question wrong and worked out the wrong solution which passed the first test case somehow.

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

vvi g;
vi visited;
int ans = 0;
vi goal;
vi initial;

vi output;
void dfs(int nn, int pp, int num_ones, int num_zeroes)
{
    if (visited[nn])
    {
        return;
    };
    if ((num_ones) % 2 == 0)
    {
        if (initial[nn] != goal[nn])
        {
            ans += 1;
            num_ones += 1;
            output.pb(nn);
            initial[nn] = goal[nn];
        }
    }
    else if ((num_ones) % 2 == 1)
    {
        if (initial[nn] == goal[nn])
        {
            ans += 1;
            num_ones += 1;
            output.pb(nn);
            initial[nn] = goal[nn];
        }
    }

    visited[nn] = 1;

    for (auto v : g[nn])
    {
        if (v != pp)
        {
            dfs(v, nn, num_zeroes, num_ones);
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    g.resize(n + 1);
    visited = vi(n + 1, 0);
    goal = vi(n + 1, 0);
    initial = vi(n + 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> initial[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> goal[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i, -1, 0, 0);
        }
    }
    cout << ans << endl;
    for (int i = 0; i < output.size(); i++)
    {
        if (i != output.size() - 1)
        {
            cout << output[i] << endl;
        }
        else
        {
            cout << output[i];
        }
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