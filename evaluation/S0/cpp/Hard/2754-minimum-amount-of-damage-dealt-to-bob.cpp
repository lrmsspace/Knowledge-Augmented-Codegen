// Source: https://leetcode.com/problems/minimum-amount-of-damage-dealt-to-bob/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer power and two integer arrays damage and health, both having length n.
//
// Bob has n enemies, where enemy i will deal Bob damage[i] points of damage per second while they are alive (i.e. health[i] > 0).
//
// Every second, after the enemies deal damage to Bob, he chooses one of the enemies that is still alive and deals power points of damage to them.
//
// Determine the minimum total amount of damage points that will be dealt to Bob before all n enemies are dead.
//
// Example:
// Input: power = 4, damage = [1,2,3,4], health = [4,5,6,8]
//
// Output: 39
//
// Explanation:
//
//
// 	Attack enemy 3 in the first two seconds, after which enemy 3 will go down, the number of damage points dealt to Bob is 10 + 10 = 20 points.
// 	Attack enemy 2 in the next two seconds, after which enemy 2 will go down, the number of damage points dealt to Bob is 6 + 6 = 12 points.
// 	Attack enemy 0 in the next second, after which enemy 0 will go down, the number of damage points dealt to Bob is 3 points.
// 	Attack enemy 1 in the next two seconds, after which enemy 1 will go down, the number of damage points dealt to Bob is 2 + 2 = 4 points.
//
// Constraints:
// 1 <= power <= 104
// 	1 <= n == damage.length == health.length <= 105
// 	1 <= damage[i], health[i] <= 104
//

class Solution {
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size();
        vector<pair<long long, int>> enemies(n);
        for (int i = 0; i < n; i++) {
            int hits = (health[i] + power - 1) / power;
            enemies[i] = {1LL * damage[i] * hits, i};
        }
        
        sort(enemies.begin(), enemies.end());
        
        long long totalDamage = 0;
        for (int i = 0; i < n; i++) {
            totalDamage += 1LL * damage[i] * ((health[i] + power - 1) / power);
        }
        
        long long minTotalDamage = totalDamage;
        for (int i = 0; i < n; i++) {
            int idx = enemies[i].second;
            int hits = (health[idx] + power - 1) / power;
            totalDamage -= 1LL * damage[idx] * hits;
            hits--;
            if (hits > 0) {
                totalDamage += 1LL * damage[idx] * hits;
            }
            minTotalDamage = min(minTotalDamage, totalDamage);
        }
        
        return minTotalDamage;          
    }
};
