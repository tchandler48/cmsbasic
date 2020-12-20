USERID GCCCMS
'  bx7 version 9

  DIM xylophone = 0, yazoo = 0, abc = 0, xyz = 0
  DIM quasar = 0, zapp = 0
'
  CLS
  PRINT "hello world!"
  LET xylophone = 50
  LET yazoo = 100
  LET abc = yazoo/xylophone
  xyz = yazoo/10

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

TheEnd:
  END
