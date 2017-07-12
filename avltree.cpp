#include<bits/stdc++.h>
using namespace std;
#define int long long
//BEGIN CUT HERE
struct AVL{
  struct node{
    int key;
    int size,height;
    node *child[2];
    node (const int &key):key(key),size(1),height(1){
      child[0]=child[1]=0;
    }
  } *root;
  typedef node *pointer;
  AVL(){root=NULL;}
  pointer find(int key){
    return find(root,key);
  }
  node *find(node *t,const int key){
    if(t==NULL) return NULL;
    if(key==(t->key)) return t;
    else if(key<(t->key)) return find(t->child[0],key);
    else return find(t->child[1],key);
  }
  void insert(const int key){
    root=insert(root,new node(key));
  }
  node *insert(node *t,node *x){
    if(t==NULL) return x;
    if((x->key)<=(t->key)) t->child[0]=insert(t->child[0],x);
    else t->child[1]=insert(t->child[1],x);
    t->size+=1;
    return balance(t);
  }
  void erase(const int key){
    int t=key;
    if(find(t)==NULL) return;
    root=erase(root,key);
  }
  node *erase(node *t,const int x){
    if(t==NULL) return NULL;
    if(x==(t->key)){
      return move_down(t->child[0],t->child[1]);
    }else{
      if(x<(t->key)) t->child[0]=erase(t->child[0],x);
      else t->child[1]=erase(t->child[1],x);
      t->size-=1;
      return balance(t);
    }
  }
  node *move_down(node *t,node *rhs){
    if(t==NULL) return rhs;
    t->child[1]=move_down(t->child[1],rhs);
    return balance(t);
  }
  int sz(node *t){
    if(t!=NULL) return t->size;
    return 0;
  }
  int ht(node *t){
    if(t!=NULL) return t->height;
    return 0;
  }
  node *rotate(node *t,int l,int r){
    node *s=t->child[r];
    t->child[r]=s->child[l];
    s->child[l]=balance(t);
    if(t!=NULL) t->size=sz(t->child[0])+sz(t->child[1])+1;
    if(s!=NULL) s->size=sz(s->child[0])+sz(s->child[1])+1;
    return balance(s);
  }
  node *balance(node *t){
    for(int i=0;i<2;i++){
      if(ht(t->child[!i])-ht(t->child[i])<-1){
	if(ht(t->child[i]->child[!i])-ht(t->child[i]->child[i])>0)
	  t->child[i]=rotate(t->child[i],i,!i);
	return rotate(t,!i,i);
      }
    }
    if(t!=NULL) t->height=max(ht(t->child[0]),ht(t->child[1]))+1;
    if(t!=NULL) t->size=sz(t->child[0])+sz(t->child[1])+1;
    return t;
  }
  pointer rank(int k){
    return rank(root,k);
  }
  pointer rank(node *t,int k){
    if(t==NULL) return NULL;
    int m=sz(t->child[0]);
    if(k<m) return rank(t->child[0],k);
    if(k==m) return t;
    if(k>m) return rank(t->child[1],k-m-1);
  }
  int index(int key){
    if(find(key)==NULL) return -1;
    return index(root,key);
  }
  int index(node *t,int key){
    if(key==(t->key)) return sz(t->child[0]);
    if(key<(t->key)) return index(t->child[0],key);
    else return sz(t)-sz(t->child[1])+index(t->child[1],key);
  }
};
//END CUT HERE

signed main(){
  int n,k;
  cin>>n>>k;
  int x[n];
  for(int i=0;i<n;i++) cin>>x[i];
  map<int,int> m;
  for(int i=0;i<n;i++) m[x[i]]=i+1;
  AVL avl;
  for(int i=0;i<k-1;i++) avl.insert(x[i]);
  for(int i=k-1;i<n;i++){
    avl.insert(x[i]);
    int key=avl.rank(k-1)->key;
    cout<<m[key]<<endl;
    assert(avl.index(key)==k-1);
  }
  return 0;
}

/*
verified on 2017/02/24
http://arc028.contest.atcoder.jp/tasks/arc028_2
http://arc033.contest.atcoder.jp/tasks/arc033_3
*/

