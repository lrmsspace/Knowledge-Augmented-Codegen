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

/**

 * Return an array of arrays of size *returnSize.

 * The sizes of the arrays are returned as *returnColumnSizes array.

 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().

 */

char *** displayTable(char *** orders, int ordersSize, int* ordersColSize, int* returnSize, int** returnColumnSizes){


    // Hash map to store food items and their corresponding indices
    #define MAX_FOOD_ITEMS 501
    #define MAX_TABLES 501
    #define MAX_FOOD_NAME_LENGTH 21

    int foodItemCount = 0;
    char foodItems[MAX_FOOD_ITEMS][MAX_FOOD_NAME_LENGTH];
    int foodItemIndexMap[128][128] = {0}; // Simple hash map for food item indexing

    // Count unique food items
    for (int i = 0; i < ordersSize; i++) {
        char *foodItem = orders[i][2];
        if (foodItemIndexMap[(unsigned char)foodItem[0]][(unsigned char)foodItem[1]] == 0) {
            strcpy(foodItems[foodItemCount], foodItem);
            foodItemIndexMap[(unsigned char)foodItem[0]][(unsigned char)foodItem[1]] = ++foodItemCount;
        }
    }

    // Sort food items alphabetically
    qsort(foodItems, foodItemCount, sizeof(foodItems[0]), (int (*)(const void *, const void *))strcmp);

    // Map food items to their sorted indices
    for (int i = 0; i < foodItemCount; i++) {
        foodItemIndexMap[(unsigned char)foodItems[i][0]][(unsigned char)foodItems[i][1]] = i + 1;
    }

    // Table orders count
    int tableOrders[MAX_TABLES][MAX_FOOD_ITEMS] = {0};
    int tableExists[MAX_TABLES] = {0};

    // Process orders
    for (int i = 0; i < ordersSize; i++) {
        int tableNumber = atoi(orders[i][1]);
        char *foodItem = orders[i][2];
        int index = foodItemIndexMap[(unsigned char)foodItem[0]][(unsigned char)foodItem[1]];
        tableOrders[tableNumber][index]++;
        tableExists[tableNumber] = 1;
    }

    // Prepare result
    char ***result = (char ***)malloc((MAX_TABLES + 1) * sizeof(char **));
    *returnColumnSizes = (int *)malloc((MAX_TABLES + 1) * sizeof(int));
    int resultSize = 0;

    // Header row
    result[resultSize] = (char **)malloc((foodItemCount + 1) * sizeof(char *));
    (*returnColumnSizes)[resultSize] = foodItemCount + 1;
    result[resultSize][0] = strdup("Table");
    for (int i = 0; i < foodItemCount; i++) {
        result[resultSize][i + 1] = strdup(foodItems[i]);
    }
    resultSize++;
    // Data rows
    for (int tableNumber = 1; tableNumber < MAX_TABLES; tableNumber++) {
        if (tableExists[tableNumber]) {
            result[resultSize] = (char **)malloc((foodItemCount + 1) * sizeof(char *));
            (*returnColumnSizes)[resultSize] = foodItemCount + 1;
            result[resultSize][0] = (char *)malloc(4 * sizeof(char));
            sprintf(result[resultSize][0], "%d", tableNumber);
            for (int j = 1; j <= foodItemCount; j++) {
                result[resultSize][j] = (char *)malloc(4 * sizeof(char));
                sprintf(result[resultSize][j], "%d", tableOrders[tableNumber][j]);
            }
            resultSize++;
        }
    }   
    *returnSize = resultSize;
    return result;
}
