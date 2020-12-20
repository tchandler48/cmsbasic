USERID GCCCMS
'  bx12 version 12
'
  DIM xylophone# = 0, yazoo# = 0, abc = 0, xyz = 0, quasar = 0, zapp = 0
'
Start1:
  CLS
  PRINT "hello world!"
' ------------
  LET xylophone# = 50.3
  LET yazoo# = 101.25
  LET abc = yazoo#/xylophone#
  xyz = yazoo#/10
  quasar = 2
  zapp = 4
  abc = (quasar * quasar * zapp + zapp)/5
  xyz = ((quasar * quasar) * zapp) + zapp
  abc = 2*(3+4)*5/10
'
  CLEAR
' ------------------------------------------
TheEnd:
  END
