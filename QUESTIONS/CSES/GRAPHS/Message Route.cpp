// Date: 05-06-2024
// Start Time: 11:03:32
// End Time  : 11:27:40
// Time Taken: 24 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1667
// Rating: Easy
// Description: Find whether 2 nodes are in the same component or not if yes find the shortes distance between them
// Solved: Yes
// Learning: Just a practice on bfs

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
// to stroe the distance of other nodes from 1
int dis[MAXM + 5];
int n, m;
int par[MAXM + 5];
void print_path(int node)
{
    if (node == -1)
        return;
    print_path(par[node]);
    cout << node << " ";
}

void bfs(vvi &v)
{
    queue<int> q;
    q.push(1);
    dis[1] = 1;
    par[1] = -1;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (auto nn : v[node])
        {
            if (dis[nn] > dis[node] + 1)
            {
                par[nn] = node;
                q.push(nn);
                dis[nn] = dis[node] + 1;
            }
        }
    }

    if (dis[n] > 1e5)
        cout << "IMPOSSIBLE";
    else
    {
        cout << dis[n] << endl;
        print_path(n);
    }
}

void solve()
{
    for (int i = 0; i < MAXM + 5; i++)
    {
        dis[i] = 1e9; // large value tells that this node is unreachable form other node
    }
    cin >> n >> m;
    vvi v(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    // reach form node 1 to n
    // simply find if node n and 1 are in the same component and find the distance between them
    // use bfs
    bfs(v);
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