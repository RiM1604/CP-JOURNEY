// Date: 10-06-2024
// Start Time: 08:55:40
// End Time  : 09:54:48
// Time Taken: 59 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://codeforces.com/problemset/problem/1948/C
// Rating: 1300
// Description: Find a path between 2 cells
// Solved: Yes
// Learning: Identify that the different nodes have different types of edges possible in the grid

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
const int mod = 1e9 + 7;
const int INF = 1e9 + 5;
const long long INFF = 1000000000000000005LL;
const double EPS = 1e-9;
const double PI = acos(-1);
vector<long> factors[MAXM + 5];
vpii dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
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

// odd cell: those cells which have the sum of their coordintes as odd no
int n;
int vis[2][2 * MAXM + 5];
bool check(int x, int y)
{
    return (x >= 0 && x < 2 && y >= 0 && y < n);
}

bool dfs(int x, int y, vector<string> &v, int parity)
{
    vis[x][y] = 1;
    debug(x, y, parity);
    if (x == 1 && y == n - 1)
        return true;
    // the point to note is that every even node has 4 options to go and odd even node has only one option to go that is the character in the grid
    bool ans = false;
    if (parity % 2 == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            if (check(x + dir[i].first, y + dir[i].second))
            {
                if (!vis[x + dir[i].first][y + dir[i].second])
                    ans |= dfs(x + dir[i].first, y + dir[i].second, v, parity ^ 3);
                if (ans == true)
                    return true;
            }
        }
    }
    else
    {
        // go right
        if (v[x][y] == '>')
            ans |= dfs(x, y + 1, v, parity ^ 3);
        else
            ans = false;
    }
    return ans;
}

void solve()
{
    memset(vis, 0, sizeof(vis));
    cin >> n;
    vector<string> v(2);
    for (int i = 0; i < 2; i++)
    {
        cin >> v[i];
    }
    // now call dfs
    // cout << dfs(0, 0, v, 2) << endl;
    if (dfs(0, 0, v, 2))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //         cout << vis[i][j] << " ";
    //     cout << endl;
    // }
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

/*
4
4
>><<
>>><
2
><
><
4
>>><
>><<
6
>><<><
><>>><

Case #1
1
Case #2
1
Case #3
0
Case #4
1
*/