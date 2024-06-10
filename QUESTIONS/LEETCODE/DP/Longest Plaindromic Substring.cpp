// Date: 29-05-2024
// Start Time: 21:38:10
// End Time  : 22:08:54
// Time Taken: 30 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://leetcode.com/problems/longest-palindromic-substring/
// Rating: Hard
// Description: find the longest palindromic substring
// Solved: No
// Learning: how to iterate over substrings of a string (2nd way)

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

/*********************************************Definition*************************************************/
const ll MAXM = 1e5;
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};
int mod = 1e9 + 7;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double EPS = 1e-9;
double PI = acos(-1);
vl factors[MAXM + 5];

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

void solve()
{
    string str;
    cin >> str;
    int n = str.length();
    // preprocess the string
    string s_prime;
    int dp[1005][1005];
    memset(dp, 0, sizeof(dp));

    vector<int> ans(2);
    // initialisation dp[i][j] tells you whether the substring starting from i and ending at j is a substring
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 1;
        if (i + 1 < n)
        {
            if (str[i] == str[i + 1])
            {
                dp[i][i + 1] = 2;
                ans = {i, i + 1};
            }
        }
    }
    // this is a genius move i iterate over all the substrings of lenth 3 then 4 and so on and if i find a palindrome then i update my ans bounds this helps me because i do need to find the bounds again after the dp array has been filled
    for (int diff = 2; diff < n; diff++)
    {
        for (int i = 0; i < n - diff; i++)
        {
            int j = i + diff;
            if (str[i] == str[j] && dp[i + 1][j - 1])
            {
                dp[i][j] = 1;
                ans = {i, j};
            }
        }
    }
    int i = ans[0];
    int j = ans[1];
    // cout << i << " " << j;
    cout << str.substr(i, j - i + 1);
}

signed main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    int t = 1;
    cin >> t;
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
// Checksum: 8b9938d1eb0f8bdf2603802d6deedaad952b399564d7c9cf0c24ecbc9a3bd618
