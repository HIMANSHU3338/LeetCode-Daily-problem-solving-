
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1,vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count = 0;
        for (int num : arr1) {
            auto it = lower_bound(
                arr2.begin(),
                arr2.end(),
                num
            );
            bool valid = true;
            if (it != arr2.end() && abs(*it - num) <= d) {
                valid = false;
            }
            if (it != arr2.begin() && abs(*prev(it) - num) <= d) {
                valid = false;
            }
            if (valid) {
                count++;
            }
        }
        return count;
    }
};