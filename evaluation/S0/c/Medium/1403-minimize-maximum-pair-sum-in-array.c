// Source: https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/   |   Difficulty: Medium
//
// Problem Description:
// The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the largest pair sum in a list of pairs.
//
//
// 	For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
//
//
// Given an array nums of even length n, pair up the elements of nums into n / 2 pairs such that:
//
//
// 	Each element of nums is in exactly one pair, and
// 	The maximum pair sum is minimized.
//
//
// Return the minimized maximum pair sum after optimally pairing up the elements.
//
// Example:
// Input: nums = [3,5,2,3]
// Output: 7
// Explanation: The elements can be paired up into pairs (3,3) and (5,2).
// The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	n is even.
// 	1 <= nums[i] <= 105
//



int minPairSum(int* nums, int numsSize){
    // Counting sort
    int max_val = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }

    int count[max_val + 1];
    for (int i = 0; i <= max_val; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    // Two pointers
    int left = 1;
    int right = max_val;
    int max_pair_sum = 0;

    while (left <= right) {
        while (left <= max_val && count[left] == 0) {
            left++;
        }
        while (right >= 1 && count[right] == 0) {
            right--;
        }
        if (left > right) {
            break;
        }

        if (left == right) {
            int pairs = count[left] / 2;
            if (pairs > 0) {
                int pair_sum = left + right;
                if (pair_sum > max_pair_sum) {
                    max_pair_sum = pair_sum;
                }
                count[left] -= pairs * 2;
            } else {
                break;
            }
        } else {
            int pairs = (count[left] < count[right]) ? count[left] : count[right];
            if (pairs > 0) {
                int pair_sum = left + right;
                if (pair_sum > max_pair_sum) {
                    max_pair_sum = pair_sum;
                }
                count[left] -= pairs;
                count[right] -= pairs;
            } else {
                break;
            }
        }
    }

    return max_pair_sum;
}
