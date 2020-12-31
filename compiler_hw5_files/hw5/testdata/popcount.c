int m, n, ret, bit, f;

int PopCount() {
  ret = 0;
  while (n > 0) {
    bit = n - (n / 2) * 2;
    if (bit) ret = ret + 1;
    n = n / 2;
  }
  return ret;
}

int MAIN() {
  m = 1;
  while (m <= 10) {
    n = m;
    write(PopCount());
    write("\n");
    m = m + 1;
  }
  f = 0;
  while (m <= 1000000000) {
    n = m;
    write(PopCount());
    write("\n");
    m = m * 2;
    if (f) m = m + 1;
    f = !f;
  }
}
