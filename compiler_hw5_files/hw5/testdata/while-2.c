int i, j;
int MAIN() {
  i = 0;
  while (i < 10) {
    j = 9;
    while (j >= 0) {
      write(i);
      write(" ");
      write(j);
      write("\n");
      j = j - 1;
    }
    i = i + 1;
  }
}
