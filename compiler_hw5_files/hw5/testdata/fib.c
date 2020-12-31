int n;

int DoFib() {
  int fib[50];
  int i;
  fib[0] = 0;
  fib[1] = 1;
  i = 2;
  while (i <= n) {
    fib[i] = fib[i - 1] + fib[i - 2];
    i = i + 1;
  }
  return fib[n];
}

int MAIN() {
  n = 1;
  while (n <= 10) {
    write(DoFib());
    n = n + 1;
  }
}
