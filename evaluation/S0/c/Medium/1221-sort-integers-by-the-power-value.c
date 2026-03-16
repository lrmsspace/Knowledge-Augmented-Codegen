// Source: https://leetcode.com/problems/sort-integers-by-the-power-value/   |   Difficulty: Medium
//
// Problem Description:
// The power of an integer x is defined as the number of steps needed to transform x into 1 using the following steps:
//
//
// 	if x is even then x = x / 2
// 	if x is odd then x = 3 * x + 1
//
//
// For example, the power of x = 3 is 7 because 3 needs 7 steps to become 1 (3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1).
//
// Given three integers lo, hi and k. The task is to sort all integers in the interval [lo, hi] by the power value in ascending order, if two or more integers have the same power value sort them by ascending order.
//
// Return the kth integer in the range [lo, hi] sorted by the power value.
//
// Notice that for any integer x (lo <= x <= hi) it is guaranteed that x will transform into 1 using these steps and that the power of x is will fit in a 32-bit signed integer.
//
// Example:
// Input: lo = 12, hi = 15, k = 2
// Output: 13
// Explanation: The power of 12 is 9 (12 --> 6 --> 3 --> 10 --> 5 --> 16 --> 8 --> 4 --> 2 --> 1)
// The power of 13 is 9
// The power of 14 is 17
// The power of 15 is 17
// The interval sorted by the power value [12,13,14,15]. For k = 2 answer is the second element which is 13.
// Notice that 12 and 13 have the same power value and we sorted them in ascending order. Same for 14 and 15.
//
// Constraints:
// 1 <= lo <= hi <= 1000
// 	1 <= k <= hi - lo + 1
//

int getKth(int lo, int hi, int k) {
    int power[1001] = {0};

    // Function to compute power value using memoization
    int computePower(int x) {
        if (x == 1) return 0;
        if (x < 1001 && power[x] != 0) return power[x];

        int next = (x % 2 == 0) ? x / 2 : 3 * x + 1;
        int result = 1 + computePower(next);

        if (x < 1001) power[x] = result;
        return result;
    }

    // Create an array of pairs (number, power)
    typedef struct {
        int number;
        int power;
    } NumPowerPair;

    NumPowerPair arr[1000];
    int index = 0;

    for (int i = lo; i <= hi; i++) {
        arr[index].number = i;
        arr[index].power = computePower(i);
        index++;
    }

    // Sort the array based on power and then by number
    int compare(const void *a, const void *b) {
        NumPowerPair *pairA = (NumPowerPair *)a;
        NumPowerPair *pairB = (NumPowerPair *)b;

        if (pairA->power != pairB->power) {
            return pairA->power - pairB->power;
        } else {
            return pairA->number - pairB->number;
        }
    }

    qsort(arr, index, sizeof(NumPowerPair), compare);

    return arr[k - 1].number;       
}
