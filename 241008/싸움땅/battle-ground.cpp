#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector <vector<vector<int>>> gun;
vector <vector<int>> people;
vector <vector<int>> info;
int N,M,K;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

void changeGun(int player,int x, int y){
    if(gun[x][y].size()==0)return;
    if(gun[x][y][0]>info[player][4]){ // 총 바꿔들기
        int tmp = info[player][4];
        info[player][4]=gun[x][y][0];
        gun[x][y][0]=tmp;
        sort(gun[x][y].begin(), gun[x][y].end(),greater<int>());
    }
}
void fight(int p1, int p2, int x, int y){
    // 승자 패자 결정
    int p1power=info[p1][3]+info[p1][4];
    int p2power=info[p2][3]+info[p2][4];
    int winner=p1, looser=p2;
    if(p1power==p2power){
        if(info[p1][3]<info[p2][3]) {
            winner=p2;
            looser=p1;
        }
    } else if(p1power<p2power){
        winner=p2;
        looser=p1;
    }
    int score=(p1power-p2power);
    if (score<0)score*=-1;
    info[winner][5]+=score;
    // cout<<score<<"차이 \n";

    // 총 내려놓기
    if(info[looser][4]!=0){
        gun[x][y].push_back(info[looser][4]);
        info[looser][4]=0;
        sort(gun[x][y].begin(), gun[x][y].end(),greater<int>());
    }
    

    // 이긴사람 총 변경
    changeGun(winner,x,y);


    // 진 사람 이동 
    int nx,ny,nd;
    int d=info[looser][2];
    // cout<<looser<<d;
    for(int i=0;i<4;i++){
        nd=(d+i)%4;
        nx=x+dx[nd];
        ny=y+dy[nd];
        if(nx >= 1 && nx <= N && ny >= 1 && ny <= N && people[nx][ny] == 0){
            info[looser][0]=nx;
            info[looser][1]=ny;
            info[looser][2]=nd;
            people[nx][ny]=looser;
            changeGun(looser,nx,ny);
            break;
        }

    }
    
    // 이동
    info[winner][0]=x;
    info[winner][1]=y;

    people[x][y]=winner;
}

void move(int player){
    // 이동 좌표 파악
    int d=info[player][2];
    int nx=info[player][0]+dx[d];
    int ny=info[player][1]+dy[d];
    if(nx<1||nx>N||ny<1||ny>N){
        d=(d+2)%4;
        info[player][2]=d;
        nx=info[player][0]+dx[d];
        ny=info[player][1]+dy[d];
    }

    if(people[nx][ny]==0){ // 사람 없는 경우
        // 이동
        people[info[player][0]][info[player][1]]=0;
        people[nx][ny]=player;
        info[player][0]=nx;
        info[player][1]=ny;
        changeGun(player,nx,ny);
    }
    else { // 사람 만난 경우
        people[info[player][0]][info[player][1]]=0;
        fight(player,people[nx][ny],nx,ny);
    }


}


int main() {
    int a;
    cin>>N>>M>>K;
    gun.resize(N+1,vector<vector<int>>(N+1));
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin>>a;
            if(a!=0)gun[i][j].push_back(a);
        }
    }
    info.resize(M+1,vector<int>(6,0)); // x좌표 y좌표 방향 초기 총 점수
    people.resize(N+1,vector<int>(N+1));
    for(int i=1;i<=M;i++){
        cin>>info[i][0]>>info[i][1]>>info[i][2]>>info[i][3];
        people[info[i][0]][info[i][1]]=i;
    }
    for(int i=1;i<=K;i++){

        for(int j=1;j<=M;j++){
            move(j);
        }
    }
    for(int i=1;i<=M;i++){
        cout<<info[i][5]<<" ";
    }

    return 0;
}