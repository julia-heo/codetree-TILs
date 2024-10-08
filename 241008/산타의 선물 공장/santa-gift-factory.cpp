#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int N,M,order;
//v.erase(v.begin() + i);


vector <queue <pair<int,int>>> Belt;

map <int,pair<int,int>> Box;




void getout(int w_max){
    int total=0;
    for (size_t i = 0; i < Belt.size(); ++i){
        if(Belt[i].empty()) continue;
        int first_id=Belt[i].front().first;
        int first_w=Belt[i].front().second;
        if(first_w>w_max){
            Belt[i].pop();
            Belt[i].push(make_pair(first_id,first_w));
        }else{
            Belt[i].pop();
            Box[first_id].second=-1;
            total+=first_w;
        }
    }
    
    cout<<total<<endl;
}
void remove(int r_id){
    auto it = Box.find(r_id);
    if(it == Box.end()) {
        cout<<-1<<endl;
        return;
    }
    int bn=Box[r_id].second;
    if(bn==-1)cout<<-1<<endl;
    else{
        queue <pair<int,int>> tmpque;
        while (!Belt[bn].empty()) {
            int front_id = Belt[bn].front().first;
            int front_w = Belt[bn].front().second;
            Belt[bn].pop();
            if (front_id != r_id) {
                tmpque.push(make_pair(front_id,front_w));
            }
        }
        Belt[bn]=tmpque;
        Box[r_id].second=-1;
        cout<<r_id<<endl;
    }
}
void check(int f_id){
    int bn=Box[f_id].second;
    if(bn==-1)cout<<-1<<endl;
    else{
        queue <pair<int,int>> tmpque;
        tmpque.push(make_pair(f_id,Box[f_id].first));
        while (!Belt[bn].empty()) {
            int front_id = Belt[bn].front().first;
            int front_w = Belt[bn].front().second;
            Belt[bn].pop();
            if (front_id != f_id) {
                tmpque.push(make_pair(front_id,front_w));
            }
        }
        Belt[bn]=tmpque;
        cout<<bn+1<<endl;
    }
}

void broken(int b_num){
    if(Belt[b_num].empty())cout<<-1<<endl;
    else{
        int next=0;
        for(int i=1;i<M;i++){
            if(!Belt[(b_num+i)%M].empty()){
                next=(b_num+i)%M;
            }
        }
        
        while (!Belt[b_num].empty()) {
            pair <int,int> p=Belt[b_num].front();
            Belt[next].push(p);
            Belt[b_num].pop();
            Box[p.first].second=next;
        }
        cout<<b_num+1<<endl;
    }
}


int main() {
    int K,v;
    cin>>K;
    cin>>order>>N>>M;
    Belt.resize(M);
    int n=N/M;
    int id,w;
    vector <int> inputId(N);
    vector <int> inputW(N);
    for(int i=0;i<N;i++){
        cin>>inputId[i];
    }
    for(int i=0;i<N;i++){
        cin>>inputW[i];
    }
    for(int i=0;i<N;i++){
        int num=i/n;
        Box.insert(make_pair(inputId[i],make_pair(inputW[i],num)));
        Belt[num].push(make_pair(inputId[i],inputW[i]));
    }


    for(int i=1;i<K;i++){
        cin>>order>>v;
        if(order==200) getout(v);
        else if(order==300) remove(v);
        else if(order==400) check(v);
        else if(order==500) broken(v-1);
    }


    return 0;
}