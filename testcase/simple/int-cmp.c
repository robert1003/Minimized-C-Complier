int a, b;

void IntCompare() {
  write(a); write("\n");
  write(b); write("\n");
  write(a == b); write("\n");
  write(a != b); write("\n");
  write(a > b); write("\n");
  write(a < b); write("\n");
  write(a >= b); write("\n");
  write(a <= b); write("\n");
}

int MAIN() {
  a = 123;
  b = 456; 
  IntCompare();
  a = 0;
  b = 1;
  IntCompare();
  a = -1;
  b = 123;
  IntCompare();
  a = 7777;
  b = -66;
  IntCompare();
  a = 3;
  b = 3;
  IntCompare();
  a = 0;
  b = 0;
  IntCompare();
  a = -123;
  b = -123;
  IntCompare();
}
