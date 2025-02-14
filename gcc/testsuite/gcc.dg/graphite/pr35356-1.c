/* { dg-options "-O2 -fgraphite-identity -fdump-tree-graphite-all" } */

int a[100];

int
foo (int bar, int n, int k)
{
  int i;

  for (i = 0; i < n; i++)
    if (i == k)
      a[i] = bar;

  for (i = 0; i < n; i++)
    if (i == k)
      a[i] = bar;

  return a[bar];
}

/* There should be no loops generated for this testcase, instead we
   should generate the following:

   | if (k >= 0 && k < n)
   |   a[k] = bar;

   Check that this text is produced:

ISL AST generated by ISL:
if (n >= k + 1 && k >= 0) {
  S_6(k);
  S_11(k);
}

*/

/* { dg-final { scan-tree-dump-times "if \\\(P_9 >= P_10 \\\+ 1 && P_10 >= 0\\\) \\\{" 1 "graphite" } } */
