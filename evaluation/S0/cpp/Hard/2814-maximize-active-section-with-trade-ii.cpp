// Source: https://leetcode.com/problems/maximize-active-section-with-trade-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s of length n, where:
//
//
//  '1' represents an active section.
//  '0' represents an inactive section.
//
//
// You can perform at most one trade to maximize the number of active sections in s. In a trade, you:
//
//
//  Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
//  Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
//
//
// Additionally, you are given a 2D array queries, where queries[i] = [li, ri] represents a substring s[li...ri].
//
// For each query, determine the maximum possible number of active sections in s after making the optimal trade on the substring s[li...ri].
//
// Return an array answer, where answer[i] is the result for queries[i].
//
// Note
//
//
//  For each query, treat s[li...ri] as if it is augmented with a '1' at both ends, forming t = '1' + s[li...ri] + '1'. The augmented '1's do not contribute to the final count.
//  The queries are independent of each other.
//
// Example:
// Input: s = "01", queries = [[0,1]]
//
// Output: [1]
//
// Explanation:
//
// Because there is no block of '1's surrounded by '0's, no valid trade is possible. The maximum number of active sections is 1.
//
// Constraints:
// 1 <= n == s.length <= 105
//  1 <= queries.length <= 105
//  s[i] is either '0' or '1'.
//  queries[i] = [li, ri]
//  0 <= li <= ri < n
//

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> prefixOnes(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefixOnes[i + 1] = prefixOnes[i] + (s[i] == '1' ? 1 : 0);
        }
        
        vector<int> result;
        for (const auto& query : queries) {
            int l = query[0], r = query[1];
            int totalOnes = prefixOnes[r + 1] - prefixOnes[l];
            int maxGain = 0;
            int currentGain = 0;
            
            for (int i = l; i <= r; i++) {
                if (s[i] == '0') {
                    currentGain++;
                } else {
                    currentGain--;
                }
                if (currentGain < 0) {
                    currentGain = 0;
                }
                maxGain = max(maxGain, currentGain);
            }
            
            result.push_back(totalOnes + maxGain);
        }
        
        return result;          
    }
};
