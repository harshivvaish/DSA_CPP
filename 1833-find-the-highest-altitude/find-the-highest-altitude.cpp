class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int current_altitude = 0;
        int max_altitude = 0; // Starts at 0 because the biker begins at altitude 0
        
        for (int i = 0; i < gain.size(); i++) {
            current_altitude += gain[i]; // Update current altitude with the next net gain
            max_altitude = max(max_altitude, current_altitude); // Keep track of the highest peak
        }
        
        return max_altitude;
    }
};