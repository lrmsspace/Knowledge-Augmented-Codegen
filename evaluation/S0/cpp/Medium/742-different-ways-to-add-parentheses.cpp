// Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
//
// The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
//
// Example:
// Input: expression = "2-1-1"
// Output: [0,2]
// Explanation:
// ((2-1)-1) = 0 
// (2-(1-1)) = 2
//
// Constraints:
// 1 <= expression.length <= 20
// 	expression consists of digits and the operator '+', '-', and '*'.
// 	All the integer values in the input expression are in the range [0, 99].
// 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
//

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> results;
        for (int i = 0; i < expression.size(); ++i) {
            char c = expression[i];
            if (c == '+' || c == '-' || c == '*') {
                string leftExpr = expression.substr(0, i);
                string rightExpr = expression.substr(i + 1);

                vector<int> leftResults = diffWaysToCompute(leftExpr);
                vector<int> rightResults = diffWaysToCompute(rightExpr);

                for (int left : leftResults) {
                    for (int right : rightResults) {
                        int computedValue = 0;
                        if (c == '+') {
                            computedValue = left + right;
                        } else if (c == '-') {
                            computedValue = left - right;
                        } else if (c == '*') {
                            computedValue = left * right;
                        }
                        results.push_back(computedValue);
                    }
                }
            }
        }

        // Base case: if the expression is a number, convert it to int and return
        if (results.empty()) {
            results.push_back(stoi(expression));
        }

        return results;         
    }
};
