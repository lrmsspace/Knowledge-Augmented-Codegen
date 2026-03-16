// Source: https://leetcode.com/problems/count-elements-with-maximum-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// Return the total frequencies of elements in nums such that those elements all have the maximum frequency.
//
// The frequency of an element is the number of occurrences of that element in the array.
//
// Example:
// Input: nums = [1,2,2,3,1,4]
// Output: 4
// Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
// So the number of elements in the array with maximum frequency is 4.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxFrequencyElements(int* nums, int numsSize) {
    int frequency[101] = {0}; // Frequency array to count occurrences of numbers from 1 to 100
    int maxFreq = 0; // Variable to keep track of the maximum frequency

    // Count the frequency of each number in the input array
    for (int i = 0; i < numsSize; i++) {
        frequency[nums[i]]++;
        if (frequency[nums[i]] > maxFreq) {
            maxFreq = frequency[nums[i]]; // Update max frequency if current number's frequency is higher
        }
    }

    int count = 0; // Variable to count the total frequencies of elements with maximum frequency

    // Sum up the frequencies of elements that have the maximum frequency
    for (int i = 1; i <= 100; i++) {
        if (frequency[i] == maxFreq) {
            count += frequency[i]; // Add the frequency of this element to the count
        }
    }

    return count; // Return the total frequencies of elements with maximum frequency        
}
