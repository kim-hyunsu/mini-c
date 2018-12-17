int main(void) {
  int mark[4];
  mark[0] = 0;
  mark[1] = 1;
  mark[2] = 2;
  mark[3] = 3;

  printf("%d\n", mark[0]);
  printf("%d %d\n", mark[0], mark[1]);
  printf("%d %d %d\n", mark[0], mark[1], mark[2]);
  printf("%d %d %d %d\n", mark[0], mark[1], mark[2], mark[3]);

  float reals[4];
  reals[0] = 0;
  reals[1] = 1;
  reals[2] = 2;
  reals[3] = 3;

  printf("%f\n", reals[0]);
  printf("%f %f\n", reals[0], reals[1]);
  printf("%f %f %f\n", reals[0], reals[1], reals[2]);
  printf("%f %f %f %f\n", reals[0], reals[1], reals[2], reals[3]);
}
