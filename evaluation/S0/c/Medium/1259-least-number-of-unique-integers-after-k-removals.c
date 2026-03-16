// Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
//
// Example:
// Input: arr = [5,5,4], k = 1
// Output: 1
// Explanation: Remove the single 4, only 5 is left.
//
// Constraints:
// 1 <= arr.length <= 10^5
// 	1 <= arr[i] <= 10^9
// 	0 <= k <= arr.length
//

int findLeastNumOfUniqueInts(int* arr, int arrSize, int k){


    int freq[100001] = {0};
    for (int i = 0; i < arrSize; i++) {
        freq[arr[i]]++;
    }

    int countFreq[100001] = {0};
    for (int i = 0; i < 100001; i++) {
        if (freq[i] > 0) {
            countFreq[freq[i]]++;
        }
    }

    int uniqueCount = 0;
    for (int i = 1; i <= arrSize && k > 0; i++) {
        while (countFreq[i] > 0 && k >= i) {
            k -= i;
            countFreq[i]--;
        }
    }

    for (int i = 1; i <= arrSize; i++) {
        uniqueCount += countFreq[i];
    }

    return uniqueCount;
}
