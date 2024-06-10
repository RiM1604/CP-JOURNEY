// Date: 07-06-2024
// Start Time: 11:18:47
// End Time  : 11:59:25
// Time Taken: 40 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Medium
// Description: Find the shortes path in a weithted graph
// Solved: Yes
// Learning: Using Dijkstra's algo to solve it and the most important thing to learn is that the top element is kept at the back of the vector

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
const int mod = 1e9 + 7;
const int INF = 1e9 + 5;
const long long INFF = 1000000000000000005LL;
const double EPS = 1e-9;
const double PI = acos(-1);
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

#define F first
#define S second
int n, m;
vector<vpii> v;
vector<ll> dist;
vi vis;

class Priortize
{
public:
    bool operator()(pair<int, ll> &a, pair<int, ll> &b)
    {
        return a.S > b.S;
    }
};

// the most important thing to learn is that the top element is kept at the back of the vector therefore we return a.S > b.S
// so that the smallest value is at the end of the vector

void dijkstra(int src)
{
    dist[src] = 0;
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, Priortize> pq;
    pq.push({src, 0});
    while (!pq.empty())
    {
        auto node = pq.top();
        pq.pop();
        if (vis[node.F])
            continue;
        vis[node.F] = 1;
        for (auto nn : v[node.F])
        {
            if (dist[nn.F] > dist[node.F] + nn.S)
            {
                // the important step is the rlaxation step here
                dist[nn.F] = dist[node.F] + nn.S;
                pq.push({nn.F, dist[nn.F]});
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    v.resize(n + 1);
    dist.resize(n + 1, 1e18);
    vis.resize(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].pb({b, c});
        v[b].pb({a, c});
    }
    // i need the shortest path to each node
    int src;
    cin >> src;
    dijkstra(src);
    for (int i = 0; i <= n; i++)
    {
        cout << i << "->" << dist[i] << endl;
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

/*
TEST CASE
9 14
0 1 4
1 2 8
2 3 7
3 4 9
4 5 10
5 6 2
6 7 1
7 0 8
7 1 11
7 8 7
6 8 6
8 2 2
2 5 4
3 5 14
0
*/