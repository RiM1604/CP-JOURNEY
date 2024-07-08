// Date: 08-07-2024
// Start Time: 11:10:41
// End Time  : 14:32:30
// Time Taken: 201 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1983/problem/C
// Rating: Easy to Medium
// Description: Find ranges la,ra,lb,rb,lc,rc from given three arrays a,b,c which have sum >= upper_ceil(tot/3) in O(n);
// Solved: Yes
// Learning: Did a very brute force application and made mistakes in changing the starting points and the arrays to calculate in

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

int tot = 0;
vi prefix_a;
vi prefix_b;
vi prefix_c;
int check(int i, int arr, int arr_start)
{
    int temp;
    if (arr == 0)
    {
        // cout << "i" << i << endl;
        // cout << prefix_a[i] << endl;
        temp = prefix_a[i] - ((arr_start == 0) ? 0 : prefix_a[arr_start - 1]);
        // cout << "temp" << temp << endl;
    }
    else if (arr == 1)
    {
        // cout << "i1," << i << endl;
        temp = prefix_b[i] - ((arr_start == 0) ? 0 : prefix_b[arr_start - 1]);
        // cout << "temp1," << temp << endl;
    }
    else if (arr = 2)
    {
        // cout << "i2," << i << endl;
        temp = prefix_c[i] - ((arr_start == 0) ? 0 : prefix_c[arr_start - 1]);
        // cout << "temp2," << temp << endl;
    }
    int upper_ceil = ((tot + 2) / 3);
    // cout << "ceil" << upper_ceil << endl;
    if (temp >= upper_ceil)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int binsearch(int low, int high, int n, int arr)
{

    int ans = n;
    int temp;
    temp = arr;
    int arr_start = low;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        // cout << "mid" << mid << endl;
        if (check(mid, temp, arr_start))
        {
            high = mid - 1;
            ans = mid;
            // cout << "ans" << ans << endl;
        }
        else
        {
            low = mid + 1;
        }
    }
    // cout << "returnans" << ans << endl;
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    vi a, b, c;
    prefix_a.clear();
    prefix_b.clear();
    prefix_c.clear();
    tot = 0;
    a = vi(n + 1, 0);
    b = vi(n + 1, 0);
    c = vi(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        tot += a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    prefix_a = a;
    prefix_b = b;
    prefix_c = c;
    for (int i = 1; i < n; i++)
    {
        prefix_a[i] += prefix_a[i - 1];
        prefix_b[i] += prefix_b[i - 1];
        prefix_c[i] += prefix_c[i - 1];
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << prefix_a[i] << " ";
    // }
    // cout << endl;

    // case 1 starting with a
    vector<pair<int, int>> ans_a;
    vector<pair<int, int>> ans_b;
    vector<pair<int, int>> ans_c;

    for (int i = 1; i <= 3; i++)
    {
        if (i == 1)
        {
            // cout << n - 1 << endl;
            int ans_a_ind = binsearch(0, n - 1, n, 0);
            // cout << "ans_a_ind" << ans_a_ind << endl;
            if (ans_a_ind == n)
            {
                ans_a.pb({-1, -1});
            }
            else
            {
                ans_a.pb({0, ans_a_ind});
                ans_a.pb({0, ans_a_ind});
            }
            int ans_b_ind = binsearch(ans_a_ind + 1, n - 1, n, 1);
            // cout << "ans_b_ind" << ans_b_ind << endl;
            if (ans_b_ind == n)
            {
                ans_b.pb({-1, -1});
            }
            else
            {
                ans_b.pb({ans_a_ind + 1, ans_b_ind});
            }
            int ans_c_ind = binsearch(ans_b_ind + 1, n - 1, n, 2);
            // cout << "ans_c_ind" << ans_c_ind << endl;
            if (ans_c_ind == n)
            {
                ans_c.pb({-1, -1});
            }
            else
            {
                ans_c.pb({ans_b_ind + 1, ans_c_ind});
            }
            // case 1.2
            ans_c_ind = binsearch(ans_a_ind + 1, n - 1, n, 2);
            // cout << "ans_c_ind" << ans_c_ind << endl;
            if (ans_c_ind == n)
            {
                ans_c.pb({-1, -1});
            }
            else
            {
                ans_c.pb({ans_a_ind + 1, ans_c_ind});
            }

            ans_b_ind = binsearch(ans_c_ind + 1, n - 1, n, 1);
            // cout << "ans_b_ind" << ans_b_ind << endl;
            if (ans_b_ind == n)
            {
                ans_b.pb({-1, -1});
            }
            else
            {
                ans_b.pb({ans_c_ind + 1, ans_b_ind});
            }
        }
        else if (i == 2)
        {
            // cout << n - 1 << endl;
            int ans_b_ind = binsearch(0, n - 1, n, 1);
            // cout << "ans_b_ind" << ans_b_ind << endl;
            if (ans_b_ind == n)
            {
                ans_b.pb({-1, -1});
            }
            else
            {
                ans_b.pb({0, ans_b_ind});
                ans_b.pb({0, ans_b_ind});
            }
            //
            int ans_a_ind = binsearch(ans_b_ind + 1, n - 1, n, 0);
            // cout << "ans_a_ind" << ans_a_ind << endl;

            if (ans_a_ind == n)
            {
                ans_a.pb({-1, -1});
            }
            else
            {
                ans_a.pb({ans_b_ind + 1, ans_a_ind});
            }
            int ans_c_ind = binsearch(ans_a_ind + 1, n - 1, n, 2);
            // cout << "ans_c_ind" << ans_c_ind << endl;

            if (ans_c_ind == n)
            {
                ans_c.pb({-1, -1});
            }
            else
            {
                ans_c.pb({ans_a_ind + 1, ans_c_ind});
            }
            // case 1.2
            ans_c_ind = binsearch(ans_b_ind + 1, n - 1, n, 2);
            // cout << "ans_c_ind" << ans_c_ind << endl;
            if (ans_c_ind == n)
            {
                ans_c.pb({-1, -1});
            }
            else
            {
                ans_c.pb({ans_b_ind + 1, ans_c_ind});
            }

            ans_a_ind = binsearch(ans_c_ind + 1, n - 1, n, 0);
            // cout << "ans_a_ind" << ans_a_ind << endl;
            if (ans_a_ind == n)
            {
                // cout << "no" << endl;
                ans_a.pb({-1, -1});
            }
            else
            {
                // cout << "yes" << endl;
                ans_a.pb({ans_c_ind + 1, ans_a_ind});
            }
        }
        else if (i == 3)
        {
            // cout << n - 1 << endl;
            int ans_c_ind = binsearch(0, n - 1, n, 2);
            if (ans_c_ind == n)
            {
                ans_c.pb({-1, -1});
            }
            else
            {
                ans_c.pb({0, ans_c_ind});
                ans_c.pb({0, ans_c_ind});
            }
            int ans_a_ind = binsearch(ans_c_ind + 1, n - 1, n, 0);
            if (ans_a_ind == n)
            {
                ans_a.pb({-1, -1});
            }
            else
            {
                ans_a.pb({ans_c_ind + 1, ans_a_ind});
            }
            int ans_b_ind = binsearch(ans_a_ind + 1, n - 1, n, 1);
            if (ans_b_ind == n)
            {
                ans_b.pb({-1, -1});
            }
            else
            {
                ans_b.pb({ans_a_ind + 1, ans_b_ind});
            }
            // case 1.2
            ans_b_ind = binsearch(ans_c_ind + 1, n - 1, n, 1);
            if (ans_b_ind == n)
            {
                ans_b.pb({-1, -1});
            }
            else
            {
                ans_b.pb({ans_c_ind + 1, ans_b_ind});
            }

            ans_a_ind = binsearch(ans_b_ind + 1, n - 1, n, 0);
            if (ans_a_ind == n)
            {
                ans_a.pb({-1, -1});
            }
            else
            {
                ans_a.pb({ans_b_ind + 1, ans_a_ind});
            }
        }
    }
    int flag = 0;
    // cout << ans_a.size() << ans_b.size() << ans_c.size() << endl;
    for (int i = 0; i < ans_a.size(); i++)
    {
        if (ans_a[i].F == -1 || ans_b[i].F == -1 || ans_c[i].F == -1)
        {
            continue;
        }
        else
        {
            flag = 1;
            // cout << "yesi" << i << endl;
            cout << ans_a[i].F + 1 << " " << ans_a[i].S + 1 << " " << ans_b[i].F + 1 << " " << ans_b[i].S + 1 << " " << ans_c[i].F + 1 << " " << ans_c[i].S + 1 << endl;
            break;
        }
    }
    if (flag == 0)
    {
        cout << -1 << endl;
    }
    // cout << ans_a[0].F << "," << ans_a[0].S << " " << ans_b[0].F << "," << ans_b[0].S << " " << ans_c[0].F << "," << ans_c[0].S << endl;
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