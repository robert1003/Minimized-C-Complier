int sum[100000 + 1], arr[100000];
int n, q, seed, i, j, l, r, tmp, brute;

int rand() {
  seed = seed * 131 + 1;
  seed = seed - (seed / 100000) * 100000;
  return seed;
}

void DoPartialSum() {
  i = 0;
  while (i < n) {
    arr[i] = rand();
    arr[i] = arr[i] - (arr[i] / 100) * 100;
    i = i + 1;
  }
  while (i < n) {
    sum[i + 1] = sum[i] + arr[i];
    i = i + 1;
  }
  while (i < q) {
    l = rand();
    if (l >= n) {
      l = l - (l / n) * n;
    }
    r = rand();
    if (r >= n) {
      r = r - (r / n) * n;
    }
    if (l > r) {
      tmp = l;
      r = l;
      l = tmp;
    }
    write(sum[r + 1] - sum[l]);
    write("\n");
    brute = 0;
    j = l;
    while (j <= r) {
      brute = brute + arr[j];
      j = j + 1;
    }
    if (brute != sum[r + 1] - sum[l]) write("wrong\n");
    else write("correct\n");
    i = i + 1;
  }
}

int MAIN() {
  n = 1;
  while (n < 10) {
    q = n;
    seed = n;
    DoPartialSum();
    n = n + 1;
  }
  while (n <= 100000) {
    q = 10;
    seed = 123 * n;
    DoPartialSum();
    n = n * 10;
  }
  return 0;
}
