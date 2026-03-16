// Source: https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s consisting only of zeroes and ones.
//
// A substring of s is considered balanced if all zeroes are before ones and the number of zeroes is equal to the number of ones inside the substring. Notice that the empty substring is considered a balanced substring.
//
// Return the length of the longest balanced substring of s.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "01000111"
// Output: 6
// Explanation: The longest balanced substring is "000111", which has length 6.
//
// Constraints:
// 1 <= s.length <= 50
// 	'0' <= s[i] <= '1'
//

class Solution {
    public int findTheLongestBalancedSubstring(String s) {
        int maxLength = 0;
        int n = s.length();
        
        for (int i = 0; i < n - 1; i++) {
            if (s.charAt(i) == '0') {
                int zeroCount = 0;
                int oneCount = 0;
                
                for (int j = i; j < n; j++) {
                    if (s.charAt(j) == '0') {
                        zeroCount++;
                    } else {
                        oneCount++;
                    }
                    
                    if (zeroCount == oneCount) {
                        maxLength = Math.max(maxLength, 2 * zeroCount);
                    } else if (oneCount > zeroCount) {
                        break; // No need to continue if ones exceed zeros
                    }
                }
            }
        }
        
        return maxLength;           
    }
}
