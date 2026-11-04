
class Solution {
public:
    multiset<int> low, high;
    long long sumLow = 0, sumHigh = 0;

    void add(int num) {
        if (low.empty() || num <= *low.rbegin()) {
            low.insert(num);
            sumLow += num;
        } else {
            high.insert(num);
            sumHigh += num;
        }

        balance();
    }

    void remove(int num) {
        auto it = low.find(num);

        if (it != low.end()) {
            sumLow -= num;
            low.erase(it);
        } else {
            it = high.find(num);
            sumHigh -= num;
            high.erase(it);
        }

        balance();
    }

    void balance() {
        int target = (low.size() + high.size() + 1) / 2;

        while (low.size() > target) {
            auto it = prev(low.end());
            int val = *it;

            low.erase(it);
            sumLow -= val;

            high.insert(val);
            sumHigh += val;
        }

        while (low.size() < target) {
            auto it = high.begin();
            int val = *it;

            high.erase(it);
            sumHigh -= val;

            low.insert(val);
            sumLow += val;
        }
    }

    long long getCost() {
        long long median = *low.rbegin();

        return median * low.size() - sumLow
             + sumHigh - median * high.size();
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }
        const long long INF = 1e18;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];
                if (i >= x) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
