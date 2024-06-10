// Date: 05-06-2024
// Start Time: 12:45:34
// End Time  : 15:27:44
// Time Taken: 162 minutes
// Author: Shashwat Kumar
// QUESTION LINK: https://cses.fi/problemset/task/1194/
// Rating: Difficult
// Description: Can you get out of the grid whithout getting caught by any monster
// Solved: Yes
// Learning: Multisource BFS and also how to print the path, here I had to use BSF twice

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
int n, m;
vpii edge, monsters;
pii me;
queue<pair<int, int>> q;
queue<pair<int, int>> my_q;
// D , U, R, L
vector<vector<pair<pii, char>>> parent(1005, vector<pair<pii, char>>(1005));
vector<pair<int, char>> dir = {{0, 'D'}, {1, 'U'}, {2, 'R'}, {3, 'L'}};
pii d[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// check return whether i can go to that cell or not
bool check(int x, int y, vector<vector<char>> &v)
{
    bool ret_val = (x >= 0 && x < n) && (y >= 0 && y < m) && v[x][y] != '#';
    // debug(ret_val);
    return ret_val;
}

void print_grid(vvi &dist)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(10) << dist[i][j] << " ";
        }
        cout << endl;
    }
}

void print_path(pii node)
{
    if (parent[node.F][node.S].F == make_pair(-1, -1))
        return;
    print_path(parent[node.F][node.S].F);
    cout << parent[node.F][node.S].S;
}

void bfs(vector<vector<char>> &v, vvi &dist, queue<pii> &q)
{
    parent[me.F][me.S] = {{-1, -1}, 'X'};
    // debug(q.empty());
    while (!q.empty())
    {
        pair<int, int> node = q.front();
        // debug(node.F, node.S);
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            // debug(node.F + d[i].F, node.S + d[i].S);
            if (check(node.F + d[i].F, node.S + d[i].S, v) && dist[node.F + d[i].F][node.S + d[i].S] > dist[node.F][node.S] + 1)
            {
                parent[node.F + d[i].F][node.S + d[i].S] = {node, dir[i].S};
                q.push({node.F + d[i].F, node.S + d[i].S});
                dist[node.F + d[i].F][node.S + d[i].S] = dist[node.F][node.S] + 1;
            }
        }
    }

    // uncomment to print the shortest distance to all reachable points
    // print_grid(dist);
}

void solve()
{
    cin >> n >> m;
    vvi dist(n + 5, vi(m + 5, 1e9));
    vvi my_dist(n + 5, vi(m + 5, 1e9));
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 'M')
            {
                q.push({i, j});
                monsters.pb({i, j});
                dist[i][j] = 0;
            }
            else if (v[i][j] == 'A')
            {
                if ((i == 0 || i == n - 1) || (j == 0 || j == m - 1))
                {
                    cout << "YES" << endl;
                    cout << 0;
                    return;
                }
                me = {i, j};
                my_q.push({i, j});
                my_dist[i][j] = 0;
            }
            else if (v[i][j] == '.')
            {
                if ((i == 0 || i == n - 1) || (j == 0 || j == m - 1))
                    edge.pb({i, j});
            }
        }
    }

    // using multisource bfs
    bfs(v, dist, q);
    bfs(v, my_dist, my_q);
    for (auto it : edge)
    {
        int distance = my_dist[it.F][it.S];
        if (distance < dist[it.F][it.S])
        {
            cout << "YES" << endl;
            cout << distance << endl;
            print_path(it);
            return;
        }
    }
    cout << "NO";
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