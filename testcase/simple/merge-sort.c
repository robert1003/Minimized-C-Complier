int n, arr[100000], tmp[100000], seed, l, r;
int i, j, k;

int rand() {
  seed = seed * 131 + 1;
  seed = seed - (seed / 100000) * 100000;
  return seed;
}

void MergeSort() {
  int mid, tl, tr;
  if (r - l == 1) return;
  mid = (l + r) / 2;
  tl = l;
  tr = r;
  r = mid;
  MergeSort();
  l = mid;
  r = tr;
  MergeSort();
  l = tl;
  r = tr;
  i = l;
  j = mid;
  k = l;
  while (i < mid && j < r) {
    if (arr[i] < arr[j]) {
      tmp[k] = arr[i];
      i = i + 1;
    } else {
      tmp[k] = arr[j];
      j = j + 1;
    }
    k = k + 1;
  }
  while (i < mid) {
    tmp[k] = arr[i];
    i = i + 1;
    k = k + 1;
  }
  while (j < r) {
    tmp[k] = arr[j];
    j = j + 1;
    k = k + 1;
  }
  i = l;
  while (i < r) {
    arr[i] = tmp[i];
    i = i + 1;
  }
}

void DoMergeSort() {
  int i;
  i = 0;
  while (i < n) {
    arr[i] = rand();
    i = i + 1;
  }
  l = 0;
  r = n;
  MergeSort();
  i = 1;
  while (i < n) {
    if (arr[i] < arr[i - 1]) {
      write("wrong\n");
      return;
    }
    i = i + 1;
  }
  write("correct\n");
}

int MAIN() {
  n = 1;
  while (n < 10) {
    seed = n;
    DoMergeSort();
    n = n + 1;
  }
  while (n <= 100000) {
    seed = 123;
    DoMergeSort();
    n = n * 10;
  }
}
