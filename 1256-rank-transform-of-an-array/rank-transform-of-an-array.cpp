class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        // Optimize standard I/O streams for performance
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        if (arr.empty()) return {};

        // 1. Create a copy of the original array
        vector<int> sorted_arr = arr;

        // 2. Sort and remove all duplicate elements
        sort(sorted_arr.begin(), sorted_arr.end());
        sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

        // 3. Map each unique element to its 1-indexed rank
        unordered_map<int, int> rank_map;
        rank_map.reserve(sorted_arr.size()); // Maximize map lookup efficiency
        
        for (int i = 0; i < sorted_arr.size(); ++i) {
            rank_map[sorted_arr[i]] = i + 1;
        }

        // 4. Replace each element in the original array with its rank
        for (int& num : arr) {
            num = rank_map[num];
        }

        return arr;
    }
};