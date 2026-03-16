// Source: https://leetcode.com/problems/the-score-of-students-solving-math-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that contains digits 0-9, addition symbols '+', and multiplication symbols '*' only, representing a valid math expression of single digit numbers (e.g., 3+5*2). This expression was given to n elementary school students. The students were instructed to get the answer of the expression by following this order of operations:
//
//
// 	Compute multiplication, reading from left to right; Then,
// 	Compute addition, reading from left to right.
//
//
// You are given an integer array answers of length n, which are the submitted answers of the students in no particular order. You are asked to grade the answers, by following these rules:
//
//
// 	If an answer equals the correct answer of the expression, this student will be rewarded 5 points;
// 	Otherwise, if the answer could be interpreted as if the student applied the operators in the wrong order but had correct arithmetic, this student will be rewarded 2 points;
// 	Otherwise, this student will be rewarded 0 points.
//
//
// Return the sum of the points of the students.
//
// Example:
// Input: s = "7+3*1*2", answers = [20,13,42]
// Output: 7
// Explanation: As illustrated above, the correct answer of the expression is 13, therefore one student is rewarded 5 points: [20,13,42]
// A student might have applied the operators in this wrong order: ((7+3)*1)*2 = 20. Therefore one student is rewarded 2 points: [20,13,42]
// The points for the students are: [2,5,0]. The sum of the points is 2+5+0=7.
//
// Constraints:
// 3 <= s.length <= 31
// 	s represents a valid expression that contains only digits 0-9, '+', and '*' only.
// 	All the integer operands in the expression are in the inclusive range [0, 9].
// 	1 <= The count of all operators ('+' and '*') in the math expression <= 15
// 	Test data are generated such that the correct answer of the expression is in the range of [0, 1000].
// 	Test data are generated such that value never exceeds 109 in intermediate steps of multiplication.
// 	n == answers.length
// 	1 <= n <= 104
// 	0 <= answers[i] <= 1000
//

int scoreOfStudents(char* s, int* answers, int answersSize) {
    int n = 0;
    int nums[16];
    char ops[15];
    for (int i = 0; s[i]; ) {
        nums[n++] = s[i++] - '0';
        if (s[i]) ops[n - 1] = s[i++];
    }

    int dpMin[16][16], dpMax[16][16];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dpMin[i][j] = 1001;
            dpMax[i][j] = -1;
        }
        dpMin[i][i] = dpMax[i][i] = nums[i];
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                if (ops[k] == '+') {
                    if (dpMin[i][k] + dpMin[k + 1][j] < dpMin[i][j]) {
                        dpMin[i][j] = dpMin[i][k] + dpMin[k + 1][j];
                    }
                    if (dpMax[i][k] + dpMax[k + 1][j] > dpMax[i][j]) {
                        dpMax[i][j] = dpMax[i][k] + dpMax[k + 1][j];
                    }
                } else { // ops[k] == '*'
                    if (dpMin[i][k] * dpMin[k + 1][j] < dpMin[i][j]) {
                        dpMin[i][j] = dpMin[i][k] * dpMin[k + 1][j];
                    }
                    if (dpMax[i][k] * dpMax[k + 1][j] > dpMax[i][j]) {
                        dpMax[i][j] = dpMax[i][k] * dpMax[k + 1][j];
                    }
                }
            }
        }
    }

    int correctAnswer = dpMax[0][n - 1];

    int possibleAnswers[1001] = {0};
    for (int len = 2; len <= n; len++) {    
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                for (int left = dpMin[i][k]; left <= dpMax[i][k]; left++) {
                    for (int right = dpMin[k + 1][j]; right <= dpMax[k + 1][j]; right++) {
                        if (ops[k] == '+') {
                            int val = left + right;
                            if (val <= 1000) {
                                possibleAnswers[val] = 1;
                            }
                        } else { // ops[k] == '*'
                            long long val = (long long)left * right;
                            if (val <= 1000) {
                                possibleAnswers[val] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    int totalScore = 0;
    for (int i = 0; i < answersSize; i++) {
        if (answers[i] == correctAnswer) {
            totalScore += 5;
        } else if (answers[i] >= 0 && answers[i] <= 1000 && possibleAnswers[answers[i]]) {
            totalScore += 2;
        }
    }
    return totalScore;    
}
