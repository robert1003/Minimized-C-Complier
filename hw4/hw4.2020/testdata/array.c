void f(int a){}
void ff(int a[]){}
void ff2(int a[2]){}
void fff(int a[][2]){}
int main(){
    int a,aa[1],aaa[2][3],fa[1.5];
    a=5;
    aa=1;
    aaa=2;
    aa[0]=3;
    aaa[1]=2;
    aaa[1][2]=3;
    aa[1]=aaa[2];
    aa[0]=aaa[0][1];
    a[0]=5;
    aa[1][3]=a;
    aaa[2][3][4]=a;
    aaa[1][3]=aa;
    a=aaa;
    a[1.5]=1;
    aa[0.5]=2;
    aaa[1.][1]=1;
    aaa[1][1.]=2;
    f(a);
    f(aa);
    f(aa[0]);
    ff(a);
    ff(aa);
    ff(aa[0]);
    ff(aaa);
    ff(aaa[0]);
    ff2(aa);
    ff2(aa[0]);
    fff(aa);
    fff(aaa);
    fff(aaa[0]);
}
