int a[2 * 2];
int b[2 * 2];
int c[2 * 2];
int kP;

void Mult() {
  int i, j, k;
  i = 0;
  while (i < 4) {
    c[i] = 0;
    i = i + 1;
  }
  i = 0;
  while (i < 2) {
    j = 0;
    while (j < 2) {
      k = 0;
      while (k < 2) {
        c[i * 2 + j] = c[i * 2 + j] + a[i * 2 + k] * b[k * 2 + j];
        c[i * 2 + j] = c[i * 2 + j] - (c[i * 2 + j] / kP) * kP;
        k = k + 1;
      }
      j = j + 1;
    }
    i = i + 1;
  }
}

int n;

int Fib() {
  int x[2 * 2], y[2 * 2], i;
  x[0] = 1;
  x[1] = 1;
  x[2] = 1;
  x[3] = 0;
  y[0] = 1;
  y[1] = 0;
  y[2] = 0;
  y[3] = 1;
  while (n > 0) {
    int bit;
    bit = n - n / 2 * 2;
    if (bit) {
      i = 0;
      while (i < 4) {
        a[i] = y[i];
        b[i] = x[i];
        i = i + 1;
      }
      Mult();
      i = 0;
      while (i < 4) {
        y[i] = c[i];
        i = i + 1;
      }
    }
    i = 0;
    while (i < 4) {
      a[i] = x[i];
      b[i] = x[i];
      i = i + 1;
    }
    Mult();
    i = 0;
    while (i < 4) {
      x[i] = c[i];
      i = i + 1;
    }
    n = n / 2;
  }
  return y[0];
}

int MAIN() {
  int m;
  kP = 10003;
  m = 1;
  while (m <= 10) {
    n = m;
    write(Fib());
    write("\n");
    m = m + 1;
  }
  while (m <= 1000000000) {
    n = m;
    write(Fib());
    write("\n");
    m = m * 10;
  }
}
