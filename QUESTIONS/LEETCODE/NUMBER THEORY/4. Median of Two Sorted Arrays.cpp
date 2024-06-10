// Date: 09-06-2024
// Start Time: 13:14:52
// End Time  : 13:53:29
// Time Taken: 38 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// Rating: Hard
// Description: Find the median of 2 sorted arrays
// Solved: No
// Learning: Binary search is a great tool

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
// #define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vpii;

/**************************************************Global Variables*************************************************/
const ll MAXM = 1e5;
const int mod = 1e9 + 7;
const int INF = 1e9 + 5;
const long long INFF = 1000000000000000005LL;
const double EPS = 1e-9;
const double PI = acos(-1);
vector<long> factors[MAXM + 5];
vpii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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
int n, m;

double findMedianSortedArrays(vector<int> &a, vector<int> &b)
{
    // basically we need equal number of elements in our left and right partition of the merged sorted array
    int n1 = a.size(), n2 = b.size();
    if (n1 > n2)
    {
        return findMedianSortedArrays(b, a);
    }
    // we run the bin_serach on smaller array
    int lo = 0;
    int hi = n1 + 1;
    double ans;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        // i am choosing elements in the smaller array upto index mid (inclusive)
        int idx_y = (n + m) / 2 - mid;
        int max_left = max(a[mid], b[idx_y]);
        int min_right = min(a[mid + 1], b[idx_y + 1]);
        debug(lo, hi, mid, idx_y, a[mid], b[idx_y]);
        if (max_left < min_right)
        {
            if ((n + m) % 2 == 0)
            {
                ans = (double)(max_left + min_right) / 2;
            }
            else
            {
                ans = min_right;
            }
            break;
        }
        if (b[idx_y + 1] < a[mid])
        {
            hi = mid - 1;
        }
        else if (b[idx_y] > a[mid + 1])
        {
            lo = mid + 1;
        }
    }
    return ans;
}

void solve()
{
    cin >> n >> m;
    vi a(n + 2, 1e9), b(m + 2, 1e9);
    a[0] = INT_MIN;
    b[0] = INT_MIN;
    for (int i = 1; i < n + 1; i++)
        cin >> a[i];
    for (int i = 1; i < m + 1; i++)
        cin >> b[i];
    cout << findMedianSortedArrays(a, b);
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