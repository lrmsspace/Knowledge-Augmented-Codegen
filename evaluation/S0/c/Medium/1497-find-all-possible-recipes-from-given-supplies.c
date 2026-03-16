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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findAllRecipes(char** recipes, int recipesSize, char*** ingredients, int ingredientsSize, int* ingredientsColSize, char** supplies, int suppliesSize, int* returnSize) {
    // Create a hash set for supplies
    #define HASH_SIZE 256
    typedef struct HashSet {
        char* table[HASH_SIZE];
    } HashSet;

    HashSet* createHashSet() {
        HashSet* set = (HashSet*)malloc(sizeof(HashSet));
        memset(set->table, 0, sizeof(set->table));
        return set;
    }

    unsigned int hash(const char* str) {
        unsigned int h = 0;
        while (*str) {
            h = (h << 5) + h + (unsigned char)(*str++);
        }
        return h % HASH_SIZE;
    }

    void hashSetAdd(HashSet* set, const char* str) {
        unsigned int idx = hash(str);
        set->table[idx] = strdup(str);
    }

    int hashSetContains(HashSet* set, const char* str) {
        unsigned int idx = hash(str);
        return set->table[idx] != NULL && strcmp(set->table[idx], str) == 0;
    }

    void freeHashSet(HashSet* set) {
        for (int i = 0; i < HASH_SIZE; i++) {
            if (set->table[i]) {
                free(set->table[i]);
            }
        }
        free(set);
    }

    HashSet* supplySet = createHashSet();
    for (int i = 0; i < suppliesSize; i++) {
        hashSetAdd(supplySet, supplies[i]);
    }

    char** result = (char**)malloc(recipesSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < recipesSize; i++) {
        int canMake = 1;
        for (int j = 0; j < ingredientsColSize[i]; j++) {
            if (!hashSetContains(supplySet, ingredients[i][j])) {
                canMake = 0;
                break;
            }
        }
        if (canMake) {
            result[count++] = strdup(recipes[i]);
            // Add the newly made recipe to supplies
            hashSetAdd(supplySet, recipes[i]);
        }
    }

    freeHashSet(supplySet);
    *returnSize = count;
    return result;      
}
