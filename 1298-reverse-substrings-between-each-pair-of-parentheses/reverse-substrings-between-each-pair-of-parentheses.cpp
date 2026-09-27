class Solution {
public:
    string reverseParentheses(string s) {
        stack<int> st;
        vector<int> pair(s.size());

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        string ans;
        int i = 0;
        int direction = 1;

        while (i < s.size()) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];
                direction = -direction;
            } else {
                ans += s[i];
            }

            i += direction;
        }

        return ans;
    }
};