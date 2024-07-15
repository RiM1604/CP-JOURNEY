// Date: 14-07-2024
// Start Time: 10:18:04
// End Time  : 10:46:44
// Time Taken: 28 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1741/problem/D
// Rating: Easy
// Description: Find the no of swap operations to be done to sort the leaves of the binary tree.
// Solved: Yes
// Learning: To construct a binary tree on an array use: for ith node the children are 2*i, 2*i+1. in case you want to consturct a tree with three child nodes for ith node children are 3*i,3*i+1,3*i+2.

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

void solve()
{
    int m;
    cin >> m;
    vi permutation = vi(m + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        cin >> permutation[i];
    }

    vi max_val = vi(2 * m, 0);
    vi min_val = vi(2 * m, m + 1);
    for (int i = 1; i <= m; i++)
    {
        max_val[m + i - 1] = permutation[i];
        min_val[m + i - 1] = permutation[i];
    }
    int ans = 0;
    for (int i = m - 1; i >= 1; i--)
    {
        max_val[i] = max(max_val[2 * i], max_val[2 * i + 1]);
        min_val[i] = min(min_val[2 * i], min_val[2 * i + 1]);
        if (max_val[2 * i] > min_val[2 * i + 1] && min_val[2 * i] < max_val[2 * i + 1])
        {
            ans = -1;
            break;
        }
        else if (min_val[2 * i] > max_val[2 * i + 1])
        {
            ans++;
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