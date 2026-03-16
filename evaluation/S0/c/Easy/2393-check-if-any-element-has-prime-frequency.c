// Source: https://leetcode.com/problems/check-if-any-element-has-prime-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// Return true if the frequency of any element of the array is prime, otherwise, return false.
//
// The frequency of an element x is the number of times it occurs in the array.
//
// A prime number is a natural number greater than 1 with only two factors, 1 and itself.
//
// Example:
// Input: nums = [1,2,3,4,5,4]
//
// Output: true
//
// Explanation:
//
// 4 has a frequency of two, which is a prime number.
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
//

bool checkPrimeFrequency(int* nums, int numsSize) {
    int frequency[101] = {0};
    for (int i = 0; i < numsSize; i++) {
        frequency[nums[i]]++;
    }

    for (int i = 0; i < 101; i++) {
        int freq = frequency[i];
        if (freq > 1) {
            bool isPrime = true;
            for (int j = 2; j * j <= freq; j++) {
                if (freq % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                return true;
            }
        }
    }
    return false;       
}
