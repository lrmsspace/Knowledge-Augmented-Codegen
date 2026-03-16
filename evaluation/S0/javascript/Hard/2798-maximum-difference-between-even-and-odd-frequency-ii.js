// Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:
//
//
// 	subs has a size of at least k.
// 	Character a has an odd frequency in subs.
// 	Character b has a non-zero even frequency in subs.
//
//
// Return the maximum difference.
//
// Note that subs can contain more than 2 distinct characters.
//
// Example:
// Input: s = "12233", k = 4
//
// Output: -1
//
// Explanation:
//
// For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.
//
// Constraints:
// 3 <= s.length <= 3 * 104
// 	s consists only of digits '0' to '4'.
// 	The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
// 	1 <= k <= s.length
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var maxDifference = function(s, k) {
    const n = s.length;
    let maxDiff = -1;
    for (let a = 0; a <= 4; a++) {
        for (let b = 0; b <= 4; b++) {
            if (a === b) continue;
            let freqA = 0;
            let freqB = 0;
            let left = 0;
            for (let right = 0; right < n; right++) {
                if (s[right] === a.toString()) freqA++;
                if (s[right] === b.toString()) freqB++;
                while (right - left + 1 > k) {
                    if (s[left] === a.toString()) freqA--;
                    if (s[left] === b.toString()) freqB--;
                    left++;
                }
                if (right - left + 1 >= k && freqA % 2 === 1 && freqB % 2 === 0 && freqB > 0) {
                    maxDiff = Math.max(maxDiff, freqA - freqB);
                }
            }
        }
    }
    return maxDiff;
};
