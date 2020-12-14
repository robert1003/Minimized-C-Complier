typedef int I0,I1[2],I2[3][2],I3[4][2][3];
typedef float F;
void f0(int a){}
void f1(int a[]){}
void f2(int a[3]){}
void f3(int a[][3]){}
int main(){
    I0 i00,i01[2],i02[3][2],i03[2][2][3];
    I1 i11,i12[2],i13[3][2];
    I2 i22,i23[3];
    I3 i3;
    F f;
    f0(i00); 
    f0(i01); 
    f0(i11); 
    f0(i11[0]); 
    f0(i23[0][1]);
    f0(i3[1][2][3]);
    f0(f);
    f1(i00);
    f1(i01);
    f1(i11);
    f1(i13);
    f1(i22[0]);
    f1(i22[1][3]);
    f2(i02);
    f2(i13);
    f2(i12);
    f2(i22);
    f2(i22[0]);
    f2(i12[0][1]);
    f2(i13[1]);
    f2(i3[0]);
    f3(i13);
    f3(i3);
    f3(i12);
}
