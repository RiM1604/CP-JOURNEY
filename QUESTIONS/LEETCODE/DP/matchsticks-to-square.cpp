// Date: 11-07-2024
// Start Time: 14:12:16
// End Time  :
// Time Taken:
// Author: RiM1604
// QUESTION LINK: https://leetcode.com/problems/matchsticks-to-square/
// Rating: Hard
// Description: k-subset sum paritioning where k=4
// Solved: Yes
// Learning:  here reverse sorting the matchsticks array helps in reducing the time complexity because it takes lesser steps than sorted in increasing order to reach a backtracking point where one of the sum's of a,b,c,d becomes > target.

// note that this is a K-subset sum NP problem where K=4 which cant be solved in polynomial TC. and the complexity is O(4^n) here so we do some optimizations to get it accepted.

// here reverse sorting the matchsticks array helps in reducing the time complexity because it takes lesser steps than sorted in increasing order to reach a backtracking point where one of the sum's of a,b,c,d becomes > target.

class Solution
{
public:
    using lli = long long int;
    lli n;
    lli sum_a = 0, sum_b = 0, sum_c = 0, sum_d = 0;
    lli target = 0;
    lli rec(vector<int> &sticks, lli i)
    {
        if (sum_a > target || sum_b > target || sum_c > target || sum_d > target)
        {
            return 0;
        }
        if (i == n)
        {
            if ((sum_a == target && sum_b == target && sum_c == target && sum_d == target))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }

        lli ans = 0;
        sum_a += sticks[i];
        if (sum_a <= target)
        {
            ans = max(ans, rec(sticks, i + 1));
        }
        sum_a -= sticks[i];

        sum_b += sticks[i];
        if (sum_b <= target)
        {
            ans = max(ans, rec(sticks, i + 1));
        }
        sum_b -= sticks[i];

        sum_c += sticks[i];
        if (sum_c <= target)
        {
            ans = max(ans, rec(sticks, i + 1));
        }
        sum_c -= sticks[i];

        sum_d += sticks[i];
        if (sum_d <= target)
        {
            ans = max(ans, rec(sticks, i + 1));
        }
        sum_d -= sticks[i];

        return ans;
    }

    bool makesquare(vector<int> &matchsticks)
    {
        n = matchsticks.size();
        lli sum = 0;
        for (lli i = 0; i < n; i++)
        {
            sum += matchsticks[i];
        }
        if (matchsticks.size() < 4)
            return false;
        if (sum % 4 != 0)
        {
            return false;
        }
        target = sum / 4;
        sort(matchsticks.rbegin(), matchsticks.rend());
        lli ans = rec(matchsticks, 0);
        return ans;
    }
};