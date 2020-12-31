float a, b;

void FloatCompare() {
  write(a); write("\n");
  write(b); write("\n");
  write(a == b); write("\n");
  write(a != b); write("\n");
  write(a >= b); write("\n");
  write(a <= b); write("\n");
  write(a > b); write("\n");
  write(a < b); write("\n");
}

int MAIN() {
  a = 0.0;
  b = 0.0;
  FloatCompare();
  a = 1.0;
  b = 0.0;
  FloatCompare();
  a = 1.123;
  b = 4.456;
  FloatCompare();
  a = -1.0;
  b = 0.0;
  FloatCompare();
  a = -1.0;
  b = -0.0;
  FloatCompare();
  a = 0.0;
  b = 1232.343;
  FloatCompare();
  a = 0.23483;
  b = 3.14159;
  FloatCompare();
  a = -1.414;
  b = 0.000001;
  FloatCompare();
  a = 1.313;
  b = 1.3130;
  FloatCompare();
}
