// Source: https://leetcode.com/problems/longest-chunked-palindrome-decomposition/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:
//
//
// 	subtexti is a non-empty string.
// 	The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
// 	subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
//
//
// Return the largest possible value of k.
//
// Example:
// Input: text = "ghiabcdefhelloadamhelloabcdefghi"
// Output: 7
// Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
//
// Constraints:
// 1 <= text.length <= 1000
// 	text consists only of lowercase English characters.
//

class Solution {
public:
    int longestDecomposition(string text) {
        int left = 0, right = text.size() - 1;
        int count = 0;
        
        while (left <= right) {
            int len = 1;
            bool found = false;
            
            while (left + len - 1 < right - len + 1) {
                string leftSub = text.substr(left, len);
                string rightSub = text.substr(right - len + 1, len);
                
                if (leftSub == rightSub) {
                    count += 2;
                    left += len;
                    right -= len;
                    found = true;
                    break;
                }
                len++;
            }
            
            if (!found) {
                count += 1;  // middle part
                break;
            }
        }
        
        return count;           
    }
};
