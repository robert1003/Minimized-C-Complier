int MAIN() {
  int a;
  a = 0;
  {
    int a;
    a = 1;
    write(a);
    {
      {
        int a;
        a = 2;
        {
          write(a);
          a = 3;
          write(a);
          {
            a = 4;
            write(a);
            {
              int a;
              a = 5;
              write(a);
            }
            write(a);
            a = -4;
            write(a);
          }
          write(a);
          a = -3;
          write(a);
        }
      }
    }
    write(a);
    a = -1;
    write(a);
  }
}
