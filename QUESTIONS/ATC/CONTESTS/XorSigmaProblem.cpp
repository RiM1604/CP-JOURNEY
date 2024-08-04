// Date: 04-08-2024
// Start Time: 00:20:08
// End Time  : 11:45:01
// Time Taken: 684 minutes
// Author: RiM1604
// QUESTION LINK: https://atcoder.jp/contests/abc365/tasks/abc365_e
// Rating: Medium
// Description: Find the sum of xor of all subsets of the array
// Solved: No
// Learning: using prefix xor to get a1, a1^a2, a1^a2^a3, a1^a2^a3^a4 from this we keep a count of the ones and zeroes for all the 30 bits and we do all combinations of the

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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        // cout << a[i];
    }
    vector<int> preXor = a;
    preXor[0] = 0;
    vector<int> onecount(31, 0), zerocount(31, 0);

    for (int i = 1; i <= n; i++)
    {
        preXor[i] ^= preXor[i - 1];
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if ((preXor[i] & (1 << j)))
            {
                onecount[j]++;
            }
            else
            {
                zerocount[j]++;
            }
        }
    }
    int sum = 0;
    for (int j = 0; j < 30; j++)
    {
        sum += (1 << j) * (onecount[j] * zerocount[j]);
    }
    for (auto i : a)
    {
        sum -= i;
    }
    cout << sum << endl;
}

signed main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);

    int t = 1;
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