// Date: 07-08-2024
// Start Time: 15:08:22
// End Time  :
// Time Taken:
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

int query(int b)
{
    int a = 1;
    cout << "?" << " " << a << " " << b << endl;
    int res;
    cin >> res;
    if (res > b)
    {
        return 0;
    }
    return 1;
}

void solve()
{
    int low = 2;
    int high = 999;
    int ans = 2;
    while (low <= high)
    {
        int mid = (low + high) << 1;
        if (query(mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << "!" << " " << ans + 1 << endl;
    cout.flush();
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