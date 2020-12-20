USERID GCCCMS
'  bx21 version 21
'
  DIM Hello$ = "", test$ = ""
  DIM abc = 0, xyz = 0, yazoo# = 0, xylophone# = 0
  DIM quasar% = 0, zapp% = 0, abcl% = 0, xyzl% = 0
  DIM abcf! = 0, xyzf! = 0, abcd# = 0, xyzd# = 0
'
  GOSUB Start1
  GOSUB DoubleFloat
  GOSUB LongIntegers
  GOSUB RDParser
  GOSUB PrintVars
  GOSUB ClearVars
  GOTO TheEnd
' ------------------------------------------
Start1:
  CLS
  Hello$ = "hello world!"
  PRINT Hello$
  RETURN
' ------------------------------------------double float
DoubleFloat:
  LET xylophone# = 50.3
  LET yazoo# = 101.25
  LET abc = yazoo# / xylophone#
  xyz = yazoo# / 10
  LOCATE abc , xyz
  PRINT Hello$
  RETURN
' ------------------------------------------long integers
LongIntegers:
  quasar% = 2
  zapp% = 4
  abcl% = (quasar% * quasar% * zapp% + zapp%)/5
  xyzl% = ((quasar% * quasar%) * zapp%) + zapp%
  LOCATE abcl%, xyzl%
  PRINT Hello$
  RETURN
' ------------------------------------------
RDParser:
  abc = 2*(3+4)*5/10
  PRINT "": " 2*(3+4)*5/10 ="; abc
  RETURN
' ------------------------------------------
PrintVars:
  abc = 11100
  xyz = 32000
  abcl% = 33000
  xyzl% = 99000
  abcf! = 33000.33
  xyzf! = 99000.47
  abcd# = 333000.33
  xyzd# = 999000.47
'                                          integers
  PRINT "": "abc="; abc: "xyz="; xyz
'                                          long integers
  PRINT "abcl%="; abcl%: "xyzl%="; xyzl%
'                                          float
  PRINT "abcf!="; abcf!: "xyzf!="; xyzf!
'                                          double
  PRINT "abcd#="; abcd#: "xyzd#="; xyzd#
  RETURN
' ------------------------------------------
ClearVars:
  test$ = "test"
  CLEAR
  RETURN
' ------------------------------------------
TheEnd:
  END
