// Date: 12-06-2024
// Start Time: 18:02:04
// End Time  : 18:41:54
// Time Taken: 39 minutes
// Author: RiM1604
// QUESTION LINK: In PC
// Rating: Easy
// Description: Finding the no of diameters in case of single center and two centers
// Solved: Yes
// Learning: Keep track of how many nodes at distance len/2 in subtree[] using dfs. Took time to debug the code and dont be too scared to write the total code sometimes.

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

void bfs(int st, vi &dist, vvi &g, vi &par)
{

    queue<int> q;
    q.push(st);
    dist[st] = 0;
    while (!q.empty())
    {
        auto pos = q.front();
        q.pop();
        for (auto v : g[pos])
        {
            if (dist[v] > dist[pos] + 1)
            {
                dist[v] = dist[pos] + 1;
                par[v] = pos;
                q.push(v);
            }
        }
    }
}

void dfs(int nn, int pp, int dd, int len, vi &subtree, vvi &g)
{
    if (dd == len)
    {
        subtree[nn] = 1;
        return;
    }
    for (auto v : g[nn])
    {
        if (v != pp)
        {
            dfs(v, nn, dd + 1, len, subtree, g);
            subtree[nn] += subtree[v];
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    vvi g;
    g.resize(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    vi dist = vi(n + 1, 1e9);
    vi par = vi(n + 1);
    bfs(1, dist, g, par);
    int max1 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[max1] < dist[i])
        {
            max1 = i;
        };
    }
    for (int i = 1; i <= n; i++)
    {
        dist[i] = 1e9;
    }
    bfs(max1, dist, g, par);
    int max2 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dist[max2] < dist[i])
            max2 = i;
    }
    // cout << dist[max2] << endl;
    int temp = max2;
    vi ans;
    while (temp != max1)
    {
        ans.pb(temp);
        // len++;
        temp = par[temp];
    }
    int len = dist[max2];
    if (len % 2 != 0)
    {
        int center1 = ans[len / 2 + 1];
        int center2 = ans[len / 2];
        vi subtree = vi(n + 1, 0);
        // cout << center1 << endl;
        int sum1 = 0;
        // int sq_sum = 0;
        dfs(center1, center2, 0, len / 2, subtree, g);
        sum1 += subtree[center1];
        // sq_sum += subtree[center1] * subtree[center1];
        // cout << sq_sum;
        subtree.assign(n + 1, 0);
        dfs(center2, center1, 0, len / 2, subtree, g);
        int sum2 = 0;
        sum2 += subtree[center2];
        // sq_sum += subtree[center2] * subtree[center2];
        // cout << sum2 << endl;
        // cout << subtree[center2] << endl;
        int ans = sum1 * sum2;
        cout << ans << endl;
    }
    else
    {
        int center = ans[len / 2];
        // cout << center << endl;
        vi subtree = vi(n + 1, 0);
        dfs(center, -1, 0, len / 2, subtree, g);
        int sum = 0;
        int sq_sum = 0;
        for (auto v : g[center])
        {
            sum += subtree[v];
            sq_sum += subtree[v] * subtree[v];
        }
        // cout << sum << endl;
        // cout << sq_sum << endl;
        int ans = (sum * sum - sq_sum) / 2;
        cout << ans << endl;
    }
    // cout << len << endl;
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