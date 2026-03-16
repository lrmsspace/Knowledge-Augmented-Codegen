// Source: https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. In one operation, you can add or subtract 1 from any element of nums.
//
// Return the minimum number of operations to make all elements of nums divisible by 3.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 3
//
// Explanation:
//
// All array elements can be made divisible by 3 using 3 operations:
//
//
// 	Subtract 1 from 1.
// 	Add 1 to 2.
// 	Subtract 1 from 4.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

int minimumOperations(int* nums, int numsSize) {
    int countRemainder1 = 0;
    int countRemainder2 = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 3 == 1) {
            countRemainder1++;
        } else if (nums[i] % 3 == 2) {
            countRemainder2++;
        }
    }
    int operations = 0;
    int minCount = countRemainder1 < countRemainder2 ? countRemainder1 : countRemainder2;
    operations += minCount;
    countRemainder1 -= minCount;
    countRemainder2 -= minCount;
    operations += countRemainder1 * 1; // Each remainder 1 needs 1 operation
    operations += countRemainder2 * 1; // Each remainder 2 needs 1 operation
    return operations;      
}
