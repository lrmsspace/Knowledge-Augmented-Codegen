// Source: https://leetcode.com/problems/maximize-the-confusion-of-an-exam/   |   Difficulty: Medium
//
// Problem Description:
// A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false. He wants to confuse the students by maximizing the number of consecutive questions with the same answer (multiple trues or multiple falses in a row).
//
// You are given a string answerKey, where answerKey[i] is the original answer to the ith question. In addition, you are given an integer k, the maximum number of times you may perform the following operation:
//
//
// 	Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
//
//
// Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.
//
// Example:
// Input: answerKey = "TTFF", k = 2
// Output: 4
// Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
// There are four consecutive 'T's.
//
// Constraints:
// n == answerKey.length
// 	1 <= n <= 5 * 104
// 	answerKey[i] is either 'T' or 'F'
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} answerKey
 * @param {number} k
 * @return {number}
 */
var maxConsecutiveAnswers = function(answerKey, k) {
    const n = answerKey.length;
    let maxLength = 0;

    const countMaxConsecutive = (charToReplace) => {
        let left = 0;
        let replacements = 0;
        for (let right = 0; right < n; right++) {
            if (answerKey[right] === charToReplace) {
                replacements++;
            }
            while (replacements > k) {
                if (answerKey[left] === charToReplace) {
                    replacements--;
                }
                left++;
            }
            maxLength = Math.max(maxLength, right - left + 1);
        }
    };

    countMaxConsecutive('T'); // Max consecutive 'F's by replacing 'T's
    countMaxConsecutive('F'); // Max consecutive 'T's by replacing 'F's

    return maxLength;
};
