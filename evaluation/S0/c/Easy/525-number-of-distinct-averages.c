// Source: https://leetcode.com/problems/number-of-distinct-averages/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums of even length.
//
// As long as nums is not empty, you must repetitively:
//
//
// 	Find the minimum number in nums and remove it.
// 	Find the maximum number in nums and remove it.
// 	Calculate the average of the two removed numbers.
//
//
// The average of two numbers a and b is (a + b) / 2.
//
//
// 	For example, the average of 2 and 3 is (2 + 3) / 2 = 2.5.
//
//
// Return the number of distinct averages calculated using the above process.
//
// Note that when there is a tie for a minimum or maximum number, any can be removed.
//
// Example:
// Input: nums = [4,1,4,0,3,5]
// Output: 2
// Explanation:
// 1. Remove 0 and 5, and the average is (0 + 5) / 2 = 2.5. Now, nums = [4,1,4,3].
// 2. Remove 1 and 4. The average is (1 + 4) / 2 = 2.5, and nums = [4,3].
// 3. Remove 3 and 4, and the average is (3 + 4) / 2 = 3.5.
// Since there are 2 distinct numbers among 2.5, 2.5, and 3.5, we return 2.
//
// Constraints:
// 2 <= nums.length <= 100
// 	nums.length is even.
// 	0 <= nums[i] <= 100
//

int distinctAverages(int* nums, int numsSize) {
    int count[201] = {0};
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int distinct_count = 0;
    for (int sum = 0; sum <= 200; sum++) {
        for (int a = 0; a <= sum / 2; a++) {
            int b = sum - a;
            if (b > 100) continue;
            if (a == b) {
                if (count[a] >= 2) {
                    distinct_count++;
                    break;
                }
            } else {
                if (count[a] > 0 && count[b] > 0) {
                    distinct_count++;
                    break;
                }
            }
        }
    }

    return distinct_count;      
}
