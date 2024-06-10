// Date: 30-05-2024
// Start Time: 21:38:10
// End Time  : 22:08:54
// Time Taken: 30 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://www.codechef.com/problems/SUMMODE
// Rating: Hard
// Description: Count the number of substrings with equal no of 0's and 1's
// Solved: Obviously Not
// Learning: Solving the question in O(N)

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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cntl = 0, cnt0 = 0, cntr = 0;
    ll ans = (1LL * n * (n + 1)) / 2;
    // now i need to count the substrings with equal number of 1's and 0's
    vi pre(n);
    // this frequency map contains the number of times a give sum has appeared and how is it helpful?
    /*
    look at it as follows
    each time you get a sum = 0 it means that there is a substring ending at index i where the number
    of 1 is equal to the number of 0s
    now look at it more generally
    each time you encounter a sum which you have seen previously it means by some occurances of 1's and -1's
    you reached the same sum which means that there is a substring between the two indices where the
    sum was same such that it has equal number of 1's and 0's as their contribution to the sum
    is 0 because we have reached the same sum
    */
    map<int, int> freq_sum;
    freq_sum[0]++;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
            pre[i] = 1;
        else
            pre[i] = -1;
        if (i > 0)
            pre[i] += pre[i - 1];
        ans += freq_sum[pre[i]]++;
    }
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
// Checksum: f916d03272e52e9ab78ce50e07e69d01a6c498017d22b9a81e47616bcc7e2a3e
