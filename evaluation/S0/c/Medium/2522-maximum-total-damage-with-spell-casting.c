// Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/   |   Difficulty: Medium
//
// Problem Description:
// A magician has various spells.
//
// You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.
//
// It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
//
// Each spell can be cast only once.
//
// Return the maximum possible total damage that a magician can cast.
//
// Example:
// Input: power = [1,1,3,4]
//
// Output: 6
//
// Explanation:
//
// The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
//
// Constraints:
// 1 <= power.length <= 105
// 	1 <= power[i] <= 109
//

long long maximumTotalDamage(int* power, int powerSize) {
    // Step 1: Find the maximum power value to determine the size of the frequency array
    int max_power = 0;
    for (int i = 0; i < powerSize; i++) {
        if (power[i] > max_power) {
            max_power = power[i];
        }
    }

    // Step 2: Create and populate the frequency array
    long long* freq = (long long*)calloc(max_power + 1, sizeof(long long));
    for (int i = 0; i < powerSize; i++) {
        freq[power[i]] += power[i];
    }

    // Step 3: Dynamic programming to calculate maximum damage
    long long prev2 = 0; // dp[i-2]
    long long prev1 = freq[0]; // dp[i-1]
    long long current = prev1;

    for (int i = 1; i <= max_power; i++) {
        current = (prev2 + freq[i] > prev1) ? (prev2 + freq[i]) : prev1;
        prev2 = prev1;
        prev1 = current;
    }

    free(freq);
    return current;     
}
