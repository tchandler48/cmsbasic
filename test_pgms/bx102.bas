USERID GCCCMS
'   bx102
   CLS
   stnum = CLOCK()
   PRINT "CLOCK stnum = "; stnum
   PRINT "bx102 Test Program"
   FOR x = 1 TO 1000 
   LET j = j + 1
   NEXT
   stpnum = CLOCK()
   PRINT "CLOCK stpnum = "; stpnum
   a$ = DATE$();
   PRINT "DATE = "; a$
TheEnd:
   END
