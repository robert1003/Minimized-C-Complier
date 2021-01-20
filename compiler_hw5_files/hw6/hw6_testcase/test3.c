
int MAIN(){
  int a[10];
  int i,j,tmp,min_idx;
  
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
    min_idx=i;
    for(j=i+1;j<10;j=j+1){
      if(a[j]<a[min_idx]){
        min_idx=j;
      }
    }
    tmp=a[i];
    a[i]=a[min_idx];
    a[min_idx]=tmp;
  }
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}