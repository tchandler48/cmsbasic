USERID GCCCMS
'  bx14 version 14
'
  DIM xylophone# = 0, yazoo# = 0, abc = 0
  DIM xyz = 0, quasar = 0, zapp = 0
'
Start1:
  CLS
  PRINT "hello world!"
' ------------
  LET xylophone# = 50.3
  LET yazoo# = 101.25
  LET abc = yazoo#/xylophone#
  xyz = yazoo#/10
  LOCATE abc , xyz
  PRINT "hello world!"
' ------------------------------------------
  quasar = 2
  zapp = 4
  abc = (quasar * quasar * zapp + zapp)/5
  xyz = ((quasar * quasar) * zapp) + zapp
  LOCATE abc, xyz
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
TheEnd:
  CLEAR
  END
