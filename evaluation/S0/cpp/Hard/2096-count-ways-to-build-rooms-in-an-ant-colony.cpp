// Source: https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/   |   Difficulty: Hard
//
// Problem Description:
// You are an ant tasked with adding n new rooms numbered 0 to n-1 to your colony. You are given the expansion plan as a 0-indexed integer array of length n, prevRoom, where prevRoom[i] indicates that you must build room prevRoom[i] before building room i, and these two rooms must be connected directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan is given such that once all the rooms are built, every room will be reachable from room 0.
//
// You can only build one room at a time, and you can travel freely between rooms you have already built only if they are connected. You can choose to build any room as long as its previous room is already built.
//
// Return the number of different orders you can build all the rooms in. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: prevRoom = [-1,0,1]
// Output: 1
// Explanation: There is only one way to build the additional rooms: 0 → 1 → 2
//
// Constraints:
// n == prevRoom.length
// 	2 <= n <= 105
// 	prevRoom[0] == -1
// 	0 <= prevRoom[i] < n for all 1 <= i < n
// 	Every room is reachable from room 0 once all the rooms are built.
//

class Solution {

public:

    int waysToBuildRooms(vector<int>& prevRoom) {

        
        const int MOD = 1e9 + 7;
        int n = prevRoom.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; ++i) {
            tree[prevRoom[i]].push_back(i);
        }

        vector<long long> fact(n + 1, 1), invFact(n + 1, 1);
        for (int i = 2; i <= n; ++i) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invFact[n] = modInverse(fact[n], MOD);
        for (int i = n - 1; i >= 2; --i) {
            invFact[i] = invFact[i + 1] * (i + 1) % MOD;
        }

        function<pair<int, long long>(int)> dfs = [&](int node) {
            int size = 1;
            long long ways = 1;
            for (int child : tree[node]) {
                auto [childSize, childWays] = dfs(child);
                size += childSize;
                ways = ways * childWays % MOD;
                ways = ways * invFact[childSize] % MOD;
            }
            ways = ways * fact[size - 1] % MOD;
            return make_pair(size, ways);
        };

        return dfs(0).second;
    }

};
