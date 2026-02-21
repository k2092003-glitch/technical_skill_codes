#include <bits/stdc++.h>
using namespace std;

class StreamingMax {
    deque<pair<int,int>> dq;
    int k, idx;

public:
    StreamingMax(int window) {
        k = window;
        idx = 0;
    }

    int add(int value) {
        while (!dq.empty() && dq.back().first <= value)
            dq.pop_back();

        dq.push_back({value, idx});

        if (!dq.empty() && dq.front().second <= idx - k)
            dq.pop_front();

        idx++;

        if (idx >= k)
            return dq.front().first;

        return -1;
    }
};

int main() {
    StreamingMax sm(3);
    vector<int> arr = {1,3,-1,-3,5,3,6,7};

    for (int x : arr)
        cout << sm.add(x) << " ";
}
