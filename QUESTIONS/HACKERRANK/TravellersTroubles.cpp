// Date: 11-06-2024
// Start Time: 23:45:48
// End Time  : 00:30:46
// Time Taken: -1395 minutes
// Author: RiM1604
// QUESTION LINK:
// Rating:
// Description:
// Solved:
// Learning:

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
#define int long long
#define F first
#define S second
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

class prioritize
{
public:
    bool operator()(pair<int, int> &p1, pair<int, int> &p2)
    {
        return p1.S > p2.S;
    }
};

void dijkstra(int sc, vi &dist, vi &visited, vector<vector<pair<int, int>>> &g)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, prioritize> pq;
    pq.push({sc, 0});
    dist[sc] = 0;

    while (!pq.empty())
    {
        auto pos = pq.top();
        pq.pop();
        if (visited[pos.F])
        {
            continue;
        }
        visited[pos.F] = 1;
        for (auto v : g[pos.F])
        {
            if (dist[v.F] > dist[pos.F] + v.S)
            {
                dist[v.F] = dist[pos.F] + v.S;
                pq.push({v.F, dist[v.F]});
            }
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    int x, y;
    cin >> x >> y;
    vector<vector<pair<int, int>>> g = vector<vector<pair<int, int>>>(n + 1);
    vector<vector<pair<int, int>>> g_rev = vector<vector<pair<int, int>>>(n + 1);
    vector<pair<pair<int, int>, int>> edgelist;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g_rev[b].pb({a, c});
        edgelist.pb({{a, b}, c});
    }
    vi visited = vi(n + 1, 0);
    vi dist = vi(n + 1, 1e18);
    vi dist_rev = vi(n + 1, 1e18);

    priority_queue<pair<int, int>, vector<pair<int, int>>, prioritize> pq;
    pq.push({x, 0});
    dist[x] = 0;

    while (!pq.empty())
    {
        auto pos = pq.top();
        pq.pop();
        if (visited[pos.F])
        {
            continue;
        }
        visited[pos.F] = 1;
        for (auto v : g[pos.F])
        {
            if (dist[v.F] > dist[pos.F] + v.S)
            {
                dist[v.F] = dist[pos.F] + v.S;
                pq.push({v.F, dist[v.F]});
            }
        }
    }

    // dijkstra(x, dist, visited, g);
    for (int i = 1; i <= n; i++)
    {
        visited[i] = 0;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, prioritize> pq2;
    pq2.push({y, 0});
    dist_rev[y] = 0;

    while (!pq2.empty())
    {
        auto pos = pq2.top();
        pq2.pop();
        if (visited[pos.F])
        {
            continue;
        }
        visited[pos.F] = 1;
        for (auto v : g_rev[pos.F])
        {
            if (dist_rev[v.F] > dist_rev[pos.F] + v.S)
            {
                dist_rev[v.F] = dist_rev[pos.F] + v.S;
                pq2.push({v.F, dist_rev[v.F]});
            }
        }
    }

    // dijkstra(y, dist_rev, visited, g_rev);
    // cout << dist[4] <<" "<< dist_rev[1] << endl;
    // vi ans;
    for (int i = 1; i <= m; i++)
    {
        auto edge = edgelist[i - 1];
        int temp = min(dist[edge.first.first], dist[edge.first.second]) + min(dist_rev[edge.first.first], dist_rev[edge.first.second]);
        temp = min(temp, dist[y]);
        if (temp >= 1e18)
        {
            cout << -1 << " ";
        }
        else
        {
            cout << temp << " ";
        }
    }
    // for (int i = 0; i < m;i++){
    //     cout << ans[i] << " ";
    // }
    cout << endl;
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
    // cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}