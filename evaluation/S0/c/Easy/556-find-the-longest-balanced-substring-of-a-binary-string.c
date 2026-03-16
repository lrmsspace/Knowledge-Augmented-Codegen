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

int findTheLongestBalancedSubstring(char* s) {
    int max_len = 0;
    int n = strlen(s);
    
    for (int i = 0; i < n;) {
        if (s[i] == '0') {
            int count_0 = 0;
            int count_1 = 0;
            
            // Count consecutive '0's
            while (i < n && s[i] == '0') {
                count_0++;
                i++;
            }
            
            // Count consecutive '1's
            int j = i;
            while (j < n && s[j] == '1') {
                count_1++;
                j++;
            }
            
            // Update max_len with the minimum of count_0 and count_1
            int balanced_len = 2 * (count_0 < count_1 ? count_0 : count_1);
            if (balanced_len > max_len) {
                max_len = balanced_len;
            }
            
            // Move i to j for the next iteration
            i = j;
        } else {
            i++;
        }
    }
    
    return max_len;     
}
