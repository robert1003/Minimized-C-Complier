int b, i;

void IfWhile() {
  if (b) {
    i = 0;
    if (b > 0) {
      while (i < 10) {
        write(i);
        write("\n");
        i = i + 1;
      }
    } else {
      i = 9;
      while (i >= 0) {
        write(i);
        write("\n");
        i = i - 1;
      }
    }
  } else {
    i = 0;
    while (i < 10) {
      write(0);
      write("\n");
      i = i + 1;
    }
    if (!b) b = 1;
  }
}

int MAIN() {
  b = 0;
  IfWhile();
  IfWhile();
  b = -1;
  IfWhile();
}
