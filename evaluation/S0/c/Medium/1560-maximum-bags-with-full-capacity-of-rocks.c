// Source: https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/   |   Difficulty: Medium
//
// Problem Description:
// You have n bags numbered from 0 to n - 1. You are given two 0-indexed integer arrays capacity and rocks. The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks. You are also given an integer additionalRocks, the number of additional rocks you can place in any of the bags.
//
// Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.
//
// Example:
// Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
// Output: 3
// Explanation:
// Place 1 rock in bag 0 and 1 rock in bag 1.
// The number of rocks in each bag are now [2,3,4,4].
// Bags 0, 1, and 2 have full capacity.
// There are 3 bags at full capacity, so we return 3.
// It can be shown that it is not possible to have more than 3 bags at full capacity.
// Note that there may be other ways of placing the rocks that result in an answer of 3.
//
// Constraints:
// n == capacity.length == rocks.length
// 	1 <= n <= 5 * 104
// 	1 <= capacity[i] <= 109
// 	0 <= rocks[i] <= capacity[i]
// 	1 <= additionalRocks <= 109
//

int maximumBags(int* capacity, int capacitySize, int* rocks, int rocksSize, int additionalRocks) {
    int needed[capacitySize];
    for (int i = 0; i < capacitySize; i++) {
        needed[i] = capacity[i] - rocks[i];
    }

    // Simple insertion sort
    for (int i = 1; i < capacitySize; i++) {
        int key = needed[i];
        int j = i - 1;
        while (j >= 0 && needed[j] > key) {
            needed[j + 1] = needed[j];
            j = j - 1;
        }
        needed[j + 1] = key;
    }

    int fullBags = 0;
    for (int i = 0; i < capacitySize; i++) {
        if (needed[i] == 0) {
            fullBags++;
        } else if (additionalRocks >= needed[i]) {
            additionalRocks -= needed[i];
            fullBags++;
        } else {
            break;
        }
    }

    return fullBags;        
}
