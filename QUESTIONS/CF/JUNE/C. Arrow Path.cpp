// Date: 10-06-2024
// Start Time: 23:19:31
// End Time  : 23:42:49
// Time Taken: 23 minutes
// Author: RiM1604
// QUESTION LINK:
// Rating: 1300 or Easy
// Description: CF problem
// Solved: Yes
// Learning: Should have observed that even parity only have the choice whereas odd parity always shift according to the cell direction.

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
vector<vector<char>> grid;
vvi visited;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n;
int check(int i, int j)
{
    if (i > 0 && i <= 2 && j > 0 && j <= n)
    {
        return 1;
    }
    return 0;
}

void dfs(pair<int, int> node)
{
    visited[node.first][node.second] = 1;
    for (int k = 0; k < 4; k++)
    {
        if (check(node.first + dx[k], node.second + dy[k]))
        {
            if (!visited[node.first + dx[k]][node.second + dy[k]])
            {
                int child_x = node.first + dx[k];
                int child_y = node.second + dy[k];
                visited[child_x][child_y] = 1;
                if (grid[child_x][child_y] == '>')
                {
                    dfs({child_x, child_y + 1});
                }
                else if (grid[child_x][child_y] == '<')
                {
                    dfs({child_x, child_y - 1});
                }
            }
        }
    }
}

void solve()
{
    cin >> n;
    grid = vector<vector<char>>(3, vector<char>(n + 1));
    visited = vvi(3, vi(n + 1, 0));
    for (int i = 1; i <= 2; i++)
    {
        for (int j = 1; i <= n; j++)
        {
            char c;
            cin >> c;
            grid[i][j] = c;
        }
    }
    pair<int, int> st = {1, 1};
    dfs(st);
    if (visited[2][n])
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
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