// Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
//
// Problem Description:
// In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
//
// Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
//
// Example:
// Input: barcodes = [1,1,1,2,2,2]
// Output: [2,1,2,1,2,1]
//
// Constraints:
// 1 <= barcodes.length <= 10000
// 	1 <= barcodes[i] <= 10000
//

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> freq;
        for (int code : barcodes) {
            freq[code]++;
        }

        priority_queue<pair<int, int>> maxHeap;
        for (const auto& [code, count] : freq) {
            maxHeap.push({count, code});
        }

        vector<int> result;
        while (maxHeap.size() > 1) {
            auto [count1, code1] = maxHeap.top(); maxHeap.pop();
            auto [count2, code2] = maxHeap.top(); maxHeap.pop();

            result.push_back(code1);
            result.push_back(code2);

            if (--count1 > 0) {
                maxHeap.push({count1, code1});
            }
            if (--count2 > 0) {
                maxHeap.push({count2, code2});
            }
        }

        if (!maxHeap.empty()) {
            result.push_back(maxHeap.top().second);
        }

        return result;          
    }
};
