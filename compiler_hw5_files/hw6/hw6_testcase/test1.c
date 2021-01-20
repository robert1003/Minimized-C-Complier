
int MAIN(){
  int a[10];
  int i,j,tmp;
  
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
    for(j=0;j<10-1;j=j+1){
      if(a[j]>a[j+1]){
        tmp=a[j];
        a[j]=a[j+1];
        a[j+1]=tmp;
      }
    }
  }
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}