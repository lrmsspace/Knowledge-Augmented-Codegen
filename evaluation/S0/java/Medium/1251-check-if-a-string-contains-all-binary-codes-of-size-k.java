// Source: https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
//
// Example:
// Input: s = "00110110", k = 2
// Output: true
// Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 20
//

class Solution {
    public boolean hasAllCodes(String s, int k) {
        int needed = 1 << k; // Total number of binary codes of length k
        Set<String> seen = new HashSet<>();

        for (int i = 0; i <= s.length() - k; i++) {
            String substring = s.substring(i, i + k);
            if (!seen.contains(substring)) {
                seen.add(substring);
                needed--;
                if (needed == 0) {
                    return true; // All codes found
                }
            }
        }

        return false; // Not all codes found            
    }
}
