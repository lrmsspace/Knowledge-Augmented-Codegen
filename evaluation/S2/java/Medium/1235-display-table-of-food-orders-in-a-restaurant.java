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
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {

    public List<List<String>> displayTable(List<List<String>> orders) {

        
        // Step 1: Collect unique food items and table numbers
        Set<String> foodItemsSet = new HashSet<>();
        Set<String> tableNumbersSet = new HashSet<>();

        for (List<String> order : orders) {
            String tableNumber = order.get(1);
            String foodItem = order.get(2);
            tableNumbersSet.add(tableNumber);
            foodItemsSet.add(foodItem);
        }

        // Step 2: Sort the food items and table numbers
        List<String> foodItems = new ArrayList<>(foodItemsSet);
        List<String> tableNumbers = new ArrayList<>(tableNumbersSet);
        Collections.sort(foodItems);
        Collections.sort(tableNumbers, Comparator.comparingInt(Integer::parseInt));

        // Step 3: Create a mapping of table number to food item counts
        Map<String, Map<String, Integer>> tableFoodCountMap = new HashMap<>();

        for (List<String> order : orders) {
            String tableNumber = order.get(1);
            String foodItem = order.get(2);

            tableFoodCountMap.putIfAbsent(tableNumber, new HashMap<>());
            Map<String, Integer> foodCountMap = tableFoodCountMap.get(tableNumber);
            foodCountMap.put(foodItem, foodCountMap.getOrDefault(foodItem, 0) + 1);
        }

        // Step 4: Build the display table
        List<List<String>> displayTable = new ArrayList<>();

        // Add header row
        List<String> headerRow = new ArrayList<>();
        headerRow.add("Table");
        headerRow.addAll(foodItems);
        displayTable.add(headerRow);

        // Add rows for each table
        for (String tableNumber : tableNumbers) {
            List<String> row = new ArrayList<>();
            row.add(tableNumber);
            Map<String, Integer> foodCountMap = tableFoodCountMap.getOrDefault(tableNumber, new HashMap<>());

            for (String foodItem : foodItems) {
                row.add(String.valueOf(foodCountMap.getOrDefault(foodItem, 0)));
            }
            displayTable.add(row);
        }

        return displayTable;
    }

}
