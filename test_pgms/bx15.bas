USERID GCCCMS
'  bx15 version 15
'
  DIM abc = 0, xyz = 0, yazoo# = 0, xylophone# = 0
  DIM quasar% = 0, zapp% = 0, abcl% = 0, xyzl% = 0
'
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
  PRINT:
  PRINT "xylophone# = ";
  PRINT xylophone#
  PRINT "yazoo# = ";
  PRINT yazoo#
  PRINT:
  PRINT "abcl%=";
  PRINT abcl%
  PRINT "xyzl%=";
  PRINT xyzl%
' ------------------------------------------
TheEnd:
  CLEAR
  END
