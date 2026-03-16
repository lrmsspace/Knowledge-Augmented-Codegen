// Source: https://leetcode.com/problems/number-of-equivalent-domino-pairs/   |   Difficulty: Easy
//
// Problem Description:
// Given a list of dominoes, dominoes[i] = [a, b] is equivalent to dominoes[j] = [c, d] if and only if either (a == c and b == d), or (a == d and b == c) - that is, one domino can be rotated to be equal to another domino.
//
// Return the number of pairs (i, j) for which 0 <= i < j < dominoes.length, and dominoes[i] is equivalent to dominoes[j].
//
// Example:
// Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
// Output: 1
//
// Constraints:
// 1 <= dominoes.length <= 4 * 104
// 	dominoes[i].length == 2
// 	1 <= dominoes[i][j] <= 9
//

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<string, int> countMap;
        int equivalentPairs = 0;

        for (const auto& domino : dominoes) {
            int a = domino[0];
            int b = domino[1];
            string key = (a < b) ? to_string(a) + "," + to_string(b) : to_string(b) + "," + to_string(a);

            equivalentPairs += countMap[key];
            countMap[key]++;
        }

        return equivalentPairs;         
    }
};
