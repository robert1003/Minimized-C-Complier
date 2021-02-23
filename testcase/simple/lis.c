int seed, n;

int rand() {
  seed = seed * 131 + 1;
  seed = seed - (seed / 100000) * 100000;
  return seed;
}

int DoLIS() {
  int arr[100000], i, lis[100000], len; 
  i = 0;
  while (i < n) {
    arr[i] = rand();
    i = i + 1;
  }
  len = 0;
  i = 0;
  while (i < n) {
    if (len == 0) {
      lis[len] = arr[i];
      len = len + 1;
    } else if (lis[len - 1] <= arr[i]) {
      lis[len] = arr[i];
      len = len + 1;
    } else {
      int bit, pos;
      bit = 65536;
      pos = -1;
      while (bit > 0) {
        if (pos + bit < len) {
          if (lis[pos + bit] <= arr[i]) {
            pos = pos + bit;
          }
        }
        bit = bit / 2;
      }
      if (pos + 1 >= len) {
        write("wrong\n");
        return -1;
      }
      if (lis[pos + 1] <= arr[i]) {
        write("wrong");
        return -1;
      }
      lis[pos + 1] = arr[i];
    }
    i = i + 1;
  }
  i = 1;
  while (i < len) {
    if (lis[i] < lis[i - 1]) {
      write("wrong\n");
      return -1;
    }
    i = i + 1;
  }
  write("correct\n");
  return len;
}

int MAIN() {
  n = 1;
  while (n <= 10) {
    write(DoLIS());
    write("\n");
    n = n + 1;
  }
  while (n <= 100000) {
    write(DoLIS());
    write("\n");
    n = n * 10;
  }
}
