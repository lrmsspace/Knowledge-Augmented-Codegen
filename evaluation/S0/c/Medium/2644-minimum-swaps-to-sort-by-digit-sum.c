// Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the sorted order.
//
// Return the minimum number of swaps required to rearrange nums into this sorted order.
//
// A swap is defined as exchanging the values at two distinct positions in the array.
//
// Example:
// Input: nums = [37,100]
//
// Output: 1
//
// Explanation:
//
//
// 	Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
// 	Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
// 	Thus, the minimum number of swaps required to rearrange nums is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums consists of distinct positive integers.
//

int minSwaps(int* nums, int numsSize) {
    // Helper function to calculate the digit sum of a number
    int digitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    // Create an array of pairs (digit sum, original index)
    typedef struct {
        int digit_sum;
        int index;
    } Pair;

    Pair* pairs = (Pair*)malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        pairs[i].digit_sum = digitSum(nums[i]);
        pairs[i].index = i;
    }

    // Sort the pairs based on digit sum and then by original number
    qsort(pairs, numsSize, sizeof(Pair), [](const void* a, const void* b) {
        Pair* p1 = (Pair*)a;
        Pair* p2 = (Pair*)b;
        if (p1->digit_sum != p2->digit_sum) {
            return p1->digit_sum - p2->digit_sum;
        }
        return nums[p1->index] - nums[p2->index];
    });

    // Create a visited array to track visited elements
    int* visited = (int*)calloc(numsSize, sizeof(int));
    int swaps = 0;

    // Calculate the number of swaps needed
    for (int i = 0; i < numsSize; i++) {
        if (visited[i] || pairs[i].index == i) {
            continue;
        }

        int cycle_size = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = 1;
            j = pairs[j].index;
            cycle_size++;
        }

        if (cycle_size > 0) {
            swaps += (cycle_size - 1);
        }
    }

    free(pairs);
    free(visited);
    return swaps;       
}
