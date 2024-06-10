// Date: 07-06-2024
// Start Time: 00:14:42
// End Time  : 00:27:40
// Time Taken: 12 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Easy
// Description: find the sum of all paths in a tree basically summation of dist(a,b) for all a,b belongs to V
// Solved: Yes
// Learning: how to use contribution of each edge in the sum

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
int n;
vvi v;
vi subtreeSZ;
ll ans = 0;
void dfs(int node, int pp)
{
    subtreeSZ[node] = 1;
    for (auto nn : v[node])
    {
        if (nn != pp)
        {
            dfs(nn, node);
            subtreeSZ[node] += subtreeSZ[nn];
        }
    }
    ans += 1LL * subtreeSZ[node] * (n - subtreeSZ[node]);
}

void solve()
{
    // for each node i will count the number of nodes in the subtree of it and multiply it with the count of the rest of the nodes to get the count of number of times this node appears in a path
    cin >> n;
    v = vvi(n + 1);
    subtreeSZ = vi(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
    }
    // run dfs from the root to calculate the subtree size of each node
    dfs(1, -1);
    cout << ans;
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