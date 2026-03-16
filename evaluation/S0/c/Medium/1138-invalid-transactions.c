// Source: https://leetcode.com/problems/invalid-transactions/   |   Difficulty: Medium
//
// Problem Description:
// A transaction is possibly invalid if:
//
//
// 	the amount exceeds $1000, or;
// 	if it occurs within (and including) 60 minutes of another transaction with the same name in a different city.
//
//
// You are given an array of strings transaction where transactions[i] consists of comma-separated values representing the name, time (in minutes), amount, and city of the transaction.
//
// Return a list of transactions that are possibly invalid. You may return the answer in any order.
//
// Example:
// Input: transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
// Output: ["alice,20,800,mtv","alice,50,100,beijing"]
// Explanation: The first transaction is invalid because the second transaction occurs within a difference of 60 minutes, have the same name and is in a different city. Similarly the second one is invalid too.
//
// Constraints:
// transactions.length <= 1000
// 	Each transactions[i] takes the form "{name},{time},{amount},{city}"
// 	Each {name} and {city} consist of lowercase English letters, and have lengths between 1 and 10.
// 	Each {time} consist of digits, and represent an integer between 0 and 1000.
// 	Each {amount} consist of digits, and represent an integer between 0 and 2000.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** invalidTransactions(char** transactions, int transactionsSize, int* returnSize) {

    int* invalid = (int*)calloc(transactionsSize, sizeof(int));
    for (int i = 0; i < transactionsSize; i++) {
        char name1[11], city1[11];
        int time1, amount1;
        sscanf(transactions[i], "%10[^,],%d,%d,%10[^,]", name1, &time1, &amount1, city1);

        if (amount1 > 1000) {
            invalid[i] = 1;
        }

        for (int j = 0; j < transactionsSize; j++) {
            if (i == j) continue;

            char name2[11], city2[11];
            int time2, amount2;
            sscanf(transactions[j], "%10[^,],%d,%d,%10[^,]", name2, &time2, &amount2, city2);

            if (strcmp(name1, name2) == 0 && abs(time1 - time2) <= 60 && strcmp(city1, city2) != 0) {
                invalid[i] = 1;
                invalid[j] = 1;
            }
        }
    }

    char** result = (char**)malloc(transactionsSize * sizeof(char*));
    int count = 0;
    for (int i = 0; i < transactionsSize; i++) {
        if (invalid[i]) {
            result[count++] = strdup(transactions[i]);
        }
    }
    *returnSize = count;
    free(invalid);
    return result;
}