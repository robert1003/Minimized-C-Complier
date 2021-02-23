int n;
int fact() {
  if (n <= 1) {
    return 1;
  } else {
    int m;
    m = n;
    n = n - 1;
    return m * fact();
  }
}
int MAIN() {
  int m;
  m = 0;
  while (m <= 10) {
    n = m;
    write(fact());
    write("\n");
    m = m + 1;
  }
}
