// Date: 03-07-2024
// Start Time: 20:51:02
// End Time  : 23:19:26
// Time Taken: 148 minutes
// Author: RiM1604
// QUESTION LINK: https://cses.fi/problemset/task/1680/
// Rating: Medium
// Description: Find the longest path from 1 to n
// Solved: Yes
// Learning: Used dp here to do max distance by building the dp from n to 1, note that using par[] method is diff from child[] method cause par[v]=ans[i-1] you cant be sure that the parent is of the largest path, but for child[ans[i-1]]=v you can be sure of that as you know the max val is for which child.

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

vi indegree;
vi dp;
void kahn(vvi &g, int n)
{
    vi ans;
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
        ans.pb(pos);
        for (auto v : g[pos])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    vi can_reach_n = vi(n + 1, 0);
    vi dp(n + 1, 1);
    can_reach_n[n] = 1;
    vi child(n + 1, -1);
    for (int i = n; i >= 1; i--)
    {
        for (auto v : g[ans[i - 1]])
        {
            if (can_reach_n[v] == 1)
            {
                can_reach_n[ans[i - 1]] = 1;
                dp[ans[i - 1]] = max(dp[ans[i - 1]], 1 + dp[v]);
                if (dp[ans[i - 1]] == (1 + dp[v]))
                {
                    child[ans[i - 1]] = v;
                }
            }
        }
    }

    if (can_reach_n[1] == 0)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << dp[1] << endl;
        int temp = 1;
        vi ans_out;
        while (temp != -1)
        {
            ans_out.pb(temp);
            // cout << "par" << child[temp] << " ";
            temp = child[temp];
        }
        // reverse(ans_out.begin(), ans_out.end());
        for (auto v : ans_out)
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g;
    g.resize(n + 1);
    indegree = vi(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        indegree[b]++;
    }
    kahn(g, n);
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