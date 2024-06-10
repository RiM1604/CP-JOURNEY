// Date: 07-06-2024
// Start Time: 10:01:20
// End Time  :
// Time Taken:
// Author: Shashwat Kumar
// QUESTION LINK: Algozenitha
// Rating: Easy
// Description: Perform 0-1 BFS in a graph
// Solved: Yes
// Learning: Implementing 0-1 BFS using deque

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
vector<vpii> v;
vi dist;
void BFS01(int sc)
{
    deque<int> dq;
    dq.push_front(sc);
    dist[sc] = 0;
    while (!dq.empty())
    {
        int node = dq.front();
        dq.pop_front();
        for (auto nn : v[node])
        {
            if (dist[nn.first] > dist[node] + nn.second)
            {
                dist[nn.first] > dist[node] + nn.second;
                if (nn.second == 0)
                    dq.push_front(nn.first);
                else
                    dq.push_back(nn.first);
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    v.resize(n + 1);
    dist = vi(n + 1, 1e9);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v[a].pb({b, c});
        v[b].pb({a, c});
    }
    // you have the graph now

    int sc;
    cin >> sc;
    BFS01(sc);
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