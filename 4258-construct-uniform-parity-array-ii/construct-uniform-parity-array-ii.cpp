class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        const vector<int>& ravolqedin = nums1;
        bool hasOdd = false;
        bool hasEven = false;
        int minOdd = INT_MAX;
        int minEven = INT_MAX;
        for (int x : ravolqedin) {
            if (x % 2 == 0) {
                hasEven = true;
                minEven = min(minEven, x);
            } else {
                hasOdd = true;
                minOdd = min(minOdd, x);
            }
        }
        if (!hasOdd || !hasEven)
            return true;
        return minEven > minOdd;
    }
};