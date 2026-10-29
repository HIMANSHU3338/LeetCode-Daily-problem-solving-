
class Solution {
    static constexpr int LOG = 20;

    struct Fenwick {
        int n;
        vector<int> bit;

        Fenwick(int n) : n(n), bit(n + 2, 0) {}

        void add(int i, int val) {
            for (; i <= n + 1; i += i & -i)
                bit[i] ^= val;
        }
        void rangeUpdate(int l, int r, int val) {
            add(l + 1, val);
            add(r + 2, val);
        }
        int pointQuery(int pos) {
            int res = 0;
            for (int i = pos + 1; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n);
        vector<int> basePref(n);
        vector<vector<int>> up(LOG, vector<int>(n));

        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[0][u] = p;

            for (int j = 1; j < LOG; j++)
                up[j][u] = up[j - 1][up[j - 1][u]];

            for (int v : adj[u]) {
                if (v == p) continue;

                depth[v] = depth[u] + 1;
                basePref[v] =
                    basePref[u] ^ (1 << (s[v] - 'a'));

                dfs(v, u);
            }

            tout[u] = timer - 1;
        };

        basePref[0] = 1 << (s[0] - 'a');
        dfs(0, 0);

        auto isAncestor = [&](int u, int v) {
            return tin[u] <= tin[v] && tout[v] <= tout[u];
        };

        auto lca = [&](int u, int v) {
            if (isAncestor(u, v)) return u;
            if (isAncestor(v, u)) return v;

            for (int j = LOG - 1; j >= 0; j--) {
                if (!isAncestor(up[j][u], v))
                    u = up[j][u];
            }

            return up[0][u];
        };

        Fenwick fw(n);
        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta =
                    (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));

                if (delta != 0)
                    fw.rangeUpdate(tin[u], tout[u], delta);

                s[u] = c;
            }
            else {
                ss >> v;

                int pu = basePref[u] ^ fw.pointQuery(tin[u]);
                int pv = basePref[v] ^ fw.pointQuery(tin[v]);

                int w = lca(u, v);
                int mask = pu ^ pv ^ (1 << (s[w] - 'a'));
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
