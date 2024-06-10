// Date: 03-06-2024
// Start Time: 21:57:49
// End Time  : 22:11:21
// Time Taken: 13 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://atcoder.jp/contests/dp/tasks/dp_d
// Rating: Easy
// Description: Knapsack 1
// Solved: Yes
// Learning: Form 1

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
/*********************************************Main Function***********************************************/

int n, w;
vpii v(n);
ll dp[105][MAXM + 5];
ll rec(int i, int c)
{
    // if no items used or no capacity left return 0 profit
    if (i == -1 || c == 0)
        return 0;
    // if capacity is negative no item can be included
    if (c < 0)
        return 0;
    // option to choose the element in the set
    if (dp[i][c] != -1)
        return dp[i][c];
    if (v[i].first <= c)
    {
        // i can choose the element
        return dp[i][c] = max(v[i].second + rec(i - 1, c - v[i].first), rec(i - 1, c));
    }
    else
    {
        // no option but to not include the element
        return dp[i][c] = rec(i - 1, c);
    }
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    cin >> n >> w;
    v.resize(n);
    // weight and value
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }
    ll ans = rec(n - 1, w);
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