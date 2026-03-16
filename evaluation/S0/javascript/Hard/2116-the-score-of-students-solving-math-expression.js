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

/**
 * @param {string} s
 * @param {number[]} answers
 * @return {number}
 */
var scoreOfStudents = function(s, answers) {
    const MOD = 1000;
    const tokens = [];
    for (let i = 0; i < s.length; i += 1) { 
        if (s[i] === '+' || s[i] === '*') {
            tokens.push(s[i]);
        }
        else {
            tokens.push(parseInt(s[i], 10));
        }
    }
    const n = (tokens.length + 1) / 2;
    const dp = new Array(n).fill(0).map(() => new Array(n).fill(0).map(() => new Set()));
    for (let i = 0; i < n; i += 1) {
        dp[i][i].add(tokens[2 * i]);
    }
    for (let length = 2; length <= n; length += 1) {
        for (let i = 0; i <= n - length; i += 1) {
            const j = i + length - 1;
            for (let k = i; k < j; k += 1) {
                const operator = tokens[2 * k + 1];
                for (const left of dp[i][k]) {
                    for (const right of dp[k + 1][j]) {
                        let value;
                        if (operator === '+') {
                            value = (left + right) % MOD;
                        }
                        else {
                            value = (left * right) % MOD;
                        }
                        dp[i][j].add(value);
                    }
                }
            }
        }
    }
    const correctAnswer = [...dp[0][n - 1]][0];
    let score = 0;
    for (const answer of answers) {
        if (answer === correctAnswer) {
            score += 5;
        }
        else if (dp[0][n - 1].has(answer)) {
            score += 2;
        }
    }
    return score;   
};
