// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of n positive integers.
//
// The array nums is called alternating if:
//
//
// 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
// 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
//
//
// In one operation, you can choose an index i and change nums[i] into any positive integer.
//
// Return the minimum number of operations required to make the array alternating.
//
// Example:
// Input: nums = [3,1,3,2,4,3]
// Output: 3
// Explanation:
// One way to make the array alternating is by converting it to [3,1,3,1,3,1].
// The number of operations required in this case is 3.
// It can be proven that it is not possible to make the array alternating in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int minimumOperations(int* nums, int numsSize) {
    int evenCount[100001] = {0};
    int oddCount[100001] = {0};
    
    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            evenCount[nums[i]]++;
        } else {
            oddCount[nums[i]]++;
        }
    }
    
    int evenMax1 = 0, evenMax2 = 0, evenNum1 = -1, evenNum2 = -1;
    for (int i = 1; i <= 100000; i++) {
        if (evenCount[i] > evenMax1) {
            evenMax2 = evenMax1;
            evenNum2 = evenNum1;
            evenMax1 = evenCount[i];
            evenNum1 = i;
        } else if (evenCount[i] > evenMax2) {
            evenMax2 = evenCount[i];
            evenNum2 = i;
        }
    }
    
    int oddMax1 = 0, oddMax2 = 0, oddNum1 = -1, oddNum2 = -1;
    for (int i = 1; i <= 100000; i++) {
        if (oddCount[i] > oddMax1) {
            oddMax2 = oddMax1;
            oddNum2 = oddNum1;
            oddMax1 = oddCount[i];
            oddNum1 = i;
        } else if (oddCount[i] > oddMax2) {
            oddMax2 = oddCount[i];
            oddNum2 = i;
        }
    }
    
    if (evenNum1 != oddNum1) {
        return numsSize - (evenMax1 + oddMax1);
    } else {
        return numsSize - fmax(evenMax1 + oddMax2, evenMax2 + oddMax1);
    }       
}
