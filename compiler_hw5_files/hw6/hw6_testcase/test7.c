
int a[10];

int linear_search(int N,int x){
  int i;
  for(i=0;i<N;i=i+1){
    if(a[i]==x){
      return i;
    }
  }
  return -1;
}

int MAIN(){
  int pos;
  a[0]=2;
  a[1]=7;
  a[2]=28;
  a[3]=83;
  a[4]=874;
  a[5]=999;
  a[6]=3232;
  a[7]=4343;
  a[8]=66666;
  a[9]=7878787;
  
  pos=linear_search(10,66666);
  
  if(pos==-1){
    write("not found\n");
  }
  else{
    write("66666 is at ");
    write(pos);
    write("\n");
  }
  
  return 0;
}