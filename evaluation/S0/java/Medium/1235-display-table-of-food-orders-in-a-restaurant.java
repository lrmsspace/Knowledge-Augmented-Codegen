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

class Solution {

    public List<List<String>> displayTable(List<List<String>> orders) {

        
        Set<String> foodItemsSet = new HashSet<>();
        Map<Integer, Map<String, Integer>> tableOrdersMap = new HashMap<>();

        for (List<String> order : orders) {
            String foodItem = order.get(2);
            int tableNumber = Integer.parseInt(order.get(1));

            foodItemsSet.add(foodItem);

            tableOrdersMap.putIfAbsent(tableNumber, new HashMap<>());
            Map<String, Integer> foodCountMap = tableOrdersMap.get(tableNumber);
            foodCountMap.put(foodItem, foodCountMap.getOrDefault(foodItem, 0) + 1);
        }

        List<String> foodItemsList = new ArrayList<>(foodItemsSet);
        Collections.sort(foodItemsList);

        List<List<String>> result = new ArrayList<>();

        List<String> header = new ArrayList<>();
        header.add("Table");
        header.addAll(foodItemsList);
        result.add(header);

        List<Integer> tableNumbers = new ArrayList<>(tableOrdersMap.keySet());
        Collections.sort(tableNumbers);

        for (int tableNumber : tableNumbers) {
            List<String> row = new ArrayList<>();
            row.add(String.valueOf(tableNumber));
            Map<String, Integer> foodCountMap = tableOrdersMap.get(tableNumber);

            for (String foodItem : foodItemsList) {
                row.add(String.valueOf(foodCountMap.getOrDefault(foodItem, 0)));
            }

            result.add(row);
        }

        return result;
    }

}
