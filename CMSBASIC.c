USERID GCCCMS

/* cmsbasic.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011 */

#define CMS

/*--------------------- DECLARE HEADERS ---------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* bxbasic : globals.h : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011           */
/* Modified T. Chandler CMSBASIC cmsbasic.c   */

/* --- declare constants --- */
#define BUFSIZE     256
#define TOKEN_LEN   21
#define VAR_NAME    33
#define LLEN        33
#define IOARRAY     99
#define PATH        129
#define REC_LEN     128
#define DATASIZE    80
#define PARAM_STK   10


/*--------------------- SYSTEM VARIABLES ---------------------*/

    FILE *f_in, *f_out;        /* these are the i/o file handles */
    char prog_name[VAR_NAME];  /* program source-file name      */
    char p_string[BUFSIZE];    /* file input string             */
    char **array1;             /* pointer to program array      */
    char t_holder[20];         /* token data holder             */
    char s_holder[BUFSIZE];    /* xstring (print) data holder   */
     int nrows;                /* numbers of lines in source file */
     int ncolumns=BUFSIZE;     /* dimension for array1[][columns] */
     int line_ndx;             /* current execution line        */
     int s_pos, e_pos;         /* pointers to start & end of token */
    char xstring[BUFSIZE];     /* the print string              */
    char **temp_prog;          /* temp program array            */
    char **temp_label;         /* temp label name array         */
     int *temp_byte;           /* temp byte code array          */
     int *byte_array;          /* byte code array               */
    char **label_nam;          /* labels name array             */
     int token;                /* token: current byte code      */
    char var_type;             /* current variable type         */
     int use_socket = 0;	   /* tcp socket flag		 */
                       

/*--------------------- GLOBAL VARIABLES ---------------------*/

  struct Global_Table
  {
        char Nam[VAR_NAME];
         int ActSub;           /* which Sub does it belong to   */
         int Int;              /* stack:integer variable values */
        long Lng;              /* stack:long variable values    */
       float Flt;              /* stack:float variable values   */
      double Dbl;              /* stack:double float values     */
        char *Str;             /* stack:string variable array   */
  };
  struct Global_Table *Gtbl;
     int glb_vct = 0;

     int ActvSubs = 0;         /* number of currently active Subs */

     int *gosub_stack;         /* Gosub: stack array            */
     int gs_ptr=0;             /* Gosub: stack position pointer */
                            
     int fornxt_flg=0;         /* For/Next: global flag         */
    char func_type;            /* current function type         */
                           
     int do_flag=0;            /* DoWhile: instance flag        */
     int do_pointer;           /* Do: jump back line address    */
                          
     int sw_flag=0;            /* Switch/Case instance flag     */
     int iswitch;              /* Switch/Case: test value       */
                           

        /* ----------- end global vars ------------ */


/*--------------------- FILE VARIABLES ---------------------*/

  struct io_handles
  {
         char path[PATH];
         char mode;
         FILE *fptr;
  };
  struct io_handles fp[IOARRAY]; /* File: handles structure     */
                            
  struct field_buffer          /* File: Field Buffer structure  */
  {
         char *f_bffr;         /* I/O buffer                    */
     unsigned bfr_size;        /* buffer length                 */
          int *str_len;        /* string length                 */
         char **str_name;      /* string name                   */
          int fld_count;       /* number of strings             */
         long record;          /* current record number         */
          int flag;            /* PUT flag, to clear buffer     */
  };                           /* File: handles structure       */
  struct field_buffer fld_bffr[IOARRAY];
                           
     int lset_ndx;             /* File: global Lset/Rset var_index */
  struct lset_rset
  {
          int ndx;
          int cnt;
  } lrs;
                           
                                    
/*----------------------- GLOBAL ARRAYS ----------------------*/

  struct string_array
  {
       char name[VAR_NAME];    /* string array name             */
       char **elem;            /* array element pointers        */
       int  dim;               /* number of dimensions          */
       int  sub[10];           /* subscripts(2,3,4)             */
  };
  struct string_array *strArry;
     int sArryCnt=0;           /* array counter                 */
                           
  struct integer_array
  {
       char name[VAR_NAME];    /* integer array name            */
       long *elem;             /* array element pointers        */
       int  dim;               /* number of dimensions          */
       int  sub[10];           /* subscripts(2,3,4)             */
  };
  struct integer_array *intArry;
     int iArryCnt=0;           /* array counter                 */
                            
  struct float_array
  {
       char name[VAR_NAME];    /* float array name              */
       float *elem;            /* array element pointers        */
       int  dim;               /* number of dimensions          */
       int  sub[10];           /* subscripts(2,3,4)             */
  };
  struct float_array *fltArry;
     int fArryCnt=0;           /* array counter                 */
                            

  struct double_array
  {
       char name[VAR_NAME];    /* double array name             */
       double *elem;           /* array element pointers        */
       int  dim;               /* number of dimensions          */
       int  sub[10];           /* subscripts(2,3,4)             */
  };
  struct double_array *dblArry;
     int dArryCnt=0;           /* array counter                 */
                            
/*--- freed array space flags ---*/
    int fre_int=0;
    int fre_flt=0;
    int fre_dbl=0;
    int fre_str=0;
                           
/*----------------------- GLOBAL SUBs ------------------------*/

/*--- OBJECTS ---*/
    char **ObjIndx;            /* object/variables name index   */
     int **ObjType;            /* object/variables type specifier */
     int ObjNdxCnt=0;          /* object/variables index count  */
    char **ObjSubVar;          /* object/local variable flag    */

/*--- SUB's ---*/
    char **SubNameStack;       /* stack:sub name stack          */
    char SubName[VAR_NAME];    /* this sub name                 */
    char *paramStack[10];      /* stack:parameter names stack   */
     int paramType[10];        /* var type of passed parameter  */

     int paramCnt=0;           /* parameter count               */
     int thisSub;              /* this sub pointer              */

     int callFlag=0;           /* sub call flag                 */

/* -------- SUB structs -------- */

     int subCnt=0;             /* counter:number of SUBs declared   */

  struct Sub_Routines
  {
      char SubName[VAR_NAME];  /* this sub name                 */
       int paramCnt;           /* parameter count               */
       int paramType[10];      /* var type of passed parameter  */
  };
  struct Sub_Routines *SubR;

  struct Sub_Index             /* use this struct as a search table */
  {
       int index;              /* index for this sub-name       */
      char SubName[VAR_NAME];  /* this sub name                 */
  };
  struct Sub_Index *Sndx;

  struct Push_Stack
  {
         int Typ;          /* stack:variable type               */
         int Int;          /* stack:integer variable values     */
        long Lng;          /* stack:long variable values        */
       float Flt;          /* stack:float variable values       */
      double Dbl;          /* stack:double float values         */
        char *Str;         /* stack:string variable array       */
  };
  struct Push_Stack *pStk;

  struct Return_Stack
  {
         int ret_Addr;     /* stack:Sub return address          */
         int Vrcnt;        /* stack: variables count            */
  };
  struct Return_Stack *rStk;

     int sub_ndx;

/* -------- end SUB structs -------- */


/*--------------------- LOCAL VARIABLES ----------------------*/

  struct Local_Table
  {  
    char Nam[VAR_NAME];
    int Typ;
    int Adr;
  };
  struct Local_Table *Ltbl;

  int lcl_cnt = 0;
  int *thissub_vars;
  int submax_cnt;
  int *sub_stack;

/*--------------------- UDT STRUCTURES --------------------*/

  struct tag_UDT
  {
      char udtName[VAR_NAME];          /* UDT:DBase             */
       int numVars;                    /* UDT:4                 */
      char **varNames;                 /* UDT:int,long,single,string */
       int *type;                      /* UDT:type=1            */
       int *size;                      /* UDT:size=4            */
       int *offset;                    /* UDT:offset=0          */
       int length;                     /* UDT:length            */
      char *data;                      /* UDT:values array      */
  };
  struct tag_UDT *UDT;
  struct tag_UDT *udtTest;

     int UdtCnt = 0;                   /* UDT counter           */
     int udtpi;                        /* udt char pointer      */
    char udtTmpName[VAR_NAME];         /* udt temp name storage */


#include "CMSBPROT.h"
#include "CMSBARR.c"
#include "CMSBERR.c"
#include "CMSBFIL.c"
#include "CMSBGINP.c"
#include "CMSBIF.c"
#include "CMSBINP.c"
#include "CMSBLOOP.c"
#include "CMSBOUT.c"
#include "CMSBRDP.c"
#include "CMSBSTRG.c"
#include "CMSBSTRT.c"
#include "CMSBSUB.c"
#include "CMSBUTL.c"
#include "CMSBVAR.c"


/*--------------------- BEGIN PROGRAM ---------------------*/

int main(int argc, char *argv[])
{   
  int x=0;
  int ii;
  unsigned size = 1; 

  printf("CMSBASIC Interpreter [v20.3]\n");

  for(ii=0; ii < IOARRAY; ii++)         /* clear I/O file handles */   
  {	
    zero_handle(ii);
  }

  for(ii=0; ii < IOARRAY; ii++)        /* initialize file buffers */   
  {
    fld_bffr[ii].f_bffr = malloc(size * sizeof(char));
    fld_bffr[ii].f_bffr[0] = '\0';
    fld_bffr[ii].bfr_size = 1;
    fld_bffr[ii].record = 1;
    fld_bffr[ii].fld_count = 0;
    fld_bffr[ii].flag = 0;
  }
  line_cnt(argv);
  pgm_parser();

  /* --- end of program --- */
  for(ii=0; ii < nrows; ii++)
  {
    free(label_nam[ii]);
    free(array1[ii]);
  }
  
  free(label_nam);
  free(byte_array);
  free(array1);
  
  return 0;
}
/*--------- end main ---------*/


void pgm_parser()
{
  int ii = 0;
   
  line_ndx = 0;
  while(line_ndx < nrows)
  {   
    s_pos = 0;
    e_pos = 0;
    strcpy(p_string, array1[line_ndx]);
    token = byte_array[line_ndx];
    parser();
    line_ndx++;
  }
}
/*-------- end pgm_parser ---------*/


void parser()
{   
  int ab_code=4, x=line_ndx;

  switch(token)
  {   
    case 0:			      /* REM */
      break;
 
    case 1:                      /* LET */
      parse_let();
      break;

    case 2:                      /* CLEAR */
      if(ActvSubs == 0)
      {
        free(Gtbl);
        glb_vct = 0;
      }
      break;

    case 3:                      /* LOCATE */
      break;

    case 4:                      /* PRINT */
      parse_print();
      break;

    case 5:                      /* GOTO */
      go_to();
      break;

    case 6:                      /* BEEP */
      break;

    case 7:                      /* CLS */
      clr3270();
      break;
  
    case 8:                      /* END */
      printf("\nEnd of Program\n");
      line_ndx = nrows;
      break;

    case 9:                      /* GOSUB */
      do_gosub();
      break;

    case 10:                     /* RETURN */
      do_return();
      break;

    case 11:                     /* FOR */
      do_for();
      break;

    case 12:                     /* NEXT */
      do_next();
      break;

    case 13:                     /* IF */
      do_if();
      break;

    case 14:                     /* ELSEIF */
      do_if();
      break;

    case 15:                     /* ELSE */
      return;
      break;
   
    case 16:                     /* ENDIF */
      return;
      break;

    case 17:                     /* INPUT */
      get_input();
      break;

    case 18:                     /* LINE INPUT */
      get_lninput();
      break;

    case 19:                     /* OPEN */
      parse_open();
      break;

    case 20:                     /* CLOSE */
      do_fclose();
      break;

    case 21:                     /* WRITE */
      write_io();
      break;

    case 22:                     /* FIELD */
      do_field();
      break;

    case 23:                     /* LSET */
      do_lset();
      break;

    case 24:                     /* RSET */
      do_rset();
      break;

    case 25:                     /* PUT */
      do_put();
      break;

    case 26:                     /* GET */
      do_get();
      break;
   
    case 27:                     /* WHILE */
      do_While();
      break;

    case 28:                     /* WEND */
      return;
      break;

    case 29:                     /* DO */
      do_DoWhile();
      break;

    case 30:                     /* REDIM array */
      do_redim();
      break;

    case 31:                     /* SWITCH */
      do_Switch();
      break;

    case 32:                     /* CASE */
      do_Case();
      break;

    case 33:                     /* DEFAULT */
      return;
      break;
  
    case 34:                     /* ENDSWITCH */
      return;
      break;

    case 35:                     /* DIM array */
      do_dim_var();
      break;

    case 36:                     /* DECLARE */
      do_declare();
      break;

    case 37:                     /* CALL */
      do_callsub();
      break;

    case 38:                     /* SUB-label */
      enter_sub();
      break;
 
    case 39:                     /* ENDSUB */
      do_retsb();
      break;
   
    case 40:                     /* STOP */
      line_ndx = nrows;
      break;

    case 41:                     /* SYSTEM */
      line_ndx = nrows;
      break;

    case 43:                     /* ERASE */
      erase_array();
      break;

    case 44:                     /* RANDOM */
       /* do_random(); */
       break;

    case 45:                     /* KILL (delete) a file */
      do_kill();
      break;

    case 126:                    /* UDT/STRUCT */
      struct_Udt();
      break;

    case 127:                    /* ENDUDT/ENDSTRUCT */
    				     /* drop thru, do nothing. */
      return;
      break;

    case -1:	/* block label */
      break;
    
    default:
      a_bort(ab_code, x);
      break;
  }
}
/*--------- end parser ---------*/


