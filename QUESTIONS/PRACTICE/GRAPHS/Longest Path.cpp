// Date: 05-06-2024
// Start Time: 22:47:56
// End Time  : 00:01:04
// Time Taken: -1366 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Medium
// Description: Find the longest path in the graph
// Solved: No
// Learning: how to use TOPO and DP to solve the question and print the longest path

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

int n, m;
int indegree[MAXM + 5];
vi topo;

// if you want to print the lexicographically smallest topological sorting of the graph use priority_queue
void kahn(vvi &v)
{
    queue<int> q;
    // priority_queue<int> q;
    // so that we cover all the component we start the bfs from each of the nodes
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
            // q.push(-i);
        }
    }
    // now we start the traversal from all the nodes with 0 indegree considering them as the root nodes
    while (!q.empty())
    {
        int node = q.front();
        // int node = -q.top();
        q.pop();
        topo.pb(node);
        for (auto nn : v[node])
        {
            indegree[nn]--;
            if (indegree[nn] == 0)
            {
                q.push(nn);
                // q.push(-nn);
            }
        }
    }
    for (auto node : topo)
    {
        cout << node << " ";
    }
    cout << endl;
}

void solve()
{
    memset(indegree, 0, sizeof(indegree));
    // directed graph
    cin >> n >> m;
    vvi v(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        indegree[b]++;
    }
    // call bfs
    kahn(v);
    // now we use dp to find the length of the largest path
    vi dp(n + 1, 1);
    int len = INT_MIN;
    vi child(MAXM + 5);
    int start_node = -1;
    for (auto it = topo.rbegin(); it != topo.rend(); it++)
    {
        // debug(*it);
        int ans = INT_MIN;
        for (auto nn : v[*it])
        {
            // debug(nn);
            ans = max(ans, dp[nn] + 1);
            if (ans == dp[nn] + 1)
                child[*it] = nn;
        }
        ans = max(ans, 1);
        if (ans == 1)
            child[*it] = -1;
        dp[*it] = ans;
        len = max(len, ans);
        if (len == ans)
            start_node = *it;
    }
    cout << len << endl;
    // now the big question is to print the nodes in this path
    int node = start_node;
    while (node != -1)
    {
        cout << node << " ";
        node = child[node];
    }
    cout << endl;
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