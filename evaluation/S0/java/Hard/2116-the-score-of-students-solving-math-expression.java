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

class Solution {
    public int scoreOfStudents(String s, int[] answers) {
        String[] tokens = s.split("(?=[+*])|(?<=[+*])");
        int n = tokens.length;
        int correctAnswer = evaluate(tokens, true);

        boolean[][] dp = new boolean[n][1001];
        for (int i = 0; i < n; i += 2) {
            int num = Integer.parseInt(tokens[i]);
            dp[i][num] = true;
        }

        for (int length = 3; length <= n; length += 2) {
            for (int i = 0; i <= n - length; i += 2) {
                int j = i + length - 1;
                for (int k = i + 1; k < j; k += 2) {
                    for (int left = 0; left <= 1000; left++) {
                        if (!dp[i][left]) continue;
                        for (int right = 0; right <= 1000; right++) {
                            if (!dp[k + 1][right]) continue;
                            int result = tokens[k].equals("+") ? left + right : left * right;
                            if (result <= 1000) {
                                dp[i][result] = true;
                            }
                        }
                    }
                }
            }
        }

        int totalScore = 0;
        for (int answer : answers) {
            if (answer == correctAnswer) {
                totalScore += 5;
            } else if (answer >= 0 && answer <= 1000 && dp[0][answer]) {
                totalScore += 2;
            }
        }

        return totalScore;          
    }
}
