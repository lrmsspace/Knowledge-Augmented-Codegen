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

bool judgePoint24(int* cards, int cardsSize) {
    double nums[4];
    for (int i = 0; i < 4; ++i) nums[i] = (double)cards[i];

    const double EPS = 1e-6;
    const double TARGET = 24.0;

    int backtrack(double* arr, int n) {
        if (n == 1) {
            return fabs(arr[0] - TARGET) < EPS;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    double next[4];
                    int idx = 0;
                    for (int k = 0; k < n; ++k) {
                        if (k != i && k != j) {
                            next[idx++] = arr[k];
                        }
                    }
                    for (int op = 0; op < 6; ++op) {
                        if (op < 4 || arr[j] != 0) { // avoid division by zero
                            switch (op) {
                                case 0: next[idx] = arr[i] + arr[j]; break;
                                case 1: next[idx] = arr[i] - arr[j]; break;
                                case 2: next[idx] = arr[i] * arr[j]; break;
                                case 3: next[idx] = arr[i] / arr[j]; break;
                                case 4: next[idx] = arr[j] - arr[i]; break;
                                case 5: next[idx] = arr[j] / arr[i]; break;
                            }
                            if (backtrack(next, n - 1)) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        return 0;
    }

    return backtrack(nums, 4);      
}
