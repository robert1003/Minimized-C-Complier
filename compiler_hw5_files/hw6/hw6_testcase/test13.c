
int G[5][5];
int d[5][5];

void build_graph(){
  G[0][0]=0;    G[0][1]=2;    G[0][2]=9999; G[0][3]=6;    G[0][4]=9999;
  G[1][0]=2;    G[1][1]=0;    G[1][2]=3;    G[1][3]=8;    G[1][4]=5;
  G[2][0]=9999; G[2][1]=3;    G[2][2]=0;    G[2][3]=9999; G[2][4]=7;
  G[3][0]=6;    G[3][1]=8;    G[3][2]=9999; G[3][3]=0;    G[3][4]=9;
  G[4][0]=9999; G[4][1]=5;    G[4][2]=7;    G[4][3]=9;    G[4][4]=0;
}

void Folyd(){
  int i,j,k;
  for(i=0;i<5;i=i+1){
    for(j=0;j<5;j=j+1){
      d[i][j]=G[i][j];
    }
  }
  for(i=0;i<5;i=i+1){
    for(j=0;j<5;j=j+1){
      for(k=0;k<5;k=k+1){
        if(d[i][j]>d[i][k]+d[k][j]){
          d[i][j]=d[i][k]+d[k][j];
        }
      }
    }
  }
  return;
}

int MAIN(){
  int i,j;
  build_graph();
  Folyd();
  write("All-Pairs Shortest Path:\n");
  for(i=0;i<5;i=i+1){
    for(j=0;j<5;j=j+1){
      write(d[i][j]);
      write(" ");
    }
    write("\n");
  }
}