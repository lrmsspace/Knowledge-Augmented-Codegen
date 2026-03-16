// Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct integers.
//
// In one operation, you can swap any two adjacent elements in the array.
//
// An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
//
// Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
//
// If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
//
// Example:
// Input: nums = [2,4,6,5,7]
//
// Output: 3
//
// Explanation:
//
// Swapping 5 and 6, the array becomes [2,4,5,6,7]
//
// Swapping 5 and 4, the array becomes [2,5,4,6,7]
//
// Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements in nums are distinct.
//

int minSwaps(int* nums, int numsSize) {
    int evenCount = 0;
    int oddCount = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    if (abs(evenCount - oddCount) > 1) {
        return -1;
    }

    int swapsEvenStart = 0;
    int swapsOddStart = 0;
    int evenIndex = 0;
    int oddIndex = 0;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            if (nums[i] % 2 != 0) {
                swapsEvenStart += abs(i - evenIndex);
                evenIndex += 2;
            }
        } else {
            if (nums[i] % 2 == 0) {
                swapsEvenStart += abs(i - oddIndex);
                oddIndex += 2;
            }
        }
    }

    evenIndex = 1;
    oddIndex = 1;

    for (int i = 0; i < numsSize; i++) {
        if (i % 2 == 0) {
            if (nums[i] % 2 == 0) {
                swapsOddStart += abs(i - oddIndex);
                oddIndex += 2;
            }
        } else {
            if (nums[i] % 2 != 0) {
                swapsOddStart += abs(i - evenIndex);
                evenIndex += 2;
            }
        }
    }

    if (evenCount > oddCount) {
        return swapsEvenStart / 2;
    } else if (oddCount > evenCount) {
        return swapsOddStart / 2;
    } else {
        return fmin(swapsEvenStart, swapsOddStart) / 2;
    }       
}
