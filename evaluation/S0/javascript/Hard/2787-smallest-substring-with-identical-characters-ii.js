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

/**
 * @param {string} s
 * @param {number} numOps
 * @return {number}
 */
var minLength = function(s, numOps) {
    const n = s.length;
    const prefixZeros = Array(n + 1).fill(0);
    const prefixOnes = Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixZeros[i + 1] = prefixZeros[i] + (s[i] === '0' ? 1 : 0);
        prefixOnes[i + 1] = prefixOnes[i] + (s[i] === '1' ? 1 : 0);
    }
    const canAchieve = (length) => {    
        for (let start = 0; start <= n - length; start++) {
            const end = start + length - 1;
            const zerosInSubstring = prefixZeros[end + 1] - prefixZeros[start];
            const onesInSubstring = prefixOnes[end + 1] - prefixOnes[start];
            if (Math.min(zerosInSubstring, onesInSubstring) <= numOps) {
                return true;
            }
        }
        return false;
    }
    let left = 1;
    let right = n;
    let result = n;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (canAchieve(mid)) {
            result = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return result;
};
