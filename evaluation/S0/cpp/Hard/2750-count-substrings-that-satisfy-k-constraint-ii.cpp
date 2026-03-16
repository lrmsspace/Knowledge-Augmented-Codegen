// Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s and an integer k.
//
// You are also given a 2D integer array queries, where queries[i] = [li, ri].
//
// A binary string satisfies the k-constraint if either of the following conditions holds:
//
//
// 	The number of 0's in the string is at most k.
// 	The number of 1's in the string is at most k.
//
//
// Return an integer array answer, where answer[i] is the number of substrings of s[li..ri] that satisfy the k-constraint.
//
// Example:
// Input: s = "0001111", k = 2, queries = [[0,6]]
//
// Output: [26]
//
// Explanation:
//
// For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the k-constraint except for the substrings s[0..5] = "000111" and s[0..6] = "0001111".
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= s.length
// 	1 <= queries.length <= 105
// 	queries[i] == [li, ri]
// 	0 <= li <= ri < s.length
// 	All queries are distinct.
//

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        vector<long long> prefixCount(n + 1, 0);
        vector<int> zeroCount(n + 1, 0);
        vector<int> oneCount(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefixCount[i + 1] = prefixCount[i];
            zeroCount[i + 1] = zeroCount[i];
            oneCount[i + 1] = oneCount[i];
            
            if (s[i] == '0') {
                zeroCount[i + 1]++;
            } else {
                oneCount[i + 1]++;
            }
        }
        
        vector<long long> result;
        
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            long long totalSubstrings = (long long)(r - l + 1) * (r - l + 2) / 2;
            
            // Count substrings that do not satisfy k-constraint
            long long invalidSubstrings = 0;
            
            // Count substrings with more than k zeros
            int left = l;
            for (int right = l; right <= r; right++) {
                while (zeroCount[right + 1] - zeroCount[left] > k) {
                    left++;
                }
                invalidSubstrings += (right - left + 1);
            }
            
            // Count substrings with more than k ones
            left = l;
            for (int right = l; right <= r; right++) {
                while (oneCount[right + 1] - oneCount[left] > k) {
                    left++;
                }
                invalidSubstrings += (right - left + 1);
            }
            
            long long validSubstrings = totalSubstrings - invalidSubstrings;
            result.push_back(validSubstrings);
        }
        
        return result;          
    }
};
