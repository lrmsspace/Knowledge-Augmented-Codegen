// Source: https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/   |   Difficulty: Medium
//
// Problem Description:
// You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.
//
// You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.
//
// Return a list of all the recipes that you can create. You may return the answer in any order.
//
// Note that two recipes may contain each other in their ingredients.
//
// Example:
// Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
// Output: ["bread"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
//
// Constraints:
// n == recipes.length == ingredients.length
// 	1 <= n <= 100
// 	1 <= ingredients[i].length, supplies.length <= 100
// 	1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
// 	recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
// 	All the values of recipes and supplies combined are unique.
// 	Each ingredients[i] does not contain any duplicate values.
//

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_set<string> supplySet(supplies.begin(), supplies.end());
        vector<string> result;
        bool added;

        do {
            added = false;
            for (size_t i = 0; i < recipes.size(); ++i) {
                if (supplySet.count(recipes[i])) {
                    continue; // Already can make this recipe
                }

                bool canMake = true;
                for (const string& ingredient : ingredients[i]) {
                    if (!supplySet.count(ingredient)) {
                        canMake = false;
                        break;
                    }
                }

                if (canMake) {
                    supplySet.insert(recipes[i]);
                    result.push_back(recipes[i]);
                    added = true;
                }
            }
        } while (added);

        return result;          
    }
};
