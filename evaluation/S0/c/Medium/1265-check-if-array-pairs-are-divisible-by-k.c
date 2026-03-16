// Source: https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr of even length n and an integer k.
//
// We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
//
// Return true If you can find a way to do that or false otherwise.
//
// Example:
// Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
// Output: true
// Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
//
// Constraints:
// arr.length == n
// 	1 <= n <= 105
// 	n is even.
// 	-109 <= arr[i] <= 109
// 	1 <= k <= 105
//

bool canArrange(int* arr, int arrSize, int k) {
    int* count = (int*)calloc(k, sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        int rem = arr[i] % k;
        if (rem < 0) rem += k;
        count[rem]++;
    }

    if (count[0] % 2 != 0) {
        free(count);
        return false;
    }

    for (int i = 1; i <= k / 2; i++) {
        if (count[i] != count[k - i]) {
            free(count);
            return false;
        }
    }

    free(count);
    return true;        
}
