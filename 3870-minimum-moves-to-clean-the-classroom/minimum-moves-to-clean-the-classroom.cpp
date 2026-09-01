class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (classroom[r][c] == 'S') {
                    sr = r;
                    sc = c;
                }
                else if (classroom[r][c] == 'L') {
                    id[r][c] = litterCount++;
                }
            }
        }

        if (litterCount == 0)
            return 0;

        int masks = 1 << litterCount;
        int fullMask = masks - 1;
        int energyStates = energy + 1;

        auto encode = [&](int r, int c, int e, int mask) {
            int pos = r * n + c;

            return (pos * energyStates + e) * masks + mask;
        };

        auto decode = [&](int state, int &r, int &c, int &e, int &mask) {
            mask = state % masks;
            state /= masks;

            e = state % energyStates;
            state /= energyStates;

            r = state / n;
            c = state % n;
        };
        int totalStates = m * n * energyStates * masks;

        vector<char> visited(totalStates, 0);

        queue<int> q;

        int start = encode(sr, sc, energy, 0);

        visited[start] = 1;
        q.push(start);

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                int state = q.front();
                q.pop();
                int r, c, e, mask;
                decode(state, r, c, e, mask);
                if (mask == fullMask)
                    return moves;
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;
                    if (classroom[nr][nc] == 'X')
                        continue;
                    int ne = e - 1;
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }
                    int nmask = mask;

                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    int nextState = encode(nr, nc, ne, nmask);

                    if (!visited[nextState]) {
                        visited[nextState] = 1;
                        q.push(nextState);
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};