class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;
        vector<long long> dp(26,0);
        long long total = 0;
        for(char c : s) {
            int x = c - 'a';
            long long add = (total - dp[x] + 1 + MOD) % MOD;
            dp[x] = (dp[x] + add) % MOD;
            total = (total + add) % MOD;
        }
        return total;
    }
};