// Source: https://leetcode.com/problems/find-all-people-with-secret/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n indicating there are n people numbered from 0 to n - 1. You are also given a 0-indexed 2D integer array meetings where meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a meeting at timei. A person may attend multiple meetings at the same time. Finally, you are given an integer firstPerson.
//
// Person 0 has a secret and initially shares the secret with a person firstPerson at time 0. This secret is then shared every time a meeting takes place with a person that has the secret. More formally, for every meeting, if a person xi has the secret at timei, then they will share the secret with person yi, and vice versa.
//
// The secrets are shared instantaneously. That is, a person may receive the secret and share it with people in other meetings within the same time frame.
//
// Return a list of all the people that have the secret after all the meetings have taken place. You may return the answer in any order.
//
// Example:
// Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
// Output: [0,1,2,3,5]
// Explanation:
// At time 0, person 0 shares the secret with person 1.
// At time 5, person 1 shares the secret with person 2.
// At time 8, person 2 shares the secret with person 3.
// At time 10, person 1 shares the secret with person 5.​​​​
// Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 3
// 	0 <= xi, yi <= n - 1
// 	xi != yi
// 	1 <= timei <= 105
// 	1 <= firstPerson <= n - 1
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // DSU (Disjoint Set Union) implementation
        class DSU {
        public:
            DSU(int size) : parent(size), rank(size, 1) {
                for (int i = 0; i < size; ++i) parent[i] = i;
            }

            int find(int x) {
                if (parent[x] != x) {
                    parent[x] = find(parent[x]);
                }
                return parent[x];
            }

            void unite(int x, int y) {
                int rootX = find(x);
                int rootY = find(y);
                if (rootX != rootY) {
                    if (rank[rootX] < rank[rootY]) {
                        parent[rootX] = rootY;
                    } else if (rank[rootX] > rank[rootY]) {
                        parent[rootY] = rootX;
                    } else {
                        parent[rootY] = rootX;
                        rank[rootX]++;
                    }
                }
            }

        private:
            vector<int> parent;
            vector<int> rank;
        };

        // Sort meetings by time
        sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        DSU dsu(n);
        dsu.unite(0, firstPerson);

        int m = meetings.size();
        int i = 0;

        while (i < m) {
            int time = meetings[i][2];
            vector<pair<int, int>> currentMeetings;

            while (i < m && meetings[i][2] == time) {
                currentMeetings.push_back({meetings[i][0], meetings[i][1]});
                i++;
            }

            // Unite all meetings at the same time
            for (const auto& meeting : currentMeetings) {
                dsu.unite(meeting.first, meeting.second);
            }

            // Rollback connections for those who don't have the secret
            for (const auto& meeting : currentMeetings) {
                if (dsu.find(meeting.first) != dsu.find(0)) {
                    dsu.unite(meeting.first, meeting.first); // reset
                }
                if (dsu.find(meeting.second) != dsu.find(0)) {
                    dsu.unite(meeting.second, meeting.second); // reset
                }
            }
        }  
        vector<int> result;
        for (int person = 0; person < n; ++person) {
            if (dsu.find(person) == dsu.find(0)) {
                result.push_back(person);
            }
        }
        return result;         
    }
};
