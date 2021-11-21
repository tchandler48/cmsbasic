USERID GCCCMS

/* bxbasic : Loops.c : alpha version.20.3.1   */
/* Copyright:(c) sarbayo, 2001-2011           */
/* Modified T. Chandler CMSBASIC - cmsloops.c */


void go_to()
{   
   char ch;
   char goto_label[LLEN];
   int pi, si=0, ab_code=8;
   int xtest, x=line_ndx;

   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   while(isalnum(ch))
   {
     goto_label[si] = ch;
     pi++;
     si++;
     ch = p_string[pi];
   }
   goto_label[si] = '\0';             
   pi = -1;            
   xtest = -1;
   while(xtest != 0)
   {
     pi++;
     if(pi == nrows)
     {
       strcpy(t_holder, goto_label);
       a_bort(ab_code, x);        
     }
     xtest = strcmp(label_nam[pi], goto_label);
   }
   pi--;
   line_ndx = pi;            
}
/*--------- end go_to ----------*/


void do_gosub()
{   
   unsigned size;

   if(gs_ptr == 0)
   {
     size = (gs_ptr + 1);
     gosub_stack = malloc(size * sizeof(int));
   }
   else
   {
     size = (gs_ptr + 1);
     gosub_stack = realloc(gosub_stack, size * sizeof(int));
   }
   gosub_stack[gs_ptr] = line_ndx;
   gs_ptr++;
   go_to();
}
/*------- end do_gosub ----------*/


void do_return()
{   
   int ab_code=40, x=line_ndx;
   unsigned size;

   if(gs_ptr == 0)
   {
      a_bort(ab_code, x);        
   }
   else if(gs_ptr == 1)
   {
      gs_ptr--;                      
      line_ndx = gosub_stack[gs_ptr];   
      free(gosub_stack);
   }
   else
   {
      gs_ptr--;                      
      line_ndx = gosub_stack[gs_ptr];    
      size = (gs_ptr);
      gosub_stack = realloc(gosub_stack, size * sizeof(int));
   }
}
/*------- end do_return ----------*/


void do_for()
{   
   char ch;                          
   int pi, f_ndx, Inc=1;
   int start, next_tru;
   int From, Final;

   /* --- assign FROM --- */
   f_ndx = get_From();
   /* --- get TO --- */
   Final = get_To();
   /* --- get STEP --- */
   pi = e_pos;
   ch = p_string[pi];
   if(ch == 'S')
   {
     Inc = get_Step();
   }
   /* --- setup for-loop conditions --- */
   From = Gtbl[f_ndx].Int;
   start = line_ndx;                       
   fornxt_flg++;                          
   /* --- increment loop --- */
   if(From < Final)
   {
     for(; Gtbl[f_ndx].Int <= Final; Gtbl[f_ndx].Int += Inc)
     {
       next_tru = 1;
       line_ndx = (start + 1);        
       while(next_tru == 1)
       {
         strcpy(p_string, array1[line_ndx]);
         token = byte_array[line_ndx];
         s_pos = 0;
         e_pos = 0;
         parser();
         if(token == 12)           
         {
           next_tru = 0;
           token = 0;
         }
         else
         {
           line_ndx++;
         }
       }
     }
  }
  /* --- decrement loop --- */
  else
  {
    for(; Gtbl[f_ndx].Int >= Final; Gtbl[f_ndx].Int -= Inc)
    {
      next_tru = 1;
      line_ndx = (start + 1);        
      while(next_tru == 1)
      {
        strcpy(p_string, array1[line_ndx]);
        token = byte_array[line_ndx];
        s_pos = 0;
        e_pos = 0;
        parser();
        if(token == 12)           
        {
          next_tru = 0;
          token = 0;
        }
        else
        {
          line_ndx++;
         }
       }
     }
  }
  fornxt_flg--;                          
}
/*-------- end do_for ----------*/


void do_next()
{
   int ab_code=16, x=line_ndx;

   if(fornxt_flg == 0)
   {
     a_bort(ab_code,x);
   }
}
/*-------- end do_next ---------*/


int get_From()
{
   char varname[VAR_NAME];
   int pi, type, f_ndx, sav_pi, ab_code=5, x=line_ndx;

   pi = e_pos;
   sav_pi = pi;
   /* --- get varname --- */                   
   strcpy(varname, get_varname());
   type = get_objtype(pi);
   if(type != 1)
   {
     a_bort(ab_code, x);
   }
   let_int(varname);
   /* --- get array index --- */
   if(callFlag == 0)
   {
     f_ndx = get_vndx(varname);
   }
   else
   {
     f_ndx = get_llvarndx(varname);        
   }
   return f_ndx;
}
/*-------- end get_from ----------*/


int get_To()
{   
   char ch, varname[VAR_NAME];
   int pi, Final, ab_code, x=line_ndx;

   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   /* --- get TO --- */
   if(ch != 'T')
   {
     strcpy(t_holder,"TO");
     ab_code=7;
     a_bort(ab_code,x);
   }
   else
   {
     strcpy(varname, get_varname());
     pi = e_pos;
     ch = p_string[pi];
     if(strcmp(varname, "TO") != 0)
     {
       strcpy(t_holder,"TO");
       ab_code=7;
       a_bort(ab_code,x);
     }
   }
   pi = iswhite(pi);
   ch = p_string[pi];
   e_pos = pi;
   /* --- get Final value --- */
   if(isalnum(ch))
   {
     Final = (int) get_avalue();
   }
   else                       
   {
     strcpy(t_holder,"TO");
     ab_code=15;
     a_bort(ab_code, x);
   }
   return Final;
}
/*-------- end get_to ----------*/


int get_Step()
{   
   char ch, varname[VAR_NAME];
   int pi, Inc, ab_code, x=line_ndx;
   char sav_ch=' ';

   strcpy(varname, get_varname());
   if(strcmp(varname, "STEP") != 0)
   {
     strcpy(t_holder, "STEP");
     ab_code=7;
     a_bort(ab_code,x);
   }
   pi = e_pos;
   pi = iswhiter(pi);
   ch = p_string[pi];
   /* --- get Inc value --- */
   if(IsAddop(ch))
   {
     sav_ch = ch;
     pi++;
     pi = iswhiter(pi);
     ch = p_string[pi];
   }
   e_pos = pi;
   if(isalnum(ch))
   {
     Inc = (int) get_avalue();
   }
   else                       
   {
     strcpy(t_holder,"STEP");
     ab_code=15;
     a_bort(ab_code, x);
   }
   if(sav_ch == '-')
   {
     Inc = (0 - Inc);
   }
   return Inc;
}
/*-------- end get_Step ----------*/


void do_Wend()
{   
   int begn_ndx, wend_ndx;

   begn_ndx = line_ndx;
   wend_ndx = find_wend(line_ndx);
   while(boolexpress())
   {
     line_ndx++;
     while(line_ndx != wend_ndx)
     {
       s_pos = 0;
       e_pos = 0;
       strcpy(p_string, array1[line_ndx]);
       token = byte_array[line_ndx];
       parser();
       line_ndx++;
     }
     line_ndx = begn_ndx;
     strcpy(p_string, array1[line_ndx]);
     token = byte_array[line_ndx];
     e_pos = 0;
  }
  line_ndx = wend_ndx;
}
/*-------- end do_WhileWend ----------*/


int find_wend(int ndx)
{   
   int tok=0, ab_code=32, x=line_ndx;

   while((tok != 28) && (ndx < nrows))	   
   {
     ndx++;
     tok = byte_array[ndx];
     if(tok == 27)                  
     {
       ndx = find_wend(ndx);
     }
   }
   if(ndx >= nrows)
   {
     a_bort(ab_code, x);
   }
   return ndx;
}
/*------- end find_wend -------*/


void do_DoWhile()
{
  do_flag++;
  do_pointer = line_ndx;     
}
/*------- end do_DoWhile -------*/


void do_While()
{
   if(do_flag == 0)
   {
     do_Wend();        
   }
   else
   {
     do_WDo();          
   }
}
/*------- end do_While -------*/


void do_WDo()
{
   if(boolexpress())
   {
     line_ndx = do_pointer;  
   }
   else
   {
     do_flag--;
     do_pointer = 0;
   }
}
/*------- end do_WhileDo -------*/
