// Date: 12-06-2024
// Start Time: 15:44:06
// End Time  : 16:32:41
// Time Taken: 48 minutes
// Author: RiM1604
// QUESTION LINK: In PC
// Rating: Medium
// Description: Doing weighted Union Find
// Solved: Yes
// Learning: We can keep difference between two ax, ay as and edge and do union find where in merge we need to do dfs to update the ranks of the smaller tree in the merge operation which on all the operations take O(n). Here we dont consolidate the graph on find.

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

struct UnionFind
{
    int n, set_size, *rank, *parent, *A;
    vector<vector<int>> g;
    UnionFind() {}
    UnionFind(int a)
    {
        n = set_size = a;
        rank = new int[n];
        A = new int[n];
        parent = new int[n];
        g.resize(n);
        for (int i = 0; i < n; i++)
        {
            rank[i] = 1;
            A[i] = 0;
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] != x)
        {
            return find(parent[x]);
        }
        return x;
    }

    void dfs(int nn, int pp, int diff)
    {
        A[nn] += diff;
        for (auto v : g[nn])
        {
            if (v != pp)
            {
                dfs(v, nn, diff);
            }
        }
    }
    int ret_diff(int x, int y)
    {
        if (find(x) != find(y))
            return 1e9;
        return A[y] - A[x];
    }
    void merge(int x, int y, int z)
    {
        if (find(x) != find(y))
        {
            int xroot = find(x);
            int yroot = find(y);
            if (rank[xroot] < rank[yroot])
            {
                parent[xroot] = yroot;
                int diff = A[y] - A[x] - z;
                dfs(xroot, -1, diff);
            }
            else
            {
                parent[yroot] = xroot;
                int diff = A[x] - A[y] + z;
                dfs(yroot, -1, diff);
            }
            g[xroot].pb(yroot);
            g[yroot].pb(xroot);
        }
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--)
    {
        int a;
        cin >> a;
        if (a == 0)
        {
            int b, c, d;
            cin >> b >> c >> d;
            uf.merge(b, c, d);
        }
        else
        {
            int b, c;
            cin >> b >> c;
            if (uf.ret_diff(b, c) == 1e9)
            {
                cout << "?" << endl;
            }
            else
            {
                cout << uf.ret_diff(b, c) << endl;
            }
        }
    }
    // delete uf.parent;
    // delete (uf.rank);
    // delete (uf.A);
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