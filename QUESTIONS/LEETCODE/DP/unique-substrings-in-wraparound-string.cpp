//// idea was to use arr[s[i]-'a'] to keep track if this character has occured before and how many substrings of it did we include.
/// for "abc" b = +2, c= +3 we add to the ans because 2,3 more substrings are formed with the inclusion of b,c.

class Solution
{
public:
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        int arr[26];
        int ans = 1;
        int curr_ans = 1;
        arr[s[0] - 'a'] = 1;
        for (int i = 1; i < n; i++)
        {
            if ((s[i - 1] - 'a' + 1) % 26 == s[i] - 'a')
            {
                curr_ans++;
            }
            else
            {
                curr_ans = 1;
            }

            if (arr[s[i] - 'a'] < curr_ans)
            {
                ans += curr_ans - arr[s[i] - 'a'];
                arr[s[i] - 'a'] = curr_ans;
            }
        }
        return ans;
    }
};