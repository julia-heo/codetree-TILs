#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int N;

struct node {
    int data;
    int parent;
    int authority;
    int alarm;
};
vector <node> Chat;


void alarmOn(int c){
    if(Chat[c].alarm==1)Chat[c].alarm=0;
    else Chat[c].alarm=1;
}
void powerChange(int c, int power){
    Chat[c].authority=power;
}
void changeParents(int c1, int c2){
    int tmp=Chat[c1].parent;
    Chat[c1].parent=Chat[c2].parent;
    Chat[c2].parent=tmp;
    tmp=Chat[c1].alarm;
    Chat[c1].alarm=Chat[c2].alarm;
    Chat[c2].alarm=tmp;

}
void checkAlarm(int c){
    if(Chat[c].alarm==0){
        cout<<0<<endl;
        return;
    }
    int cnt=0;
    queue <pair<int,int>> check;
    check.push(make_pair(c,1));
    while(!check.empty()){
        int front_data=check.front().first;
        int front_length=check.front().second;
        check.pop();
        for(node n:Chat){
            if(n.parent==front_data&&n.alarm==1){
                if(n.authority>=front_length){
                    cnt++;
                }
                check.push(make_pair(n.data,front_length+1));
            }
        }
    }
    cout<<cnt<<endl;

}

int main() {
    int order,Q,value1, value2;
    cin>>N>>Q;
    Chat.resize(1+N);

    // 100 준비 
    cin>>order;
    for(int i=1;i<=N;i++){
        cin>>Chat[i].parent;
        Chat[i].data=i;
        Chat[i].alarm=1;
    }
    for(int i=1;i<=N;i++){
        cin>>Chat[i].authority;
    }

    // 명령 입력
    int num=1;
    while(num++<Q){
        cin>>order;
        if(order==200){
            cin>>value1;
            alarmOn(value1);
        }
        else if (order == 300){
            cin>>value1>>value2;
            powerChange(value1,value2);
        }
        else if (order == 400){
            cin>>value1>>value2;
            changeParents(value1,value2);
        }
        else if (order == 500){
            cin>>value1;
            checkAlarm(value1);
        }
    }



    
    return 0;
}