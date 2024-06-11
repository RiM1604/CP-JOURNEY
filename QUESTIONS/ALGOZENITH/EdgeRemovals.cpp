// Date: 11-06-2024
// Start Time: 18:07:11
// End Time  : 18:47:25
// Time Taken: 40 minutes
// Author: RiM1604
// QUESTION LINK: ....
// Rating: Easy
// Description: AZ problem
// Solved: Yes
// Learning: Using marked to keep track of non deleted edges and adding them using unionfind before starting the queries from the reverse order.

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
        parent = new int[n + 1];
        rank = new int[n + 1];
        for (int i = 1; i <= n; i++)
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
        for (int i = 1; i <= n; i++)
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
        for (int i = 1; i <= n; i++)
            cout << i << "->" << parent[i] << endl;
    }
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    // cout << n << m << q;
    vi marked = vi(m + 1, 0);
    vector<pair<int, int>> edgelist;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        edgelist.pb({a, b});
        // cout << a << b;
    }
    vector<pair<int, int>> query;
    int temp = q;
    while (temp--)
    {
        int a;
        cin >> a;
        // cout << a;
        if (a == 1)
        {
            int b;
            cin >> b;
            // cout << b << endl;
            query.pb({1, b});
            marked[b] = 1;
        }
        else if (a == 2)
        {
            query.pb({2, -1});
            // cout << endl;
        }
    }
    reverse(query.begin(), query.end());
    UnionFind uf(n);
    for (int i = 1; i <= m; i++)
    {
        if (!marked[i])
        {
            uf.merge(edgelist[i - 1].first, edgelist[i - 1].second);
        }
    }
    // // cout << q << endl;
    // // cout << query[q - 1].first << query[q - 1].second << endl;
    // for (int i = 0; i < q; i++)
    // {
    //     cout << query[i].first << " " << query[i].second;
    // }
    vector<int> ans;
    for (int i = 0; i < q; i++)
    {
        pair<int, int> temp = query[i];
        if (temp.first == 1)
        {
            uf.merge(edgelist[temp.second].first, edgelist[temp.second].second);
        }
        else
        {
            ans.pb(uf.size());
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
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