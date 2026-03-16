// Source: https://leetcode.com/problems/mice-and-cheese/   |   Difficulty: Medium
//
// Problem Description:
// There are two mice and n different types of cheese, each type of cheese should be eaten by exactly one mouse.
//
// A point of the cheese with index i (0-indexed) is:
//
//
// 	reward1[i] if the first mouse eats it.
// 	reward2[i] if the second mouse eats it.
//
//
// You are given a positive integer array reward1, a positive integer array reward2, and a non-negative integer k.
//
// Return the maximum points the mice can achieve if the first mouse eats exactly k types of cheese.
//
// Example:
// Input: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2
// Output: 15
// Explanation: In this example, the first mouse eats the 2nd (0-indexed) and the 3rd types of cheese, and the second mouse eats the 0th and the 1st types of cheese.
// The total points are 4 + 4 + 3 + 4 = 15.
// It can be proven that 15 is the maximum total points that the mice can achieve.
//
// Constraints:
// 1 <= n == reward1.length == reward2.length <= 105
// 	1 <= reward1[i], reward2[i] <= 1000
// 	0 <= k <= n
//

int miceAndCheese(int* reward1, int reward1Size, int* reward2, int reward2Size, int k) {
    int diffs[reward1Size];
    int total = 0;
    
    for (int i = 0; i < reward1Size; i++) {
        diffs[i] = reward1[i] - reward2[i];
        total += reward2[i];
    }
    
    // Sort diffs in descending order
    for (int i = 0; i < reward1Size - 1; i++) {
        for (int j = 0; j < reward1Size - i - 1; j++) {
            if (diffs[j] < diffs[j + 1]) {
                int temp = diffs[j];
                diffs[j] = diffs[j + 1];
                diffs[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < k; i++) {
        if (diffs[i] > 0) {
            total += diffs[i];
        }
    }
    
    return total;       
}
