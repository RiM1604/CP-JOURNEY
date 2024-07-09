// Date: 09-07-2024
// Start Time: 00:18:12
// End Time  : 11:59:48
// Time Taken: 701 minutes
// Author: RiM1604
// QUESTION LINK: https://www.hackerrank.com/contests/goc-cdc-series-31/challenges/shashwat-and-grid/problem
// Rating: Easy to Medium
// Description: Find the maximum no of leaves you can collect in x time without stepping on minesweepers.
// Solved: Yes
// Learning: Simple dfs approach but slight changes. Using marked[] to keep track if the leaf in the current node is taken or not and setting marked[]=0 before returning the ans if we collect the leaf in the current node else dont because it will override the previous choice regarding that node. and setting the ans = INT_MIN if the choices ahead are not possible.

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

vvi grid;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m, x;
bool check(int x, int y)
{
    if (x >= 0 && x < n && y >= 0 && y < m && (grid[x][y] == 1))
    {
        return true;
    }
    return false;
}
vvi marked;
vvi par;
int dp[101][101][13];
int dfs(pair<int, int> node, int time_left)
{
    // cout << "node.F" << node.F << "node.S" << node.S << endl;
    if (dp[node.F][node.S][time_left] != -1)
    {
        // cout << "alreadythere" << node.F << node.S << endl;
        return dp[node.F][node.S][time_left];
    }
    if (time_left == 0)
    {
        // cout << "ending" << node.F << node.S << endl;
        if (node.F == 0 && node.S == 0)
        {
            return 0;
        }
        else
        {
            return INT_MIN;
        }
    }
    int ans;
    if (!marked[node.F][node.S])
    {
        ans = 1;
        marked[node.F][node.S] = 1;
    }
    else
    {
        ans = 0;
    }
    int temp = INT_MIN;
    // cout << "x" << node.F << "y" << node.S << endl;
    temp = dfs({node.F, node.S}, time_left - 1);
    for (int k = 0; k < 4; k++)
    {
        // cout << "k" << k << endl;
        if (check(node.F + dx[k], node.S + dy[k]))
        {
            // cout << "yes" << endl;
            // if(!marked[node.F+dx[k]][node.S+dy[k]]){
            //     ans += 1;
            // }
            temp = max(temp, dfs({node.F + dx[k], node.S + dy[k]}, time_left - 1));
        }
    }
    if (ans == 1)
    {
        marked[node.F][node.S] = 0;
    }
    if (temp != INT_MIN)
    {
        ans += temp;
    }
    else
    {
        ans = INT_MIN;
    }
    // cout << "pathend" << endl;

    // cout << node.F << "," << node.S << "ans" << ans << endl;
    return ans;
}

void solve()
{
    cin >> n >> m >> x;

    grid.resize(n, vi(m, 0));
    marked = vvi(n, vi(m, 0));
    par = vvi(n, vi(m, -1));
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        string temp;
        cin >> temp;
        for (int j = 0; j < m; j++)
        {
            grid[i][j] = temp[j] - '0';
            // cout << grid[i][j];
        }
        // cout << endl;
        // cout << endl;
    }
    int ans = dfs({0, 0}, x);
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