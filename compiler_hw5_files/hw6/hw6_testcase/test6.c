
int a[10];

void heapify(int N,int idx){
  int Largest, Left, Right;
  Largest=idx;
  Left=2*idx+1;
  Right=2*idx+2;
  int tmp;
  
  if((Left<N)&&(a[Left]>a[Largest])){
    Largest=Left;
  }
  if((Right<N)&&(a[Right]>a[Largest])){
    Largest=Right;
  }
  
  if(Largest!=idx){
    tmp=a[idx];
    a[idx]=a[Largest];
    a[Largest]=tmp;
    
    heapify(N,Largest);
  }
}

void heapsort(int N){
  int i;
  int tmp;
  for(i=(N/2)-1;i>=0;i=i-1){
    heapify(N,i);
  }
  
  for(i=N-1;i>=0;i=i-1){
    tmp=a[0];
    a[0]=a[i];
    a[i]=tmp;
    heapify(i,0);
  }
  return;
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
  
  heapsort(10);
  
  for(i=0;i<10;i=i+1){
    write(a[i]);
    write("\n");
  }
  return 0;
}
