// Source: https://leetcode.com/problems/count-good-meals/   |   Difficulty: Medium
//
// Problem Description:
// A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.
//
// You can pick any two different foods to make a good meal.
//
// Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the i​​​​​​th​​​​​​​​ item of food, return the number of different good meals you can make from this list modulo 109 + 7.
//
// Note that items with different indices are considered different even if they have the same deliciousness value.
//
// Example:
// Input: deliciousness = [1,3,5,7,9]
// Output: 4
// Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
// Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
//
// Constraints:
// 1 <= deliciousness.length <= 105
// 	0 <= deliciousness[i] <= 220
//

int countPairs(int* deliciousness, int deliciousnessSize) {
    #define MOD 1000000007
    #define MAX_POWER 22

    int count[1 << (MAX_POWER + 1)];
    for (int i = 0; i < (1 << (MAX_POWER + 1)); i++) {
        count[i] = 0;
    }

    long long result = 0;
    for (int i = 0; i < deliciousnessSize; i++) {
        for (int power = 0; power <= MAX_POWER; power++) {
            int target = (1 << power) - deliciousness[i];
            if (target >= 0 && target < (1 << (MAX_POWER + 1))) {
                result = (result + count[target]) % MOD;
            }
        }
        count[deliciousness[i]]++;
    }

    return (int)result;     
}
