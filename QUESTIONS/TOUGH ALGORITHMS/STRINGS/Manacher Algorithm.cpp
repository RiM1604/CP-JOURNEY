// Date: 29-05-2024
// Start Time: 21:38:10
// End Time  : 22:08:54
// Time Taken: 30 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://leetcode.com/problems/longest-palindromic-substring/description/
// Rating: Hard
// Description: find the longest palindromic substring
// Solved: No
// Learning: how to find the longest palindromic substing in O(N) using Manacher's algorithm

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
// Same idea as Manachers Algorithm but in O(N^2) time to get the hint of what is actually happening in the code
// int process(string &s)
// {
//     int n = s.length();
//     vector<int> v(n, 0);
//     // i will mainitain an array containig the longest palindromic substring with center at index i
//     // O(N^2)
//     int ans = 0;
//     for (int i = 0; i < n; i++)
//     {
//         int l = i - 1, r = i + 1;
//         while (l >= 0 && r < n && s[l] == s[r])
//         {
//             l--;
//             r++;
//         }
//         v[i] += (r - i - 1);
//         cout << v[i] << " ";
//         ans = max(ans, v[i]);
//     }
//     return ans;
// }

string process(string &s)
{
    string s_prime;
    s_prime += '#';
    for (int i = 0; i < s.length(); i++)
    {
        s_prime += s[i];
        s_prime += '#';
    }
    int n = s_prime.length();
    // vector v stores the length of radii of plaindromes with character at index i as center
    vector<int> v(n, 0);
    // i will mainitain an array containig the longest palindromic substring with center at index i
    string ans = "";
    // we maintain a bounding box kind of sliding window (see code)
    int l = 1, r = 1;
    for (int i = 0; i < n; i++)
    {
        // here r and l are exclusive which means that we consider the substring between [l+1] and [r-1]
        int mirror = l + r - i;
        // for each i as center we calculate the max length of palindrome
        // we dont need to start calulating the lenth of palindrome from size = 1 rather using the value of the mirror element or the distance between i and bounding box right boundary we set the initial size of the palindromic substring
        if (r - i > 0)
        {
            v[i] = min(r - i, v[mirror]);
        }
        // now we keep on increasing the size of palindrome radii
        while (i + v[i] < n && i - v[i] >= 0 && s_prime[i + v[i]] == s_prime[i - v[i]])
        {
            v[i]++;
        }
        // moving the sliding window
        if (r < i + v[i])
        {
            l = i - v[i];
            r = i + v[i];
        }
        // now the big question is how is this code executing in O(N)
        /*
        this is because each time the while loop runs it means we found a better value of bounding box right end and right end can at max increase in O(N) times because the length of the sting in N and we then in line number 116 we would take v[mirror] as v[i] and will not enter the while loop again because we cannot have a palindrome of length more than n

        Here are 2 video links for better explanation
        Tushar Roy
        https://youtu.be/V-sEwsca1ak?si=EV9C17j2feNzWrrZ
        Algo Zenith - Vivek Gupta
        https://www.youtube.com/watch?v=ei7qghJEj4Y
        */
        cout << v[i] << " ";
    }
    int curr_idx = -1, max_len = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] > max_len)
        {
            max_len = v[i];
            curr_idx = i;
        }
    }
    int start_idx = curr_idx - (max_len - 1);
    debug(start_idx);
    ans = s_prime.substr(start_idx, 2 * max_len - 1);
    cout << ans << endl;
    // now to print the correct original array
    start_idx /= 2;
    ans = s.substr(start_idx, max_len - 1);
    return ans;
}
void solve()
{
    string str;
    cin >> str;
    // preprocess the string

    // now find the longest palindromic substring in this string and report ans / 2;
    string ans = process(str);
    cout << ans;
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

// Checksum: dd2c422d6bb37c88f4535544c251f9add8fa66ba4d8e075e6dd2e1e6d024e6de
