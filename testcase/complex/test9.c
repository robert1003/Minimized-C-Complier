

int a[20];

void dfs(int x){
  if(x>=20){
    return;
  }
  write("visit ");
  write(x);
  write("\n");
  dfs(x*2+1);
  dfs(x*2+2);
  return;
}

int MAIN(){
  int i;
  for(i=0;i<20;i=i+1){
    a[i]=i;
  }
  dfs(0);
  return 0;
}