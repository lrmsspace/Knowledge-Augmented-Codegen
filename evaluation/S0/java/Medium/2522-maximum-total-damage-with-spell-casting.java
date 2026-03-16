// Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/   |   Difficulty: Medium
//
// Problem Description:
// A magician has various spells.
//
// You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.
//
// It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
//
// Each spell can be cast only once.
//
// Return the maximum possible total damage that a magician can cast.
//
// Example:
// Input: power = [1,1,3,4]
//
// Output: 6
//
// Explanation:
//
// The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
//
// Constraints:
// 1 <= power.length <= 105
// 	1 <= power[i] <= 109
//

class Solution {
    public long maximumTotalDamage(int[] power) {
        Map<Integer, Long> damageMap = new HashMap<>();
        for (int p : power) {
            damageMap.put(p, damageMap.getOrDefault(p, 0L) + p);
        }

        List<Integer> uniquePowers = new ArrayList<>(damageMap.keySet());
        Collections.sort(uniquePowers);

        long prev1 = 0; // max damage including previous power
        long prev2 = 0; // max damage excluding previous power

        for (int i = 0; i < uniquePowers.size(); i++) {
            int currPower = uniquePowers.get(i);
            long currDamage = damageMap.get(currPower);

            long temp = prev1;
            if (i > 0 && uniquePowers.get(i - 1) == currPower - 1) {
                prev1 = Math.max(prev1, prev2 + currDamage);
            } else {
                prev1 = prev1 + currDamage;
            }
            prev2 = temp;
        }

        return Math.max(prev1, prev2);          
    }
}
