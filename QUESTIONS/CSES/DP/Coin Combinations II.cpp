// Date: 28-05-2024
// Start Time: 21:38:10
// End Time  : 22:08:54
// Time Taken: 30 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1636
// Rating: Medium
// Description: ordered number of ways to achive a sum of x
// Solved: NO
// Learning: how to take care of ordered set printing

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif
/*********************************************Definition*************************************************/
#define endl '\n'
#define F(type, i, s, n, step) for (type i = s; (step) > 0 ? i < (n) : i > (n); i += (step))
#define FN(type, i, s, n, step) for (type i = s; (step) > 0 ? i <= (n) : i >= (n); i += (step))
#define pb push_back
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, string> pss;
typedef pair<char, int> pci;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<ll> vl;
typedef vector<vl> vvl;
/******************************************Global Variables**********************************************/
const ll MAXM = 1e5;
const ll MAXV = 1e6;
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
int mod = 1e9 + 7;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double EPS = 1e-9;
double PI = acos(-1);
vl factors[MAXM + 5];
/*********************************************Utility Functions******************************************/
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

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

/*********************************************Main Function***********************************************/
int dp[105][1000005];
void solve()
{
    memset(dp, 0, sizeof(dp));
    int n, x;
    cin >> n >> x;
    vi v(n);
    for (auto &e : v)
        cin >> e;
    sort(v.begin(), v.end());
    dp[0][0] = 1;
    // dp of i,j give me the number of ways to achive sum = i using the first j coins
    for (int j = 1; j <= n; j++)
    {
        for (int sum = 0; sum <= x; sum++)
        {
            if (sum >= v[j - 1])
            {
                // this case considers that we are using v[j-1] to achive the sum = x
                dp[j][sum] = (dp[j][sum] + dp[j][sum - v[j - 1]]) % mod;
            }
            // if we are not using v[j -1] then we try to achive the sum using the first j - 1 coins
            dp[j][sum] = (dp[j][sum] + dp[j - 1][sum]) % mod;
        }
    }
    cout << dp[n][x];
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

// Checksum: 0ed9851d88310b24cef09eb311d9e8e1f5c735c995d72703ea05ffcc4ec80749
