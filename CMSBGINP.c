USERID GCCCMS
/* bxbasic : Getinput.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011            */
/* Modified T. Chandler CMSBASIC getinput.c    */


void get_lninput()
{   
   char ch, varname[VAR_NAME];
   int pi, loc=0;

   pi = e_pos;
   ch = p_string[pi];
   if(ch == '#')
   {
      p_string[pi] = '@';
      input_io();
      return;
   }
   else if(ch == ';')		
   {
      loc = 1;
      pi++;
      pi = iswhite(pi);
      ch = p_string[pi];
      e_pos = pi;
   }

   if(ch == '\"')          	
   {
      get_prnstring();
      pi = e_pos;
      pi++;
      pi = iswhite(pi);
      ch = p_string[pi];
      e_pos = pi;
   }
   /* --- input string --- */
   strcpy(varname, get_varname());
   input_str(varname,loc);
}
/*---------- end get_lninput ----------*/



void get_input()
{   
   char ch, varname[VAR_NAME];
   int pi, len, type, loc=0;
   int ab_code=19, x=line_ndx;

   pi = e_pos;
   ch = p_string[pi];
   if(ch == '#')                  
   {
      input_io();
      return;
   }
   else if(ch == ';')		
   {
      loc = 1;
      pi++;
      pi = iswhite(pi);
      ch = p_string[pi];
      e_pos = pi;
   }
   len = strlen(p_string);
   while(pi < len)                       
   {
      if(ch == '\"')          	
      {
         get_prnstring();
         pi = e_pos;
         pi++;
         pi = iswhite(pi);
         ch = p_string[pi];
         e_pos = pi;
      }
      /* --- a string$ or numeric variable --- */
      else if(isalpha(ch))
      {
         type = get_vtype(pi);
         strcpy(varname, get_varname());
         if(type == 3)       	
         {
            input_str(varname,loc);
            pi = e_pos;
            ch = p_string[pi];
         }
         else  		 
         {
            input_val(varname,loc);
            pi = e_pos;
            ch = p_string[pi];
         }
      }
      else
      {   
         a_bort(ab_code, x);
      }
   }
}
/*---------- end get_input ----------*/



void input_val(char *varname, int loc)
{   
   char ch, string[VAR_NAME];
   int pi, ndx, len, row, col;

   pi = e_pos;
   ch = p_string[pi];
   /* --- get cursor --- */
   switch(loc)
   {
      case 1:			/* --- get data-input --- */
        gets(string);
        len = strlen(string);
        break;

      default:
        gets(string);
        break;
  }

  switch(ch)
  {
      case '#':		/* --- double --- */		
        if(callFlag == 0)
        {
           ndx = get_vndx(varname);
        }
        else
        {
           ndx = get_llvarndx(varname);        
        }
        Gtbl[ndx].Dbl = (double) atof(string);
        pi++;
        break;
        
      case '!':		/* --- float --- */
        if(callFlag == 0)
        {
           ndx = get_vndx(varname);
        }
        else
        {
           ndx = get_llvarndx(varname);        
        }
        Gtbl[ndx].Flt = (float) atof(string);
        pi++;
        break;
        
      case '%':		/* --- long --- */
        if(callFlag == 0)
        {
           ndx = get_vndx(varname);
        }
        else
        {
           ndx = get_llvarndx(varname);        
        }
        Gtbl[ndx].Lng = atol(string);
        pi++;
        break;
        
      default:		/* --- integer --- */
        if(callFlag == 0)
        {
           ndx = get_vndx(varname);
        }
        else
        {
           ndx = get_llvarndx(varname);        
        }
        Gtbl[ndx].Int = atoi(string);
        break;
  }

  pi = iswhite(pi);
  ch = p_string[pi];
  if(strchr(":;,", ch))
  {
     pi++;
     set_TabNl(ch);			
  }
  pi = iswhite(pi);
  e_pos = pi;
}
/*---------- end input_val ----------*/



void input_str(char *varname, int loc)
{   
   char ch, string[BUFSIZE];
   int pi, ndx, len, row, col;
   unsigned xsize;

   if(callFlag == 0)
   {
      ndx = get_vndx(varname);
   }
   else
   {
      ndx = get_llvarndx(varname);        
   }
   /* --- get cursor --- */
   switch(loc)
   {
      case 1:		/* --- get data-input --- */
        gets(string);
        len = strlen(string);
        break;
   
      default:
        gets(string);
        break;
  }

  /* --- store data --- */
  xsize = strlen(string);
  xsize++;
  Gtbl[ndx].Str = realloc(Gtbl[ndx].Str, xsize * sizeof(char));
  strcpy(Gtbl[ndx].Str, string);
  pi = e_pos;
  pi++;
  ch = p_string[pi];
  if(strchr(":;,", ch))
  {
     pi++;
     set_TabNl(ch);			
  }
  pi = iswhite(pi);
  e_pos = pi;
}
/*---------- end input_str ----------*/
