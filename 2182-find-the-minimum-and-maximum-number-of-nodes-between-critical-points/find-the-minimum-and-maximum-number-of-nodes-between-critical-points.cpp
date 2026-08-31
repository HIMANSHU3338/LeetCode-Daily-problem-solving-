class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1;
        int last = -1;
        int minDist = INT_MAX;
        int index = 1;
        ListNode* prev = head;
        ListNode* curr = head->next;
        while(curr->next != nullptr) {
            if((curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val)) {
                    if(first == -1){
                        first = index;
                        last = index;
                    }
                    else{
                        minDist = min(minDist, index - last);
                        last = index;
                    }
                }
                prev = curr;
                curr = curr->next;
                index++;
        }
        if(first == last)
            return {-1, -1};
        int maxDist = last - first;
        return {minDist, maxDist};

    }
};