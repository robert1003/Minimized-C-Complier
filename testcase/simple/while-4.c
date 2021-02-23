int x;

int f() {
  x = x + 1;
  return x;
}

int MAIN() {
  x = -10;
  while (f()) {
    write(x);
    write("\n");
  }
  write(x);
  write("\n");
  while (!f()) {
    write(x);
    write("\n");
  }
}
