int a(){}
float b(int a){}
void c(float c){}
void d(int a,float b){}
int main(){
    int aa,bb;
    a();
    a(1);
    b();
    b(bb);
    b(2,aa);
    c();
    c(0);
    c(aa,2.3);
    c(b);
    c("abc");
    d();
    d(bb);
    d(123,4.5);
    d("abc",123);
    d(aa,456,bb);
    write("abc");
    write(123);
    write(1.5);
    write(123,aa);
    read();
    b=read(123);
    fread();
    aa=fread(456);
    write(cc);
    write(c);
}
