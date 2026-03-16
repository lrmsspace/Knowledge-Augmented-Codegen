// Source: https://leetcode.com/problems/broken-calculator/   |   Difficulty: Medium
//
// Problem Description:
// There is a broken calculator that has the integer startValue on its display initially. In one operation, you can:
//
//
// 	multiply the number on display by 2, or
// 	subtract 1 from the number on display.
//
//
// Given two integers startValue and target, return the minimum number of operations needed to display target on the calculator.
//
// Example:
// Input: startValue = 2, target = 3
// Output: 2
// Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.
//
// Constraints:
// 1 <= startValue, target <= 109
//

int brokenCalc(int startValue, int target) {
    int operations = 0;
    while (target > startValue) {
        operations++;
        if (target % 2 == 1) {
            target++;
        } else {
            target /= 2;
        }
    }
    return operations + (startValue - target);      
}
