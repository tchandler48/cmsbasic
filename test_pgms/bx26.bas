USERID GCCCMS
'  bx26 version 26
'
  DIM xyzi = 0
  DIM abcs$ = "", xyzs$ = ""
'
'
  CLS
  xyzi = 42
  abcs$ = CHR$(xyzi)
  PRINT "abcs$ = ";abcs$
'
  xyzs$ = "testing"
  abcs$ = LEFT$(xyzs$, 4)
  PRINT abcs$
'
  abcs$ = RIGHT$(xyzs$, 5)
  PRINT abcs$
'
  abcs$ = MID$(xyzs$, 3, 3)
  PRINT abcs$
'
  abcs$ = SPACE$(3)
  PRINT ">";abcs$;"<"
'
  abcs$ = STR$(199)
  PRINT abcs$
'
  abcs$ = STRING$(10, xyzi)
  PRINT ">";abcs$;"<"
' ------------------------------------------
TheEnd:
  END
