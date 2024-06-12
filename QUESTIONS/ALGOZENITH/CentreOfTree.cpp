// Date: 12-06-2024
// Start Time: 16:39:27
// End Time  : 17:47:54
// Time Taken: 68 minutes
// Author: RiM1604
// QUESTION LINK: In PC
// Rating: Easy
// Description: Find Diameter of Tree
// Solved: Yes
// Learning: Simple diameter code using 2 bfs calls

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

void bfs(int st, vi &dist, vvi &g, vi &parent)
{

    queue<int> q;
    q.push(st);
    dist[st] = 0;
    while (!q.empty())
    {
        auto pos = q.front();
        q.pop();
        for (auto v : g[pos])
        {
            if (dist[v] > dist[pos] + 1)
            {
                dist[v] = dist[pos] + 1;
                parent[v] = pos;
                q.push(v);
            }
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    vvi g;
    g.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    vi dist = vi(n + 1, 1e9);
    vi parent = vi(n + 1);
    parent[1] = -1;
    bfs(1, dist, g, parent);
    int max1 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[max1] < dist[i])
            max1 = i;
    }
    for (int i = 1; i <= n; i++)
    {
        dist[i] = 1e9;
    }
    bfs(max1, dist, g, parent);
    int max2 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[max2] < dist[i])
            max2 = i;
    }
    vi path;
    // cout << max1 << endl;
    // cout << max2 << endl;
    int temp = max2;
    // int len = 0;
    while (temp != max1)
    {
        // len++;
        path.pb(temp);
        temp = parent[temp];
    }
    path.pb(max1);
    // cout << len << endl;
    cout << dist[max2] << endl;
    // if (dist[max2] % 2 != 0)
    // {
    //     cout << -1 << endl;
    // }
    // else
    // {
    //     cout << path[dist[max2] / 2] << endl;
    // }
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