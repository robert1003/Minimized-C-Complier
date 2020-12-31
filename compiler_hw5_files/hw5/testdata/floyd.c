int dist[100 * 100];
int seed, n;

int rand() {
  seed = seed * 131 + 1;
  seed = seed - (seed / 100000) * 100000;
  return seed;
}

void DoFloyd() {
  int i, j, k;
  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      if (i == j) {
        dist[i * n + j] = 0;
      } else if (i < j) {
        int x;
        x = rand();
        dist[i * n + j] = x;
        dist[j * n + i] = x;
      }
      j = j + 1;
    }
    i = i + 1;
  }
  k = 0;
  while (k < n) {
    i = 0;
    while (i < n) {
      j = 0;
      while (j < n) {
        if (dist[i * n + k] + dist[k * n + j] < dist[i * n + j]) {
          dist[i * n + j] = dist[i * n + k] + dist[k * n + j];
        }
        j = j + 1;
      }
      i = i + 1;
    }
    k = k + 1;
  }
  i = 0;
  while (i < n) {
    j = 0;
    while (j < n) {
      write(dist[i * n + j]);
      write(" ");
      j = j + 1;
    }
    write("\n");
    i = i + 1;
  }
}

int MAIN() {
  n = 1;
  while (n <= 10) {
    DoFloyd();
    n = n + 1;
  }
}
