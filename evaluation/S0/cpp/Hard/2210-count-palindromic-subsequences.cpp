// Source: https://leetcode.com/problems/count-palindromic-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// Given a string of digits s, return the number of palindromic subsequences of s having length 5. Since the answer may be very large, return it modulo 109 + 7.
//
// Note:
//
//
// 	A string is palindromic if it reads the same forward and backward.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "103301"
// Output: 2
// Explanation: 
// There are 6 possible subsequences of length 5: "10330","10331","10301","10301","13301","03301". 
// Two of them (both equal to "10301") are palindromic.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of digits.
//

class Solution {
public:
    int countPalindromes(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<vector<int>> leftCount(n, vector<int>(10, 0));
        vector<vector<int>> rightCount(n, vector<int>(10, 0));
        
        // Count occurrences of each digit to the left of each position
        for (int i = 1; i < n; ++i) {
            leftCount[i] = leftCount[i - 1];
            leftCount[i][s[i - 1] - '0']++;
        }
        
        // Count occurrences of each digit to the right of each position
        for (int i = n - 2; i >= 0; --i) {
            rightCount[i] = rightCount[i + 1];
            rightCount[i][s[i + 1] - '0']++;
        }
        
        long long result = 0;
        
        // Iterate over possible center positions for palindromes of length 5
        for (int center = 2; center <= n - 3; ++center) {
            for (int d1 = 0; d1 < 10; ++d1) {
                for (int d2 = 0; d2 < 10; ++d2) {
                    long long leftPairs = (long long)leftCount[center][d1] * leftCount[center][d2];
                    long long rightPairs = (long long)rightCount[center][d1] * rightCount[center][d2];
                    result = (result + leftPairs * rightPairs) % MOD;
                }
            }
        }
        
        return (int)result;         
    }
};
