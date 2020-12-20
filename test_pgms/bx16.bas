USERID GCCCMS
'  bx16 version 16
'
Start1:
  CLS
' ------------------------------------------
  DIM  abc = 11100, xyz = 32000
  DIM  abcl% = 33000, xyzl% = 99000
  DIM  abcf! = 33000.33, xyzf! = 99000.47
  DIM  abcd# = 333000.33, xyzd# = 999000.47
'
'                   integer
  PRINT:
  PRINT "abc=";
  PRINT abc
  PRINT "xyz=";
  PRINT xyz
'                   long
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
