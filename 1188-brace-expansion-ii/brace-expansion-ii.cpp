class Solution {
    set<string> dfs(string& s, int& i) {
        set<string> res;
        set<string> cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == '{') {
                i++;
                set<string> part = dfs(s, i);
                i++;

                set<string> temp;
                for (auto& a : cur)
                    for (auto& b : part)
                        temp.insert(a + b);

                cur = temp;
            }
            else if (s[i] == ',') {
                res.insert(cur.begin(), cur.end());
                cur = {""};
                i++;
            }
            else {
                string ch(1, s[i++]);
                set<string> temp;

                for (auto& x : cur)
                    temp.insert(x + ch);

                cur = temp;
            }
        }

        res.insert(cur.begin(), cur.end());
        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> result = dfs(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};