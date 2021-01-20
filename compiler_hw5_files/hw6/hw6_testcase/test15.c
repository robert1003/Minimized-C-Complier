
int MAIN(){
  int N=10;
  int W=100;
  int w[11];
  int value[11];
  int i,j;
  int dp[11][101];
  
  w[0]=0;
  w[1]=23;
  w[2]=23;
  w[3]=20;
  w[4]=22;
  w[5]=22;
  w[6]=17;
  w[7]=23;
  w[8]=17;
  w[9]=23;
  w[10]=21;
  
  
  value[0]=0;
  value[1]=130;
  value[2]=123;
  value[3]=123;
  value[4]=125;
  value[5]=127;
  value[6]=124;
  value[7]=122;
  value[8]=130;
  value[9]=121;
  value[10]=119;
  
  
  for(i=0;i<=N;i=i+1){
    for(j=0;j<=W;j=j+1){
      dp[i][j]=0;
    }
  }
  
  for(i=1;i<=N;i=i+1){
    for(j=0;j<=W;j=j+1){
      dp[i][j]=dp[i-1][j];
      if((j>=w[i])&&(dp[i][j]<dp[i-1][j-w[i]]+value[i])){
        dp[i][j]=dp[i-1][j-w[i]]+value[i];
      }
    }
  }
  
  write(dp[10][100]);
  
  return 0;
}