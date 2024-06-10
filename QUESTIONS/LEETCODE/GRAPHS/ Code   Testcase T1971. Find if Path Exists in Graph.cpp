// Date: 09-06-2024
// Start Time: 15:49:20
// End Time  :
// Time Taken:
// Author: Shashwat Kumar
// QUESTION LINK: https://leetcode.com/problems/find-if-path-exists-in-graph/description/
// Rating: Easy
// Description: find if a path exist between src and dst
// Solved: Yes
// Learning: How to convert edgelist to adj list

/****************************************************Pre Processor***************************************************/
vector<int> vis;

bool dfs(int node, int dst, vector<vector<int>> &v)
{
    vis[node] = 1;
    bool ret_val = 0;
    for (auto nn : v[node])
    {
        if (nn == dst)
            return true;
        if (!vis[nn])
        {
            ret_val |= dfs(nn, dst, v);
        }
    }
    return ret_val;
}

class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edgelist, int src, int dst)
    {
        // create adj list
        vector<vector<int>> v(n);
        vis.clear();
        vis.resize(n, 0);
        if (edgelist.size() == 0 && n == 1)
        {
            return true;
        }
        for (int i = 0; i < edgelist.size(); i++)
        {
            v[edgelist[i][0]].push_back(edgelist[i][1]);
            v[edgelist[i][1]].push_back(edgelist[i][0]);
        }
        // adj list created
        // now simply call dfs from src to dst
        return dfs(src, dst, v);
    }
};