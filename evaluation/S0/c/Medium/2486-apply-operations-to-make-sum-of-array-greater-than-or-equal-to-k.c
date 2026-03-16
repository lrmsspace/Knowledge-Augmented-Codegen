// Source: https://leetcode.com/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer k. Initially, you have an array nums = [1].
//
// You can perform any of the following operations on the array any number of times (possibly zero):
//
//
// 	Choose any element in the array and increase its value by 1.
// 	Duplicate any element in the array and add it to the end of the array.
//
//
// Return the minimum number of operations required to make the sum of elements of the final array greater than or equal to k.
//
// Example:
// Input: k = 11
//
// Output: 5
//
// Explanation:
//
// We can do the following operations on the array nums = [1]:
//
//
// 	Increase the element by 1 three times. The resulting array is nums = [4].
// 	Duplicate the element two times. The resulting array is nums = [4,4,4].
//
//
// The sum of the final array is 4 + 4 + 4 = 12 which is greater than or equal to k = 11.
// The total number of operations performed is 3 + 2 = 5.
//
// Constraints:
// 1 <= k <= 105
//

int minOperations(int k) {
    int operations = 0;
    int current_sum = 1;
    int element_value = 1;
    int element_count = 1;

    while (current_sum < k) {
        if (current_sum + element_value <= k) {
            current_sum += element_value;
            element_count++;
            operations++;
        } else {
            element_value++;
            current_sum += element_count;
            operations++;
        }
    }

    return operations;      
}
