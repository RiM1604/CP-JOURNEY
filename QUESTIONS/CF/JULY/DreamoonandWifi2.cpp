// Date: 16-07-2024
// Start Time: 12:48:18
// End Time  : 13:03:02
// Time Taken: 14 minute
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/476/problem/B
// Rating: 1300
// Description: Find the probability such that s2 instructions end in the final pos expected by s1.
// Solved: Yes
// Learning: In using bitmask dp use it when it is better to store previous inputs taken or it can be solved by only storing the previous taken inputs.

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

string s1, s2;
int n;
int dp[11][1025];
int final_pos = 0;
int rec(int i, int bitmask)
{
    if (i == n)
    {
        int pos = 0;
        int step_ahead = __builtin_popcount(bitmask);
        int step_back = n - step_ahead;
        pos = step_ahead - step_back;
        if (pos == final_pos)
        {
            return 1;
        }
        return 0;
    }
    if (dp[i][bitmask] != -1)
    {
        return dp[i][bitmask];
    }
    int ans = 0;
    if (s2[i] == '+')
    {
        ans = rec(i + 1, bitmask | 1 << n - 1 - i);
    }
    else if (s2[i] == '-')
    {
        ans = rec(i + 1, bitmask);
    }
    else if (s2[i] == '?')
    {
        ans += rec(i + 1, bitmask) + rec(i + 1, bitmask | 1 << n - 1 - i);
    }
    return dp[i][bitmask] = ans;
}

void solve()
{
    cin >> s1 >> s2;
    n = s1.size();
    int count = 0;
    memset(dp, -1, sizeof(dp));
    for (auto i : s1)
    {
        if (i == '+')
            final_pos++;
        if (i == '-')
            final_pos--;
    }
    // cout << final_pos << endl;
    for (auto i : s2)
    {
        if (i == '?')
            count++;
    }
    long double ans = rec(0, 0);
    ans = ans / pow(2, count);
    cout << setprecision(12) << fixed;
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