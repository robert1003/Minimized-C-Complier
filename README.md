# C-- Compiler

A minimized RISCV C compiler that supports a subset of C operations, including functions and recursions, arithmetic operators, multi-dimensional arrays, and flow control statements.

Some Caveats
* Definition must be at the top of each function

## Example program

* Binary Search
```c
int a[10];

int binary_search(int N,int x){
  int Left=0;
  int Right;
  int Mid;
  Right=N-1;
  
  while(Left<=Right){
    Mid=(Left+Right)/2;
    if(a[Mid]==x){
      return Mid;
    }
    if(a[Mid]<x){
      Left=Mid+1;
    }
    else{
      Right=Mid-1;
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
  
  pos=binary_search(10,66666);
  
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
```

* Dijkstra (Single Source Shortest Path)
```c
int G[5][5];
int d[5];

void build_graph(){
  G[0][0]=0;    G[0][1]=2;    G[0][2]=9999; G[0][3]=6;    G[0][4]=9999;
  G[1][0]=2;    G[1][1]=0;    G[1][2]=3;    G[1][3]=8;    G[1][4]=5;
  G[2][0]=9999; G[2][1]=3;    G[2][2]=0;    G[2][3]=9999; G[2][4]=7;
  G[3][0]=6;    G[3][1]=8;    G[3][2]=9999; G[3][3]=0;    G[3][4]=9;
  G[4][0]=9999; G[4][1]=5;    G[4][2]=7;    G[4][3]=9;    G[4][4]=0;
}

void Dijkstra(){
  int parent[5];
  int visited[5];
  int i,j;
  int a,w;
  
  for(i=0;i<5;i=i+1){
    d[i]=9999;
    visited[i]=0;
  }
  d[0]=0;
  parent[0]=0;
  for(i=0;i<5;i=i+1){
    a=-1;
    w=9999;
    for(j=0;j<5;j=j+1){
      if((visited[j]==0)&&(d[j]<w)){
        a=j;
        w=d[j];
      }
    }
    
    visited[a]=1;
    for(j=0;j<5;j=j+1){
      if((visited[j]==0)&&(d[a]+G[a][j]<d[j])){
        d[j]=d[a]+G[a][j];
        parent[j]=a;
      }
    }
  }
}

int MAIN(){
  int i;
  build_graph();
  Dijkstra();
  write("Single-Source Shortest Path:\n");
  for(i=0;i<5;i=i+1){
    write("0-->");
    write(i);
    write(": cost=");
    write(d[i]);
    write("\n");
  }
}
```

## Steps

Source code

-> Lexical Analysis: Use [Flex](https://github.com/westes/flex) to parse source code to token stream (lexer3.l, define the Context Free Grammar (CFG) of the C--)

-> Syntax Analysis: Use [Bison](https://www.gnu.org/software/bison/) to build [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree) (AST) from token stream (parser.y)

-> Semantic Analysis: Analyze AST's semantics and check for errors (semanticAnalysis.c)

-> Code Generation: Generate assembly code from AST (codegen.c)

-> Convert the assembly file to object file with `riscv64-linux-gnu-gcc` compiler

-> Run it on a RISCV64 simulator (we use `qemu-riscv64` on CSIE workstation)
