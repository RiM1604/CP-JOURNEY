// Date: 02-06-2024
// Start Time: 23:03:09
// End Time  : 14:43:29
// Time Taken: -499 minutes
// Author: Shashwat Kumar
// QUESTION LINK:
// Rating:
// Description: count the number of connected components in a graph and the count of nodes in each of them
// Solved:
// Learning:

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
#define pb push_back
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

/*********************************************Definition*************************************************/
const ll MAXM = 1e5;
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
int mod = 1e9 + 7;
int INF = 1e9 + 5;
long long INFF = 1000000000000000005LL;
double EPS = 1e-9;
double PI = acos(-1);
vector<long> factors[MAXM + 5];

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

/*********************************************Utility Functions******************************************/
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
/*********************************************Main Function***********************************************/

// here dfs returns you the all the vertices connected to node _node and marks them with the same component number
void dfs(int node, int comp, vvi &v, vi &vis)
{
    vis[node] = comp;
    for (auto nn : v[node]) // O(2*E) it is like searching for all neighbours and for each edge you can have 2
        if (!vis[nn])
            dfs(nn, comp, v, vis);
}

void solve()
{
    int n, m; // vertices and edges
    cin >> n >> m;
    vvi v(n + 1);  // your adjacency list
    vi vis(n + 1); // vector to keep track of visited nodes
    for (int i = 0; i < m; i++)
    {
        // take the input for the two nodes a and b which have an edge between them
        int a, b;
        cin >> a >> b;
        v[a].pb(b);
        v[b].pb(a);
    }
    // adjacency list created
    // using dfs to traverse the graph and mark the nodes with the component number which they belong
    int cnt = 0; // to keep count of components
    // enumerating all components
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            cnt++;
            dfs(i, cnt, v, vis);
        }
    }
    cout << cnt << endl;
    vi idx(n + 1);
    for (int i = 0; i <= n; i++)
    {
        idx[i] = i;
    }
    sort(idx.begin(), idx.end(), [&vis](int a, int b) -> bool
         { return vis[a] < vis[b]; });
    for (int i = 1; i <= n; i++)
    {
        cout << idx[i] << ": " << vis[idx[i]] << endl;
    }

    // now the real question was to calucate the number of possible edges required that can be added to the graph to reduce the number of components in the graph by 1
    vi f(cnt + 1);
    for (int i = 1; i <= n; i++)
    {
        f[vis[i]]++;
    }
    vi suf(cnt + 1);
    suf[cnt] = f[cnt];
    ll ans = 0;
    for (int i = cnt - 1; i > 0; i--)
    {
        ans += f[i] * suf[i + 1];
        debug(ans);
        suf[i] = suf[i + 1] + f[i];
    }
    cout << ans;
    // this can be found out by trying to find out the number of all possible edges from one component to all the others
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