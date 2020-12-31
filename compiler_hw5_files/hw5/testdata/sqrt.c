float n, l, r, mid;
int iter;

float SquareRoot() {
  l = 0;
  r = n; 
  iter = 0;
  while (r - l > 0.0001 && iter < 100) {
    mid = 0.5 * (l + r);
    if (mid * mid < n) l = mid;
    else r = mid;
    iter = iter + 1;
  }
  return l;
}

int MAIN() {
  n = 1;
  while (n <= 10.0) {
    write(SquareRoot());
    write("\n");
    n = n + 1.0;
  }
  n = 1231283.213;
  write(SquareRoot());
  write("\n");
  n = 4578708.57841;
  write(SquareRoot());
  write("\n");
  n = 9.8596;
  write(SquareRoot());
  write("\n");
}
