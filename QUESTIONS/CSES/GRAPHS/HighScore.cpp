// Date: 11-06-2024
// Start Time: 14:15:11
// End Time  : 14:16:57
// Time Taken: 1 minutes
// Author: RiM1604
// QUESTION LINK: https://cses.fi/problemset/task/1673
// Rating: Easy
// Description: CSES problem
// Solved: Yes
// Learning: If there is a cycle in a directed graph it is not guaranteed to have infinite max distance, in this case for it to be infinite the cycle should be reachable from 1 and  you should be able to reach n from the cycle.

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
using lli = long long int;
vector<lli> dist;
vector<pair<int, pair<int, int>>> edgelist;
vector<vector<int>> g;
vi visited;
void dfs(int node)
{
    visited[node] = 1;
    for (auto v : g[node])
    {
        if (!visited[v])
        {
            dfs(v);
        }
    }
}

void solve()
{
    // type your code here for each testcase
    int n, m;
    cin >> n >> m;
    edgelist = vector<pair<int, pair<int, int>>>(m);
    visited = vi(n + 1, 0);
    g = vvi(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        // cout << a << b << c;
        edgelist[i].second.first = a;
        edgelist[i].second.second = b;
        edgelist[i].first = -1 * c;
        g[a].pb(b);
        // cout<<a<<"a"<<b<<"b"<<endl;
    }
    dist = vector<lli>(n + 1, 1e18);
    dist[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int node1 = edgelist[j].second.first;
            int node2 = edgelist[j].second.second;
            int cost = edgelist[j].first;
            // if(dist[])

            if (dist[node2] > dist[node1] + cost)
            {
                dist[node2] = dist[node1] + cost;
            }
        }
    }

    vector<int> neg;
    for (int i = 0; i < m; i++)
    {
        int node1 = edgelist[i].second.first;
        int node2 = edgelist[i].second.second;
        int cost = edgelist[i].first;
        if (dist[node2] > dist[node1] + cost)
        {
            neg.pb(node2);
        }
    }

    int ans = 0;
    for (int i = 0; i < neg.size(); i++)
    {
        int flag = 1;
        dfs(neg[i]);
        if (!visited[n])
        {
            flag = 0;
        }
        // cout<<visited[n]<<endl;
        for (int i = 1; i <= n; i++)
        {
            visited[i] = 0;
        }
        dfs(1);
        // cout<<visited[1]<<endl;
        if (!visited[neg[i]])
        {
            flag = 0;
        }
        if (flag)
        {
            ans = 1;
        }
    }
    if (ans)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << -1 * dist[n] << endl;
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