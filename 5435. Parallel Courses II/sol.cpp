struct Node {
    int val = 0;
    int outDegree = 0;

    Node(int val, int outDegree) : val(val), outDegree(outDegree) {}

    bool operator<(const Node& other) const {
        return outDegree < other.outDegree;
    }
};

class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<int> inDegrees(n);
        vector<vector<int>> lines(n);

        for (const auto& dependency : dependencies) {
            ++inDegrees[dependency[1] - 1];
            lines[dependency[0] - 1].emplace_back(dependency[1] - 1);
        }


        priority_queue<Node> nodes;
        for (int i = 0; i < n; ++i) {
            if (inDegrees[i] == 0) {
                nodes.emplace(i, lines[i].size());
            }
        }

        int result = 0;
        while (!nodes.empty()) {
            int size = nodes.size();
            size = min(size, k);
            vector<Node> nexts;
            for (int i = 0; i < size; ++i) {
                auto temp = nodes.top().val;
                nodes.pop();
                for (auto num : lines[temp]) {
                    if (--inDegrees[num] == 0) {
                        nexts.emplace_back(num, lines[num].size());
                    }
                }
            }

            for (auto&& node : nexts) {
                nodes.emplace(move(node));
            }

            ++result;
        }

        return result;
    }    
};