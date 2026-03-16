// Source: https://leetcode.com/problems/find-greatest-common-divisor-of-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.
//
// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.
//
// Example:
// Input: nums = [2,5,6,9,10]
// Output: 2
// Explanation:
// The smallest number in nums is 2.
// The largest number in nums is 10.
// The greatest common divisor of 2 and 10 is 2.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
//

int findGCD(int* nums, int numsSize) {
    int min = nums[0];
    int max = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    
    // Function to compute GCD using Euclidean algorithm
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    return gcd(min, max);       
}
