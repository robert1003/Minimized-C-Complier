int x;
int f() {
  x = x + 1;
  return 0;
}

int MAIN() {
  if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f() - f()) {
    write("wrong\n");
  } else if (f() * f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f() + f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else if (f()) {
    write("wrong\n");
  } else {
    write(x);
    write("\n");
    if (f()) {
      write("wrong\n");
    } else if (!f()) {
      write(x);
      write("\n");
    } else {
      f();
    }
  }
  write(x);
  write("\n");
}
