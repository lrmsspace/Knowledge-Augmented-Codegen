// Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
//
// Return the minimum integer you can obtain also as a string.
//
// Example:
// Input: num = "4321", k = 4
// Output: "1342"
// Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
//
// Constraints:
// 1 <= num.length <= 3 * 104
// 	num consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//

class Solution {
public:
    string minInteger(string num, int k) {
        int n = num.size();
        vector<queue<int>> pos(10);
        for (int i = 0; i < n; i++) {
            pos[num[i] - '0'].push(i);
        }
        
        // Fenwick Tree for counting shifts
        vector<int> fenw(n + 1, 0);
        
        auto fenwUpdate = [&](int idx, int delta) {
            for (++idx; idx <= n; idx += idx & -idx) {
                fenw[idx] += delta;
            }
        };
        
        auto fenwQuery = [&](int idx) {
            int sum = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                sum += fenw[idx];
            }
            return sum;
        };
        
        string result;
        for (int i = 0; i < n; i++) {
            for (int d = 0; d <= 9; d++) {
                if (pos[d].empty()) continue;
                int originalIdx = pos[d].front();
                int shifts = fenwQuery(originalIdx);
                int currentIdx = originalIdx + shifts;
                int cost = currentIdx - i;
                
                if (cost <= k) {
                    k -= cost;
                    result.push_back(d + '0');
                    fenwUpdate(0, 1);
                    fenwUpdate(originalIdx, -1);
                    pos[d].pop();
                    break;
                }
            }
        }
        
        return result;          
    }
};
