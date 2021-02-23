int MAIN(){
  int a[10];
  int i,j,ans;
  int dp[10];
  
  a[0]=2;
  a[1]=10;
  a[2]=3;
  a[3]=8;
  a[4]=1;
  a[5]=9;
  a[6]=4;
  a[7]=7;
  a[8]=6;
  a[9]=5;
  
  
  for(i=0;i<10;i=i+1){
    dp[i]=1;
  }
  
  ans=0;
  for(i=0;i<10;i=i+1){
    for(j=0;j<i;j=j+1){
      if(a[i]>a[j]){
        if(dp[i]<dp[j]+1){
          dp[i]=dp[j]+1;
        }
      }
    }
    if(dp[i]>ans){
      ans=dp[i];
    }
  }
  write(ans);
  
  return 0;
}