USERID GCCCMS
'  bx25 version 25
'
  CLS
  DIM abc = 99, xyz = 33
  DIM abcs$ = "test", xyzs$ = "testing"
'
'
  IF xyzs$ = "testing" AND abc >= xyz THEN 
     PRINT "if:expression = true"
  ELSEIF abc <= 100 OR abcs$ <= "hello" THEN
     PRINT "elseif:expression = true"
  ELSE
     PRINT "else:expressions = false"
  ENDIF
  PRINT "done"
' ------------------------------------------
TheEnd:
  END
