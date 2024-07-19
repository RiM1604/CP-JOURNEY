// Date: 18-07-2024
// Start Time: 12:34:48
// End Time  : 13:35:16
// Time Taken: 60 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1516/problem/B
// Rating: 1500
// Description: Find if its possible to make the elements in array the same but with atleast 2 remaining
// Solved: No
// Learning: Using prefix_xor like prefix_sum but here to get xor of values in i to j you do prefix_xor[j]^prefix_xor[i-1]

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

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    for (auto &i : a)
    {
        cin >> i;
    }
    int flag = 0;

    vi pre_xor = a;
    for (int i = 1; i < n; i++)
    {
        pre_xor[i] ^= pre_xor[i - 1];
    }
    if (pre_xor[n - 1] == 0)
    {
        flag = 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (pre_xor[i] == (pre_xor[j] ^ pre_xor[i]) && pre_xor[i] == (pre_xor[n - 1] ^ pre_xor[j]))
            {
                flag = 1;
            }
        }
    }

    cout << ((flag == 1) ? "YES" : "NO") << endl;
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