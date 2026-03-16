// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In one operation, you can choose any two distinct indices i and j where 0 <= i, j < nums.length and:
//
//
// 	set nums[i] = nums[i] + 2 and
// 	set nums[j] = nums[j] - 2.
//
//
// Two arrays are considered to be similar if the frequency of each element is the same.
//
// Return the minimum number of operations required to make nums similar to target. The test cases are generated such that nums can always be similar to target.
//
// Example:
// Input: nums = [8,12,6], target = [2,14,10]
// Output: 2
// Explanation: It is possible to make nums similar to target in two operations:
// - Choose i = 0 and j = 2, nums = [10,12,4].
// - Choose i = 1 and j = 2, nums = [10,14,2].
// It can be shown that 2 is the minimum number of operations needed.
//
// Constraints:
// n == nums.length == target.length
// 	1 <= n <= 105
// 	1 <= nums[i], target[i] <= 106
// 	It is possible to make nums similar to target.
//

long long makeSimilar(int* nums, int numsSize, int* target, int targetSize) {
    long long res = 0;
    long long evenDiff = 0, oddDiff = 0;

    /* Separate even and odd numbers, sort them, and calculate the total differences */
    int *numsEven = (int*)malloc(numsSize * sizeof(int));
    int *numsOdd = (int*)malloc(numsSize * sizeof(int));
    int *targetEven = (int*)malloc(targetSize * sizeof(int));
    int *targetOdd = (int*)malloc(targetSize * sizeof(int));
    if (!numsEven || !numsOdd || !targetEven || !targetOdd) {
        free(numsEven); free(numsOdd); free(targetEven); free(targetOdd);
        return -1; /* allocation failure */
    }

    int neven = 0, nodd = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] % 2 == 0) numsEven[neven++] = nums[i];
        else numsOdd[nodd++] = nums[i];
    }
    int teven = 0, todd = 0;
    for (int i = 0; i < targetSize; ++i) {
        if (target[i] % 2 == 0) targetEven[teven++] = target[i];
        else targetOdd[todd++] = target[i];
    }

    qsort(numsEven, neven, sizeof(int), cmpInt);
    qsort(numsOdd, nodd, sizeof(int), cmpInt);
    qsort(targetEven, teven, sizeof(int), cmpInt);
    qsort(targetOdd, todd, sizeof(int), cmpInt);

    for (int i = 0; i < neven; ++i) {
        evenDiff += llabs((long long)numsEven[i] - (long long)targetEven[i]);
    }
    for (int i = 0; i < nodd; ++i) {
        oddDiff += llabs((long long)numsOdd[i] - (long long)targetOdd[i]);
    }

    /* Each operation changes two numbers by 2, so divide total difference by 4 */
    res = (evenDiff + oddDiff) / 4;

    free(numsEven); free(numsOdd); free(targetEven); free(targetOdd);
    return res;     
}
