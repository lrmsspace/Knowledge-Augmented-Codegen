// Source: https://leetcode.com/problems/grumpy-bookstore-owner/   |   Difficulty: Medium
//
// Problem Description:
// There is a bookstore owner that has a store open for n minutes. You are given an integer array customers of length n where customers[i] is the number of the customers that enter the store at the start of the ith minute and all those customers leave after the end of that minute.
//
// During certain minutes, the bookstore owner is grumpy. You are given a binary array grumpy where grumpy[i] is 1 if the bookstore owner is grumpy during the ith minute, and is 0 otherwise.
//
// When the bookstore owner is grumpy, the customers entering during that minute are not satisfied. Otherwise, they are satisfied.
//
// The bookstore owner knows a secret technique to remain not grumpy for minutes consecutive minutes, but this technique can only be used once.
//
// Return the maximum number of customers that can be satisfied throughout the day.
//
// Example:
// Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
//
// Output: 16
//
// Explanation:
//
// The bookstore owner keeps themselves not grumpy for the last 3 minutes.
//
// The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
//
// Constraints:
// n == customers.length == grumpy.length
// 	1 <= minutes <= n <= 2 * 104
// 	0 <= customers[i] <= 1000
// 	grumpy[i] is either 0 or 1.
//

int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int minutes) {
    int totalSatisfied = 0;
    for (int i = 0; i < customersSize; i++) {
        if (grumpy[i] == 0) {
            totalSatisfied += customers[i];
        }
    }

    int additionalSatisfied = 0;
    for (int i = 0; i < minutes; i++) {
        if (grumpy[i] == 1) {
            additionalSatisfied += customers[i];
        }
    }

    int maxAdditionalSatisfied = additionalSatisfied;
    for (int i = minutes; i < customersSize; i++) {
        if (grumpy[i] == 1) {
            additionalSatisfied += customers[i];
        }
        if (grumpy[i - minutes] == 1) {
            additionalSatisfied -= customers[i - minutes];
        }
        if (additionalSatisfied > maxAdditionalSatisfied) {
            maxAdditionalSatisfied = additionalSatisfied;
        }
    }

    return totalSatisfied + maxAdditionalSatisfied;     
}
