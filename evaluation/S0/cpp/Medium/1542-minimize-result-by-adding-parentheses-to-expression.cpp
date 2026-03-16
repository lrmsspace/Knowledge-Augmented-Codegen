// Source: https://leetcode.com/problems/minimize-result-by-adding-parentheses-to-expression/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string expression of the form "<num1>+<num2>" where <num1> and <num2> represent positive integers.
//
// Add a pair of parentheses to expression such that after the addition of parentheses, expression is a valid mathematical expression and evaluates to the smallest possible value. The left parenthesis must be added to the left of '+' and the right parenthesis must be added to the right of '+'.
//
// Return expression after adding a pair of parentheses such that expression evaluates to the smallest possible value. If there are multiple answers that yield the same result, return any of them.
//
// The input has been generated such that the original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
//
// Example:
// Input: expression = "247+38"
// Output: "2(47+38)"
// Explanation: The expression evaluates to 2 * (47 + 38) = 2 * 85 = 170.
// Note that "2(4)7+38" is invalid because the right parenthesis must be to the right of the '+'.
// It can be shown that 170 is the smallest possible value.
//
// Constraints:
// 3 <= expression.length <= 10
// 	expression consists of digits from '1' to '9' and '+'.
// 	expression starts and ends with digits.
// 	expression contains exactly one '+'.
// 	The original value of expression, and the value of expression after adding any pair of parentheses that meets the requirements fits within a signed 32-bit integer.
//

class Solution {
public:
    string minimizeResult(string expression) {
        int plusPos = expression.find('+');
        string num1 = expression.substr(0, plusPos);
        string num2 = expression.substr(plusPos + 1);

        int minValue = INT_MAX;
        string result;

        for (int i = 0; i < num1.size(); ++i) {
            for (int j = 1; j <= num2.size(); ++j) {
                int leftMultiplier = (i == 0) ? 1 : stoi(num1.substr(0, i));
                int middleSum = stoi(num1.substr(i)) + stoi(num2.substr(0, j));
                int rightMultiplier = (j == num2.size()) ? 1 : stoi(num2.substr(j));

                int currentValue = leftMultiplier * middleSum * rightMultiplier;

                if (currentValue < minValue) {
                    minValue = currentValue;
                    result = (i == 0 ? "" : num1.substr(0, i)) + "(" +
                             num1.substr(i) + "+" + num2.substr(0, j) + ")" +
                             (j == num2.size() ? "" : num2.substr(j));
                }
            }
        }

        return result;          
    }
};
