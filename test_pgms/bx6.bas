USERID GCCCMS
1  REM  bx6 version 8
   DIM xylophone = 0, yazoo = 0, quasar = 0, zapp = 0
   DIM abc = 0, xyz = 0
2  CLS
3  PRINT "hello world!"
4  LET xylophone = 50
5  LET yazoo = 100
6  LET abc = yazoo/xylophone
7  LET xyz = yazoo/10
8  LOCATE abc , xyz
9  PRINT "hello world!"
10 LET quasar = 2
11 LET zapp = 4
12 LET abc = (quasar * quasar * zapp + zapp)/5
13 LET xyz = ((quasar*quasar)*zapp)+zapp
14 LOCATE abc, xyz
15 PRINT "hello world!"
50 END
