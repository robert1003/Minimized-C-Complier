int g1, g2;
float f1;
int arr[123];
float f2, f3[1000];

int large[10000000];
int x, y, z;
int i;

void Init() {
  i = 0;
  while (i < 10000000) {
    large[i] = i;
    i = i + 1;
  }
}

void Print() {
  write(g1);
  write(g2);
  g1 = -3;
  g2 = 3;
}

void Copy() {
  x = 0;
  i = 0;
  while (i < 123) {
    if (x) arr[i] = g1;
    else arr[i] = g2;
    x = 1 - x;
    i = i + 1;
  }
}

void CopyFloat() {
  i = 2;
  while (i < 1000) {
    f3[i] = f3[i - 2];
    i = i + 1;
  }
  write(f3[123]);
  write(f3[456]);
  f3[123] = f3[123] + f2;
  f3[456] = f3[456] - f2;
}

int MAIN() {
  Init(); 
  write(large[123]);
  write(large[456]);
  g1 = 3;
  g2 = -3;
  Print();
  write(g1);
  write(g2);
  Copy();
  write(arr[1]);
  write(arr[2]);
  write(arr[3]);
  write(arr[121]);
  write(arr[122]);
  f2 = 0.5;
  f3[0] = 0.5;
  f3[1] = 1.5;
  f3[2] = 2.5;
  CopyFloat();
  write(f3[123]);
  write(f3[456]);
}
