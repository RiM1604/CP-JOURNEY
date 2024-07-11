class Solution
{
public:
    int longestMountain(vector<int> &arr)
    {
        int n = arr.size();
        int final_ans = INT_MIN;
        int ans = 0;
        int st = -1;
        int flag = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                if (flag != 1)
                {
                    st = i;
                    // cout<<"p"<<i<<endl;
                    ans += 1;
                }
                else
                {
                    ans = 1;
                    flag = 0;
                    st = i;
                }
            }
            else if (arr[i] > arr[i + 1])
            {
                if (st != -1)
                {
                    flag = 1;
                    ans += 1;
                    final_ans = max(final_ans, ans);
                    // cout<<"n"<<i<<endl;
                }
                else
                {
                    ans = 0;
                    st = -1;
                }
            }
            else
            {
                ans = 0;
                st = -1;
            }
        }
        if (final_ans < 2)
        {
            return 0;
        }
        else
        {
            return final_ans + 1;
        }
    }
};

//// two pointer solution as well...

class Solution:
    def longestMountain(self, arr: List[int]) -> int:
        longest = 0
        up = 0
        down = 0

        for i in range(1, len(arr)):
            if (down and arr[i - 1] < arr[i]) or (arr[i - 1] == arr[i]):
                up = 0
                down = 0

            up += arr[i - 1] < arr[i]
            down += arr[i - 1] > arr[i]

            if up and down:
                longest = max(longest, up + down + 1)

        return longest
