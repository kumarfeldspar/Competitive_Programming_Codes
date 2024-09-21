//https://shorturl.at/N8lhF
class Solution {
public:
    const static int inf = 1e9;
    const static int N = 2e5 + 5;
    struct node {
        int lr;
        int l1r;
        int lr1;
        int l1r1;
    };
    node sgt[4 * N];

    node merge(node a, node b) {
        node ans;
        ans.lr = std::max({a.lr1 + b.l1r, a.lr + b.l1r, a.lr1 + b.lr});
        ans.lr1 = std::max({a.lr1 + b.l1r1, a.lr + b.l1r1, a.lr1 + b.lr1});
        ans.l1r = std::max({a.l1r1 + b.l1r, a.l1r + b.l1r, a.l1r1 + b.lr});
        ans.l1r1 = std::max({a.l1r1 + b.l1r1, a.l1r + b.l1r1, a.l1r1 + b.lr1});
        return ans;
    }

    void update(int t, int tl, int tr, int i, int value) {
        if (tl > i || tr < i)
            return;
        if (tl == tr) {
            sgt[t].lr = value;
            sgt[t].lr1 = sgt[t].l1r = sgt[t].l1r1 = 0;
            return;
        }
        int mid = (tl + tr) / 2;
        update(2 * t + 1, tl, mid, i, value);
        update(2 * t + 2, mid + 1, tr, i, value);
        int left = 2 * t + 1, right = 2 * t + 2;
        sgt[t] = merge(sgt[left], sgt[right]);
    }

    node query(int t, int tl, int tr, int l, int r) {
        if (tl > r || tr < l)
            return {0, 0, 0, 0}; // Initialize all parts to zero
        if (l <= tl && r >= tr)
            return sgt[t];
        int mid = (tl + tr) / 2;
        int left = 2 * t + 1, right = 2 * t + 2;
        return merge(query(left, tl, mid, l, r), query(right, mid + 1, tr, l, r));
    }

    int maximumSumSubsequence(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        int n = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            update(0, 0, n - 1, i, nums[i]);
        }
        int cc=1000000007;
        long long ans = 0;
        for (int i = 0; i < queries.size(); i++) {
            int x = queries[i][0], y = queries[i][1];
            if (y < 0) update(0, 0, n - 1, x, 0);
            else update(0, 0, n - 1, x, y);
            int xx = std::max({sgt[0].lr, sgt[0].lr1, sgt[0].l1r, sgt[0].l1r1});
            ans += (long long)xx;
            ans%=cc;
        }
        return ans;
    }
};
