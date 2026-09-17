#include<bits/stdc++.h>

template<typename data_type>
struct Queue {
    struct QueueNode {
        data_type data;
        QueueNode* next;

        QueueNode() { }

        QueueNode(data_type data): data(data), next(nullptr) {}
    };

    QueueNode* _front, *_back;

    Queue() {
        _front = nullptr; _back = nullptr;
    }

    void push(data_type value) {
        if (_front == nullptr) {
            _front = new QueueNode(value);
            _back = _front;
        }
        else {
            _back->next = new QueueNode(value);
            _back = _back -> next;
        }
    }

    void pop() {
        if (_front != nullptr) {
            _front = _front -> next;
        }
    }

    data_type front() {
        return _front == nullptr ? data_type() : _front -> data;
    }

    bool empty() {
        return _front == nullptr;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Queue<std::pair<int, int>> Q;
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        Q.push(std::make_pair(x, i));
    }
    int res = -1;
    while (not Q.empty()) {
        int x, i;
        std::tie(x, i) = Q.front(); Q.pop();
        if (x <= m) {
            res = i;
        }
        else {
            Q.push(std::make_pair(x - m, i));
        }
    }
    std::cout << res << '\n';
    return 0;
}