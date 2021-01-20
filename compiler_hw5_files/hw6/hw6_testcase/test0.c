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
  
    i=0;
  
  while(i<10) {                                                                                                                                                                        
      write(i);
      write("\n");
      write(a[i]);
      write("\n");
      i=i+1;
    }
    write(i);
    return 0;
  }
