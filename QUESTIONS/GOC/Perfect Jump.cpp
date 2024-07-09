// Date: 09-07-2024
// Start Time: 13:29:03
// End Time  : 15:11:26
// Time Taken: 102 minutes
// Author: RiM1604
// QUESTION LINK: https://www.hackerrank.com/contests/goc-cdc-series-31/challenges
// Rating: Medium
// Description: Find the min distance to x,y if you can only go to a neighbour (a,b)if its distance is equal to d.
// Solved: Yes
// Learning: The number of right angled triangles with integer sides given a hypotenuse d is very less it is less than O(d) and close to O(1) i think.

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

int n, m, x, y, d;
vector<pair<int, int>> sq_pairs;
// vector<vector<int>> visited;
vvi dist;

bool check(int x, int y)
{
    if (x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1)
    {
        return 1;
    }
    return 0;
}
void bfs(pair<int, int> st, vvi &dist)
{
    queue<pair<int, int>> q;
    q.push(st);
    dist[st.F][st.S] = 0;
    while (!q.empty())
    {
        auto pos = q.front();
        q.pop();
        for (int k = 0; k < sq_pairs.size(); k++)
        {
            if (check(pos.F + sq_pairs[k].F, pos.S + sq_pairs[k].S))
            {
                if (dist[pos.F + sq_pairs[k].F][pos.S + sq_pairs[k].S] > dist[pos.F][pos.S] + 1)
                {
                    dist[pos.F + sq_pairs[k].F][pos.S + sq_pairs[k].S] = dist[pos.F][pos.S] + 1;
                    q.push({pos.F + sq_pairs[k].F, pos.S + sq_pairs[k].S});
                }
            }
        }
    }
};

void solve()
{
    cin >> n >> m >> x >> y >> d;
    // visited.clear();
    dist.clear();
    sq_pairs.clear();
    // visited = vvi(n + 2, vi(m + 2, 0));
    for (int x = 0; x <= d; x++)
    {
        for (int y = 0; y <= d; y++)
        {
            if (x * x + y * y == d * d)
            {
                sq_pairs.pb({x, y});
                sq_pairs.pb({x, -y});
                sq_pairs.pb({-x, y});
                sq_pairs.pb({-x, -y});
            }
        }
    }
    // for (int i = 0; i < sq_pairs.size(); i++)
    // {
    //     cout << sq_pairs[i].F << "," << sq_pairs[i].S<<" ";
    // }
    // cout << endl;
    dist = vvi(n + 2, vi(m + 2, INFF));
    pair<int, int> st = {0, 0};
    bfs(st, dist);
    if (dist[x][y] == INFF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dist[x][y] << endl;
    }
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