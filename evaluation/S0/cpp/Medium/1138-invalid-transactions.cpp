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
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        int n = transactions.size();
        vector<bool> invalid(n, false);
        vector<tuple<string, int, int, string>> parsedTransactions;

        // Parse transactions
        for (int i = 0; i < n; ++i) {
            stringstream ss(transactions[i]);
            string name, timeStr, amountStr, city;
            getline(ss, name, ',');
            getline(ss, timeStr, ',');
            getline(ss, amountStr, ',');
            getline(ss, city, ',');

            int time = stoi(timeStr);
            int amount = stoi(amountStr);
            parsedTransactions.emplace_back(name, time, amount, city);

            // Check for amount > 1000
            if (amount > 1000) {
                invalid[i] = true;
            }
        }
        // Check for transactions within 60 minutes in different cities
        for (int i = 0; i < n; ++i) {
            auto& [name1, time1, amount1, city1] = parsedTransactions[i];
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                auto& [name2, time2, amount2, city2] = parsedTransactions[j];
                if (name1 == name2 && city1 != city2 && abs(time1 - time2) <= 60) {
                    invalid[i] = true;
                    break;
                }
            }
        }
        vector<string> result;
        for (int i = 0; i < n; ++i) {
            if (invalid[i]) {
                result.push_back(transactions[i]);
            }
        }
        return result;
    }
};
