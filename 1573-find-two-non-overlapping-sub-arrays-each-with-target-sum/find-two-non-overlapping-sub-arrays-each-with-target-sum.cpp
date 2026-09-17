class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;
        vector<int> dp(n, INF);
        unordered_map<int, int> mp;
        mp[0] = -1;
        int sum = 0;
        int best = INF;
        int ans = INF;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            if (mp.count(sum - target)) {
                int start = mp[sum - target] + 1;
                int len = i - start + 1;
                if (start > 0 && dp[start - 1] != INF) {
                    ans = min(ans, len + dp[start - 1]);
                }
                best = min(best, len);
            }
            dp[i] = best;
            mp[sum] = i;
        }
        return ans == INF ? -1 : ans;
    }
};