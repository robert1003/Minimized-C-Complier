int f00() { return 1; }
int f01() { return f00(); }
int f02() { return f01(); }
int f03() { return f02(); }
int f04() { return f03(); }
int f05() { return f04(); }
int f06() { return f05(); }
int f07() { return f06(); }
int f08() { return f07(); }
int f09() { return f08(); }
int f10() { return f09(); }
int f11() { return f10(); }
int f12() { return f11(); }
int f13() { return f12(); }
int f14() { return f13(); }
int f15() { return f14(); }
int f16() { return f15(); }
int f17() { return f16(); }
int f18() { return f17(); }
int f19() { return f18(); }
int f20() { return f19(); }
int f21() { return f20(); }
int f22() { return f21(); }
int f23() { return f22(); }
int f24() { return f23(); }
int f25() { return f24(); }
int f26() { return f25(); }
int f27() { return f26(); }
int f28() { return f27(); }
int f29() { return f28(); }
int f30() { return f29(); }
int f31() { return f30(); }
int f32() { return f31(); }
int f33() { return f32(); }
int f34() { return f33(); }
int f35() { return f34(); }
int f36() { return f35(); }
int f37() { return f36(); }
int f38() { return f37(); }
int f39() { return f38(); }

int Work() {
  int x, y;
  x = f00() + f01() + f02() + f03() + f04() + f05() + f06() + f07() + f08() + f09() + f10() + f11() + f12() + f13() + f14() + f15() + f16() + f17() + f18() + f19() + f20() + f21() + f22() + f23() + f24() + f25() + f26() + f27() + f28() + f29() + f30() + f31() + f32() + f33() + f34() + f35() + f36() + f37() + f38() + f39();
  y = f00() * f01() * f02() * f03() * f04() * f05() * f06() * f07() * f08() * f09() * f10() * f11() * f12() * f13() * f14() * f15() * f16() * f17() * f18() * f19() * f20() * f21() * f22() * f23() * f24() * f25() * f26() * f27() * f28() * f29() * f30() * f31() * f32() * f33() * f34() * f35() * f36() * f37() * f38() * f39();
  return x + y;
}

int MAIN() {
  write(Work());
  write("\n");
}
