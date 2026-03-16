// Source: https://leetcode.com/problems/expression-add-operators/   |   Difficulty: Hard
//
// Problem Description:
// Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
//
// Note that operands in the returned expressions should not contain leading zeros.
//
// Note that a number can contain multiple digits.
//
// Example:
// Input: num = "123", target = 6
// Output: ["1*2*3","1+2+3"]
// Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
//
// Constraints:
// 1 <= num.length <= 10
// 	num consists of only digits.
// 	-231 <= target <= 231 - 1
//

class Solution {
    public List<String> addOperators(String num, int target) {
        List<String> result = new ArrayList<>();
        backtrack(result, "", num, target, 0, 0, 0);
        return result;          
    }
}
