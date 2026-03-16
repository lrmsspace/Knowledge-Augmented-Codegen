// Source: https://leetcode.com/problems/find-if-digit-game-can-be-won/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of positive integers nums.
//
// Alice and Bob are playing a game. In the game, Alice can choose either all single-digit numbers or all double-digit numbers from nums, and the rest of the numbers are given to Bob. Alice wins if the sum of her numbers is strictly greater than the sum of Bob's numbers.
//
// Return true if Alice can win this game, otherwise, return false.
//
// Example:
// Input: nums = [1,2,3,4,10]
//
// Output: false
//
// Explanation:
//
// Alice cannot win by choosing either single-digit or double-digit numbers.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 99
//

bool canAliceWin(int* nums, int numsSize) {
    int single_digit_sum = 0;
    int double_digit_sum = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < 10) {
            single_digit_sum += nums[i];
        } else {
            double_digit_sum += nums[i];
        }
    }

    int total_sum = single_digit_sum + double_digit_sum;

    return (single_digit_sum > total_sum - single_digit_sum) || (double_digit_sum > total_sum - double_digit_sum);      
}
