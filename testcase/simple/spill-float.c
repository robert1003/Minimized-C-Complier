float f00() { return 3.14; }
float f01() { return f00(); }
float f02() { return f01(); }
float f03() { return f02(); }
float f04() { return f03(); }
float f05() { return f04(); }
float f06() { return f05(); }
float f07() { return f06(); }
float f08() { return f07(); }
float f09() { return f08(); }
float f10() { return f09(); }
float f11() { return f10(); }
float f12() { return f11(); }
float f13() { return f12(); }
float f14() { return f13(); }
float f15() { return f14(); }
float f16() { return f15(); }
float f17() { return f16(); }
float f18() { return f17(); }
float f19() { return f18(); }
float f20() { return f19(); }
float f21() { return f20(); }
float f22() { return f21(); }
float f23() { return f22(); }
float f24() { return f23(); }
float f25() { return f24(); }
float f26() { return f25(); }
float f27() { return f26(); }
float f28() { return f27(); }
float f29() { return f28(); }
float f30() { return f29(); }
float f31() { return f30(); }
float f32() { return f31(); }
float f33() { return f32(); }
float f34() { return f33(); }
float f35() { return f34(); }
float f36() { return f35(); }
float f37() { return f36(); }
float f38() { return f37(); }
float f39() { return f38(); }

float Work() {
  float x, y;
  x = f00() + f01() + f02() + f03() + f04() + f05() + f06() + f07() + f08() + f09() + f10() + f11() + f12() + f13() + f14() + f15() + f16() + f17() + f18() + f19() + f20() + f21() + f22() + f23() + f24() + f25() + f26() + f27() + f28() + f29() + f30() + f31() + f32() + f33() + f34() + f35() + f36() + f37() + f38() + f39();
  y = f00() * f01() * f02() * f03() * f04() * f05() * f06() * f07() * f08() * f09() * f10() * f11() * f12() * f13() * f14() * f15() * f16() * f17() * f18() * f19() * f20() * f21() * f22() * f23() * f24() * f25() * f26() * f27() * f28() * f29() * f30() * f31() * f32() * f33() * f34() * f35() * f36() * f37() * f38() * f39();
  return x + y;
}

int MAIN() {
  write(Work());
  write("\n");
}
