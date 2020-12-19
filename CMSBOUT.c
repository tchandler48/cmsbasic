USERID GCCCMS
/* bxbasic : Output.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T. Chandler CMSBASIC - cmsbout.c */


void set_TabNl(int ch)
{
   if(ch == ',')
   {
      printf("\t");
   }
   else if(ch == ':')
   {
      printf("\n");
   }
}
/*---------- end set_TabNl ----------*/


void parse_print()
{
  char varname[VAR_NAME], ch;
  int pi, pii, ii, type;
  int ab_code=9, x=line_ndx;

  pi = e_pos;
  pi = iswhiter(pi);
  ch = p_string[pi];
  e_pos = pi;
  /* --- print to file --- */
  if(ch == '#')
  {
    p_string[pi] = '@';           
    print_io();
    return;
  }
  /* --- print newline --- */
  else if(strchr(":\n", ch))
  {
    printf("\n");
    return;
  }
  /* --- LOOP: multiple print statements --- */
  while(ch != '\n')
  {
    if(isalpha(ch))    /* --- print variable --- */
    {
      pi = e_pos;
      pii = pi;                       
      strcpy(varname, get_varname());
      ii = e_pos;
      type = get_objtype(ii);
      if((UdtCnt > 0) && (type < 6))  
      {
        type = isThisUdt(varname, type);
        udtpi += pii;               
      }
      if(type == 0)
      {
        get_strvar(varname);        
      }
      else if(type == 6)
      {
        get_strarray(varname);	    
      }
      else if(type == 10)             
      {
        e_pos = pi;
        get_strUDT();
      }
      else
      {
        e_pos = pi;
        get_prnvar();		        
      }
    }
    else if(isdigit(ch))
    {
      proc_digit();	           
    }
    else if(ch == '?')
    {
      var_type = '?';
      get_prnvar();		       
    }
    else if(ch == '(')
    {
      get_prnvar();		      
    }
    else if(ch == '\"')    	  
    {
      get_prnstring();
    }
    /* --- error: --- */
    else
    {
      a_bort(ab_code, x);
    }
    pi = e_pos;
    ch = p_string[pi];
    if(ch != '\n')
    {
      pi++;
      pi = iswhiter(pi);
      ch = p_string[pi];
      e_pos = pi;
    }
  }
}
/*-------- end parse_print --------*/


void proc_digit()
{   
   char ch, val_strng[VAR_NAME];
   int pi, len, px;
   double value;

   pi = e_pos;
   len = strlen(p_string);
   /* get_paren Start */
   ch = p_string[pi];
   while((strchr("()", ch) == 0) && (pi < len))
   {
     pi++;
     ch = p_string[pi];
   }
   /* get_paren Stop */
   px = pi;
   /* get_NextOp Start */ 
   pi = while_isalnum(pi);
   pi = iswhiter(pi);
   /* get_NextOp Stop */
   if(pi == px)                      
   {
     prn_strfunc();                
   }
   else
   {
     value = rdp_main();           
     strcpy(val_strng, value2strng(value));
     pi = e_pos;
     pi = iswhiter(pi);
     ch = p_string[pi];
     e_pos = pi;
     if(ch == ',')      printf("%s \t", val_strng);
     else if(ch == ';') printf("%s ", val_strng);
     else               printf("%s \n", val_strng);
  }
}
/*-------- end proc_digit --------*/


void prn_strfunc()
{   
   char ch;
   int pi;

   /* --- get function --- */
   asn_function();

   pi = e_pos;
   pi++;
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;
   /* --- display string$ --- */
   if(ch == ',')      printf("%s\t", s_holder);
   else if(ch == ';') printf("%s", s_holder);
   else               printf("%s\n", s_holder);
}
/*--------- end prn_strfunc -----------*/


void get_prnstring()
{   
  char ch;
  int pi, si = 0, stlen;
  int ab_code=6, x=line_ndx;

  stlen = strlen(p_string);
  pi = e_pos;
  pi++;
  ch = p_string[pi];
  while((ch != '\"') && (pi < stlen))
  {
    xstring[si] = ch;
    pi++;
    si++;
    ch = p_string[pi];
  }
  xstring[si]='\0';
  /* --- error: no closing quote --- */
  if(pi >= stlen)
  {
    a_bort(ab_code, x);
  }
  /* --- advance to next character --- */
  pi++;
  pi = iswhiter(pi);
  ch = p_string[pi];
  e_pos = pi;
  /* --- print quoted string --- */
  if(ch == ',')      printf("%s\    ", xstring);
  else if(ch == ';') printf("%s",      xstring);
  else               printf("%s\n",    xstring);
}
/*-------- end get_prnstring --------*/



void get_strUDT()
{
   char varname[VAR_NAME], temp[BUFSIZE];
   char ch, *ptr;
   int pi, ndx, indx, vcount, offset, size;

   ndx = get_UDTndx();                     
   pi = udtpi;
   pi++;
   e_pos = pi;
   strcpy(varname, get_varname());	       
   /* -------------------------------- */
   pi = e_pos;
   ch = p_string[pi];
   if(ch == '$')
   {
      pi++;
   }
   pi = iswhiter(pi);
   e_pos = pi;
   /* -------------------------------- */
   vcount = UDT[ndx].numVars;         
   indx = get_UdtvNamIdx(varname, ndx, vcount); 
   offset = UDT[ndx].offset[indx];
   size = UDT[ndx].size[indx];
   /* --- make string assignment --- */
   ptr = UDT[ndx].data;
   ptr += offset;
   memcpy(temp, ptr, size * sizeof(char));
   /* --- display string$ --- */
   if(ch == ',')      printf("%s\t", temp);
   else if(ch == ';') printf("%s", temp);
   else               printf("%s\n", temp);
}
/*------ end get_strUDT ------*/


void get_strvar(char *varname)
{
   char ch;
   int pi, ndx=0, ab_code=13, x=line_ndx;

   if(callFlag == 0)
   {
     ndx = get_vndx(varname);
   }
   else
   {
     ndx = get_llvarndx(varname);       
   }
   pi = e_pos;
   ch = p_string[pi];
   if(ch == '$')
   {
      pi++;
   }
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;
   /* --- display string$ --- */
   if(ch == ',')      printf("%s\t", Gtbl[ndx].Str);
   else if(ch == ';') printf("%s", Gtbl[ndx].Str);
   else               printf("%s\n", Gtbl[ndx].Str);
}
/*--------- end get_strvar -----------*/


void get_strarray(char *varname)
{   
   char ch;
   int pi, indx, nDims, len, offset;
   int *Subscripts;

   indx = get_arrayndx(varname);
   len = strlen(p_string);
   pi = e_pos;
   /* get_paren Start */
   ch = p_string[pi];
   while((strchr("()", ch) == 0) && (pi < len))
   {
      pi++;
      ch = p_string[pi];
   }
   /* get_paren Stop */
   pi++;
   e_pos = pi;
   Subscripts = &strArry[indx].sub[0];  
   nDims = strArry[indx].dim;           
   offset = get_offset2(Subscripts, nDims, len);
   pi = e_pos;
   pi++;
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;
   /* --- display string$ --- */
   if(ch == ',')      printf("%s\t", strArry[indx].elem[offset]);
   else if(ch == ';') printf("%s", strArry[indx].elem[offset]);
   else               printf("%s\n", strArry[indx].elem[offset]);
}
/*--------- end get_strarray ---------*/


void get_prnvar()
{   
   char ch=var_type, val_strng[VAR_NAME];
   int pi;
   double value;

   /* --- call math parser --- */
   value = rdp_main();
   if(ch == '?')
   {
     var_type = func_type;
   }
   /* --- convert value to string$ --- */
   strcpy(val_strng, value2strng(value));
   var_type = '\0';
   func_type = '\0';
   pi = e_pos;
   pi = iswhiter(pi);
   ch = p_string[pi];
   e_pos = pi;
   if(ch == ',')      printf("%s \t", val_strng);
   else if(ch == ';') printf("%s ", val_strng);
   else               printf("%s \n", val_strng);
}
/*--------- end get_prnvar -----------*/


char *value2strng(double value)
{   
   static char buffer[81];
   int len, idx=0, dot=0;
   char ch, chx=var_type;

   /* --- convert to ascii, here --- */
   sprintf(buffer, "% f", value);
   len = strlen(buffer);
   ch = buffer[idx];
   /* --- trim trailing zeros --- */
   if(chx == '#')                          
   {
     idx = (len-1);
     ch = buffer[idx];
     while(ch == '0')
     {
       idx--;
       ch = buffer[idx];
     }
     buffer[(idx+1)] = '\0';
  }
  /* --- round up to .nn --- */
  else if(chx == '!')                    
  {
    dot = (len-5);
    idx = (len-1);
    while(idx > dot)
    {
      if((buffer[idx] >= '5') && (buffer[(idx-1)] == '9'))
      {
        buffer[idx] = '\0';
      }
      else if(buffer[idx] >= '5')
      {
        buffer[(idx-1)]++;
        buffer[idx] = '\0';
      }
      else
      {
         buffer[idx] = '\0';
      }
      idx--;
    }
  }
  /* --- trim to dot --- */
  else                           
  {
    idx = (len-7);
    buffer[idx] = '\0';
  }
  return buffer;
}
/*------ end value2strng -------*/

