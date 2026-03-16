// Source: https://leetcode.com/problems/smallest-substring-with-identical-characters-i/   |   Difficulty: Hard
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
// 1 <= n == s.length <= 1000
// 	s consists only of '0' and '1'.
// 	0 <= numOps <= n
//

int minLength(char* s, int numOps) {
    int n = strlen(s);
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        int needOps = n; /* larger than any possible needed ops */
        /* check for '0' */
        {
            int l = 0, r = 0, count1 = 0, minOps = n;
            while (r < n) {
                if (s[r] == '1') count1++;
                if (r - l + 1 > mid) {
                    if (s[l] == '1') count1--;
                    l++;
                }
                if (r - l + 1 == mid) {
                    if (count1 < minOps) minOps = count1;
                }
                r++;
            }
            if (minOps < needOps) needOps = minOps;
        }
        /* check for '1' */
        {
            int l = 0, r = 0, count0 = 0, minOps = n;
            while (r < n) {
                if (s[r] == '0') count0++;
                if (r - l + 1 > mid) {
                    if (s[l] == '0') count0--;
                    l++;
                }
                if (r - l + 1 == mid) {
                    if (count0 < minOps) minOps = count0;
                }
                r++;
            }
            if (minOps < needOps) needOps = minOps;
        }
        if (needOps <= numOps) right = mid;
        else left = mid + 1;
    }
    return left;        
}
