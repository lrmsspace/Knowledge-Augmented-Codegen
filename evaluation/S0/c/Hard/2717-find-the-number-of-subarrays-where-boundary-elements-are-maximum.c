// Source: https://leetcode.com/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums.
//
// Return the number of subarrays of nums, where the first and the last elements of the subarray are equal to the largest element in the subarray.
//
// Example:
// Input: nums = [1,4,3,3,2]
//
// Output: 6
//
// Explanation:
//
// There are 6 subarrays which have the first and the last elements equal to the largest element of the subarray:
//
//
// 	subarray [1,4,3,3,2], with its largest element 1. The first element is 1 and the last element is also 1.
// 	subarray [1,4,3,3,2], with its largest element 4. The first element is 4 and the last element is also 4.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
// 	subarray [1,4,3,3,2], with its largest element 2. The first element is 2 and the last element is also 2.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
//
//
// Hence, we return 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

long long numberOfSubarrays(int* nums, int numsSize) {
    long long result = 0;
    int count = 1;

    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == nums[i - 1]) {
            count++;
        } else {
            result += ((long long)count * (count + 1)) / 2;
            count = 1;
        }
    }
    result += ((long long)count * (count + 1)) / 2;

    return result;      
}
