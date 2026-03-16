// Source: https://leetcode.com/problems/splitting-a-string-into-descending-consecutive-values/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of only digits.
//
// Check if we can split s into two or more non-empty substrings such that the numerical values of the substrings are in descending order and the difference between numerical values of every two adjacent substrings is equal to 1.
//
//
// 	For example, the string s = "0090089" can be split into ["0090", "089"] with numerical values [90,89]. The values are in descending order and adjacent values differ by 1, so this way is valid.
// 	Another example, the string s = "001" can be split into ["0", "01"], ["00", "1"], or ["0", "0", "1"]. However all the ways are invalid because they have numerical values [0,1], [0,1], and [0,0,1] respectively, all of which are not in descending order.
//
//
// Return true if it is possible to split s​​​​​​ as described above, or false otherwise.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "1234"
// Output: false
// Explanation: There is no valid way to split s.
//
// Constraints:
// 1 <= s.length <= 20
// 	s only consists of digits.
//

class Solution {
public:
    bool splitString(string s) {
        int n = s.size();

        function<bool(int, long long, int)> backtrack = [&](int index, long long prevNum, int count) {
            if (index == n) {
                return count >= 2;
            }

            long long currNum = 0;
            for (int i = index; i < n; ++i) {
                currNum = currNum * 10 + (s[i] - '0');
                if (prevNum == -1 || currNum + 1 == prevNum) {
                    if (backtrack(i + 1, currNum, count + 1)) {
                        return true;
                    }
                }
                if (currNum >= prevNum && prevNum != -1) {
                    break; // No need to continue if current number is already larger or equal
                }
            }
            return false;
        };

        return backtrack(0, -1, 0);         
    }
};
