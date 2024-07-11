// here in the solution if I did check(map<int,int> freq) it gave tle but for check(map<int,int> &freq) it passed because
// the vector was getting created again and again for each check and time limit exceeded for large values.

class Solution
{
public:
    string s1;
    // map<int,int>freq;
    bool check(map<int, int> &freq)
    {
        if (freq.size() == 0)
            return true;
        auto firstelement = freq.begin();
        int val = firstelement->second;
        for (auto &[ele, f] : freq)
        {
            if (f != val)
            {
                return false;
            }
        }
        return true;
    }
    int dp[1001];
    int n;
    int rec(int idx)
    {
        if (idx == n)
        {
            return 0;
        }
        if (dp[idx] != -1)
        {
            return dp[idx];
        }
        int ans = n;
        map<int, int> freq;
        for (int k = idx; k < n; k++)
        {
            freq[s1[k] - 'a']++;
            if (check(freq))
            {
                // cout<<"k"<<k<<"idx"<<idx;
                ans = min(ans, 1 + rec(k + 1));
                // cout<<"ans"<<ans<<endl;
            }
        }
        return dp[idx] = ans;
    }

    int minimumSubstringsInPartition(string s)
    {
        n = s.size();
        s1 = s;
        // cout<<n<<endl;
        memset(dp, -1, sizeof(dp));
        // for(int i=0;i<n;i++){
        //     freq[s[i]-'a']++;
        // }
        int ans = rec(0);
        return ans;
    }
};