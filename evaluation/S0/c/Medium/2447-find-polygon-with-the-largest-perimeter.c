// Source: https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// A polygon is a closed plane figure that has at least 3 sides. The longest side of a polygon is smaller than the sum of its other sides.
//
// Conversely, if you have k (k >= 3) positive real numbers a1, a2, a3, ..., ak where a1 <= a2 <= a3 <= ... <= ak and a1 + a2 + a3 + ... + ak-1 > ak, then there always exists a polygon with k sides whose lengths are a1, a2, a3, ..., ak.
//
// The perimeter of a polygon is the sum of lengths of its sides.
//
// Return the largest possible perimeter of a polygon whose sides can be formed from nums, or -1 if it is not possible to create a polygon.
//
// Example:
// Input: nums = [5,5,5]
// Output: 15
// Explanation: The only possible polygon that can be made from nums has 3 sides: 5, 5, and 5. The perimeter is 5 + 5 + 5 = 15.
//
// Constraints:
// 3 <= n <= 105
// 	1 <= nums[i] <= 109
//

long long largestPerimeter(int* nums, int numsSize) {
    // Sort the array in descending order
    qsort(nums, numsSize, sizeof(int), (int (*)(const void *, const void *)) (int (*)(const int *, const int *)) [](const int *a, const int *b) {
        return (*b) - (*a);
    });

    // Iterate through the sorted array to find the first valid triangle
    for (int i = 0; i < numsSize - 2; i++) {
        if (nums[i] < nums[i + 1] + nums[i + 2]) {
            return (long long)(nums[i] + nums[i + 1] + nums[i + 2]);
        }
    }

    // If no valid triangle is found, return -1
    return -1;      
}
