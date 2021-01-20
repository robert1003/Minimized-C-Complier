
int a[10];

void quicksort(int Left,int Right){
  int pivot, i, j;
  pivot = Left;
  i = Left;
  j = Right;
  int tmp;
  if(Left>=Right){
    return;
  }
  while(i<j){
    while((a[i]<=a[pivot])&&i<Right){
      i=i+1;
    }
    while(a[j]>a[pivot]&&j>=Left){
      j=j-1;
    }
    if(i<j){
      tmp=a[i];
      a[i]=a[j];
      a[j]=tmp;
    }
  }
  tmp=a[pivot];
  a[pivot]=a[j];
  a[j]=tmp;
  quicksort(Left,j-1);
  quicksort(j+1,Right);
}

int MAIN(){
  int i;
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
  quicksort(0,9);
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}
