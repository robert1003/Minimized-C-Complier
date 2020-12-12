int b;
float b;
int main(){
    a=5;
    {
        int aa;
        aa=1;
        a=aa;
        aa=a;
        {
            int aa,a;
            float a;
            a=a*2+aa;
        }
        {
        int aa;
        a=5;
        aa();
        }
    }
    {
        int a;
        float aa;
        int a;
        b();
        aa();
        b=a;
    }
    b=1;
    b=a;
    return 0;
}
