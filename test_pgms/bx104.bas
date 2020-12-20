USERID GCCCMS
'   bx104
   CLS
   a$ = DATE$
   PRINT "DATE = "; a$
   number = LOG(3.14)
   PRINT "LOG number = "; number
   num = -99
   sign = SGN(num)
   IF sign = 0 THEN
      PRINT "sign equals zero"
   ELSEIF sign < 0 THEN
      PRINT "sign is negative"
   ELSEIF sign = 1 THEN
      PRINT "sign is positive"
   ENDIF
   b$ = "12345"
   c = VAL(b$)
   PRINT "VAL c = "; c
   sec% = SECONDS
   PRINT "SECONDS = ";sec%
TheEnd:
   END
