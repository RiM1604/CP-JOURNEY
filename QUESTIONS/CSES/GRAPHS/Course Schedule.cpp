// Date: 03-07-2024
// Start Time: 20:02:22
// End Time  : 20:31:07
// Time Taken: 28 minutes
// Author: RiM1604
// QUESTION LINK: https://cses.fi/problemset/task/1679
// Rating: Easy
// Description: Find the order in which you need to do courses give prerequisites
// Solved: Yes
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

vi toposort;
vi indegree;
void kahn(int n, vvi &g)
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        auto pos = q.front();
        q.pop();
        toposort.push_back(pos);
        for (auto v : g[pos])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
}
vi visited;
stack<int> st;
vi in_stack;
int dfs(int node, vvi &g)
{
    st.push(node);
    in_stack[node] = 1;
    visited[node] = 1;
    for (auto v : g[node])
    {
        if (!visited[v])
        {
            if (dfs(v, g))
            {
                return 1;
            }
        }
        else if (in_stack[v])
        {
            return 1;
        }
    }
    st.pop();
    in_stack[node] = 0;
    return 0;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi g;
    g.resize(n + 1);
    in_stack = vi(n + 1, 0);
    visited = vi(n + 1, 0);
    indegree.resize(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        indegree[b]++;
        // cout << a << b;
    }
    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, g))
            {
                flag = 1;
            }
        }
    }
    if (flag)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        kahn(n, g);
        for (auto v : toposort)
        {
            cout << v << " ";
        }
        cout << endl;
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