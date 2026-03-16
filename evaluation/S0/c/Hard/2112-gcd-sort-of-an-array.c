// Source: https://leetcode.com/problems/gcd-sort-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums, and you can perform the following operation any number of times on nums:
//
//
// 	Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
//
//
// Return true if it is possible to sort nums in non-decreasing order using the above swap method, or false otherwise.
//
// Example:
// Input: nums = [7,21,3]
// Output: true
// Explanation: We can sort [7,21,3] by performing the following operations:
// - Swap 7 and 21 because gcd(7,21) = 7. nums = [21,7,3]
// - Swap 21 and 3 because gcd(21,3) = 3. nums = [3,7,21]
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	2 <= nums[i] <= 105
//

bool gcdSort(int* nums, int numsSize) {
    int maxVal = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    int *parent = (int*)malloc((maxVal + 1) * sizeof(int));
    if (!parent) return false;
    for (int i = 0; i <= maxVal; ++i) parent[i] = i;

    /* union-find functions */
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unionSet(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) parent[px] = py;
    }

    /* build union-find structure based on prime factors */
    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        for (int f = 2; f * f <= val; ++f) {
            if (val % f == 0) {
                unionSet(val, f);
                while (val % f == 0) val /= f;
            }
        }
        if (val > 1) {
            unionSet(nums[i], val);
        }
    }

    /* check if sorting is possible */
    int *sortedNums = (int*)malloc(numsSize * sizeof(int));
    if (!sortedNums) { free(parent); return false; }
    memcpy(sortedNums, nums, numsSize * sizeof(int));
    qsort(sortedNums, numsSize, sizeof(int), cmpInt);

    for (int i = 0; i < numsSize; ++i) {
        if (find(nums[i]) != find(sortedNums[i])) {
            free(parent);
            free(sortedNums);
            return false;
        }
    }

    free(parent);
    free(sortedNums);
    return true;        
}
