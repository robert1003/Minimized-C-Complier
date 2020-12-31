int x;
int f() {
  write(x); write("\n");
  x = 2;
  write(x); write("\n");
  return 3;
}

int MAIN() {
  write(x); write("\n");
  x = f();
  write(x); write("\n");
}
