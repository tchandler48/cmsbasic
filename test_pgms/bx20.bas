USERID GCCCMS
'  bx20 version 20
'
  DIM abc = 0, xyz = 0, abcl% = 0, xyzl% = 0
  DIM abcf! = 0, xyzf! = 0, abcd# = 0, xyzd# = 0
'
Start1:
  CLS
  PRINT "hello world!"
' ------------------------------------------
  abc = 2*(3+4)*5/10
  PRINT "": " 2*(3+4)*5/10 ="; abc
' ------------------------------------------
  abc = 11100
  xyz = 32000
  abcl% = 33000
  xyzl% = 99000
  abcf! = 33000.33
  xyzf! = 99000.47
  abcd# = 333000.33
  xyzd# = 999000.47
'                                               integers
  PRINT "": "abc="; abc: "xyz="; xyz
'                                               long integers
  PRINT "abcl%="; abcl%: "xyzl%="; xyzl%
'                                               float
  PRINT "abcf!="; abcf!: "xyzf!="; xyzf!
'                                               double
  PRINT "abcd#="; abcd#: "xyzd#="; xyzd#
' ------------------------------------------
TheEnd:
  CLEAR
  END
