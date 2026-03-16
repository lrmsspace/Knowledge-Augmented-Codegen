// Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num which represents a positive integer, and an integer t.
//
// A number is called zero-free if none of its digits are 0.
//
// Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
//
// Example:
// Input: num = "1234", t = 256
//
// Output: "1488"
//
// Explanation:
//
// The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
//
// Constraints:
// 2 <= num.length <= 2 * 105
// 	num consists only of digits in the range ['0', '9'].
// 	num does not contain leading zeros.
// 	1 <= t <= 1014
//

class Solution {
public:
    string smallestNumber(string num, long long t) {
        // Factor t into its prime factors 2, 3, 5, and 7
        vector<int> primeCounts(4, 0); // counts for 2, 3, 5, 7
        vector<int> primes = {2, 3, 5, 7};
        for (int i = 0; i < primes.size(); ++i) {
            while (t % primes[i] == 0) {
                primeCounts[i]++;
                t /= primes[i];
            }
        }
        if (t > 1) return "-1"; // t has prime factors other than 2, 3, 5, or 7
        
        int n = num.size();
        string result;
        bool found = false;
        
        function<bool(int, vector<int>&, bool)> dfs = [&](int pos, vector<int>& counts, bool limit) {
            if (pos == n) {
                for (int i = 0; i < 4; ++i) {
                    if (counts[i] < primeCounts[i]) return false;
                }
                return true;
            }
            
            int startDigit = limit ? (num[pos] - '0') : 1;
            for (int d = startDigit; d <= 9; ++d) {
                vector<int> newCounts = counts;
                int temp = d;
                for (int i = 0; i < primes.size(); ++i) {
                    while (temp % primes[i] == 0) {
                        newCounts[i]++;
                        temp /= primes[i];
                    }
                }
                
                if (dfs(pos + 1, newCounts, limit && (d == startDigit))) {
                    result.push_back(d + '0');
                    return true;
                }
            }
            return false;
        };
        
        vector<int> initialCounts(4, 0);
        if (!dfs(0, initialCounts, true)) {
            // Try with a longer number
            result.clear();
            n++;
            function<bool(int, vector<int>&)> dfsLonger = [&](int pos, vector<int>& counts) {
                if (pos == n) {
                    for (int i = 0; i < 4; ++i) {
                        if (counts[i] < primeCounts[i]) return false;
                    }
                    return true;
                }
                
                int startDigit = (pos == 0) ? 1 : 1;
                for (int d = startDigit; d <= 9; ++d) {
                    vector<int> newCounts = counts;
                    int temp = d;
                    for (int i = 0; i < primes.size(); ++i) {
                        while (temp % primes[i] == 0) {
                            newCounts[i]++;
                            temp /= primes[i];
                        }
                    }
                    
                    if (dfsLonger(pos + 1, newCounts)) {
                        result.push_back(d + '0');
                        return true;
                    }
                }
                return false;
            };
            if (!dfsLonger(0, initialCounts)) {
                return "-1";
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
