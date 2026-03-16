// Source: https://leetcode.com/problems/maximum-equal-frequency/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers, return the longest possible length of an array prefix of nums, such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.
//
// If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).
//
// Example:
// Input: nums = [2,2,1,1,5,3,3,5]
// Output: 7
// Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4] = 5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int maxEqualFreq(int* nums, int numsSize) {
    int count[100001] = {0};      /* count[num] = frequency of num */
    int freqCount[100001] = {0};  /* freqCount[f] = how many numbers have frequency f */
    int maxFreq = 0;              /* maximum frequency observed so far */
    int result = 0;

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        int oldFreq = count[num];
        int newFreq = oldFreq + 1;
        count[num] = newFreq;

        freqCount[oldFreq]--;
        freqCount[newFreq]++;
        if (newFreq > maxFreq) {
            maxFreq = newFreq;
        }

        int valid = 0;
        if (maxFreq == 1) {
            valid = 1; /* all numbers appear once */
        } else if (freqCount[maxFreq] * maxFreq + freqCount[maxFreq - 1] * (maxFreq - 1) == i + 1 &&
                   freqCount[maxFreq] == 1) {
            valid = 1; /* one number has maxFreq, others have maxFreq - 1 */
        } else if (freqCount[maxFreq] * maxFreq + 1 == i + 1 &&
                   freqCount[1] == 1) {
            valid = 1; /* one number has frequency 1, others have maxFreq */
        }

        if (valid) {
            result = i + 1;
        }
    }

    return result;      
}
