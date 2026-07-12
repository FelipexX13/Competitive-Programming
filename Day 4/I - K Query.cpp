#include <bits/stdc++.h>
using namespace std;

struct Element {
    int value;
    int pos;
};

struct Query {
    int l, r, k;
    int id;
};

bool cmpElement(const Element &a, const Element &b) {
    return a.value > b.value;
}

bool cmpQuery(const Query &a, const Query &b) {
    return a.k > b.k;
}

class Fenwick {
    vector<int> bit;
    int n;

public:
    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Element> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i].value;
        arr[i].pos = i + 1;
    }

    sort(arr.begin(), arr.end(), cmpElement);

    int q;
    cin >> q;

    vector<Query> queries(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), cmpQuery);

    Fenwick bit(n);
    vector<int> ans(q);

    int idx = 0;

    for (auto &qu : queries) {
        while (idx < n && arr[idx].value > qu.k) {
            bit.update(arr[idx].pos, 1);
            idx++;
        }
        ans[qu.id] = bit.rangeQuery(qu.l, qu.r);
    }

    for (int x : ans)
        cout << x << "\n";

    return 0;
}