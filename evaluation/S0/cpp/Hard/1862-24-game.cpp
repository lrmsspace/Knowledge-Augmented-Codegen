// Source: https://leetcode.com/problems/24-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
//
// You are restricted with the following rules:
//
//
// 	The division operator '/' represents real division, not integer division.
//
// 	
// 		For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
// 	
// 	
// 	Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
// 	
// 		For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
// 	
// 	
// 	You cannot concatenate numbers together
// 	
// 		For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
// 	
// 	
//
//
// Return true if you can get such expression that evaluates to 24, and false otherwise.
//
// Example:
// Input: cards = [4,1,8,7]
// Output: true
// Explanation: (8-4) * (7-1) = 24
//
// Constraints:
// cards.length == 4
// 	1 <= cards[i] <= 9
//

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        const double TARGET = 24.0;
        const double EPSILON = 1e-6;
        
        function<bool(vector<double>&)> dfs = [&](vector<double>& nums) {
            if (nums.size() == 1) {
                return fabs(nums[0] - TARGET) < EPSILON;
            }
            
            for (int i = 0; i < nums.size(); i++) {
                for (int j = 0; j < nums.size(); j++) {
                    if (i != j) {
                        vector<double> nextNums;
                        for (int k = 0; k < nums.size(); k++) {
                            if (k != i && k != j) {
                                nextNums.push_back(nums[k]);
                            }
                        }
                        
                        for (int op = 0; op < 4; op++) {
                            if (op < 2 && i > j) continue; // avoid duplicate calculations
                            
                            double a = nums[i], b = nums[j];
                            if (op == 0) nextNums.push_back(a + b);
                            else if (op == 1) nextNums.push_back(a * b);
                            else if (op == 2) nextNums.push_back(a - b);
                            else {
                                if (fabs(b) < EPSILON) continue; // avoid division by zero
                                nextNums.push_back(a / b);
                            }
                            
                            if (dfs(nextNums)) return true;
                            nextNums.pop_back();
                        }
                    }
                }
            }
            return false;
        };
        
        vector<double> nums(cards.begin(), cards.end());
        return dfs(nums);           
    }
};
