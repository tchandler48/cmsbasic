USERID GCCCMS
'  bx23 version 23
'
  DIM x = 0, y = 0
'
  CLS
  GOSUB TOP
  GOSUB Center
  GOSUB Bottom
  GOTO TheEnd
'----------------------
Center:
  FOR x = 1 TO 5
      PRINT "*";
      FOR y = 1 TO 28
          PRINT " ";
      NEXT y
      PRINT "*":
  NEXT x
  RETURN
'----------------------
TOP:
Bottom:
  FOR x = 1 TO 30
      PRINT "*";
  NEXT x
  PRINT "":
  RETURN
'----------------------
TheEnd:
  END
