// Date: 08-07-2024
// Start Time: 20:57:49
// End Time  : 21:43:56
// Time Taken: 46 minutes
// Author: RiM1604
// QUESTION LINK: https://codeforces.com/contest/1857/problem/D
// Rating: Easy
// Description: Find the strong vertices i.e vertices which have path to all other vertices
// Solved: Yes
// Learning: lambda in c++ [&b](int x, int y)-> bool{return b[x]<b[y]} ;

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
    vi a = vi(n + 1, 0);
    vi b = vi(n + 1, 0);
    vector<pair<int, int>> subbed = vector<pair<int, int>>(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vi indexes = vi(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        indexes[i] = i;
        b[i] = a[i] - b[i];
    }
    sort(indexes.begin() + 1, indexes.end(), [&b](int x, int y) -> bool
         { return b[x] < b[y]; });

    int count_new = 0;
    vi ans_new;
    for (int i = 1; i <= n; i++)
    {
        if (b[indexes[i]] == b[indexes[n]])
        {
            ans_new.pb(indexes[i]);
            count_new += 1;
        }
    }
    cout << count_new << endl;
    for (auto v : ans_new)
    {
        cout << v << " ";
    }
    cout << endl;

    // for (int i = 1; i <= n;i++){
    //     subbed[i] = {a[i] - b[i], i};
    // }
    // sort(subbed.begin() + 1, subbed.end());
    // int last_val = subbed[n].F;
    // vi ans;
    // int count = 0;
    // for (int i = 1; i <= n; i++)
    // {
    //     if(subbed[i].F==last_val){
    //         ans.pb(subbed[i].S);
    //         count += 1;
    //     }
    // }
    // cout << count << endl;

    // sort(ans.begin(), ans.end());
    // for(auto v: ans){
    //     cout << v << " ";
    // }
    // cout << endl;
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