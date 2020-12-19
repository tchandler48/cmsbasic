USERID GCCCMS
/* cmsbasic : Ifendif.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011            */
/* Modified T. Chandler CMSBASIC CMSBIF.c      */


void do_Switch()
{    
   int pi;

   pi = 0;
   pi = iswhite(pi);             
   e_pos = pi;
   iswitch = (int) get_avalue();  
   sw_flag++;                     
}
/*------- end do_Switch ----------*/


void do_Case()
{
   int ibool, case_ndx, endsw_ndx;
   int ab_code = 37, x = line_ndx;

   if(sw_flag <= 0)
   {
      a_bort(ab_code, x);
   }
   ibool = sw_boolexpres();
   /* --- now take action --- */
   if(ibool == 1)
   {
      case_ndx = find_case(line_ndx);   
      endsw_ndx = find_sw(line_ndx);  
      line_ndx++;			 
      while(line_ndx != case_ndx)
      {
         s_pos = 0;
         e_pos = 0;
         strcpy(p_string, array1[line_ndx]);
         token = byte_array[line_ndx];
         if(token == 5)
         {
            break;
         }
         parser();
         line_ndx++;
      }
      if(token == 5)
      {
         line_ndx--;
         return;
      }
      sw_flag--;                    
      line_ndx = endsw_ndx;          
   }
   else
   {
      case_ndx = find_case(line_ndx);     
      case_ndx--;
      line_ndx = case_ndx;
   }
}
/*------- end do_Case ----------*/


int find_case(int ndx)
{   
   int tok=0;

   while((tok != 32) && (tok != 33) && (tok != 34))
   {
      ndx++;			    
      tok = byte_array[ndx];
      if(tok == 31)
      {
        ndx = find_sw(ndx); 	
      }
   }
   return ndx;
}
/*------- end find_case -------*/


int find_sw(int ndx)
{   
   int tok=0;

   while(tok != 34)  		
   {
     ndx++;
     tok = byte_array[ndx];
     if(tok == 31)
     {
       ndx = find_sw(ndx);
     }
   }
   return ndx;
}
/*------- end find_endsw -------*/


int sw_boolexpres()
{   
   int ibool=0, pi;
   int rvalue;

   pi = 0;
   pi = iswhite(pi);              
   e_pos = pi;
   rvalue = (int) get_avalue();   
   if(iswitch == rvalue)
   {
     ibool = 1;
   }
   return ibool;
}
/*------- end sw_boolexpres -------*/


void do_if()
{   
   int ibool, els_ndx, end_ndx;

   ibool = boolexpress();
   /* --- now take action --- */
   if(ibool == 1)
   {
      els_ndx = find_else(line_ndx);   
      end_ndx = find_if(line_ndx);  
      line_ndx++;			
      while(line_ndx != els_ndx)
      {
        s_pos = 0;
        e_pos = 0;
        strcpy(p_string, array1[line_ndx]);
        token = byte_array[line_ndx];
        if(token == 5)
        {
           break;
        }
        parser();
        line_ndx++;
      }
      if(token == 5)
      {
        line_ndx--;
        return;
      }
      line_ndx = end_ndx;
   }
   else
   {
      els_ndx = find_else(line_ndx);     
      els_ndx--;
      line_ndx = els_ndx;
   }
}
/*------- end do_if ----------*/


int find_else(int ndx)
{   
   int tok=0;

   while((tok != 14) && (tok != 15) && (tok != 16))
   {
     ndx++;                      
     tok = byte_array[ndx];
     if(tok == 13)
     {
       ndx = find_if(ndx);  
     }
   }
   return ndx;
}
/*------- end find_else -------*/


int find_if(int ndx)
{   
   int tok=0;

   while(tok != 16)  		
   {
     ndx++;
     tok = byte_array[ndx];
     if(tok == 13)
     {
       ndx = find_if(ndx);
     }
   }
   return ndx;
}
/*------- end find_endif -------*/


int boolexpress()
{   
   int ibool, type, a_bool, or_bool, op;
   int ab_code=17, x=line_ndx;

   type = get_type();		
   switch(type)
   {
      case 1:
      case 2:
        ibool = Nboolterm(type);        
        break;
   
      case 3:
      case 4:
        ibool = Sboolterm(type);       
        break;
  
      case 5:
        ibool = is_eof();               
        if(ibool != 0)
        {
           ibool = 1;
        }
        break;
        
      default:
        a_bort(ab_code,x);
        break;
  }

  /* --- process AND / OR --- */
  op = IsAndOrOp();
  while(op != 0)
  {
    if(op == 1)
    {
      a_bool = AndOrBoolExp();		
      if((ibool == 1) && (a_bool == 1))
      {
         ibool = 1;
      }
      else
      {
         ibool = 0;
      }
    }
    else if(op == 2)
    {
       or_bool = AndOrBoolExp();		
       if((ibool == 1) || (or_bool == 1))
       {
          ibool = 1;
       }
    }
    op = IsAndOrOp();
  }
  return ibool;
}
/*------- end boolexpress --------*/


int AndOrBoolExp()
{   
   int ibool, type;
   int ab_code=17, x=line_ndx;

   type = get_type();		
   switch(type)
   {
     case 1:
     case 2:
       ibool = Nboolterm(type);        
       break;
    
     case 3:
     case 4:
       ibool = Sboolterm(type);      
       break;
 
     default:
       a_bort(ab_code,x);
       break;
  }
  return ibool;
}
/*------- end AndOrBoolExp --------*/


int Nboolterm(int type)
{
   int ibool;
   double lvalue;

   if(type == 1)
   {
     lvalue = get_avalue();	     
   }
   else
   {
     lvalue = rdp_main();	    
   }
   ibool = Nrelation(lvalue);
   return ibool;
}
/*------- end Nboolterm --------*/


int Nrelation(double lvalue)
{
   int ibool, op, type;
   int ab_code=17, x=line_ndx;
   double rvalue;

   op = get_op();			
   type = get_type();			
   switch(type)
   {
     case 1:
       rvalue = get_avalue();   
       break;

     case 2:
       rvalue = rdp_main();    
       break;

     default:
       a_bort(ab_code,x);
       break;
  }
  ibool = eval_value(lvalue, rvalue, op);  
  return ibool;
}
/*------- end Nrelation --------*/


int eval_value(double lval,double rval,int op)
{
   int ibool=0;

   switch(op)
   {
     case 1:
       if(lval == rval)
       {
          ibool = 1;
       }
       break;
       
     case 2:
       if(lval < rval)
       {
          ibool = 1;
       }
       break;
       
     case 3:
       if(lval > rval)
       {
          ibool = 1;
       }
       break;
       
     case 4:
       if(lval <= rval)
       {
          ibool = 1;
       }
       break;
       
     case 5:
       if(lval >= rval)
       {
          ibool = 1;
       }
       break;
       
     case 6:
       if(lval != rval)
       {
          ibool = 1;
       }
       break;
       
     default:
       break;
  }
  return ibool;
}
/*------- end eval_value -------*/


int Sboolterm(int type)
{
   char lstring[BUFSIZE];
   int ibool, ndx;

   if(type == 3)
   {
      ndx = get_string();		
      strcpy(lstring, Gtbl[ndx].Str);
   }
   else
   {
      get_qstring();			
      strcpy(lstring, s_holder);
   }
   ibool = Srelation(lstring);
   return ibool;
}
/*------- end Sboolterm --------*/


int Srelation(char *lstring)
{
   char rstring[BUFSIZE];
   int ibool, ndx, op, type;
   int ab_code=17, x=line_ndx;

   op = get_op();			
   type = get_type();			
   switch(type)
   {
     case 3:
       ndx = get_string();	        
       strcpy(rstring, Gtbl[ndx].Str);
       break;

     case 4:
       get_qstring();              
       strcpy(rstring, s_holder);
       break;

     default:
       a_bort(ab_code,x);
       break;
  }
  ibool = eval_string(lstring, rstring, op);
  return ibool;
}
/*------- end Srelation --------*/


int eval_string(char *lstr,char *rstr,int op)
{   
   int ibool=0, comp;

   comp = strcmp(lstr, rstr);
   /* --- now test expression --- */
   switch(op)
   {
      case 1:
        if(comp == 0)
        {
           ibool = 1;
        }
        break;
        
      case 2:
        if(comp < 0)
        {
           ibool = 1;
        }
        break;
        
      case 3:
        if(comp > 0)
        {
           ibool = 1;
        }
        break;
     
      case 4:
        if(comp <= 0)
        {
           ibool = 1;
        }
        break;
        
      case 5:
        if(comp >= 0)
        {
           ibool = 1;
        }
        break;
        
      case 6:
        if(comp != 0)
        {
           ibool = 1;
        }
        break;
        
      default:
        break;
  }
  return ibool;
}
/*------- end eval_string -------*/


int IsAndOrOp()
{   
   char ch;
   int pi, op=0;

   pi = e_pos;
   pi = iswhiter(pi);
   ch = p_string[pi];
   if(ch == '&')
   {
      op = 1;
      pi++;
      pi = iswhiter(pi);
   }
   else if(ch == '|')
   {
      op = 2;
      pi++;
      pi = iswhiter(pi);
   }
   e_pos = pi;
   return op;
}
/*------- end IsAndOrOp --------*/


int get_type()
{
   char ch;
   int pi, type=0;

   pi = e_pos;
   pi = iswhiter(pi);
   ch = p_string[pi];
   if(isalpha(ch))
   {
      s_pos = pi;
      type = get_vtype(pi);          
   }
   else if(isdigit(ch))
   {
      type = 1;                      
   }
   else if(ch == '(')
   {
      type = 2;                      
   }
   else if(ch == '\"')
   {
      type = 4;                      
   }
   else if(ch == '\?')
   {
      type = 5;                      
      pi = pi + 3;
   }
   e_pos = pi;
   return type;
}
/*------- end get_type ---------*/


int get_string()
{   
   char varname[VAR_NAME];
   int pi, ndx;

   strcpy(varname, get_varname());    
   /* --- get stack index --- */
   ndx = 0;
   if(callFlag == 0)
   {
      ndx = get_vndx(varname);         
   }
   else
   {
      ndx = get_llvarndx(varname);        
   }
   pi = e_pos;
   pi++;
   pi = iswhiter(pi);
   e_pos = pi;
   return ndx;
}
/*------- end get_string -------*/


void get_qstring()
{   
   char ch, quote='\"';
   int pi, si=0, stlen, ab_code=6, x=line_ndx;

   stlen = strlen(p_string);
   pi = e_pos;                        
   pi++;
   ch = p_string[pi];
   /* --- we now have first character --- */
   /* --- fill buffer with string --- */
   si = 0;
   while((ch != quote) && (pi < stlen))
   {
      s_holder[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
   }
   s_holder[si] = '\0';
   if(pi == stlen)                
   {
      a_bort(ab_code,x);
   }
   pi++;
   e_pos = pi;
}
/*------- end get_qstring -------*/


int get_op()
{
   char ch;
   int pi, op, ab_code=18, x=line_ndx;

   pi = e_pos;
   ch = p_string[pi];
   if(strchr("\"$%!#", ch))
   {
      pi++;			
   }
   pi = iswhite(pi);
   ch = p_string[pi];
   switch(ch)
   {
      case '=':
        op = 1;             
        break;

      case '<':
        pi++;
        ch = p_string[pi];
        if(ch == '>')
        {
           op = 6;         
        }
        else if(ch == '=')
        {
           op = 4;		
        }
        else
        {
           op = 2;		
        }
        break;
        
      case '>':
        pi++;
        ch = p_string[pi];
        if(ch == '=')
        {
           op = 5;         
        }
        else
        {
           op = 3;         
        }
        break;
        
      default:
        a_bort(ab_code,x);
        break;
  }
  if(strchr("=>", ch))
  {
     pi++;
  }
  e_pos = pi;
  return op;
}
/*------- end get_op -------*/


int if_eof()
{
   char tmp[4];
   int flag=0;

   strcpy(tmp, "EOF");       
   flag = find_strng(tmp);   
   return flag;
}
/*-------- end if_eof ---------*/


int is_eof()
{   
   int pi, len, ibool, port, maxfiles=(IOARRAY-1);
   int x=line_ndx, ab_code=23;
   double file_no;
   char ch;
   FILE *handle;

   len = strlen(p_string);
   pi = e_pos; 
   /* get_digit Start */
   ch = p_string[pi];
   while((isdigit(ch) == 0) && (pi < len))
   {
      pi++;
      ch = p_string[pi];
   }
   e_pos = pi;
   /* get_digit Stop */
   file_no = get_avalue();
   port = (int) file_no;
   port--;
   err_hndlr(ab_code, x, 3, port, maxfiles);   
   err_hndlr(ab_code, x, 9, port, 0);         
   handle = fp[port].fptr;
   ibool = feof(handle);
   return ibool;
}
/*------- end is_eof ----------*/
