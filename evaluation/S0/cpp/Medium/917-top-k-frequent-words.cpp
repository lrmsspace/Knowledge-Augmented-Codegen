// Source: https://leetcode.com/problems/top-k-frequent-words/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings words and an integer k, return the k most frequent strings.
//
// Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.
//
// Example:
// Input: words = ["i","love","leetcode","i","love","coding"], k = 2
// Output: ["i","love"]
// Explanation: "i" and "love" are the two most frequent words.
// Note that "i" comes before "love" due to a lower alphabetical order.
//
// Constraints:
// 1 <= words.length <= 500
// 	1 <= words[i].length <= 10
// 	words[i] consists of lowercase English letters.
// 	k is in the range [1, The number of unique words[i]]
//
//
//  
// Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
//

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freqMap;
        for (const string& word : words) {
            freqMap[word]++;
        }

        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b) {
            if (a.second == b.second) {
                return a.first < b.first; // Lexicographical order for same frequency
            }
            return a.second > b.second; // Higher frequency first
        };

        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> minHeap(cmp);

        for (const auto& entry : freqMap) {
            minHeap.push(entry);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        return result;          
    }
};
