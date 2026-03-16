// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//

class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> result(n, -1);
        vector<bool> isBanned(n, false);
        for (int pos : banned) {
            isBanned[pos] = true;
        }
        
        set<int> evenPositions, oddPositions;
        for (int i = 0; i < n; i++) {
            if (i != p && !isBanned[i]) {
                if (i % 2 == 0) {
                    evenPositions.insert(i);
                } else {
                    oddPositions.insert(i);
                }
            }
        }
        
        queue<int> q;
        q.push(p);
        result[p] = 0;
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            int currDist = result[curr];
            
            int leftBound = max(0, curr - k + 1);
            int rightBound = min(n - 1, curr + k - 1);
            
            int minPos = leftBound + (k - 1 - (curr - leftBound));
            int maxPos = rightBound - (k - 1 - (rightBound - curr));
            
            set<int>& targetSet = (minPos % 2 == 0) ? evenPositions : oddPositions;
            auto it = targetSet.lower_bound(minPos);
            
            while (it != targetSet.end() && *it <= maxPos) {
                int nextPos = *it;
                result[nextPos] = currDist + 1;
                q.push(nextPos);
                it = targetSet.erase(it);
            }
        }
        
        return result;          
    }
};
