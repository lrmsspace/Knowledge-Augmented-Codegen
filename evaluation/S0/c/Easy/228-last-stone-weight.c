// Source: https://leetcode.com/problems/last-stone-weight/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers stones where stones[i] is the weight of the ith stone.
//
// We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:
//
//
// 	If x == y, both stones are destroyed, and
// 	If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
//
//
// At the end of the game, there is at most one stone left.
//
// Return the weight of the last remaining stone. If there are no stones left, return 0.
//
// Example:
// Input: stones = [2,7,4,1,8,1]
// Output: 1
// Explanation: 
// We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
// we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
// we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
// we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
//
// Constraints:
// 1 <= stones.length <= 30
// 	1 <= stones[i] <= 1000
//

int lastStoneWeight(int* stones, int stonesSize) {
    int weightCount[1001] = {0};
    int maxWeight = 0;

    // Count the occurrences of each stone weight
    for (int i = 0; i < stonesSize; i++) {
        weightCount[stones[i]]++;
        if (stones[i] > maxWeight) {
            maxWeight = stones[i];
        }
    }

    // Process stones from heaviest to lightest
    for (int weight = maxWeight; weight > 0; weight--) {
        if (weightCount[weight] % 2 == 1) { // If there's an odd number of stones of this weight
            // Find the next lighter stone to smash with
            int nextWeight = weight - 1;
            while (nextWeight > 0 && weightCount[nextWeight] == 0) {
                nextWeight--;
            }
            if (nextWeight == 0) {
                return weight; // No lighter stones left, return current weight
            }
            // Smash the stones
            weightCount[nextWeight]--;
            int newWeight = weight - nextWeight;
            weightCount[newWeight]++;
        }
    }

    return 0; // No stones left     
}
