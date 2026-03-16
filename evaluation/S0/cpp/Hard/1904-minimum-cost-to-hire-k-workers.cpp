// Source: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/   |   Difficulty: Hard
//
// Problem Description:
// There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
//
// We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:
//
//
// 	Every worker in the paid group must be paid at least their minimum wage expectation.
// 	In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.
//
//
// Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: quality = [10,20,5], wage = [70,50,30], k = 2
// Output: 105.00000
// Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
//
// Constraints:
// n == quality.length == wage.length
// 	1 <= k <= n <= 104
// 	1 <= quality[i], wage[i] <= 104
//

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> workers; // (ratio, quality)
        
        for (int i = 0; i < n; i++) {
            double ratio = (double)wage[i] / quality[i];
            workers.push_back({ratio, quality[i]});
        }
        
        sort(workers.begin(), workers.end());
        
        priority_queue<int> maxHeap; // max-heap for quality
        double result = 1e9;
        double totalQuality = 0.0;
        
        for (const auto& worker : workers) {
            double ratio = worker.first;
            int q = worker.second;
            
            maxHeap.push(q);
            totalQuality += q;
            
            if (maxHeap.size() > k) {
                totalQuality -= maxHeap.top();
                maxHeap.pop();
            }
            
            if (maxHeap.size() == k) {
                result = min(result, totalQuality * ratio);
            }
        }
        
        return result;          
    }
};
