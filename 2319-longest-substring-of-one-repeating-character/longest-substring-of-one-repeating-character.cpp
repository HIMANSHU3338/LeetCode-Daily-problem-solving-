class Solution {
public:
    struct Node {
        int len = 0;
        int left = 0;
        int right = 0;
        int best = 0;
        char lc = 0;
        char rc = 0;
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        // Prefix
        res.left = a.left;

        if (a.left == a.len && a.rc == b.lc) {
            res.left = a.len + b.left;
        }
        res.right = b.right;
        if (b.right == b.len && a.rc == b.lc) {
            res.right = b.len + a.right;
        }
        res.best = max(a.best, b.best);
        if (a.rc == b.lc) {
            res.best = max(res.best, a.right + b.left);
        }

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node].len = 1;
            tree[node].left = 1;
            tree[node].right = 1;
            tree[node].best = 1;
            tree[node].lc = s[l];
            tree[node].rc = s[l];
            return;
        }

        int mid = l + (r - l) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int pos, char c) {
        if (l == r) {
            tree[node].lc = c;
            tree[node].rc = c;
            tree[node].len = 1;
            tree[node].left = 1;
            tree[node].right = 1;
            tree[node].best = 1;
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            update(node * 2, l, mid, pos, c);
        } else {
            update(node * 2 + 1, mid + 1, r, pos, c);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        this->s = s;
        int n = s.size();
        tree.assign(4 * n + 5, Node());

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            int pos = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, pos, c);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};