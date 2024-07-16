// Date: 16-07-2024
// Start Time: 12:24:47
// End Time  : 12:43:44
// Time Taken: 18 minutes
// Author: RiM1604
// QUESTION LINK:
// Rating:
// Description:
// Solved:
// Learning:

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

int dp[11][21][21];
int n;
string s1, s2;
int rec(int i, int pos, int dest)
{

    if (i == n)
    {
        if (pos == dest)
        {
            return 1;
        }
        return 0;
    }
    if (dp[i][pos][dest] != -1)
    {
        return dp[i][pos][dest];
    }
    int ans = 0;
    if (s2[i] == '+')
    {
        ans = rec(i + 1, pos + 1, dest);
    }
    else if (s2[i] == '-')
    {
        ans = rec(i + 1, pos - 1, dest);
    }
    else if (s2[i] == '?')
    {
        ans = rec(i + 1, pos + 1, dest) + rec(i + 1, pos - 1, dest);
    }
    return dp[i][pos][dest] = ans;
}

void solve()
{
    cin >> s1 >> s2;
    n = s1.size();
    int final_pos = 0;
    int count = 0;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < s1.size(); i++)
    {
        if (s1[i] == '+')
            final_pos++;
        else
            final_pos--;

        if (s2[i] == '?')
            count++;
    }
    long double ans = rec(0, 10, final_pos + 10);
    cout << setprecision(12) << fixed;
    // cout << "2pow" << ans << endl;
    ans = ans / pow(2, count);
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