// Source: https://leetcode.com/problems/longest-consecutive-sequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
//
// You must write an algorithm that runs in O(n) time.
//
// Example:
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
//
// Constraints:
// 0 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    // Create a hash set to store unique numbers
    int hashSize = numsSize * 2 + 1; // Simple hash size
    int* hashSet = (int*)calloc(hashSize, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        int index = (nums[i] + 1000000000) % hashSize;
        while (hashSet[index] != 0 && hashSet[index] != nums[i] + 1000000001) {
            index = (index + 1) % hashSize;
        }
        hashSet[index] = nums[i] + 1000000001; // Store offset value to handle negative numbers
    }

    int longestStreak = 0;

    for (int i = 0; i < numsSize; i++) {
        int currentNum = nums[i];
        int index = (currentNum + 1000000000) % hashSize;
        // Check if it's the start of a sequence
        int prevIndex = (currentNum - 1 + 1000000000) % hashSize;
        while (hashSet[prevIndex] != 0 && hashSet[prevIndex] != currentNum) {
            prevIndex = (prevIndex + 1) % hashSize;
        }
        if (hashSet[prevIndex] == 0) {
            int currentStreak = 1;
            int nextNum = currentNum + 1;
            int nextIndex = (nextNum + 1000000000) % hashSize;

            while (1) {
                while (hashSet[nextIndex] != 0 && hashSet[nextIndex] != nextNum + 1000000001) {
                    nextIndex = (nextIndex + 1) % hashSize;
                }
                if (hashSet[nextIndex] == nextNum + 1000000001) {
                    currentStreak++;
                    nextNum++;
                    nextIndex = (nextNum + 1000000000) % hashSize;
                } else {
                    break;
                }
            }
            if (currentStreak > longestStreak) {
                longestStreak = currentStreak;
            }
        }
    }

    free(hashSet);
    return longestStreak;       
}
