int a, b, c, d, seed, x;

int rand() {
  seed = seed * 131 + 1;
  seed = seed - (seed / 100001) * 100001;
  return seed;
}

int rand2() {
  x = rand();
  x = x - x / 2 * 2;
  return x;
}

void DoWhile() {
  a = rand2();
  b = rand2();
  c = rand2();
  d = rand2();
  while (a || !b || c && d) {
    write(a); write(" "); write(b); write(" "); write(c); write(" "); write(d); write("\n");
    a = rand2();
    b = rand2();
    c = rand2();
    d = rand2();
  }  
}

int MAIN() {
  seed = 7122;
  DoWhile();
  seed = 123;
  DoWhile();
  seed = 456;
  DoWhile();
}
