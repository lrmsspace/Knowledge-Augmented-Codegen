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

/**
 * @param {string} answerKey
 * @param {number} k
 * @return {number}
 */
var maxConsecutiveAnswers = function(answerKey, k) {
    const maxConsecutiveChar = (char) => {
        let left = 0;
        let maxLength = 0;
        let count = 0;
        for (let right = 0; right < answerKey.length; right++) {
            if (answerKey[right] !== char) {
                count++;
            }
            while (count > k) {
                if (answerKey[left] !== char) {
                    count--;
                }
                left++;
            }
            maxLength = Math.max(maxLength, right - left + 1);
        }
        return maxLength;
    };

    return Math.max(maxConsecutiveChar('T'), maxConsecutiveChar('F'));
};
