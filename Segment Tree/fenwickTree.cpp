#include <bits/stdc++.h>
using namespace std;
vector<int>a;
class fenwickTree{
    public:
        vector<int> Tree;
        int n;
        fenwickTree(int n){
            Tree.resize(n+1,0);
            this->n=n;
        }
        void add(int idx,int v){
            while(idx<=n){//can extend 
                Tree[idx]+=v;
                idx+=idx&(-idx);//removes lsb
                //-a= 1+ (~a) (all inverted bits of a)
            }
        }
        int sum(int L,int R){
            if(L>R)return 0;
            return query(R)-query(L-1);
        }
        int query(int idx){
            // 1 to idx
            int ans=0;
            while(idx>0){//will only shrink
                ans+=Tree[idx];
                idx-=idx&(-idx);
            }
            return ans;
        }
};
int32_t main(){
    int n;cin>>n;
    a.resize(n+1,0);
    for(int i=1;i<=n;i++)cin>>a[i];
    fenwickTree ft(n);
    for(int i=1;i<=n;i++)ft.add(i,a[i]);
    cout<<ft.sum(1,3)<<'\n';
    //when point updating , just add(idx,newVal-oldVal)
}
