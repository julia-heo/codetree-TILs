#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
int L,N,Q;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
vector <vector <int>> chess;
vector <vector <int>> knLo;

struct knight {
    int r;
    int c;
    int h;
    int w;
    int k;
    int dm;
};

vector <knight> Knight;

void move(int n,int d,deque<int> q){
    vector <vector <int>> tmpLo(L+1,vector <int>(L+1,0));

    while(!q.empty()){
        int tmp=q.back();
        q.pop_back();

        // 기존 위치 다 0으로 설정
        for(int j=0;j<Knight[tmp].h;j++){
            for(int k=0;k<Knight[tmp].w;k++){
                knLo[Knight[tmp].r+j][Knight[tmp].c+k]=0;
            }
        }

        // 위치정보 r,c 변경
        Knight[tmp].r=Knight[tmp].r+dx[d];
        Knight[tmp].c=Knight[tmp].c+dy[d];

        // 명령 받은애 아니면 데미지 계산, 죽나 확인
        if(tmp!=n){
            for(int j=0;j<Knight[tmp].h;j++){
                for(int k=0;k<Knight[tmp].w;k++){
                    if(chess[Knight[tmp].r+j][Knight[tmp].c+k]==1){ // 함정이라면
                        Knight[tmp].dm++; //데미지 계산
                        Knight[tmp].k--; // 체력 계산
                        if(Knight[tmp].k<=0){ // 체력 고갈된 경우 죽음
                            Knight[tmp].r=-1; 
                            Knight[tmp].c=-1;
                            Knight[tmp].h=-1;
                            Knight[tmp].w=-1;
                            break;
                        }
                    }
                }
                if(Knight[tmp].r==-1)break;
            }
        }
        if(Knight[tmp].r!=-1){ //안죽었으면 다시 배치
            for(int j=0;j<Knight[tmp].h;j++){
                for(int k=0;k<Knight[tmp].w;k++){
                    knLo[Knight[tmp].r+j][Knight[tmp].c+k]=tmp;
                }
            }
        }
    }

    
}

void play(int n,int d){

    int r=Knight[n].r;
    int c=Knight[n].c;
    int h=Knight[n].h;
    int w=Knight[n].w;

    queue <int> nextK;
    deque <int> tmp;
    while(!tmp.empty())tmp.pop_back();
    tmp.push_back(n);
    int can=1;
    for(int j=0;j<h;j++){
        for(int k=0;k<w;k++){
            if(chess[r+j+dx[d]][c+k+dy[d]]==2){
                can=0;
                break;
            }
            int next= knLo[r+j+dx[d]][c+k+dy[d]];
            if(next!=0&&next!=n) {
                nextK.push(next);
                tmp.push_back(next);
            }
        }
        if(can==0)break;
    }
    if(can==1){
        while(!nextK.empty()&&can==1){
            int nn=nextK.front();
            nextK.pop();
            for(int j=0;j<Knight[nn].h;j++){
                for(int k=0;k<Knight[nn].w;k++){
                    if(chess[Knight[nn].r+j+dx[d]][Knight[nn].c+k+dy[d]]==2){
                        can=0;
                        break;
                    }
                    int next= knLo[Knight[nn].r+j+dx[d]][Knight[nn].c+k+dy[d]];
                    
                    if(next!=0&&next!=nn) {
                        nextK.push(next);
                        tmp.push_back(next);
                    }
                }
                if(can==0)break;
            }
        }
    }
    if(can) move(n,d,tmp);
    
}



int main() {
    cin>>L>>N>>Q;
    chess.resize(L+2,vector <int>(L+2,2));
    knLo.resize(L+1,vector <int>(L+1,0));
    Knight.resize(N+1);

    for(int i=1;i<=L;i++){
        for(int j=1;j<=L;j++){
            cin>>chess[i][j];
        }
    }
    int r,c,h,w,k;
    for(int i=1;i<=N;i++){
        cin>>r>>c>>h>>w>>k;
        Knight[i].r=r;
        Knight[i].c=c;
        Knight[i].h=h;
        Knight[i].w=w;
        Knight[i].k=k;
        Knight[i].dm=0;
        for(int j=0;j<h;j++){
            for(int k=0;k<w;k++){
                knLo[r+j][c+k]=i;
            }
        }
    }

    int n,d,rr=0;
    while(rr++<Q){
        cin>>n>>d;
        play(n,d);
        
    }
    int ans=0;
    for(knight k: Knight){
        if(k.r!=-1) ans+=k.dm;
    }
    cout<<ans;
    return 0;
}