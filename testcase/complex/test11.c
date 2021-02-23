

int G[5][5];

void build_graph(){
  G[0][0]=0;    G[0][1]=2;    G[0][2]=9999; G[0][3]=6;    G[0][4]=9999;
  G[1][0]=2;    G[1][1]=0;    G[1][2]=3;    G[1][3]=8;    G[1][4]=5;
  G[2][0]=9999; G[2][1]=3;    G[2][2]=0;    G[2][3]=9999; G[2][4]=7;
  G[3][0]=6;    G[3][1]=8;    G[3][2]=9999; G[3][3]=0;    G[3][4]=9;
  G[4][0]=9999; G[4][1]=5;    G[4][2]=7;    G[4][3]=9;    G[4][4]=0;
}

int Prim(){
  int d[5];
  int parent[5];
  int visited[5];
  int i,j;
  int sum=0;
  int a,w;
  
  for(i=0;i<5;i=i+1){
    d[i]=9999;
    visited[i]=0;
  }
  d[0]=0;
  parent[0]=0;
  for(i=0;i<5;i=i+1){
    a=-1;
    w=9999;
    for(j=0;j<5;j=j+1){
      if((visited[j]==0)&&(d[j]<w)){
        a=j;
        w=d[j];
      }
    }
    sum=sum+w;
    visited[a]=1;
    for(j=0;j<5;j=j+1){
      if((visited[j]==0)&&(G[a][j]<d[j])){
        d[j]=G[a][j];
        parent[j]=a;
      }
    }
  }
  return sum;
}

int MAIN(){
  int w;
  build_graph();
  w=Prim();
  write("MST weight = ");
  write(w);
  write("\n");
}