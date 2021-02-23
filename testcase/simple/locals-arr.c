void f() {
  int a;
  int b[100];
  int c;
  int d[100];
  float e;
  int f;
  float g[1000];
  int h;
  a = 123;
  g[123] = 777.777;
  b[0] = a;
  b[77] = b[0] + b[0];
  f = f;
  e = 1.0 / 2.0;
  f = a * a;
  h = a && a;
  d[9] = (a == f) + (a == h);
  write(a);
  write(b[0]);
  write(b[77]);
  c = b[77] - b[0];
  write(c);
  write(g[123]);
  write(d[9]);
  write(h);
  write(f);
}

int MAIN() {
  f();
  f();
  f();
}
