USERID GCCCMS
'  bx10 version 10
  CLS
'               now jump to a block label
  GOTO OverThere
'
TheBeginning:
  PRINT "We're at The Beginning!"
  GOTO TheEnd
'
There:
  PRINT "We're There!"
  GOTO TheBeginning
'
JumpBack1:
  PRINT "We Jumped Back 1!"
  GOTO There
'
OverThere:
  PRINT "We're Over There!"
  GOTO JumpBack1
'
TheEnd:
  END
