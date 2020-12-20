USERID GCCCMS
'   bx31
  CLS
  filename$ = "test.txt"
  PRINT "Opening Test File #2"
  OPEN "I", #1, "test.txt"
  INPUT#1, input$,next$,valuea,valueb%,valuec!,valued#
  CLOSE 1
  PRINT input$,next$,valuea,valueb%,valuec!,valued#
TheEnd:
  END
