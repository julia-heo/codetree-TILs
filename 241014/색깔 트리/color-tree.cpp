#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

struct node {
    int parent;
    int color;
    int c[5] = {0}; // 색깔 카운트 초기화
    int d_max;
    int score;
};

unordered_map<int, node> Node;

void add(int m_id, int p_id, int color, int d_max) {
    int d = 1, can = 1;
    // 삽입 가능성 검사
    while (p_id != -1) {
        if (Node[p_id].d_max < d) {
            can = 0;
            break;
        }
        p_id = Node[p_id].parent;
        d++;
    }

    if (can) {
        struct node new_node = {p_id, color, {0}, d_max, 1};
        new_node.c[color - 1] = 1; // 색깔 초기화
        Node[m_id] = new_node;

        // 부모 노드 업데이트
        p_id = Node[m_id].parent;
        while (p_id != -1) {
            if (Node[p_id].c[color - 1] == 0) {
                Node[p_id].c[color - 1]++;
                Node[p_id].score++;
            }
            p_id = Node[p_id].parent;
        }
    }
}

void change(int m_id, int color) {
    // 기존 색깔 정보
    int oldColor = Node[m_id].color;
    Node[m_id].color = color;

    int p_id = Node[m_id].parent;

    // 색깔 변경으로 부모 노드의 색깔 카운트 업데이트
    while (p_id != -1) {
        Node[p_id].c[oldColor - 1]--;
        if (Node[p_id].c[oldColor - 1] == 0) {
            Node[p_id].score--;
        }
        if (Node[p_id].c[color - 1] == 0) {
            Node[p_id].c[color - 1]++;
            Node[p_id].score++;
        }
        p_id = Node[p_id].parent;
    }
}

void check(int m_id) {
    cout << Node[m_id].color << endl;
}

void score() {
    int ans = 0;
    for (const auto& n : Node) {
        ans += n.second.score * n.second.score;
    }
    cout << ans << endl;
}

int main() {
    int Q, m, p, c, d_max, order;
    cin >> Q;
    while (Q-- > 0) {
        cin >> order;
        if (order == 100) {
            cin >> m >> p >> c >> d_max;
            add(m, p, c, d_max);
        } else if (order == 200) {
            cin >> m >> c;
            change(m, c);
        } else if (order == 300) {
            cin >> m;
            check(m);
        } else if (order == 400) {
            score();
        }
    }
    return 0;
}