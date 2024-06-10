// Date: 04-06-2024
// Start Time: 10:46:39
// End Time  : 11:50:29
// Time Taken: 63 minutes
// Author: Shashwat Kumar
// QUESTION LINK: Algozenith
// Rating: Easy
// Description: find the shortest path from S to E in a grid using graph and bfs and print the path
// Solved: Yes
// Learning: how to transform a grid into a graph

/***********************************************Pre Processor*********************************************/
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...) 42
#endif

/**************************************************Definition*************************************************/
#define endl '\n'
#define pb push_back
// #define int long long
#define F first
#define S second
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
/************************************************Main Function***********************************************/

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;
pair<int, int> st, en;

bool check(pair<int, int> node, vector<vector<char>> &v)
{
    if (node.F >= 0 && node.F < n && node.S >= 0 && node.S < m && v[node.F][node.S] != '#')
        return 1;
    return 0;
}

void print_parent(vector<vpii> &v, pii &en)
{
    if (v[en.F][en.S] == make_pair(-1, -1))
    {
        cout << en.F << " " << en.S << endl;
        return;
    }
    print_parent(v, v[en.F][en.S]);
    cout << en.F << " " << en.S << endl;
}

void bfs(vector<vector<char>> &v, pair<int, int> st)
{
    vvi dist(n, vi(m, 1e9));      // initialising with a large value which signifies that all nodes unreachable in start it means that they are unvisited
    vector<vpii> par(n, vpii(m)); // array to keep track of parent of each node
    // iterate over all the nodes
    queue<pair<int, int>> q;
    par[st.F][st.S] = {-1, -1};
    dist[st.F][st.S] = 0;
    q.push(st); // starting node
    while (!q.empty())
    {
        pair<int, int> node = q.front();
        debug(node.F, node.S);
        q.pop();
        for (int neighbours = 0; neighbours < 4; neighbours++)
        {
            if (check({node.F + dx[neighbours], node.S + dy[neighbours]}, v) && dist[node.F + dx[neighbours]][node.S + dy[neighbours]] > dist[node.F][node.S] + 1)
            {
                debug(node.F + dx[neighbours], node.S + dy[neighbours]);
                dist[node.F + dx[neighbours]][node.S + dy[neighbours]] = dist[node.F][node.S] + 1;
                q.push({node.F + dx[neighbours], node.S + dy[neighbours]});
                par[node.F + dx[neighbours]][node.S + dy[neighbours]] = {node.F, node.S};
            }
        }
    }
    cout << dist[en.F][en.S] << endl;
    print_parent(par, en);
}

void solve()
{
    // length and breadth of the grid
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }
    // start and end cell
    cin >> st.F >> st.S;
    cin >> en.F >> en.S;

    // bfs will return me a vector with the shortest path to all other nodes
    bfs(v, st);
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
// Test case

// 6 6
// #....#
// ####.#
// ......
// .#....
// .####.
// ......

//     0 1 5 0