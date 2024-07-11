// Date: 11-07-2024
// Start Time: 12:45:16
// End Time  :
// Time Taken:
// Author: RiM1604
// QUESTION LINK: https://leetcode.com/problems/maximum-students-taking-exam/description/
// Rating: Medium to Hard
// Description: Find the maximum no of students you can seat given a restriction.
// Solved: Yes
// Learning: Learnt about using dp profile method in bitmask dp where you store a section of the previous choices which effect the current choice.
class Solution
{
public:
    int n, m;
    int dp[9][9][1 << 9];
    vector<vector<char>> grid;
    int rec(int r, int c, int mask)
    {
        // if(r==m-1 && c==n){
        //     return 0;
        // }
        if (c == n)
        {
            if (r == m - 1)
            {
                return 0;
            }
            else
            {
                int ans = rec(r + 1, 0, mask);
                return ans;
            }
        }
        if (dp[r][c][mask] != -1)
        {
            return dp[r][c][mask];
        }
        int ans = 0;
        // if(r==0 && c==0){
        //     cout<<"yes"<<endl;
        //     if(grid[r][c]=='.'){
        //         ans = max(ans, 1+rec(r,c+1,mask|1<<(m)));
        //     }
        //     ans= max(ans, rec(r,c+1,mask>>1));
        // }

        // if(r==0){
        //     if((!mask&(1<<m)) && (!mask&(1))){
        //         if(grid[r][c]=='.'){
        //             ans = max(ans, 1+rec(r,c+1,mask>>1|(1<<m)));
        //         }
        //     }
        //     ans = rec(r,c+1,mask>>1);
        // }
        if (c == 0)
        {
            cout << "r" << r << "c" << c << "out" << endl;
            if (!(mask & (1 << 2)) && grid[r][c] == '.')
            {
                cout << "r" << r << "c" << c << endl;
                ans = max(ans, 1 + rec(r, c + 1, mask >> 1 | (1 << n)));
            }
        }
        else if (c == n - 1)
        {
            cout << "r" << r << "cn-1" << c << "out" << mask << "mask" << endl;
            if (!(mask & (1 << n)) && !(mask & (1)) && grid[r][c] == '.')
            {
                cout << "r" << r << "cn-1" << c << "in" << mask << "mask" << endl;
                ans = max(ans, 1 + rec(r, c + 1, mask >> 1 | (1 << n)));
            }
        }
        else
        {
            cout << "r" << r << "c" << c << "out" << mask << "mask" << endl;
            if (!(mask & (1 << n)) && !(mask & (1)) && !(mask & (1 << 2)) && grid[r][c] == '.')
            {
                cout << "r" << r << "c" << c << "in" << endl;
                ans = max(ans, 1 + rec(r, c + 1, mask >> 1 | 1 << n));
            }
        }
        ans = max(ans, rec(r, c + 1, mask >> 1));
        return dp[r][c][mask] = ans;
    }

    int maxStudents(vector<vector<char>> &seats)
    {
        grid = seats;
        m = grid.size();
        n = grid[0].size();
        cout << n << m << endl;
        // cout<<m<<n<<endl;
        // cout<<(grid[0][1]=='.')<<endl;
        memset(dp, -1, sizeof(dp));
        // visited = vector<vector<int>>(m+1,vector<int>(n+1,0));
        // int ans = 0;
        int ans = rec(0, 0, 0);
        // cout<<dp[0][0][0]<<endl;
        // cout<<dp[0][1][0]<<endl;
        // cout<<dp[0][2][1<<5]<<endl;
        // cout<<dp[0][3][0]<<endl;
        // cout<<dp[0][4][0]<<endl;
        // cout<<dp[1][2][0]<<endl;
        // cout<<check(0,0,grid)<<endl;
        // cout<<check(0,1,grid)<<endl;

        return ans;
    }
};