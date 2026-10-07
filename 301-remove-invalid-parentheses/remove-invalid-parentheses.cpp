class Solution {
public:
    unordered_set<string> ans;

    void solve(string &s, int index,
               int leftCount, int rightCount,
               int leftRemove, int rightRemove,
               string path) {
        if (index == s.size()) {
            if (leftRemove == 0 && rightRemove == 0) {
                ans.insert(path);
            }
            return;
        }
        char ch = s[index];
        if (ch == '(' && leftRemove > 0) {
            solve(s, index + 1,
                  leftCount, rightCount,
                  leftRemove - 1, rightRemove,
                  path);
        }
        if (ch == ')' && rightRemove > 0) {
            solve(s, index + 1,
                  leftCount, rightCount,
                  leftRemove, rightRemove - 1,
                  path);
        }
        if (ch != '(' && ch != ')') {
            solve(s, index + 1,
                  leftCount, rightCount,
                  leftRemove, rightRemove,
                  path + ch);
        }
        else if (ch == '(') {
            solve(s, index + 1,
                  leftCount + 1, rightCount,
                  leftRemove, rightRemove,
                  path + ch);
        }
        else if (ch == ')' && leftCount > rightCount) {
            solve(s, index + 1,
                  leftCount, rightCount + 1,
                  leftRemove, rightRemove,
                  path + ch);
        }
    }
    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0;
        int rightRemove = 0;
        for (char ch : s) {

            if (ch == '(') {
                leftRemove++;
            }

            else if (ch == ')') {
                if (leftRemove > 0) {
                    leftRemove--;
                }
                else {
                    rightRemove++;
                }
            }
        }
        solve(s, 0, 0, 0,
              leftRemove, rightRemove, "");

        return vector<string>(ans.begin(), ans.end());
    }
};