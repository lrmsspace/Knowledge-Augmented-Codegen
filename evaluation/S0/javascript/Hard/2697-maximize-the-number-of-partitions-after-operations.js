// Source: https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and an integer k.
//
// First, you are allowed to change at most one index in s to another lowercase English letter.
//
// After that, do the following partitioning operation until s is empty:
//
//
// 	Choose the longest prefix of s containing at most k distinct characters.
// 	Delete the prefix from s and increase the number of partitions by one. The remaining characters (if any) in s maintain their initial order.
//
//
// Return an integer denoting the maximum number of resulting partitions after the operations by optimally choosing at most one index to change.
//
// Example:
// Input: s = "accca", k = 2
//
// Output: 3
//
// Explanation:
//
// The optimal way is to change s[2] to something other than a and c, for example, b. then it becomes "acbca".
//
// Then we perform the operations:
//
//
// 	The longest prefix containing at most 2 distinct characters is "ac", we remove it and s becomes "bca".
// 	Now The longest prefix containing at most 2 distinct characters is "bc", so we remove it and s becomes "a".
// 	Finally, we remove "a" and s becomes empty, so the procedure ends.
//
//
// Doing the operations, the string is divided into 3 partitions, so the answer is 3.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists only of lowercase English letters.
// 	1 <= k <= 26
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var maxPartitionsAfterOperations = function(s, k) {
    const n = s.length;
    const count = Array(26).fill(0);
    let distinctCount = 0;
    let partitions = 0;
    for (let i = 0; i < n; i++) {
        const charIndex = s.charCodeAt(i) - 97;
        if (count[charIndex] === 0) {
            distinctCount++;
        }
        count[charIndex]++;
        if (distinctCount > k) {
            partitions++;
            count.fill(0);
            distinctCount = 0;
            i--;
        }
    }
    if (distinctCount > 0) {
        partitions++;
    }
    return partitions;
};
