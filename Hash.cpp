//Kyokai no Kanata //
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> II;
typedef vector<II> VII;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef long long int LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr<<name<<" : "<<arg1<<endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
  const char* comma=strchr(names+1,',');
  cerr.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...)
#endif
class Hash{
  public:
    int bufsize,marker,mod;
    vector<set<int>> Bucket;
    vector<set<int>> Overflow;
    Hash(int sz,int bufsz){
      bufsize = bufsz,mod= sz;
      Bucket.resize(sz);marker=0;
      Overflow.resize(sz);
    }
    void split(int val)
    {
      Bucket.PB(set<int>());Overflow.PB(set<int>());
      for(auto v:Bucket[val]) if(v%(2*mod)==val+mod)  Bucket[val+mod].insert(v);
      for(auto v:Bucket[val+mod]) Bucket[val].erase(v);
      for(auto v:Overflow[val]) if(v%(2*mod)==val+mod)  Overflow[val+mod].insert(v);
      for(auto v:Overflow[val+mod]) Overflow[val].erase(v);
    }
    void changemod(){
      for(int i=0;i<mod;i++) Bucket.PB(set<int>()),Overflow.PB(set<int>());
      mod*=2;marker=0;
    }
    int insert(int x)
    {
      int bucketno = x%mod;
      if(bucketno < marker) bucketno = x%(2*mod);
      if (Bucket[bucketno].count(x)+ Overflow[bucketno].count(x)) return 0;
      if(Bucket[bucketno].size()==bufsize) 
      {
        Overflow[bucketno].insert(x);
        split(marker++);
        if(marker==mod) changemod();
      }
      else Bucket[bucketno].insert(x);
      return 1;
    }
};
const int VV = int(1e9)+5;
vector<int> Input;
vector<int> Output;
void emptyOutput()
{
      reverse(ALL(Output));
      while(Output.size())
      {
        auto x = Output.back(); 
        Output.pop_back();
        dout(x-VV);
      }
      fflush(stdout);
}
int main(int argc,char *argv[])
{
  if(argc<4) cerr<<"Invalid input" <<endl;
  int M = atoi(argv[1]); 
  int B = atoi(argv[2]);freopen(argv[3],"r",stdin);
  Hash H = Hash(M-1,B);
  int x;
  while(1)
  {
    while(Input.size()<((M-1)*B) && si(x)!=EOF) Input.PB(x+VV);         
    if(!Input.size()) {emptyOutput();break;}
    reverse(ALL(Input)); 
    while(Input.size())
    {
      auto x = Input.back(); 
      Input.pop_back(); 
      if(H.insert(x)) Output.PB(x);
      if(Output.size()==B) emptyOutput();
    }
  }
  return 0;
}
