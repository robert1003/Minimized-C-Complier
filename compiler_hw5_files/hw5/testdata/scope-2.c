int MAIN() {
  int a[100];
  int b[100];
  b[99] = 456;
  {
    int a[100];
    {
      int a[100];
      a[0] = 123;
      write(a[0]);
      write(b[99]);
    }
    a[0] = 456;
    write(a[0]);
    write(b[99]);
    {
      int b[100];
      b[99] = 666;
      write(a[0]);
      write(b[99]);
    }
  }
  write(a[0]);
  write(b[99]);
}
