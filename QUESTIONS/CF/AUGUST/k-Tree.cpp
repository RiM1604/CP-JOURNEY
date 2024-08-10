// Date: 10-08-2024
// Start Time: 16:50:15
// End Time  : 17:04:13
// Time Taken: 13 minutes
// Author: RiM1604
// QUESTION LINK:
// Rating:
// Description:
// Solved: Yes
// Learning: Observed that the computation of find the number of possible roots was overlapping so applied dp and used 0 or 1 to indicate whether edge of length atleast d was taken or not.

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
    int n, k, d;
    cin >> n >> k >> d;
    vector<vector<int>> dp = vector<vector<int>>(n + 1, vector<int>(2, 0));
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            if (i - j >= 0)
            {
                dp[i][0] = (dp[i][0] + dp[i - j][0]) % mod;
            }
            if (j >= d)
            {
                if (i - j >= 0)
                {
                    dp[i][1] = (dp[i][1] + dp[i - j][0]) % mod;
                }
            }
            else
            {
                if (i - j >= 0)
                {
                    dp[i][1] = (dp[i][1] + dp[i - j][1]) % mod;
                }
            }
        }
    }
    cout << dp[n][1] % mod << endl;
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