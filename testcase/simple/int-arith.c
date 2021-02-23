int a, b;

void IntArith() {
  write(a); write("\n");
  write(b); write("\n");
  write(a + b); write("\n");
  write(a - b); write("\n");
  write(a * b); write("\n");
  write(a / b); write("\n");
  write(a && b); write("\n");
  write(a || b); write("\n");
  write(!a); write("\n");
  write(!b); write("\n");
  write(-a); write("\n");
  write(-b); write("\n");
}

int MAIN() {
  a = 123;
  b = 456; 
  IntArith();
  a = 0;
  b = 1;
  IntArith();
  a = -1;
  b = 123;
  IntArith();
  a = 7777;
  b = -66;
  IntArith();
}
