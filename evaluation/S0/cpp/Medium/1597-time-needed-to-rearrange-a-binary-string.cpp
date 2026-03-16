// Source: https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s. In one second, all occurrences of "01" are simultaneously replaced with "10". This process repeats until no occurrences of "01" exist.
//
// Return the number of seconds needed to complete this process.
//
// Example:
// Input: s = "0110101"
// Output: 4
// Explanation: 
// After one second, s becomes "1011010".
// After another second, s becomes "1101100".
// After the third second, s becomes "1110100".
// After the fourth second, s becomes "1111000".
// No occurrence of "01" exists any longer, and the process needed 4 seconds to complete,
// so we return 4.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
//
//
//  
// Follow up:
//
// Can you solve this problem in O(n) time complexity?
//

class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        int n = s.size();
        int zeros = 0;
        int result = 0;

        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '0') {
                zeros++;
            } else if (zeros > 0) {
                result = max(result + 1, zeros);
            }
        }

        return result;          
    }
};
