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

 * @param {string[][]} orders

 * @return {string[][]}

 */

var displayTable = function(orders) {

    

    const foodItemsSet = new Set();
    const tableOrdersMap = new Map();
    for (const [_, tableNumber, foodItem] of orders) {
        foodItemsSet.add(foodItem);
        if (!tableOrdersMap.has(tableNumber)) {
            tableOrdersMap.set(tableNumber, new Map());
        }
        const foodCountMap = tableOrdersMap.get(tableNumber);
        foodCountMap.set(foodItem, (foodCountMap.get(foodItem) || 0) + 1);
    }
    const foodItems = Array.from(foodItemsSet).sort();
    const result = [];
    result.push(['Table', ...foodItems]);
    const sortedTableNumbers = Array.from(tableOrdersMap.keys()).sort((a, b) => Number(a) - Number(b));
    for (const tableNumber of sortedTableNumbers) {
        const foodCountMap = tableOrdersMap.get(tableNumber);
        const row = [tableNumber];
        for (const foodItem of foodItems) {
            row.push((foodCountMap.get(foodItem) || 0).toString());
        }
        result.push(row);
    }
    return result;
    
};
