USERID GCCCMS
'  bx51 version 51
'
'                 create single dimension array
  DIM MyArray%(5)
  DIM value = 0
'
  CLS
'
  MyArray%(1) = 10
  MyArray%(2) = 20
  MyArray%(3) = 30
  MyArray%(4) = 40
  MyArray%(5) = 50
'
  PRINT MyArray%(1)
  PRINT MyArray%(2)
  PRINT MyArray%(3)
  PRINT MyArray%(4)
  PRINT MyArray%(5)
'
  value = MyArray%(1) + MyArray%(2)
'
  PRINT
  PRINT value
'
' ------------------------------------------
TheEnd:
  END
