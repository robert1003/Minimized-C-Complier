int MAIN() {
  int a;
  a = 1;
  {
    int a;
    a = 2;
    write(a);
  }
  write(a);
}
