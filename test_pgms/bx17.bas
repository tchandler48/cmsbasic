USERID GCCCMS
'  bx17 version 17
'
  DIM xylophone# = 0, yazoo# = 0, abc = 0, xyz = 0
  DIM quasar% = 0, zapp% = 0, abcl% = 0, xyzl% = 0
  DIM abcf! = 0, xyzf! = 0, abcd# = 0, xyzd# = 0
'
Start1:
  CLS
  PRINT "hello world!"
' ------------------------------------------double float
  LET xylophone# = 50.3
  LET yazoo# = 101.25
  LET abc = yazoo# / xylophone#
  xyz = yazoo# / 10
  LOCATE abc , xyz
  PRINT "hello world!"
' ------------------------------------------long integers
  quasar% = 2
  zapp% = 4
  abcl% = (quasar% * quasar% * zapp% + zapp%)/5
  xyzl% = ((quasar% * quasar%) * zapp%) + zapp%
  LOCATE abcl%, xyzl%
  PRINT "hello world!"
' ------------------------------------------
  PRINT:
  PRINT " 2*(3+4)*5/10 = ";
  abc = 2*(3+4)*5/10
  PRINT abc
' ------------------------------------------
  abc = 11100
  xyz = 32000
  abcl% = 33000
  xyzl% = 99000
  abcf! = 33000.33
  xyzf! = 99000.47
  abcd# = 333000.33
  xyzd# = 999000.47
'                   integers
  PRINT:
  PRINT "abc=";
  PRINT abc
  PRINT "xyz=";
  PRINT xyz
'                   long integers
  PRINT "abcl%=";
  PRINT abcl%
  PRINT "xyzl%=";
  PRINT xyzl%
'                   float
  PRINT "abcf!=";
  PRINT abcf!
  PRINT "xyzf!=";
  PRINT xyzf!
'                   double
  PRINT "abcd#=";
  PRINT abcd#
  PRINT "xyzd#=";
  PRINT xyzd#
' ------------------------------------------
TheEnd:
  CLEAR
  END
