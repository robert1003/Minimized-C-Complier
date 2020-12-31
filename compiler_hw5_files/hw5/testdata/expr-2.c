int a, b, c, d, e, f;

int A() { return a; }
int B() { return b; }
int C() { return c; }
int D() { return d; }
int E() { return e; }
int F() { return f; }

int MAIN() {
  a = 4;
  b = 3;
  c = 2;
  d = 1;
  e = 5;
  f = 6;
  write(a + b + c + d + e + f);
  write("\n");
  write(a * (b + c) + (d * e / f) * f + 123);
  write("\n");
  write(a && b + c && d + e || f);
  write("\n");
  write(b / b * a);
  write("\n");
  write(a / b / c / d / e / f);
  write("\n");
  write(a && b || c + a * (d + e + f) / 5);
  write("\n");

  write(A() + B() + C() + D() + E() + F());
  write("\n");
  write(A() * (B() + C()) + (D() * E() / F()) * F() + 123);
  write("\n");
  write(A() && B() + C() && D() + E() || F());
  write("\n");
  write(B() / B() * A());
  write("\n");
  write(A() / B() / C() / D() / E() / F());
  write("\n");
  write(A() && B() || C() + A() * (D() + E() + F()) / 5);
  write("\n");
}
