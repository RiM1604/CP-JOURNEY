// Date: 06-06-2024
// Start Time: 12:32:10
// End Time  : 13:55:57
// Time Taken: 83 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Medium
// Description: Find the diameter of a tree (length of the longest path) and print the daimeter
// Solved: Yes
// Learning: using 2dfs to find the extreme nodes in a tree

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

vi dist;
vvi v;
vi parent;
// O(N) because there are only n-1 edges
void dfs(int node, int pp, int dd)
{
    dist[node] = dd;
    parent[node] = pp;
    for (auto nn : v[node])
    {
        if (nn != pp)
        {
            dfs(nn, node, dd + 1);
        }
    }
}

void print_path(int nn)
{
    if (nn == -1)
        return;
    print_path(parent[nn]);
    cout << nn << " ";
}

void solve()
{
    int n;
    cin >> n;
    v.resize(n + 1);
    parent.resize(n + 1);
    dist.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    // adj list created
    // select a random node and find the node farthest from it
    dfs(1, -1, 0);
    // now find the farthest node and run dfs again from that
    int max1 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] > dist[max1])
            max1 = i;
    }
    cout << max1 << endl;
    // now run the dfs from this node
    dfs(max1, -1, 0);
    int max2 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] > dist[max2])
            max2 = i;
    }
    // this is your tre daimeter
    cout << dist[max2] << " " << max2 << endl;
    // now the question is to print the nodes in this diameter
    print_path(max2);
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
TEST CASE::
17
1 3
1 2
1 4
2 5
2 6
2 7
7 12
6 11
6 10
3 8
3 9
9 13
9 14
9 15
14 17
14 16
*/