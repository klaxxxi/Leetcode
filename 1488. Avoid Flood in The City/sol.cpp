class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        vector<int> result(rains.size(), 1);
        for (int i = 0, size = rains.size(); i < size; ++i) {
            if (rains[i] == 0) {
                mSuns.emplace(i);
            } else {
                auto [iter, flag] = mLakes.try_emplace(rains[i], i);
                if (!flag) {
                    auto it = mSuns.lower_bound(iter->second);
                    if (it == mSuns.end()) {
                        result.clear();
                        break;
                    }
                    result[*it] = rains[i];
                    mSuns.erase(it);
                    iter->second = i;
                }
                result[i] = -1;
            }
        }
        return result;
        
    }

private:
    // store full lakes an when become full
    unordered_map<int, int> mLakes;

    // store no rain days
    set<int> mSuns;
};