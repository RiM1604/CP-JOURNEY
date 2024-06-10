// Date: 05-06-2024
// Start Time: 15:31:32
// End Time  : 15:54:03
// Time Taken: 22 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1193
// Rating: Medium
// Description: Find the shortest distance from the start cell to end cell
// Solved: Yes
// Learning: How to print the path in a grid

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

#define F first
#define S second
vector<pair<int, char>> d = {{0, 'D'}, {1, 'U'}, {2, 'R'}, {3, 'L'}};
vpii dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
pii st, en;

vvi dist(1005, vi(1005, 1e9));
vector<vector<pair<pii, char>>> parent(1005, vector<pair<pii, char>>(1005));

bool check(int x, int y, vector<vector<char>> &v)
{
    return (x >= 0 && x < n && y >= 0 && y < m && v[x][y] != '#');
}

void print_path(pii node)
{
    if (parent[node.F][node.S].F == make_pair(-1, -1))
        return;
    print_path(parent[node.F][node.S].F);
    cout << parent[node.F][node.S].S;
}
void bfs(vector<vector<char>> &v)
{
    queue<pii> q;
    q.push(st);
    dist[st.F][st.S] = 0;
    parent[st.F][st.S] = {{-1, -1}, 'X'};

    while (!q.empty())
    {
        pii node = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            // traverse all the neighbours which are valid
            if (check(node.F + dir[i].F, node.S + dir[i].S, v) && dist[node.F + dir[i].F][node.S + dir[i].S] > dist[node.F][node.S] + 1)
            {
                parent[node.F + dir[i].F][node.S + dir[i].S] = {node, d[i].S};
                dist[node.F + dir[i].F][node.S + dir[i].S] = dist[node.F][node.S] + 1;
                q.push({node.F + dir[i].F, node.S + dir[i].S});
            }
        }
    }
    int distance = dist[en.F][en.S];
    if (distance > 1e6)
    {
        cout << "NO";
        return;
    }
    cout << "YES" << endl;
    cout << distance << endl;
    print_path(en);
}

void solve()
{
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 'A')
                st = {i, j};
            else if (v[i][j] == 'B')
                en = {i, j};
        }
    }

    bfs(v);
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