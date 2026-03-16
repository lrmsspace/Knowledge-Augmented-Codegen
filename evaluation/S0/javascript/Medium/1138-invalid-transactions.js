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
 * @param {string[]} transactions
 * @return {string[]}
 */
var invalidTransactions = function(transactions) {
    const parsedTransactions = transactions.map(transaction => {
        const [name, time, amount, city] = transaction.split(',');
        return { name, time: parseInt(time), amount: parseInt(amount), city, original: transaction };
            
    }); 
    const invalids = new Set();
    const n = parsedTransactions.length;    
    for (let i = 0; i < n; i++) {
        const t1 = parsedTransactions[i];
        if (t1.amount > 1000) {
            invalids.add(t1.original);
        }
        for (let j = i + 1; j < n; j++) {
            const t2 = parsedTransactions[j];
            if (t1.name === t2.name && t1.city !== t2.city && Math.abs(t1.time - t2.time) <= 60) {
                invalids.add(t1.original);
                invalids.add(t2.original);
            }
        }
    }   
    return Array.from(invalids);    
        
};
