#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int R, C, K, ans;
vector<vector<int>> location;
vector<vector<int>> hac;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void clear() {
    for (int i = 0; i < R + 2; i++) {
        fill(location[i].begin(), location[i].end(), 0);
    }
}

void start(int player, int c, int d) {
    int x = 0, y = c; // 시작 좌표 location[0][c]

    while (true) { 
        if (x == R) break;
        
        // 이동 가능 여부 체크
        if (location[x + 2][y] == 0 && location[x + 1][y + 1] == 0 && location[x + 1][y - 1] == 0) { // 남쪽으로 이동 가능
            x++;
        } else if (y > 1 && location[x][y - 2] == 0 && location[x - 1][y - 1] == 0 &&
                   location[x + 1][y - 1] == 0 && location[x + 2][y - 1] == 0 && location[x + 1][y - 2] == 0) { // 서쪽으로 이동 가능
            x++;
            y--;
            d = (d + 3) % 4; // 방향 변경
        } else if (y < C - 2 && location[x][y + 2] == 0 && location[x + 1][y + 1] == 0 &&
                   location[x - 1][y + 1] == 0 && location[x + 2][y + 1] == 0 && location[x + 1][y + 2] == 0) { // 동쪽으로 이동 가능
            x++;
            y++;
            d = (d + 1) % 4; // 방향 변경
        } else break; // 더 이상 이동할 수 없을 때 종료
    }

    // 이동 완료 후 상태 확인
    if (x <= 2) {
        clear();
        return;
    }

    // 위치 저장
    hac[player][0] = x;
    hac[player][1] = y;
    hac[player][2] = d;

    // 플레이어의 위치 업데이트
    location[x][y] = player;
    location[x + 1][y] = player;
    location[x][y + 1] = player;
    location[x - 1][y] = player;
    location[x][y - 1] = player;

    // 최종 위치 찾기
    int final_x = 0;
    queue<int> q;
    q.push(player);
    vector<int> visited(K + 1, 0); // 방문 배열 초기화
    visited[player] = 1;

    while (!q.empty()) {
        int front = q.front();
        q.pop();
        final_x = max(final_x, hac[front][0]);

        int quit_x = hac[front][0] + dx[hac[front][2]];
        int quit_y = hac[front][1] + dy[hac[front][2]];

        for (int i = 0; i < 4; i++) {
            int nx = quit_x + dx[i];
            int ny = quit_y + dy[i];
            if (nx < 0 || nx >= R + 2 || ny < 0 || ny >= C) continue; // 범위 체크
            int tmp = location[nx][ny];

            if (tmp != 0 && tmp != front && visited[tmp] == 0) {
                q.push(tmp);
                visited[tmp] = 1;
            } 
        }
    }

    ans += final_x;
}

int main() {
    cin >> R >> C >> K;
    location.resize(R + 2, vector<int>(C, 0));
    hac.resize(K + 1, vector<int>(3, 0)); // K+1로 변경

    for (int i = 1; i <= K; i++) {
        int c, d;
        cin >> c >> d;
        start(i, c - 1, d);
    }

    cout << ans << endl;

    return 0;
}