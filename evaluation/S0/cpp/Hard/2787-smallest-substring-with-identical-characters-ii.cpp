// Source: https://leetcode.com/problems/smallest-substring-with-identical-characters-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a binary string s of length n and an integer numOps.
//
// You are allowed to perform the following operation on s at most numOps times:
//
//
// 	Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1', change s[i] to '0' and vice versa.
//
//
// You need to minimize the length of the longest substring of s such that all the characters in the substring are identical.
//
// Return the minimum length after the operations.
//
// Example:
// Input: s = "000001", numOps = 1
//
// Output: 2
//
// Explanation: 
//
// By changing s[2] to '1', s becomes "001001". The longest substrings with identical characters are s[0..1] and s[3..4].
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s consists only of '0' and '1'.
// 	0 <= numOps <= n
//

class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        int left = 1, right = n;

        auto canAchieve = [&](int maxLen) {
            int count = 0;
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                int len = j - i;
                count += len / (maxLen + 1);
                i = j;
            }
            return count <= numOps;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;            
    }
};
