float a, b;

void FloatArith() {
  write(a); write("\n");
  write(b); write("\n");
  write(a + b); write("\n");
  write(a - b); write("\n");
  write(a * b); write("\n");
  write(a / b); write("\n");
  write(-a); write("\n");
  write(-b); write("\n");
}

int MAIN() {
  a = 0.0;
  b = 0.0;
  FloatArith();
  a = 1.0;
  b = 0.0;
  FloatArith();
  a = 1.123;
  b = 4.456;
  FloatArith();
  a = -1.0;
  b = 0.0;
  FloatArith();
  a = -1.0;
  b = -0.0;
  FloatArith();
  a = 0.0;
  b = 1232.343;
  FloatArith();
  a = 0.23483;
  b = 3.14159;
  FloatArith();
  a = -1.414;
  b = 0.000001;
  FloatArith();
}
