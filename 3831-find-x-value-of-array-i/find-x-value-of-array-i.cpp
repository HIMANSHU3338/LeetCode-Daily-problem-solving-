class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);
        for(int num : nums) {
            int rem = num % k;
            vector<long long>next (k, 0);
            next[rem]++;
            for(int r = 0; r < k; r++){
                int newRem = (r * rem) % k;
                next[newRem] += dp[r];
            }
            for (int r = 0; r < k; r++) {
                ans[r] += next[r];
            }
            dp = next;
        }
        return ans;
    }
};