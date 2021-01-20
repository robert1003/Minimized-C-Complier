int fac(int n){
    write("call ");
    write(n);
    write("\n");
    if(n==0) return 1;
    return n*fac(n-1);
}
int MAIN(){
    int i;
    for(i=0;i<=10;i=i+1){
        write(fac(i));
        write("\n");
    }
}
