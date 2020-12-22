USERID GCCCMS
/* cmsbasic : Rdparser.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011             */
/* special credits to: Jack Crenshaw's:
   "How to Build a Compiler"                    */
/* Modified T. Chandler CMSBASIC - CMSBRDP.c    */


double rdp_main()		
{   
   double value;

   value = Expression();
   return value;
}
/*---------- end rdp_main ----------*/


double Expression()	
{
   char ch;
   int pi;
   double Value;

   pi = e_pos;
   ch = p_string[pi];
   if(IsAddop(ch))
   {               
     Value = 0;  /* ie: 0 = 0 - 2  (= -2) */
   }
   else
   {
     Value = Term();
     pi = e_pos;
     ch = p_string[pi];
   }
   while(IsAddop(ch))
   {
     switch(ch)
     {
        case '+':
          Match('+');
          Value = Value + Term();
          break;
    
        case '-':
          Match('-');
          Value = Value - Term();
          break;

        default:
          break;
     }
     pi = e_pos;
     ch = p_string[pi];
  }
  return Value;
}
/*---------- end Expression ----------*/


double Term()		
{   
   char ch;
   int pi;
   double Value;

   Value = Factor();
   pi = e_pos;
   ch = p_string[pi];
   while(IsMultop(ch))
   {
     switch(ch)
     {
        case '*':
          Match('*');
          Value = Value * Factor();   
          break;
    
        case '/':
          Match('/');
          Value = Value / Factor();   
          break;

        case '^':
          Match('^');
          Value = pow(Value, Factor()); 
          break;

        case '%':
          Match('%');
          Value = (int) Value % (int) Factor();     
          break;

        default:
          break;
     }
     pi = e_pos;
     ch = p_string[pi];
  }
  return Value;
}
/*---------- end Term ----------*/


double Factor()                        
{   
   char ch;
   int pi;
   double value;

   pi = e_pos;
   ch = p_string[pi];
   if(ch == '(')
   {
     Match('(');
     value = Expression();
     Match(')');
   }
   else
   {
     if(isalpha(ch))			
     {
       strcpy(s_holder, get_varname());
       value = get_varvalue();
       SkipWhite();
     }
     else if(ch == '?')		
     {
       value = math_functn();
       SkipWhite();
     }
     else				
     {
       value = GetNum();
     }
  }
  return value;
}
/*---------- end Factor ----------*/


double math_functn()
{   
  char ch, varname[VAR_NAME]; 
  int pi, type, ndx, len; 
  double value = 0;
  long ivalue;

  pi = e_pos;                     
  pi++;                          
  e_pos = pi;
  type = (int) get_avalue();

  switch(type)
  {
    case 1:		/* get_ABS */
      ivalue = (long) Factor();
      value = (double) abs(ivalue);
      break;

    case 2:		/* get_ASC */
      pi = e_pos;
      pi++;
      pi = iswhite(pi);
      ch = p_string[pi];
      e_pos = pi;
      if(isalpha(ch))                  
      {
        strcpy(varname, get_varname());
        if(callFlag == 0)
        {
          ndx = get_vndx(varname);          
        }
        else
        {
          ndx = get_llvarndx(varname);        
        }
        ch = Gtbl[ndx].Str[0];
      }
      else                            
      {
        pi++;
        ch = p_string[pi];
      }
      len = strlen(p_string);
      ch = p_string[pi];
      while((strchr("()", ch) == 0) && (pi < len))
      {
        pi++;
        ch = p_string[pi];
      }
      pi++;
      e_pos = pi;
      value = (double) ch;
      break;

    case 3:		/* get_ATN */
      value = Factor();
      value = atan(value);
      break;

    case 4:		/* get_COS */
      value = Factor();
      value = cos(value);
      break;

    case 5:		/* get_SIN */
      value = Factor();
      value = sin(value);
      break;

    case 6:		/* get_TAN */
      value = Factor();
      value = tan(value);
      break;

    case 7:		/* get_SQRT */
      value = Factor();
      value = sqrt(value);
      break;

        case 8:
     /*       value = get_INT();	     */       
            break;
        case 9:
    /*        value = get_LEN();	     */         
            break;
        case 10:
    /*        value = get_LOF();	     */            
            break;
        case 11:
    /*        value = get_LOC();	     */             
            break;
        case 12:			                    
        case 13:			                     
        case 14:			                     
    /*        value = get_CVD();	    */
            break;
        case 16:
    /*        value = get_VAL();       */             
            break;
        case 17:
    /*        value = get_CLOCK();     */            
            break;
        case 18:
    /*        value = do_RAND();      */            
            break;
        case 19:
    /*        value = do_LOG();       */             
            break;
        case 20:
    /*        value = do_LOG10();     */             
            break;
        case 21:
    /*        value = get_SECONDS();  */            
            break;
        case 22:
            break;
        case 23:
    /*        value = get_EXP();     */              
            break;
        case 24:
    /*        value = get_ACOS();     */             
            break;
        case 25:
    /*        value = get_ASIN();    */              
            break;
        case 26:
     /*       value = get_CEIL();    */              
            break;
        case 27:
    /*        value = get_COSH();     */             
            break;
        case 28:
    /*        value = get_FABS();    */              
            break;
        case 29:
     /*       value = get_FLOOR();   */              
            break;
        case 30:
      /*      value = get_FMOD();    */              
            break;
        case 31:
    /*        value = get_HYPOT();   */              
            break;
        case 32:
    /*        value = get_LDEXP();   */              
            break;
        case 33:
    /*        value = get_MODF();    */              
            break;
        case 34:
     /*       value = get_POW();    */              
            break;
        case 35:
     /*       value = get_POW10();     */            
            break;

    case 36:		/*  get_SINH */
      value = Factor();
      value = sinh(value);
       break;

    case 37:		/*  get_TANH */
      value = Factor();
      value = tanh(value);
      break;

        case 38:
     /*       value = get_ATAN2();   */              
            break;
        case 39:
     /*       value = get_FREXP();    */             
            break;
        case 40:
     /*       value = get_LABS();     */             
            break;
        case 41:
     /*       value = call_API();     */             
            break;
        case 43:
     /*       value = get_SGN();     */             
            break;
        case 48:
     /*       value = get_CINT();    */              
            break;
        case 49:
     /*       value = get_CDBL();   */               
            break;
        case 50:
     /*       value = get_CSNG();    */              
            break;
        case 51:
     /*       value = get_CLNG();    */              
            break;
     /**/
        default:
            /* error */
            break;
    }

    switch(type)
    {   case 1:
        case 2:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
            func_type = '%';
            break;

        case 12:
            func_type = '#';
            break;

        default:
            func_type = '!';
            break;
    }
    return value;
}
/*---------- end math_functn ----------*/


/*
double get_CLNG()
{   long lngpart;
    double value;              
                            
    value = Factor();

    if(value > 0)
    {                             
        lngpart = (long) value;
        value -= lngpart;

        if(value >= .5)
        {
            value = 1.0;
        }
        else
        {
            value = 0.0;
        }
    }
    else
    {                            
        lngpart = (long) value;
        value -= lngpart;

        if(value <= -.5)
        {
            value = -1.0;
        }
        else
        {
            value = 0.0;
        }
    }

    value += lngpart;
    return value;
}
*/
/*---------- end get_CLNG ----------*/


/*
double get_CSNG()
{   float  fvalue;
    double value;             
                               
    fvalue = (float) Factor();
    value = fvalue;

    return value;
}
*/
/*---------- end get_CSNG ----------*/


/*
double get_CDBL()
{   double value;              
                              
    value = (double) Factor();

    return value;
}
*/
/*---------- end get_CDBL ----------*/



/*
double get_CINT()
{   int intpart;
    double value;             
                         
    value = Factor();

    if(value > 0)
    {                             
        intpart = (int) value;
        value -= intpart;

        if(value >= .5)
        {
            value = 1.0;
        }
        else
        {
            value = 0.0;
        }
    }
    else
    {                            
        intpart = (int) value;
        value -= intpart;

        if(value <= -.5)
        {
            value = -1.0;
        }
        else
        {
            value = 0.0;
        }
    }

    value += intpart;

    return value;
}
*/
/*---------- end get_CINT ----------*/


/*
double get_SGN()
{   double value;      
                       

    value = Factor();

    if(value > 0)
    {
        value = 1;
    }
    else if(value < 0)
    {
        value = -1;
    }
    else
    {
        value = 0;
    }

    return value;
}
*/
/*---------- end get_SGN ----------*/



/*
double get_LABS()
{   long ivalue;           
    double value;           
                            

    ivalue = (long) Factor();     
    value = (double) labs(ivalue); 

    return value;

}
*/
/*---------- end get_LABS ----------*/


/*
double get_FREXP()
{   char varname[VAR_NAME], ch;       
    int pi, len, ndx, valuey;     
    double value, valuex;         
                                  
                                  
    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;
    strcpy(varname, get_varname());		

    if(callFlag == 0)
    {
        ndx = get_vndx(varname);         
    }
    else
    {
        ndx = get_llvarndx(varname);        
    }

    value = frexp(valuex, &valuey);

    Gtbl[ndx].Int = valuey;        

    return value;

}
*/
/*---------- end get_FREXP ----------*/


/*
double get_ATAN2()
{   int pi, len; 
    char ch;                
    double value, valuex, valuey;


    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
   
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuey = get_avalue();
    value = atan2(valuex, valuey);

    return value;

}
*/
/*---------- end get_ATAN2 ----------*/


/*
double get_POW10()
{   double value, valuex=10, valuey;
                               

    valuey = Factor();
    value = pow(valuex, valuey);

    return value;

}
*/
/*---------- end get_POW10 ----------*/


/*
double get_POW()
{   int pi, len;
    char ch;                 
    double value, valuex, valuey;


    len = strlen(p_string);
    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
   
    e_pos = pi;

    valuey = get_avalue();
    value = pow(valuex, valuey);

    return value;

}
*/
/*---------- end get_POW ----------*/


/*
double get_MODF()
{   char varname[VAR_NAME], ch;       
    int pi, len, ndx;             
    double value, valuex, valuey; 


    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
   
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;
    strcpy(varname, get_varname());		

    if(callFlag == 0)
    {
        ndx = get_vndx(varname);         
    }
    else
    {
        ndx = get_llvarndx(varname);        
    }

    value = modf(valuex, &valuey);

    Gtbl[ndx].Dbl = valuey;        

    return value;

}
*/
/*---------- end get_MODF ----------*/


/*
double get_LDEXP()
{   int pi, len, valuey;  
    char ch;   
    double value, valuex;    
                             

    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuey = (int) get_avalue();
    value = ldexp(valuex, valuey);

    return value;

}
*/
/*---------- end get_LDEXP ----------*/


/*
double get_HYPOT()
{   int pi, len;  
    char ch;                  
    double value, valuex, valuey;   
                                    
                                    
    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
   
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
   
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuey = get_avalue();
    value = hypot(valuex, valuey);

    return value;

}
*/
/*---------- end get_HYPOT ----------*/


/*
double get_FMOD()
{   int pi, len;   
    char ch;                   
    double value, valuex, valuey;     
                                      

    len = strlen(p_string);
    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuex = get_avalue();

    pi = e_pos;
    
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    
    e_pos = pi;

    valuey = get_avalue();
    value = fmod(valuex, valuey);

    return value;

}
*/
/*---------- end get_FMOD ----------*/


/*
double get_FLOOR()
{   double value;         
                          
                          
    value = Factor();
    value = floor(value);

    return value;

}
*/
/*---------- end get_FLOOR ----------*/


/*
double get_FABS()
{   double value;          
                           
                           
    value = Factor();
    value = fabs(value);

    return value;

}
*/
/*---------- end get_FABS ----------*/


/*
double get_COSH()
{   double value;         
                          

    value = Factor();
    value = cosh(value);

    return value;

}
*/
/*---------- end get_COSH ----------*/


/*
double get_CEIL()
{   double value;       
                         
                         
    value = Factor();
    value = ceil(value);

    return value;

}
*/
/*---------- end get_CEIL ----------*/


/*
double get_ASIN()
{   double value;           
                            

    value = Factor();
    value = asin(value);

    return value;

}
*/
/*---------- end get_ASIN ----------*/


/*
double get_ACOS()
{   double value;         
                           

    value = Factor();
    value = acos(value);

    return value;

}
*/
/*---------- end get_ACOS ----------*/


/*
double get_EXP()
{   double value;          
                           

    value = Factor();
    value = exp(value);

    return value;

}
*/
/*---------- end get_EXP ----------*/


/*
long get_SECONDS()
{   long value;            
    time_t timer;          

    time(&timer);
    value = (long) timer;

    return value;

}
*/
/*---------- end get_SECONDS ----------*/


/*
double do_LOG10()
{   double value;              
                               

    value = Factor();
    value = log10(value);

    return value;
}
*/
/*---------- end do_LOG10 ----------*/


/*
double do_LOG()
{   double value;              
                               

    value = Factor();
    value = log(value);

    return value;
}
*/
/*---------- end do_LOG ----------*/


/*
int do_RAND()
{   char ch;                  
    int pi, len, random_val;  


    len = strlen(p_string);
    pi = e_pos;
    ch = p_string[pi];

    while((ch != ')') && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }

    pi++;
    pi = iswhite(pi);
    e_pos = pi;

    random_val = rand();

    return random_val;
}
*/
/**------ END RND_HANDLER -------**/


/*
long get_CLOCK()
{   long value;           
                         

    value = (long) clock();

    return value;
}
*/
/*---------- end get_CLOCK ----------*/


/*
void do_random()
{   char ch;
    int pi, seed;
    double value;


    pi = e_pos;
    pi = iswhite(pi);
    ch = p_string[pi];
    

    if((isalpha(ch)) || (isdigit(ch)))	
    {
        e_pos = pi;
        value = get_avalue();

        seed = (int) value;
    }

    srand(seed);

}
*/
/*---------- end do_random ----------*/


/*
double get_VAL()
{   char ch, quote='\"', varname[VAR_NAME];       
    int pi, ndx, len, si, ab_code=9, x=line_ndx;
    double value;                  


    len = strlen(p_string);
    pi = e_pos;
    pi++;
    pi = iswhite(pi);
    ch = p_string[pi];
    e_pos = pi;

    if(isalpha(ch))			
    {
        strcpy(varname, get_varname());
        ndx = get_strndx(varname);

        value = atof(Gtbl[ndx].Str);
    }
    else if(ch == quote)
    {				        
        si = 0;
        pi++;
        ch = p_string[pi];

        while((ch != quote) && (pi < len))
        {
            s_holder[si] = ch;
            si++;
            pi++;
            ch = p_string[pi];
        }
        s_holder[si] = '\0';

        value = atof(s_holder);
    }
    else
    {   a_bort(ab_code,x);
    }

   
    ch = p_string[pi];
    while((strchr("()", ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
   
		
    pi++;
    e_pos = pi;

    return value;

}
*/
/*---------- end get_VAL ----------*/



/*
double get_INT()
{   long ivalue;            
    double value;           

    ivalue = (long) Factor();
    value = (double) ivalue;

    return value;
}
*/
/*---------- end get_INT ----------*/


void Match(char x)             
{   
   char ch, string[6];
   int pi, ab_code=12, ln=line_ndx;

   pi = e_pos;
   ch = p_string[pi];
   if(ch != x)
   {
     strcpy(string, "\" \"");
     string[1] = x;
     strcpy(t_holder, string);
     a_bort(ab_code,ln);
   }
   else
   {
     _GetChar();
     SkipWhite();
   }
}
/*---------- end Match ----------*/


void _GetChar()
{
  e_pos++;
}
/*---------- end _GetChar ----------*/


int Is_White(char ch)
{   
   int test=0;

   if((ch == ' ') || (ch == '\t'))
   {
     test = -1;
   }
   return test;
}
/*---------- end Is_White ----------*/


void SkipWhite() 	
{   
   char ch;
   int pi;

   pi = e_pos;
   ch = p_string[pi];
   while(Is_White(ch))
   {
     _GetChar();
     pi = e_pos;
     ch = p_string[pi];
   }
}
/*---------- end SkipWhite ----------*/


double GetNum()			
{   
   char ch;
   int pi, ab_code=12, ln=line_ndx;
   double value=0;

   pi = e_pos;
   ch = p_string[pi];
   if((! isdigit(ch)) && (ch != '.'))
   {
     strcpy(t_holder, "Numeric Value");
     a_bort(ab_code,ln);
   }
   value = asc_2_dbl();
   pi = e_pos;
   ch = p_string[pi];
   if(isdigit(ch))
   {
     while(isdigit(ch))
     {
       pi++;
       ch = p_string[pi];
     }
     e_pos = pi;
  }
  SkipWhite();
  return value;
}
/*---------- end GetNum ----------*/


int IsAddop(char ch) 		
{   
   int rval=0;

   if((ch == '+') || (ch == '-'))
   {
     rval = 1;
   }
   return rval;
}
/*---------- end IsAddop ----------*/


int IsMultop(char ch) 		
{   
   int rval=0;

   if(ch == '\0')
   {                       
     rval = 0;           
   }
   else if(strchr("*^/%", ch))
   {
     rval = 1;
   }
   return rval;
}
/*---------- end IsMultop ----------*/


double asc_2_dbl()
{   
   char ch, cvalue[33];
   int pi, vi_pos=0;
   double fvalue;

   pi = e_pos;
   ch = p_string[pi];
   while((isdigit(ch)) || (ch == '.') && (vi_pos <= 32))
   {
     cvalue[vi_pos] = ch;
     pi++;
     vi_pos++;
     ch = p_string[pi];
   }
   cvalue[vi_pos] = '\0';
   fvalue = atof(cvalue);                 
   e_pos = pi;
   return fvalue;
}
/*------- end asc_2_dbl ---------*/


/*
double get_LEN()
{   char ch, varname[VAR_NAME];          
    int pi, ndx, len, strnglen=0;        
    int type, indx, offset, nDims;
    int *Subscripts;
    double value=0;


    len = strlen(p_string);
    pi = e_pos;
 
    ch = p_string[pi];
    while((strchr("()", ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }

    if(pi < len)
    {
        pi++;
        pi = iswhite(pi);
        ch = p_string[pi];

        if(isalpha(ch))
        {
            e_pos = pi;
            strcpy(varname, get_varname());
            type = get_objtype(pi);

            switch(type)
            {
                case 0:                     
                    if(callFlag == 0)
                    {
                        ndx = get_vndx(varname);
                    }
                    else
                    {
                        ndx = get_llvarndx(varname);     
                    }

                    strnglen = strlen(Gtbl[ndx].Str);
                    pi = e_pos;
                    break;
                case 6:                     
                    indx = get_arrayndx(varname);

                    Subscripts = &strArry[indx].sub[0];  
                    nDims = strArry[indx].dim;           
                    pi = e_pos;

                    ch = p_string[pi];
                    while((strchr("()", ch) == 0) && (pi < len))
                    {
                      pi++;
                      ch = p_string[pi];
                    }

                    pi++;
                    e_pos = pi;

                    offset = get_offset2(Subscripts, nDims, len);

                    strnglen = strlen(strArry[indx].elem[offset]);
                    break;
            }
        }
        else
        {
            pi++;
            ch = p_string[pi];

            while((ch != '\"') && (pi < len))
            {
                strnglen++;
                pi++;
                ch = p_string[pi];
            }
        }
    }

    e_pos = pi;
    value = (double) strnglen;

    return value;
}
*/
/*---------- end get_LEN ----------*/


/*
double get_LOC()
{   int ndx, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=30;
    long fil_rcrd;                
    double value;
    FILE *handle;


    value = Factor();                        
    ndx = (int) value;
    ndx--;

    err_hndlr(ab_code, x, 3, ndx, maxfiles);   
    err_hndlr(ab_code, x, 9, ndx, 0);         

    handle = fp[ndx].fptr;
    fil_rcrd = ftell(handle);
    value = (double) fil_rcrd;

    return value;
}
*/
/*---------- end get_LOC ----------*/


/*
double get_LOF()
{   int ndx, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=31;
    long offset;
    double value;
    FILE *handle;


    value = Factor();                         
    ndx = (int) value;
    ndx--;

    err_hndlr(ab_code, x, 3, ndx, maxfiles);   
    err_hndlr(ab_code, x, 9, ndx, 0);         

    handle = fp[ndx].fptr;
    fseek(handle, 0L, SEEK_END);
    offset = ftell(handle);
    value = (double) offset;

    return value;
}
*/
/*---------- end get_LOF ----------*/


/*
double get_CVD()
{   double value;        
                        

    value = Factor();

    return value;
}
*/
/*---------- end get_CVD ----------*/
