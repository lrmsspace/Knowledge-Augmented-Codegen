// Source: https://leetcode.com/problems/most-frequent-ids/   |   Difficulty: Medium
//
// Problem Description:
// The problem involves tracking the frequency of IDs in a collection that changes over time. You have two integer arrays, nums and freq, of equal length n. Each element in nums represents an ID, and the corresponding element in freq indicates how many times that ID should be added to or removed from the collection at each step.
//
//
// 	Addition of IDs: If freq[i] is positive, it means freq[i] IDs with the value nums[i] are added to the collection at step i.
// 	Removal of IDs: If freq[i] is negative, it means -freq[i] IDs with the value nums[i] are removed from the collection at step i.
//
//
// Return an array ans of length n, where ans[i] represents the count of the most frequent ID in the collection after the ith step. If the collection is empty at any step, ans[i] should be 0 for that step.
//
// Example:
// Input: nums = [2,3,2,1], freq = [3,2,-3,1]
//
// Output: [3,3,2,2]
//
// Explanation:
//
// After step 0, we have 3 IDs with the value of 2. So ans[0] = 3.
// After step 1, we have 3 IDs with the value of 2 and 2 IDs with the value of 3. So ans[1] = 3.
// After step 2, we have 2 IDs with the value of 3. So ans[2] = 2.
// After step 3, we have 2 IDs with the value of 3 and 1 ID with the value of 1. So ans[3] = 2.
//
// Constraints:
// 1 <= nums.length == freq.length <= 105
// 	1 <= nums[i] <= 105
// 	-105 <= freq[i] <= 105
// 	freq[i] != 0
// 	The input is generated such that the occurrences of an ID will not be negative in any step.
//

class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        unordered_map<int, long long> countMap; // ID -> count
        map<long long, int> freqMap; // count -> number of IDs with this count
        vector<long long> result;
        long long maxFreq = 0;

        for (size_t i = 0; i < nums.size(); ++i) {
            int id = nums[i];
            long long change = freq[i];
            long long oldCount = countMap[id];
            long long newCount = oldCount + change;

            // Update freqMap for old count
            if (oldCount > 0) {
                freqMap[oldCount]--;
                if (freqMap[oldCount] == 0) {
                    freqMap.erase(oldCount);
                }
            }

            // Update countMap and freqMap for new count
            if (newCount > 0) {
                countMap[id] = newCount;
                freqMap[newCount]++;
            } else {
                countMap.erase(id);
            }

            // Update maxFreq
            if (!freqMap.empty()) {
                maxFreq = freqMap.rbegin()->first;
            } else {
                maxFreq = 0;
            }

            result.push_back(maxFreq);
        }

        return result;          
    }
};
