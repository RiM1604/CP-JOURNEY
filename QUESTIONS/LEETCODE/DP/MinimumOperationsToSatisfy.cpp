class Solution
{
public:
    int precomputed[1001][11];
    int dp[1001][11];
    int n;
    int rec(int idx, int prev_val)
    {

        if (idx == n)
        {
            return 0;
        }

        if (dp[idx][prev_val] != -1)
        {
            return dp[idx][prev_val];
        }
        int ans = INT_MAX;
        for (int val = 0; val <= 9; val++)
        {
            if (val != prev_val)
            {
                ans = min(ans, precomputed[idx][val] + rec(idx + 1, val));
            }
        }
        return dp[idx][prev_val] = ans;
    }

    int minimumOperations(vector<vector<int>> &grid)
    {
        int m = grid.size();
        n = grid[0].size();
        int mapping[n][10];
        memset(mapping, 0, sizeof(mapping));
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                mapping[i][grid[j][i]]++;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int target = 0; target <= 9; target++)
            {
                precomputed[i][target] = m - mapping[i][target];
            }
        }
        int ans = 0;
        ans = rec(0, 10);
        return ans;
    }
};