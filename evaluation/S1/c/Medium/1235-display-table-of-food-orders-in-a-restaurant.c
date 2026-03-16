// Source: https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/   |   Difficulty: Medium
//
// Problem Description:
// Given the array orders, which represents the orders that customers have done in a restaurant. More specifically orders[i]=[customerNamei,tableNumberi,foodItemi] where customerNamei is the name of the customer, tableNumberi is the table customer sit at, and foodItemi is the item customer orders.
//
// Return the restaurant's “display table”. The “display table” is a table whose row entries denote how many of each food item each table ordered. The first column is the table number and the remaining columns correspond to each food item in alphabetical order. The first row should be a header whose first column is “Table”, followed by the names of the food items. Note that the customer names are not part of the table. Additionally, the rows should be sorted in numerically increasing order.
//
// Example:
// Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
// Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],["3","0","2","1","0"],["5","0","1","0","1"],["10","1","0","0","0"]] 
// Explanation:
// The displaying table looks like:
// Table,Beef Burrito,Ceviche,Fried Chicken,Water
// 3    ,0           ,2      ,1            ,0
// 5    ,0           ,1      ,0            ,1
// 10   ,1           ,0      ,0            ,0
// For the table 3: David orders "Ceviche" and "Fried Chicken", and Rous orders "Ceviche".
// For the table 5: Carla orders "Water" and "Ceviche".
// For the table 10: Corina orders "Beef Burrito".
//
// Constraints:
// 1 <= orders.length <= 5 * 10^4
// 	orders[i].length == 3
// 	1 <= customerNamei.length, foodItemi.length <= 20
// 	customerNamei and foodItemi consist of lowercase and uppercase English letters and the space character.
// 	tableNumberi is a valid integer between 1 and 500.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**

 * Return an array of arrays of size *returnSize.

 * The sizes of the arrays are returned as *returnColumnSizes array.

 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().

 */

char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, int* returnSize, int** returnColumnSizes){
    // Step 1: Collect unique food items and table numbers
    #define MAX_FOOD_ITEMS 500
    #define MAX_TABLES 500

    char* foodItems[MAX_FOOD_ITEMS];
    int foodItemCount = 0;
    int tableOrders[MAX_TABLES][MAX_FOOD_ITEMS];
    int tableExists[MAX_TABLES] = {0};
    memset(tableOrders, 0, sizeof(tableOrders));

    for (int i = 0; i < ordersSize; i++) {
        char* foodItem = orders[i][2];
        int tableNumber = atoi(orders[i][1]);

        // Add food item if not already present
        int found = 0;
        for (int j = 0; j < foodItemCount; j++) {
            if (strcmp(foodItems[j], foodItem) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            foodItems[foodItemCount++] = foodItem;
        }

        // Record the order
        tableOrders[tableNumber][foodItemCount - 1]++;
        tableExists[tableNumber] = 1;
    }

    // Step 2: Sort food items alphabetically
    qsort(foodItems, foodItemCount, sizeof(char*), (int (*)(const void*, const void*))strcmp);

    // Step 3: Prepare the result table
    int totalTables = 0;
    for (int i = 1; i < MAX_TABLES; i++) {
        if (tableExists[i]) {
            totalTables++;
        }
    }

    char*** result = (char***)malloc((totalTables + 1) * sizeof(char**));
    *returnColumnSizes = (int*)malloc((totalTables + 1) * sizeof(int));
    
    // Header row
    result[0] = (char**)malloc((foodItemCount + 1) * sizeof(char*));
    result[0][0] = "Table";
    for (int i = 0; i < foodItemCount; i++) {
        result[0][i + 1] = foodItems[i];
    }
    (*returnColumnSizes)[0] = foodItemCount + 1;

    // Data rows
    int rowIndex = 1;
    for (int i = 1; i < MAX_TABLES; i++) {
        if (tableExists[i]) {
            result[rowIndex] = (char**)malloc((foodItemCount + 1) * sizeof(char*));
            // Table number
            char* tableStr = (char*)malloc(10 * sizeof(char));
            sprintf(tableStr, "%d", i);
            result[rowIndex][0] = tableStr;

            // Food item counts
            for (int j = 0; j < foodItemCount; j++) {
                char* countStr = (char*)malloc(10 * sizeof(char));
                sprintf(countStr, "%d", tableOrders[i][j]);
                result[rowIndex][j + 1] = countStr;
            }
            (*returnColumnSizes)[rowIndex] = foodItemCount + 1;
            rowIndex++;
        }
    }
    *returnSize = totalTables + 1;
    return result;
}
