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

int maxConsecutiveAnswers(char* answerKey, int k) {
    int maxLen = 0;
    int countT = 0, countF = 0;
    int left = 0;
    int n = strlen(answerKey);

    for (int right = 0; right < n; right++) {
        if (answerKey[right] == 'T') {
            countT++;
        } else {
            countF++;
        }

        while (fmin(countT, countF) > k) {
            if (answerKey[left] == 'T') {
                countT--;
            } else {
                countF--;
            }
            left++;
        }

        maxLen = fmax(maxLen, right - left + 1);
    }

    return maxLen;      
}
