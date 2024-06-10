// Date: 05-06-2024
// Start Time: 11:56:49
// End Time  : 12:07:50
// Time Taken: 11 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1668
// Rating: Easy
// Description: Is the graph a Bipartite graph
// Solved: Yes
// Learning: If the graph can be coloured with 2 cloures such that no neighbours have same colour then yes

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

int n, m;
int coloured[MAXM + 5];

bool dfs(int node, vvi &v, int colour)
{
    coloured[node] = colour;
    for (auto nn : v[node])
    {
        if (coloured[nn] == 0)
        {
            if (!dfs(nn, v, colour ^ 3))
                return false;
        }
        else if (coloured[nn] == colour)
        {
            return false;
        }
    }
    return true;
}

void solve()
{
    cin >> n >> m;
    vvi v(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }

    // check if there is cycle such that me and my neighbour are coloured same
    for (int i = 1; i <= n; i++)
    {
        // if not coloured it means that this node is a part of a new component
        if (coloured[i] == 0)
        {
            if (!dfs(i, v, 1))
            {
                cout << "IMPOSSIBLE";
                return;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << coloured[i] << " ";
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