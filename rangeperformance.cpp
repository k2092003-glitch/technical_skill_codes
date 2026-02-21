
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4*n);
        build(arr, 0, 0, n-1);
    }

    void build(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2*node+1, start, mid);
            build(arr, 2*node+2, mid+1, end);
            tree[node] = max(tree[2*node+1], tree[2*node+2]);
        }
    }

    void update(int idx, int val, int node, int start, int end) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(idx, val, 2*node+1, start, mid);
            else
                update(idx, val, 2*node+2, mid+1, end);

            tree[node] = max(tree[2*node+1], tree[2*node+2]);
        }
    }

    int query(int l, int r, int node, int start, int end) {
        if (r < start || end < l)
            return INT_MIN;

        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) / 2;
        return max(
            query(l, r, 2*node+1, start, mid),
            query(l, r, 2*node+2, mid+1, end)
        );
    }

    void update(int idx, int val) {
        update(idx, val, 0, 0, n-1);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, n-1);
    }
};

int main() {
    vector<int> arr = {1,3,5,7,9,11};
    SegmentTree st(arr);

    cout << st.query(1,4) << "\n";
    st.update(2,10);
    cout << st.query(1,4) << "\n";
}
