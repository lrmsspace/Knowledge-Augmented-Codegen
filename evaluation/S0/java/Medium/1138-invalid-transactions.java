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

class Solution {
    public List<String> invalidTransactions(String[] transactions) {
        List<String> result = new ArrayList<>();
        Map<String, List<int[]>> map = new HashMap<>();

        for (String transaction : transactions) {
            String[] parts = transaction.split(",");
            String name = parts[0];
            int time = Integer.parseInt(parts[1]);
            int amount = Integer.parseInt(parts[2]);
            String city = parts[3];

            if (amount > 1000) {
                result.add(transaction);
            }

            map.putIfAbsent(name, new ArrayList<>());
            List<int[]> userTransactions = map.get(name);

            for (int[] t : userTransactions) {
                int tTime = t[0];
                String tCity = parts[3 + t[1]]; // city is stored as index 3 + cityIndex
                if (Math.abs(tTime - time) <= 60 && !tCity.equals(city)) {
                    result.add(transaction);
                    result.add(t[2] + "," + tTime + "," + t[3] + "," + tCity); // reconstruct the transaction string
                }
            }

            userTransactions.add(new int[]{time, userTransactions.size(), amount, city});
        }

        return new ArrayList<>(new HashSet<>(result)); // remove duplicates         
    }
}
