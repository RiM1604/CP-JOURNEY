// Date: 11-06-2024
// Start Time: 17:40:15
// End Time  : 18:00:12
// Time Taken: 19 minutes
// Author: RiM1604
// QUESTION LINK: ...
// Rating: Easy
// Description: AZ Problem
// Solved: Yes
// Learning: Did mistake of doing rank change and parent change on x and y instead of find(x) and find(y) should be careful to remember that x is represented by find(x)

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

struct UnionFind
{
    int n, set_size, *parent, *rank;
    UnionFind() {}
    UnionFind(int a)
    {
        n = set_size = a;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    int find(int x)
    {
        if (parent[x] != x)
        {
            return parent[x] = find(parent[x]);
        }
        return x;
    }
    void merge(int x, int y)
    {
        if (find(x) != find(y))
        {
            set_size -= 1;
            int xroot = find(x);
            int yroot = find(y);
            if (rank[xroot] <= rank[yroot])
            {
                rank[yroot] += rank[xroot];
                parent[xroot] = yroot;
            }
            else
            {
                rank[xroot] += rank[yroot];
                parent[yroot] = xroot;
            }
        }
    }
    void reset()
    {
        set_size = n;
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    int size()
    {
        return set_size;
    }
    void print()
    {
        for (int i = 0; i < n; i++)
            cout << i << "->" << parent[i] << endl;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    while (q--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 0)
        {
            uf.merge(b, c);
        }
        else if (a == 1)
        {
            if (uf.find(b) == uf.find(c))
            {
                cout << 1 << endl;
            }
            else
            {
                cout << 0 << endl;
            }
        }
    }
    // uf.merge(0, 1);
    // uf.merge(1, 2);
    // uf.merge(1, 4);
    // cout << uf.set_size << endl;
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