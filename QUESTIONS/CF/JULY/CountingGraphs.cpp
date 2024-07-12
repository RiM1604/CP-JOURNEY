// Date: 12-07-2024
// Start Time: 17:56:46
// End Time  : 19:03:19
// Time Taken: 66 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1857/problem/G
// Rating: 2000
// Description: Find the number of graphs which has mst equal to the given one
// Solved: No
// Learning: Idea here was to sort edges based on weight and process from the starting so that we are sure that the current edge is the highest weighted edge.

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
#define int long long
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
int new_mod = 998244353;

int bin_pow(int base, int pow)
{
    int ans = 1;
    while (pow)
    {
        if (pow & 1)
        {
            ans = 1LL * ans * base % new_mod;
        }
        base = 1LL * base * base % new_mod;
        pow /= 2;
    }
    return ans;
}
/***************************************************Main Function**************************************************/

struct UnionFind
{
    int n, set_size, *parent, *rank;
    UnionFind(int a)
    {
        n = set_size = a;
        parent = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            rank[i] = 1;
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        else
        {
            return parent[x] = find(parent[x]);
        }
    }

    void merge(int x, int y)
    {
        int xroot = find(x);
        int yroot = find(y);
        if (xroot != yroot)
        {
            if (rank[xroot] >= rank[yroot])
            {
                parent[yroot] = xroot;
                rank[xroot] += rank[yroot];
            }
            else
            {
                parent[xroot] = yroot;
                rank[yroot] += rank[xroot];
            }
            set_size -= 1;
        }
    }

    void reset()
    {
        set_size = n;
        for (int i = 1; i <= n; i++)
        {
            rank[i] = 1;
            parent[i] = i;
        }
    }
};

void solve()
{
    int n, s;
    cin >> n >> s;
    vector<pair<int, pair<int, int>>> edgelist;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edgelist.pb({c, {a, b}});
    }
    sort(edgelist.begin(), edgelist.end());
    int ans = 1;
    // cout << n << s << endl;
    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++)
    {
        int w = edgelist[i].F;
        int u = edgelist[i].S.F;
        int v = edgelist[i].S.S;
        // cout << u << v << w << endl;
        int uroot = uf.find(u);
        int vroot = uf.find(v);
        int power = uf.rank[uroot] * uf.rank[vroot] - 1;
        int temp = (s - w + 1);
        // cout << "temp" << temp << endl;
        // cout << "power" << power << endl;
        ans = (1LL * ans * bin_pow(temp, power) % new_mod);
        // cout << "ans" << ans << endl;
        uf.merge(u, v);
    }
    cout << ans << endl;
    uf.reset();
    delete[] uf.rank;
    delete[] uf.parent;
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
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    return 0;
}