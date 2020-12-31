int a, b, c;

void If() {
  if (a == b) {
    if (b == c) write("a = b = c");
    else if (a > b) write("dead");
    else if (a == c) write("dead");
  } else if (b == c || a == c) {
    if (a < b && a > b) write("dead");
    if (b == c) {
      if (a > c) write("a > b = c");
      else write("b = c > a");
    } else {
      if (b > a) write("b > a = c");
      else if (b > c) write("dead");
      else write("b < a = c");
    }
  }
  if (a != b && b != c && a != c) {
    if (a > b) {
      if (a > c) {
        if (b > c) write("a > b > c");
        else write("a > c > b");
      } else {
        if (b > c) write("dead");
        else write("c > a > b");
      }
    } else {
      if (a < c) {
        if (b > c) write("b > c > a");
        else write("c > b > a");
      } else {
        if (b > c) write("b > a > c");
        else write("dead");
      }
    }
  }
}

int MAIN() {
  a = 0;
  b = 0;
  c = 0;
  If();
  a = 1;
  b = 0;
  c = 0;
  If();
  a = 2;
  b = 1;
  c = 0;
  If();
  a = 1;
  b = 2;
  c = 0;
  If();
  a = 0;
  b = 1;
  c = 2;
  If();
  a = 0;
  b = 0;
  c = 1;
  If();
  a = 1;
  b = 1;
  c = 0;
  If();
  a = 0;
  b = 1;
  c = 0;
  If();
  a = 1;
  b = 0;
  c = 1;
  If();
  a = 0;
  b = 1;
  c = 1;
  If();
  a = 0;
  b = 2;
  c = 1;
  If();
  a = 2;
  b = 0;
  c = 1;
  If();
  a = 1;
  b = 0;
  c = 2;
  If();
}
