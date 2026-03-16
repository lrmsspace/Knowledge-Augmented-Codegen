// Source: https://leetcode.com/problems/smallest-string-with-swaps/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.
//
// You can swap the characters at any pair of indices in the given pairs any number of times.
//
// Return the lexicographically smallest string that s can be changed to after using the swaps.
//
// Example:
// Input: s = "dcab", pairs = [[0,3],[1,2]]
// Output: "bacd"
// Explaination: 
// Swap s[0] and s[3], s = "bcad"
// Swap s[1] and s[2], s = "bacd"
//
// Constraints:
// 1 <= s.length <= 10^5
// 	0 <= pairs.length <= 10^5
// 	0 <= pairs[i][0], pairs[i][1] < s.length
// 	s only contains lower case English letters.
//

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        auto unionSets = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
            }
        };

        for (const auto& p : pairs) {
            unionSets(p[0], p[1]);
        }

        unordered_map<int, vector<char>> components;
        for (int i = 0; i < n; ++i) {
            components[find(i)].push_back(s[i]);
        }

        for (auto& [_, chars] : components) {
            sort(chars.begin(), chars.end(), greater<char>());
        }

        string result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            int root = find(i);
            result.push_back(components[root].back());
            components[root].pop_back();
        }

        return result;          
    }
};
