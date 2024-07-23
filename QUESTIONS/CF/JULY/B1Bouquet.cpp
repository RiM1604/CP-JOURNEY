// Date: 23-07-2024
// Start Time: 20:30:39
// End Time  : 21:19:56
// Time Taken: 49 minutes
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
    /* Your code here */
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i : a)
    {
        cin >> i;
    }
    sort(a.begin(), a.end());
    // for (auto v : a)
    // {
    //     cout << v << " ";
    // }
    // cout << endl;
    vector<int> prefix_a = a;
    // reverse(prefix_a.begin(), prefix_a.end());
    for (int i = 1; i < prefix_a.size(); i++)
    {
        prefix_a[i] += prefix_a[i - 1];
        // cout << prefix_a[i] << " ";
    }
    // cout << endl;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int l1_temp = upper_bound(a.begin(), a.end(), min(a[n - 1], a[i] + 1)) - a.begin() - 1;
        // cout << "i" << i << endl;
        // cout << "l1" << l1_temp << endl;
        int temp_cost = m;
        temp_cost += (i == 0) ? 0 : prefix_a[i - 1];
        int l2_temp = upper_bound(prefix_a.begin(), prefix_a.end(), min(temp_cost, prefix_a[n - 1])) - prefix_a.begin();
        l2_temp--;
        // cout << "l2" << l2_temp << endl;
        int temp = prefix_a[min(l2_temp, l1_temp)];
        if (i > 0)
        {
            temp -= prefix_a[i - 1];
        }
        // cout << "temp" << temp << endl;
        ans = max(ans, temp);
    }

    // int last = a[n - 1];
    // last -= 1;
    // cout << "last" << last << endl;
    // int limit = lower_bound(a.begin(), a.end(), last)-a.begin();
    // // limit -= 1;
    // cout << "l" << limit << endl;
    // cout << endl;
    // int sum_limit = lower_bound(prefix_a.begin(), prefix_a.end(), min(m,prefix_a[n-1])) - prefix_a.begin();
    // cout << "sL" << sum_limit << endl;

    // cout << prefix_a[min(sum_limit, n-1-limit)] << endl;
    cout << ans << endl;
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