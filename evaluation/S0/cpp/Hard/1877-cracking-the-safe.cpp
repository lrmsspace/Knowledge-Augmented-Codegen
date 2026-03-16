// Source: https://leetcode.com/problems/cracking-the-safe/   |   Difficulty: Hard
//
// Problem Description:
// There is a safe protected by a password. The password is a sequence of n digits where each digit can be in the range [0, k - 1].
//
// The safe has a peculiar way of checking the password. When you enter in a sequence, it checks the most recent n digits that were entered each time you type a digit.
//
//
// 	For example, the correct password is "345" and you enter in "012345":
//
// 	
// 		After typing 0, the most recent 3 digits is "0", which is incorrect.
// 		After typing 1, the most recent 3 digits is "01", which is incorrect.
// 		After typing 2, the most recent 3 digits is "012", which is incorrect.
// 		After typing 3, the most recent 3 digits is "123", which is incorrect.
// 		After typing 4, the most recent 3 digits is "234", which is incorrect.
// 		After typing 5, the most recent 3 digits is "345", which is correct and the safe unlocks.
// 	
// 	
//
//
// Return any string of minimum length that will unlock the safe at some point of entering it.
//
// Example:
// Input: n = 1, k = 2
// Output: "10"
// Explanation: The password is a single digit, so enter each digit. "01" would also unlock the safe.
//
// Constraints:
// 1 <= n <= 4
// 	1 <= k <= 10
// 	1 <= kn <= 4096
//

class Solution {
public:
    string crackSafe(int n, int k) {
        string result;
        unordered_set<string> visited;
        string start(n - 1, '0');
        
        function<void(string)> dfs = [&](string node) {
            for (int x = 0; x < k; x++) {
                string nei = node + to_string(x);
                if (visited.count(nei)) continue;
                visited.insert(nei);
                dfs(nei.substr(1));
                result += to_string(x);
            }
        };
        
        dfs(start);
        result += start;
        reverse(result.begin(), result.end());
        return result;          
    }
};
