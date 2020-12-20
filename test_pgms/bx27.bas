USERID GCCCMS
'  bx27 version 27
'
  DIM ixyz = 0
  DIM sxyz$ = "", sabc$ = ""
'
'
  CLS
  ixyz = 42
  sxyz$ = "testing"
'
  sabc$ = LEFT$(sxyz$, 4) + CHR$(ixyz) + RIGHT$(sxyz$, 5) + SPACE$(3)
  sabc$ = sabc$ + MID$(sxyz$, 3, 3) + STR$(-199) + STRING$(10, ixyz)

  PRINT sabc$
'
  sabc$ = CHR$(34) + "Hello" + CHR$(32) + "world!" + CHR$(34)
  PRINT sabc$
' ------------------------------------------
TheEnd:
  END

