// Date: 04-06-2024
// Start Time: 10:46:39
// End Time  : 13:08:46
// Time Taken: 142 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1192
// Rating: Medium
// Description: find the number of components in a graph but input is a grid
// Solved: No
// Learning: how to transform a grid into a graph

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

/**************************************************Definition*************************************************/
#define endl '\n'
#define pb push_back
// #define int long long
#define F first
#define S second
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
/************************************************Main Function***********************************************/

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;
int vis[1005][1005];

// check function returns whether i can go to cell x,y or not
bool check(int x, int y, vector<vector<bool>> &v)
{
    if (x >= 0 && x < n && y >= 0 && y < m && v[x][y] == true)
        return 1;
    return 0;
}

void dfs(int x, int y, vector<vector<bool>> &v)
{
    // find all the nodes which belong to the same component as v[i][j] and mark them visited
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        if (check(x + dx[i], y + dy[i], v) && !vis[x + dx[i]][y + dy[i]])
        {
            dfs(x + dx[i], y + dy[i], v);
        }
    }
}

void solve()
{
    // length and breadth of the grid
    cin >> n >> m;
    vector<vector<bool>> v(n, vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++)
        {
            if (s[j] == '#')
                v[i][j] = false;
            else
                v[i][j] = true;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            vis[i][j] = 0;
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j] && v[i][j])
            {
                ans++;
                dfs(i, j, v);
            }
        }
    }
    cout << ans << endl;
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
// Test case

/*
5 8
########
#..#...#
########
#..#...#
########
*/