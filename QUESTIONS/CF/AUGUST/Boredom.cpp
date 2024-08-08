// Date: 07-08-2024
// Start Time: 16:47:54
// End Time  : 16:59:46
// Time Taken: 11 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/problemset/problem/455/A
// Rating: Med
// Description: Find max sum possible given an arr a[] where choose ai and remove all occurences ai,ai-1,ai+1 and add the score of ai.
// Solved: Yes
// Learning: Was not so obvious that this was a dp problem could have gotten a hint looking at the constraints of ai.

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
#define int long long
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

vector<int> dp;
map<int, int> mp;
int max_val = INT_MIN;
int rec(int a)
{
    if (a > max_val)
    {
        return 0;
    }
    if (dp[a] != -1)
    {
        return dp[a];
    }
    int ans = INT_MIN;
    if (mp[a] == 0)
    {
        ans = rec(a + 1);
    }
    else
    {
        ans = max(ans, mp[a] * a + rec(a + 2));
        ans = max(ans, rec(a + 1));
    }
    return dp[a] = ans;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    dp.resize(100001, -1);
    for (auto &i : a)
    {
        cin >> i;
        max_val = max(max_val, i);
        mp[i]++;
    }

    int ans = rec(1);
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