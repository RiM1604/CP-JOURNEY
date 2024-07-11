

////here to get the number of substrings of 54321  = num_substrings of(5432) + (length(54321)-1)->new substrings created with the inclusion of 1-> this is because in the new substring created you need to take one or else the substring will overlap with the substrings in (5432)

class Solution
{
public:
    long long getDescentPeriods(vector<int> &prices)
    {
        int n = prices.size();
        long curr_ans = 1;
        long long ans = 1;
        int taken[100001];
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i - 1] - prices[i] == 1)
            {
                curr_ans++;
            }
            else
            {
                curr_ans = 1;
            }
            ans += curr_ans;
        }
        return ans;
    }
};