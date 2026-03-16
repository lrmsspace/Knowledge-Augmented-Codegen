// Source: https://leetcode.com/problems/find-longest-awesome-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it a palindrome.
//
// Return the length of the maximum length awesome substring of s.
//
// Example:
// Input: s = "3242415"
// Output: 5
// Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of digits.
//

class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        int maxLength = 0;
        unordered_map<int, int> pos;
        pos[0] = -1;  // initial state
        
        int state = 0;
        for (int i = 0; i < n; i++) {
            int digit = s[i] - '0';
            state ^= (1 << digit);
            
            // Check for even counts
            if (pos.find(state) != pos.end()) {
                maxLength = max(maxLength, i - pos[state]);
            } else {
                pos[state] = i;
            }
            
            // Check for one odd count
            for (int d = 0; d < 10; d++) {
                int toggledState = state ^ (1 << d);
                if (pos.find(toggledState) != pos.end()) {
                    maxLength = max(maxLength, i - pos[toggledState]);
                }
            }
        }
        
        return maxLength;           
    }
};
