// Date: 03-06-2024
// Start Time: 21:26:41
// End Time  : 21:54:57
// Time Taken: 28 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://atcoder.jp/contests/dp/tasks/dp_c
// Rating: Easy
// Description: Form 1
// Solved: Yes
// Learning: Nothing special

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
#define pb push_back
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

/*********************************************Definition*************************************************/
const ll MAXM = 1e5;
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
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

int n;
vvi v;
int dp[MAXM + 5][3];
ll rec(int day, int last_taken)
{
    if (day < 0)
        return 0;
    if (dp[day][last_taken] != -1)
        return dp[day][last_taken];
    if (day == n - 1)
    {
        return dp[day][last_taken] = max({v[day][0] + rec(day - 1, 0), v[day][1] + rec(day - 1, 1), v[day][2] + rec(day - 1, 2)});
    }
    if (last_taken == 0)
    {
        return dp[day][last_taken] = max(v[day][1] + rec(day - 1, 1), v[day][2] + rec(day - 1, 2));
    }
    else if (last_taken == 1)
    {
        return dp[day][last_taken] = max(v[day][0] + rec(day - 1, 0), v[day][2] + rec(day - 1, 2));
    }
    else
    {
        return dp[day][last_taken] = max(v[day][0] + rec(day - 1, 0), v[day][1] + rec(day - 1, 1));
    }
}

void solve()
{
    cin >> n;
    v.resize(n, vi(3));
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
            cin >> v[i][j];
    }
    ll ans = rec(n - 1, 0);
    cout << ans;
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