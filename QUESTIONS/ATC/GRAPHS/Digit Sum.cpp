// Date: 07-07-2024
// Start Time: 09:58:00
// End Time  : 14:00:53
// Time Taken: 242 minutes
// Author: RiM1604
// QUESTION LINK: https://atcoder.jp/contests/dp/tasks/dp_s
// Rating: Medium
// Description: Find the number of integers in between 1 and K which are divisible by D
// Solved: Yes
// Learning: Learnt to write the code for digit dp for this sum using only one right tightness. Did mistake of changing rem and passing it in the next recursion.

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

string a;
int D;
int len;
int dp[10002][2][102];

int rec(int idx, int hi, int rem)
{
    if (idx == len)
    {
        if (rem == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (dp[idx][hi][rem] == -1)
    {
        // cout << "idx" << idx << "hi" << hi << "rem" << rem << endl;
        int hiLimit = 9;
        int loLimit = 0;
        if (hi == 1)
        {
            hiLimit = a[idx] - '0';
        }
        int ans = 0;
        for (int i = loLimit; i <= hiLimit; i++)
        {
            int nhi = hi;
            if (i != a[idx] - '0')
            {
                nhi = 0;
            }
            ans = (ans + rec(idx + 1, nhi, (rem + i) % D)) % mod;
        }
        return dp[idx][hi][rem] = ans;
    }
    return dp[idx][hi][rem];
}

void solve()
{
    cin >> a >> D;
    len = a.size();
    // cout << len << endl;
    memset(dp, -1, sizeof(dp));
    // cout << a << D << endl;
    // cout << rec(0, 1, 0) << endl;
    cout << (rec(0, 1, 0) - 1 + mod) % mod << endl;
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