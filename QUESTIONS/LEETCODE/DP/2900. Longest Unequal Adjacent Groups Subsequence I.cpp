// Date: 09-06-2024
// Start Time: 11:05:29
// End Time  : 11:40:29
// Time Taken: 35 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/description/
// Rating: Medium
// Description: Find the longest alternating subsequence and print it
// Solved: Yes
// Learning: Keeping a parent array pointing to the parent of an element

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
vpii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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

int n;
int previous[105];
int dp[105];
int rec(int idx, vi &g)
{
    // longest alternating subsequence ending at index n-1
    if (idx < 0)
        return 0;
    int ans = 1;
    if (dp[idx] != -1)
        return dp[idx];
    for (int i = 0; i < idx; i++)
    {
        if (g[i] != g[idx])
        {
            int temp = rec(i, g);
            if (1 + temp > ans)
            {
                ans = temp + 1;
                previous[idx] = i;
            }
        }
    }
    debug(idx, ans);
    return dp[idx] = ans;
}

vector<string> getLongestSubsequence(vector<string> &v, vector<int> &g)
{
    vector<string> res;
    int idx = -1;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (rec(i, g) > ans)
        {
            ans = rec(i, g);
            idx = i;
        }
    }
    while (idx != -1)
    {
        debug(idx);
        cout << v[idx] << " ";
        res.pb(v[idx]);
        idx = previous[idx];
    }
    reverse(res.begin(), res.end());
    return res;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    memset(previous, -1, sizeof(previous));
    cin >> n;
    vector<string> s(n), res;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    vector<int> g(n);
    for (int i = 0; i < n; i++)
        cin >> g[i];
    res = getLongestSubsequence(s, g);
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