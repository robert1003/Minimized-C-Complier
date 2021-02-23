int x;

int f() {
  x = x + 1;
  return 1;
}

int MAIN() {
  write(x);
  write("\n");
  if (f()) {
    write(x);
    write("\n");
    if (f() + f()) {
      write(x);
      write("\n");
    }
    if (f() - f()) {
      write("wrong\n");
    }
    write(x);
    write("\n");
  }
}
