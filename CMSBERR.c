USERID GCCCMS
/* cmsbasic : error.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T.Chandler CMSBASIC - error.c    */

void a_bort(int code,int line_ndx)
{
  switch(code)
  {
    case 1:
      printf("Unspecified Program Name.\n");
      printf("Enter:\"bxbasic program_name.bas\"\n");
      printf("code(%d)\n",code);
      break;
 
    case 2:
      printf("Program file:\"%s\" not found.\n", t_holder);
      printf("Enter: \"bxbasic program_name.bas\"\n");
      printf("Program Terminated.\ncode(%d)\n", code);
      break;

    case 3:
      printf("\nSyntax error: in program line:");
      printf(" %d.\n%s",(line_ndx+1),p_string);
      printf("Keywords must be in UpperCase:\n");
      printf("code(%d)\n", code);
      break;

    case 4:
      printf("\nSyntax error: in program line:");
      printf(" %d.\n%s",(line_ndx+1),p_string);
      printf("Unknown Command.\ncode(%d)\n", code);
      break;

    case 5:
      printf("\nVariable Type error: in program line:");
      printf(" %d.\n%s",(line_ndx+1),p_string);
      printf("Type must be: Integer.\ncode(%d)\n", code);
      break;

    case 6:
      printf("\nSyntax error: in program line:");
      printf(" %d.\n%s",(line_ndx+1),p_string);
      printf("No closing quotes.\ncode(%d)\n", code);
      break;

    case 7:
      printf("\nSyntax error: in program line:");
      printf(" %d.\n%s",(line_ndx+1),p_string);
      printf("Expected: \"%s\".\ncode(%d)\n",t_holder,code);
      break;

    case 8:
      printf("\nGOTO Error: no such label:");
      printf(" %s:\nin program line:",t_holder);
      printf(" %d:\nGOTO %s",(line_ndx+1),p_string);
      printf("Program Terminated\ncode(%d)\n", code);
      break;

    case 9:
      printf("\nSyntax error: in program line: %d.\n",(line_ndx+1));
      printf("%s", p_string);
      printf("Missing quotes.\ncode(%d)\n", code);
      break;

    case 11:
      printf("\nSyntax error: in program line: %d.\n",(line_ndx+1));
      printf("%s", p_string);
      printf("Useage LET (variable assignment):\ncode(%d)\n", code);
      break;
 
    case 12:
      printf("\nExpected %s ",t_holder);
      printf(": in line: %d.\n", (line_ndx+1));
      printf("%scode(%d)\n", p_string, code);
      break;

    case 13:
      printf("\nVariable not found: in line: %d.\n", (line_ndx+1));
      printf("%scode(%d)\n", p_string, code);
      break;

    case 14:
      printf("\nInvalid operator: in line: %d.\n", (line_ndx+1));
      printf("%scode(%d)\n", p_string, code);
      break;

    case 15:
      printf("\nSyntax error: in line: %d.\n", (line_ndx+1));
      printf("%s {value} not found.\n%s", t_holder, p_string);
      printf("code(%d)\n", code);
      break;

    case 16:
      printf("\nFOR NEXT error: in line: %d.\n", (line_ndx+1));
      printf("NEXT without a FOR.\nNEXT %s", p_string);
      printf("code(%d)\n", code);
      break;

    case 17:
      printf("\nIF:Operand Type error: in line: ");
      printf("%d.\n%s\nNot a valid ", (line_ndx+1), p_string);
      printf("variable type.\ncode(%d)\n", code);
      break;

    case 18:
      printf("\nRelational Operator Type error: in line: ");
      printf("%d.\n%s\nValid operators:", (line_ndx+1), p_string);
      printf(" =<> .\ncode(%d)\n", code);
      break;

    case 19:
      printf("\nINPUT : error: in statement: %d.\n",(line_ndx+1));
      printf("INPUT %sUsage: INPUT \"Enter your ", p_string);
      printf("name\"; name$:\ncode(%d)\n", code);
      break;

    case 20:
      printf("\nOPEN : error: in statement: %d.\n",(line_ndx+1));
      printf("%s\tOPEN %sUsage: OPEN \"I\", #1, ",xstring,p_string);
      printf("\"filename\"\ncode(%d)\n", code);
      break;
 
    case 21:
      printf("\nINPUT : error: in statement: ");
      printf("%d.\n\tINPUT %s%s\n",(line_ndx+1),p_string,xstring);
      printf("Usage: INPUT#1, input$, (var,,)\ncode(%d)\n", code);
      break;
 
    case 22:
      printf("\nCLOSE : error: in statement: %d.\n",(line_ndx+1));
      printf("\tCLOSE %s%s\t",p_string,xstring);
      printf("Usage: CLOSE 1, (handle,,)\ncode(%d)\n", code);
      break;

    case 23:
      printf("\nIF EOF : error: in statement: ");
      printf("%d.\n\tIF %s%s",(line_ndx+1),p_string,xstring);
      printf("Usage: IF EOF(1) THEN...\ncode(%d)\n", code);
      break;

    case 24:
      printf("\nWRITE : error: in statement: ");
      printf("%d.\n\tWRITE %s%s\n",(line_ndx+1),p_string,xstring);
      printf("Usage: WRITE#1, output$, (var,,)\ncode(%d)\n", code);
      break;

    case 25:
      printf("\nFIELD : error: in statement: %d.\n",(line_ndx+1));
      printf("\tFIELD %s%s\n",p_string,xstring);
      printf("Usage: FIELD 1, 1 AS a$, (var,,)\ncode(%d)\n", code);
      break;

    case 26:
      printf("\nLSET : error: in statement: ");
      printf("%d.\n\tLSET %s%s",(line_ndx+1),p_string,xstring);
      printf("Usage: LSET A$ = var$\ncode(%d)\n", code);
      break;

    case 27:
      printf("\nRSET : error: in statement: ");
      printf("%d.\n\tRSET %s%s",(line_ndx+1),p_string,xstring);
      printf("Usage: RSET A$ = var$\ncode(%d)\n", code);
      break;

    case 28:
      printf("\nPUT : error: in statement: ");
      printf("%d.\n\tPUT %s%s",(line_ndx+1),p_string,xstring);
      printf("Usage: PUT 1, [record%c]\ncode(%d)\n", '%', code);
      break;

    case 29:
      printf("\nGET : error: in statement: ");
      printf("%d.\n\tGET %s%s",(line_ndx+1),p_string,xstring);
      printf("Usage: GET 1, [record%c]\ncode(%d)\n", '%', code);
      break;

    case 30:
      printf("\nLOC : error: in statement: %d.\n",(line_ndx+1));
      printf("%s\nUsage: n = LOC(1)\n",xstring);
      printf("code(%d)\n", code);
      break;

    case 31:
      printf("\nLOF : error: in statement: %d.\n",(line_ndx+1));
      printf("%s\nUsage: n = LOF(1)\n",xstring);
      printf("code(%d)\n", code);
      break;

    case 32:
      printf("\nWHILE : error: in statement: %d.\n",(line_ndx+1));
      printf("WHILE without WEND\n");
      printf("code(%d)\n", code);
      break;

    case 33:
      printf("\nDIM Array(n)\tin statement:%d\n",(line_ndx+1));
      printf("%s", p_string);
      printf("Invalid array type.\ncode(%d)\n", code);
      break;

    case 34:
      printf("\nDIM Array(n)\tin statement:%d\n",(line_ndx+1));
      printf("%s", p_string);
      printf("Array already dimensioned.\ncode(%d)\n", code);
      break;

    case 35:
      printf("\nArray index not found\n");
      printf("%s in line:%d\n", p_string, (line_ndx+1));
      printf("Recheck spelling of array name.\n");
      printf("code(%d)\n", code);
      break;
  
    case 36:
      printf("\nERASE Array(n)\tin statement:%d\n",(line_ndx+1));
      printf("%s", p_string);
      printf("Invalid array type.\ncode(%d)\n", code);
      break;

    case 37:
      printf("\nCASE without SWITCH, in line:%d\n", line_ndx+1);
      printf("CASE %s", p_string);
      printf("code(%d)\n", code);
      break;

    case 38:
      printf("\nNo SUBs have been DECLARED, in line:%d\n", line_ndx+1);
      printf("CALL %s", p_string);
      printf("code(%d)\n", code);
      break;

    case 39:
      printf("\nSUB has not been DECLARED, in line:%d\n", line_ndx+1);
      printf("CALL %s", p_string);
      printf("code(%d)\n", code);
      break;

    case 40:
      printf("\nRETURN without GOSUB, in line:%d\n", line_ndx+1);
      printf("code(%d)\n", code);
      break;

    case 42:
      printf("\nDECLARE without SUB, in line:%d\n", line_ndx+1);
      printf("DECLARE %s", p_string);
      printf("code(%d)\n", code);
      break;

    case 43:
      printf("\nDECLARE %s...in line:%d\n", p_string, line_ndx+1);
      printf("Functions are not yet enabled.\n");
      printf("code(%d)\n", code);
      break;

    case 44:
      printf("\nVariable not found: in line: %d.\n", (line_ndx+1));
      printf("CALL %s...%s\n", p_string, s_holder);
      printf("\ncode(%d)\n", code);
      break;

    case 45:
      printf("\nCALL without Parameter: in line: %d.\n", (line_ndx+1));
      printf("CALL %s", p_string);
      printf("\ncode(%d)\n", code);
      break;

    case 46:
      printf("\nSUB without Parameter: in line: %d.\n", (line_ndx+1));
      printf("SUB %s", p_string);
      printf("\ncode(%d)\n", code);
      break;

    case 47:
      printf("\nSyntax error: in program line: %d.\n",(line_ndx+1));
      printf("NAME %s", p_string);
      printf("Use: NAME Old, New .\ncode(%d)\n", code);
      break;

    case 48:
      printf("\nSyntax error: in program line: %d.\n",(line_ndx+1));
      printf("MESSAGEBOX %s", p_string);
      printf("\nMissing delimiter (comma)\ncode(%d)\n", code);
      break;

    case 49:
      printf("\nCall_Type: %s  not supported.\n", s_holder);
      printf("in program line: %d.\n",(line_ndx+1));
      printf("\nCALLAPI %s code(%d)\n", p_string, code);
      break;

    case 54:
      printf("\nDraw Line error: in program line: %d.\n",(line_ndx+1));
      printf("LINE %s", p_string);
      printf("\nNo gui window created yet.\ncode(%d)\n", code);
      break;

    case 55:
      printf("\nDraw error: in program line: %d.\n",(line_ndx+1));
      printf("%s %s", t_holder, p_string);
      printf("\nDid not find window name.\ncode(%d)\n", code);
      break;

    case 56:
      printf("\nDraw Box error: in program line: %d.\n",(line_ndx+1));
      printf("BOX %s", p_string);
      printf("\nNo gui window created yet.\ncode(%d)\n", code);
      break;

    case 57:
      printf("\nDraw Text error: in program line: %d.\n",(line_ndx+1));
      printf("TEXT %s", p_string);
      printf("\nNo gui window created yet.\ncode(%d)\n", code);
      break;

    case 58:
      printf("\nFONT error: in program line: %d.\n",(line_ndx+1));
      printf("FONT %s", p_string);
      printf("\nNo gui window created yet.\ncode(%d)\n", code);
      break;

    case 78:
      printf("\nBKMODE error: in program line: %d.\n",(line_ndx+1));
      printf("BKMODE %s", p_string);
      printf("\nNo gui window created yet.\ncode(%d)\n", code);
      break;

    case 79:
      printf("\nBKMODE error: in program line: %d.\n",(line_ndx+1));
      printf("BKMODE %s", p_string);
      printf("\nMode type not found.\ncode(%d)\n", code);
      break;

    case 97:
      printf("\nSYSMETRIC error: in program line: %d.\n",(line_ndx+1));
      printf("%s", p_string);
      printf("\nMetric parameter not found.\ncode(%d)\n", code);
      break;

    case 131:
      printf("\nSyntax error: in program line: %d.\n",(line_ndx+1));
      printf("UDT %s", p_string);
      printf("Useage: UDT (udt name):\ncode(%d)\n", code);
      break;
 
    case 132:
      printf("\nUDT Element not found: in line: %d.\n", (line_ndx+1));
      printf("%scode(%d)\n", p_string, code);
      break;

    case 133:
      printf("\nUDT structure found: in line: %d.\n", (line_ndx+1));
      printf("UDT %s\n", p_string);
      printf("UDT already defined.\ncode(%d)\n", code);
      break;

    default:
      printf("Program aborted, undefined error.\n");
      printf("%s", p_string);
      break;
  }
     
  int ii;

  printf("\n");
  for(ii = (subCnt-1); ii >= 0; ii--)
  {
    printf("%d, %s\n", ii, SubR[ii].SubName);
  }
  printf("\nvar count=%d\nactive subs=%d\n\n", glb_vct, ActvSubs);
/*    exit(1);*/

  if(glb_vct > 0)
  {
    printf("\nloop\n");
    for(ii = (glb_vct - 1); ii >= 0; ii--)
    {
      printf("%d, %s, %d\n", ii, Gtbl[ii].Nam, Gtbl[ii].Int);
    }
  }
  exit(1);
}
/*----------end a_bort -----------*/


void err_hndlr(int ab_code, int x, int mssg, int p1, int p2)
{
  int ibool=0;

  switch(mssg)
  {
    case 1:
      if(p1 == p2)
      {
        strcpy(xstring, "Invalid I/O Mode:");
        ibool = 1;
      }
      break;
     
    case 2:
      if(p1 == p2)
      {
        strcpy(xstring, "Invalid I/O Format:");
        ibool = 1;
      }
      break;
     
    case 3:
      if((p1 < 0) || (p1 > p2))
      {
        strcpy(xstring, "Invalid File Number:\n1 to 99:");
        ibool = 1;
      }
      break;
    
    case 4:
      if(fp[p1].path[0] != '\0')
      {
        strcpy(xstring, "File Number In Use:");
        ibool = 1;
      }
      break;
     
    case 5:
      if(p1 == p2)
      {
        strcpy(xstring, "Invalid File Name:");
        ibool = 1;
      }
      break;
    
    case 6:
      strcpy(xstring, "Unable to Open File:");
      break;

    case 7:
      if(fp[p1].mode != 'I')
      {
        strcpy(xstring, "FILE not OPEN for INPUT:");
        ibool = 1;
      }
      break;
     
    case 8:
      if((p1 != 'O') && (p1 != 'A'))
      {   
        strcpy(xstring, "FILE not OPEN for OUTPUT:");
        ibool = 1;
      }
      break;
 
    case 9:
      if(fp[p1].path[0] == '\0')
      {
        strcpy(xstring, "File Number Not Open:");
        ibool = 1;
      }
      break;
      
    case 10:
      if(p1 == p2)
      {
        strcpy(xstring, "Invalid Field Format:");
        ibool = 1;
      }
      break;
     
    case 11:
      if(p1 < p2)
      {
        strcpy(xstring, "Invalid Field Format:");
        ibool = 1;
      }
      break;
     
    case 12:
      if(p1 > p2)
      {
        strcpy(xstring, "Incorrect Field length:");
        ibool = 1;
      }
      break;
     
    case 13:
      if((p1 == 0) || (p2 >= IOARRAY))
      {
        strcpy(xstring, "Source variable not found:\n");
        ibool = 1;
      }
      break;
     
    default:
      break;
  }
  if(ibool == 1)
  {
    a_bort(ab_code,x);
  }
}
/* ------ end err_hndlr ------ */
