float r, pi;

float Calc() {
  float ret;
  ret = r * r * pi;
  return ret;
}

int MAIN() {
  pi = 3.14159;
  r = 1.0;
  write(Calc());
  write("\n");
  r = 0.0;
  write(Calc());
  write("\n");
  r = pi;
  write(Calc());
  write("\n");
  r = 100000000000.0000;
  write(Calc());
  write("\n");
  r = 1231232131.123;
  write(Calc());
  write("\n");
}
