#include "../include/hashset.hpp"
#include "stdbool.h"

int test(char* label, bool a, bool b) {
  printf("%s: ", label);
  if (a==b) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed. lhs=%x, rhs= %x\n",a,b);
    exit(1);
  }
}

int main() {

	HashSet hs(10);

  int a = 0x12ab345;
  int b = 0xfeed425;
  int c = 0xabcd38;
  int d = 0x1235698;
  int e = 0x2c374;
  int f = 0xa0f8982;
  int g = 0x053eba;
  int h = 0x61c2f5e;
  int i = 0xe0295f2;
  int j = 0x5e700eaa;
  int k = 0xe75bf1;
  int l = 0x6baa9bb;
  int m = 0x8b1390a;
  int n = 0x59dd1;
  int o = 0xfc32;
  int p = 0xa9d89d8;
  int q = 0x5b2c9e;
  int r = 0x2431e3;
  int s = 0x1910a;
  int t = 0x72;

	hs.insert(a); // insert an item into the table

 	test("Test1", hs.contains(a), true); // find the item
  test("Test2", hs.insert(a), false); // can't insert the same item twice

  hs.insert(b);
  hs.insert(c);
  hs.insert(d);
  hs.insert(e);
  hs.insert(f);
  hs.insert(g);
  hs.insert(h);
  hs.insert(i);
  hs.insert(j);
  hs.insert(k);
  hs.insert(l);
  hs.insert(m);
  hs.insert(n);
  hs.insert(o);
  hs.insert(p);
  hs.insert(q);
  hs.insert(r);
  hs.insert(s);
  hs.insert(t);


  test("Test3", hs.remove(a), true); // test remove
  test("Test4", hs.contains(a), false); // the item should be gone
  test("Test5", hs.remove(a), false); // can't remove again
  test("Test6", hs.insert(a), true); // but we can add it back

  // 5 new tests I created
  test("newTest7", hs.contains(r), true); // test contains with r
  test("newTest8", hs.insert(a), false); // cant insert item again
  test("newTest9", hs.remove(a), true); // should be able to remove because we couldnt add another a
  test("newTest10", hs.insert(o), false); // cant insert o again
  test("newTest11", hs.contains(o), true); // seeing if able to find o in the array of LL after insertion

  return 0;
}
