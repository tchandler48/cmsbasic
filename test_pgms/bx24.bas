USERID GCCCMS
'  BX24 version 24
'
' not working  ????
' ------------------------------------------
Start1:
  CLS
  power = 10 ^ 2
  PRINT "power="; power
'
  ten = 10
  three = 3
'                we can use the modulus operator: %
  mod = ten % three
  PRINT "mod="; mod
'                or we can use the keyword: MOD 
  mod = ten MOD (30 MOD 9)
  PRINT "mod="; mod
  REM RETURN
  END
