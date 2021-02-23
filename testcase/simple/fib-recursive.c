int n;

int fib() {
  int m, ret;
  m = n;
  ret = 0;
  if (n <= 1) return 1;
  n = m - 1;
  ret = ret + fib();
  n = m - 2;
  ret = ret + fib();
  return ret;
}

int MAIN() {
  int m;
  m = 1;
  while (m <= 10) {
    n = m;
    write(fib());
    m = m + 1;
  }
}
