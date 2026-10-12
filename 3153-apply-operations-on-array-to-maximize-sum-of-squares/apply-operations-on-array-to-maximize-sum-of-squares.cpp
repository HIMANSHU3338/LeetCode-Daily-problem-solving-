
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1000000007;
        vector<int> cnt(31, 0);
        for (int num : nums) {
            for (int bit = 0; bit < 31; bit++) {
                if ((num >> bit) & 1) {
                    cnt[bit]++;
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < k; i++) {
            long long x = 0;

            for (int bit = 0; bit < 31; bit++) {
                if (cnt[bit] > 0) {
                    x |= (1LL << bit);
                    cnt[bit]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return ans;
    }
};
