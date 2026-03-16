// Source: https://leetcode.com/problems/substring-xor-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s, and a 2D integer array queries where queries[i] = [firsti, secondi].
//
// For the ith query, find the shortest substring of s whose decimal value, val, yields secondi when bitwise XORed with firsti. In other words, val ^ firsti == secondi.
//
// The answer to the ith query is the endpoints (0-indexed) of the substring [lefti, righti] or [-1, -1] if no such substring exists. If there are multiple answers, choose the one with the minimum lefti.
//
// Return an array ans where ans[i] = [lefti, righti] is the answer to the ith query.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "101101", queries = [[0,5],[1,2]]
// Output: [[0,2],[2,3]]
// Explanation: For the first query the substring in range [0,2] is "101" which has a decimal value of 5, and 5 ^ 0 = 5, hence the answer to the first query is [0,2]. In the second query, the substring in range [2,3] is "11", and has a decimal value of 3, and 3 ^ 1 = 2. So, [2,3] is returned for the second query.
//
// Constraints:
// 1 <= s.length <= 104
// 	s[i] is either '0' or '1'.
// 	1 <= queries.length <= 105
// 	0 <= firsti, secondi <= 109
//

class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        unordered_map<int, pair<int, int>> valToIndices;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (valToIndices.find(0) == valToIndices.end()) {
                    valToIndices[0] = {i, i};
                }
                continue;
            }

            int val = 0;
            for (int j = i; j < min(n, i + 31); ++j) {
                val = (val << 1) | (s[j] - '0');
                if (valToIndices.find(val) == valToIndices.end()) {
                    valToIndices[val] = {i, j};
                }
            }
        }

        vector<vector<int>> result;
        for (const auto& query : queries) {
            int first = query[0];
            int second = query[1];
            int targetVal = first ^ second;

            if (valToIndices.find(targetVal) != valToIndices.end()) {
                result.push_back({valToIndices[targetVal].first, valToIndices[targetVal].second});
            } else {
                result.push_back({-1, -1});
            }
        }

        return result;          
    }
};
