// Date: 03-06-2024
// Start Time: 22:13:38
// End Time  : 00:10:23
// Time Taken: -1323 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://atcoder.jp/contests/dp/tasks/dp_e
// Rating: Hard
// Description: same as knapsack 1 but with different constraing
// Solved: No
// Learning: How to modify the dp states to solve the quesiton and also how to reframe the question

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

/**************************************************Definition*************************************************/
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
int n, w;
vpii v;
ll dp[105][MAXM + 5];
ll rec(int idx, int value_left) // returns the min weight required to achive sum = Value_left
{
    if (value_left == 0)
        return 0;
    if (idx == -1)
    {
        // it means that value_left is either negative of we have considered all elements and the total value sum was not equal to V
        // we return a large value which means that do not consider taking the item in line 90
        return 1e15;
    }
    if (dp[idx][value_left] != -1)
        return dp[idx][value_left];
    // dont take the element
    ll ans = rec(idx - 1, value_left);
    // take the element
    if (value_left - v[idx].second >= 0)
        ans = min(ans, rec(idx - 1, value_left - v[idx].second) + v[idx].first);
    return dp[idx][value_left] = ans;
}

void solve()
{
    // looking at the contrains vi <= 1000 and  N <= 100, we keep rec(idx, value_left) as dp states
    //  we reframe the question as the min weight required to get the sum of values == V and iterate over V from 1e5 to 0
    memset(dp, -1, sizeof(dp));
    cin >> n >> w;
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }
    for (int i = 1e5; i >= 0; i--)
    {
        ll temp = rec(n - 1, i);
        if (temp <= w)
        {
            cout << i;
            return;
        }
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