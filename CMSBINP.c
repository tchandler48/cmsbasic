USERID GCCCMS

/* bxbasic : input.c : alpha version.20.3.1  */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T. Chandler CMSBASIC - CMSBINP.c */


void line_cnt(char *argv[])
{   
   int pi, len, ii=0, x=0;
   int ab_code=2;
   unsigned fnam_len;
   int xx,yy;
   char tch;

   nrows = 0;
 
#ifdef CMS
  strcpy(prog_name, argv[1]);
  xx = 0;
  yy = 0;
  tch = prog_name[xx];
  while(tch != '.')
  {
     s_holder[yy] = tch;
     xx++;
     yy++;
     tch = prog_name[xx];
   }
   s_holder[yy] = ' ';
   s_holder[yy+1] = 'b';
   s_holder[yy+2] = 'a';
   s_holder[yy+3] = 's';
   s_holder[yy+4] = ' ';
   s_holder[yy+5] = 'a';

  strcpy(prog_name,s_holder);
#endif


   f_in = fopen(prog_name,"r");
   if(f_in == NULL)                
   {
      a_bort(ab_code, x);
   }
   else
   {
      load_src();            
      loader_1();            
      loader_2();           
   }
}
/*------- end line_cnt ----------*/


void load_src()
{   
   char *tmp="source tmp a";
   int pi, len;
   char ch;
    
   f_out = fopen(tmp,"w");                      
   while(fgets(p_string, BUFSIZE, f_in) != NULL)
   {
     pi = 0;
     pi = iswhite(pi);
     len = strlen(p_string);
     if((len > 2) && (pi < len))              
     {
       if(len != 999)
       {   
         strcpy(xstring, "  ");
         strcat(xstring, p_string);
         pi = 0;
         ch = p_string[pi];
         /* --- test for a Label: --- */
         if(isupper(ch) != 0)
         {
           len = (LLEN-2);
           pi = while_isalnum(pi);                  
           ch = p_string[pi];
           if((ch == ':') && (pi <= len))
           {
             pi++;
             p_string[pi] = '\0';
             strcat(p_string, "\n\0");
             fprintf(f_out,"%s", p_string);       
             nrows++;
           }
           else
           {
             fprintf(f_out,"%s", xstring);        
             nrows++;
           }
         }
/* --- test for numbered line --- */
         else if(isdigit(ch))
         {
           fprintf(f_out,"%s", p_string);           
           nrows++;
         }
         else
         {
            pi = iswhite(pi);
            ch = p_string[pi];
            if(ch != '\'')                           
            {
              fprintf(f_out,"%s", xstring);        
              nrows++;
            }
          }
        }
      }
   }
   fclose(f_in);
   fclose(f_out);
}
/*------- end load_src ----------*/


void loader_1()
{   
   char ch;
   char *tmp="source tmp a";
   int ii, len, pi;
   unsigned size=ncolumns;

   /* --- create temp arrays --- */
   temp_prog = malloc(nrows * sizeof(char *));
   for(ii = 0; ii < nrows; ii++)
   {
      temp_prog[ii] = malloc(size * sizeof(char));
   }
   temp_label = malloc(nrows * sizeof(char *));

   for(ii = 0; ii < nrows; ii++)
   {
      temp_label[ii] = malloc(LLEN * sizeof(char));
   }
   temp_byte = malloc(nrows * sizeof(int));

   /* --- open source.tmp for Read --- */
   f_in = fopen(tmp,"r");
   ii = 0;
   while(fgets(p_string, BUFSIZE, f_in) != NULL)                      
   {
     if(len != 999)
     {
       len = strlen(p_string);
       /* ----- fill temp_label[] here ----- */
       tmp_label(ii);                      
       pi = e_pos;
       ch = p_string[pi];
       if(ch == ':')                       
       {
         temp_byte[ii] = -1;
         strcpy(temp_prog[ii], "\n\0");
       }
       else
       {
          tmp_byte(ii);                    
          tmp_prog(ii);
       }
     }
     ii++;
  }
  fclose(f_in);
}
/*---------- end loader_1 ----------*/


void tmp_label(int ii)
{
   char ch, ln_label[LLEN];
   int pi;

   /* ----- fill temp_label[] here ----- */
   pi = 0;
   ch = p_string[pi];
   if(isalnum(ch))
   {
     while(isalnum(ch))
     {
       ln_label[pi] = ch;
        pi++;
        ch = p_string[pi];
     }
     ln_label[pi] = '\0';
     strcpy(temp_label[ii], ln_label);
  }
  else
  {
     strcpy(temp_label[ii], " \0");
  }
  e_pos = pi;
}
/*---------- end tmp_label ----------*/


void tmp_byte(int ii)
{
   char ch;
   int pi, si, byte;
   int x=ii, ab_code=4;

   /* ----- fill temp_byte[] here ----- */
   pi = e_pos;
   pi = iswhite(pi);
   ch = p_string[pi];
   if(ch == '\'')                               
   {
     byte = 0;
     strcpy(temp_prog[ii], "\n\0");
   }
   else
   {
     if(isupper(ch))                          
     {
       e_pos = pi;
       byte = get_byte(ii);                 
       pi = e_pos;
     }
     else if(isalpha(ch))                     
     {
       si = pi;                             
       /* pi = while_isalnum(pi); */
       pi = while_dd(pi);           
       pi = iswhite(pi);
       ch = p_string[pi];
       if(strchr("=#%!$", ch))              
       {
         byte = 1;
         get_MOD(pi);                     
         pi = si;
       }
       else
       {
         a_bort(ab_code, x);              
       }
     }
     else
     {
       a_bort(ab_code, x);                 
     }
   }
   temp_byte[ii] = byte;
   e_pos = pi;
}
/*---------- end tmp_byte ----------*/


void get_MOD(int pi)
{   
   char ch, temp[VAR_NAME];
   int i, si=0, xi, len;

   len = strlen(p_string);
   xi = pi;
   pi = get_quote(pi, len);           
   if(pi < len)
   {
      return;                                  
   }
   else
   {
      pi = xi;
   }
   pi++;
   pi = iswhite(pi);
   ch = p_string[pi];
   while( pi < (len - 2))
   {
     if((ch == 'F') && (p_string[pi+1] == 'M'))
     {                                        
       pi = pi + 2;
       ch = p_string[pi];
     }
     if(ch == 'M')
     {
       if(p_string[pi+3] == 'F')
       {
         pi = pi + 2;
         ch = p_string[pi];
       }
     }
     if(ch == 'M')                            
     {
       si = pi;
       i = 0;
       while(isalnum(ch))
       {
         temp[i] = ch;
         pi++;
         i++;
         ch = p_string[pi];
       }
       temp[i] = '\0';
       if(strcmp(temp, "MOD") == 0)         
       {
         p_string[si] = '%';
         si++;
         xi = si;                         
         while(pi < len)                  
         {
            p_string[si] = p_string[pi];
            pi++;
            si++;
         }
         p_string[si] = '\0';
         pi = xi;                         
       }
       pi++;
     }
     else
     {
        pi++;
     }
     ch = p_string[pi];
  }
}
/*---------- end get_MOD ----------*/


int get_byte(int ii)
{   
   char ch, keyword[TOKEN_LEN];
   int pi, si=0, pii, byte;
   int x=ii, ab_code=4;

   pi = e_pos;
   ch = p_string[pi];
   while(isalnum(ch))
   {
      keyword[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
   }
   keyword[si] = '\0';

   /* --- assign byte code --- */
   if(strcmp(keyword, "REM") == 0)            byte=0;
   else if(strcmp(keyword, "LET") == 0)
   {			   byte=1;
      get_MOD(pi);    /* scan for a MOD expression */
   }
   else if(strcmp(keyword, "CLEAR") == 0)     byte=2;
   else if(strcmp(keyword, "LOCATE") == 0)    byte=3;
   else if(strcmp(keyword, "PRINT") == 0)     byte=4;
   else if(strcmp(keyword, "GOTO") == 0)      byte=5;
   else if(strcmp(keyword, "BEEP") == 0)      byte=6;
   else if(strcmp(keyword, "CLS") == 0)       byte=7;
   else if(strcmp(keyword, "END") == 0)       byte=8;
   else if(strcmp(keyword, "GOSUB") == 0)     byte=9;
   else if(strcmp(keyword, "RETURN") == 0)    byte=10;
   else if(strcmp(keyword, "FOR") == 0)       byte=11;
   else if(strcmp(keyword, "NEXT") == 0)      byte=12;
   else if(strcmp(keyword, "IF") == 0)        byte=13;
   else if(strcmp(keyword, "ELSEIF") == 0)    byte=14;
   else if(strcmp(keyword, "ELSE") == 0)      byte=15;
   else if(strcmp(keyword, "ENDIF") == 0)     byte=16;
   else if(strcmp(keyword, "INPUT") == 0)     byte=17;
   else if(strcmp(keyword, "LINE") == 0)
   {
     pii = pi;
     pii = iswhite(pii);
     ch = p_string[pii];
     if(ch == 'I')                          byte=18;
     else                                   byte=58;
  }
  else if(strcmp(keyword, "OPEN") == 0)      byte=19;
  else if(strcmp(keyword, "CLOSE") == 0)     byte=20;
  else if(strcmp(keyword, "WRITE") == 0)     byte=21;
  else if(strcmp(keyword, "FIELD") == 0)     byte=22;
  else if(strcmp(keyword, "LSET") == 0)      byte=23;
  else if(strcmp(keyword, "RSET") == 0)      byte=24;
  else if(strcmp(keyword, "PUT") == 0)       byte=25;
  else if(strcmp(keyword, "GET") == 0)       byte=26;
  else if(strcmp(keyword, "WHILE") == 0)     byte=27;
  else if(strcmp(keyword, "WEND") == 0)      byte=28;
  else if(strcmp(keyword, "DO") == 0)        byte=29;
  else if(strcmp(keyword, "REDIM") == 0)     byte=30;
  else if(strcmp(keyword, "SWITCH") == 0)    byte=31;
  else if(strcmp(keyword, "CASE") == 0)      byte=32;
  else if(strcmp(keyword, "DEFAULT") == 0)   byte=33;
  else if(strcmp(keyword, "ENDSWITCH") == 0) byte=34;
  else if(strcmp(keyword, "DIM") == 0)       byte=35;
  else if(strcmp(keyword, "DECLARE") == 0)   byte=36;
  else if(strcmp(keyword, "CALL") == 0)      byte=37;
  else if(strcmp(keyword, "SUB") == 0)       byte=38;
  else if(strcmp(keyword, "ENDSUB") == 0)    byte=39;
  else if(strcmp(keyword, "STOP") == 0)      byte=40;
  else if(strcmp(keyword, "SYSTEM") == 0)    byte=41;
  else if(strcmp(keyword, "ERASE") == 0)     byte=43;
  else if(strcmp(keyword, "RANDOM") == 0)    byte=44;
  else if(strcmp(keyword, "KILL") == 0)      byte=45;
  else if(strcmp(keyword, "UDT") == 0)          byte=126;
  else if(strcmp(keyword, "STRUCT") == 0)       byte=126;
  else if(strcmp(keyword, "ENDUDT") == 0)       byte=127;
  else if(strcmp(keyword, "ENDSTRUCT") == 0)    byte=127;
  else if(strcmp(keyword, "APPTYPE") == 0)      byte=200;
  else
  {
     pi = iswhite(pi);
     ch = p_string[pi];
     if(strchr("=#%!$", ch))                 
     {
        byte = 1;
        get_MOD(pi);                    
        pi = e_pos;                          
     }
     else if(strchr("._", ch))                
     {
        byte = 1;
        get_MOD(pi);                    
        pi = e_pos;                          
     }
     else
     {
        a_bort(ab_code, x);            
     }
  }
  e_pos = pi;
  return byte;
}
/*---------- end get_byte ----------*/


void tmp_prog(int ii)
{   
   char ch, prog[BUFSIZE];
   int pi, si=0, len;

   len = strlen(p_string);
   pi = e_pos;
   pi = iswhite(pi);
   /* --- correct: LINE INPUT --- */
   if(temp_byte[ii] == 18)
   {
      ch = p_string[pi];
      while(isalpha(ch))
      {
         pi++;                               
         ch = p_string[pi];
      }
      pi = iswhite(pi);
      ch = p_string[pi];
      while(ch != '\0')
      {
         prog[si] = ch;
         si++;
         pi++;
         ch = p_string[pi];
      }
      prog[si] = '\0';
  }
  else if((pi < len) && (temp_byte[ii] != 0))
  {
     ch = p_string[pi];
     while(ch != '\0')
     {
        prog[si] = ch;
        si++;
        pi++;
        ch = p_string[pi];
     }
     prog[si] = '\0';
  }
  else
  {
     strcpy(prog, "\n\0");
  }
  strcpy(temp_prog[ii], prog);
}
/*---------- end tmp_prog ----------*/


void loader_2()
{   
   int ndx, ii, line_count=0, lines=nrows;
   unsigned size;

   /* --- re-count number of lines --- */
   for(ndx=0; ndx < nrows; ndx++)
   {
      if(temp_byte[ndx] != 0)
      {
        line_count++;
      }
      if((temp_byte[ndx] == 13) || (temp_byte[ndx] == 14))
      {
         token_if(ndx);		            
         str_fun3(ndx);
      }
      if(temp_byte[ndx] == 27)
      {
         token_if(ndx);		            
         str_fun3(ndx);
      }
      else if(temp_byte[ndx] == 1)
      {
         str_funn(ndx);	           
      }
      else if(temp_byte[ndx] == 4)
      {
         str_fun2(ndx);	            
      }
      else if((temp_byte[ndx] == 23) || (temp_byte[ndx] == 24))
      {
         str_funn(ndx);	  		    
      }
      else if(temp_byte[ndx] == 38)
      {
         preproc_sub(ndx);	  			    
      }
  }
  /* nrows = line_count; */
  line_count = nrows;
  /* --- create program arrays --- */
  array1 = malloc(nrows * sizeof(char *));
  label_nam = malloc(nrows * sizeof(char *));
  for(ii = 0; ii < nrows; ii++)
  {
    label_nam[ii] = malloc(LLEN * sizeof(char));
  }
  byte_array = malloc(nrows * sizeof(int));
  /* --- transfer temp_arrays to program_arrays --- */
  ndx = 0;
  for(ii=0; ii < lines; ii++)
  {
    if(temp_byte[ii] != 0)
    {
       strcpy(label_nam[ndx], temp_label[ii]);
       byte_array[ndx] = temp_byte[ii];
       size = strlen(temp_prog[ii]);
       size++;
       array1[ndx] = malloc(size * sizeof(char));
       strcpy(array1[ndx], temp_prog[ii]);
       ndx++;
    }
  }
  /* --- free temp array memory --- */
  for(ii=0; ii < lines; ii++)
  {
     free(temp_label[ii]);
     free(temp_prog[ii]);
  }
  free(temp_label);
  free(temp_byte);
  free(temp_prog);
}
/*---------- end loader_2 ----------*/


void preproc_sub(int ndx)
{   
   char label[LLEN];
   int pi=0;

   e_pos = pi;
   strcpy(p_string, temp_prog[ndx]);
   strcpy(label, get_varname());
   strcpy(temp_label[ndx], label);		      
}
/*------- end preproc_sub -------*/


void token_if(int ndx)
{   
   char temp[TOKEN_LEN];
   int loc;

   strcpy(p_string, temp_prog[ndx]);
   s_pos = 0;
   strcpy(temp, "AND");
   loc = 0;
   while(loc >= 0)
   {
     loc = find_strng(temp);
     loc--;
     if(loc > 0)
     {
       p_string[loc] = '&';                 
       p_string[(loc+1)] = ' ';
       p_string[(loc+2)] = ' ';
     }
  }
  strcpy(temp, "OR");
  loc = 0;
  while(loc >= 0)
  {
    loc = find_strng(temp);
    loc--;
    if(loc > 0)
    {
      p_string[loc] = '|';                 
      p_string[(loc+1)] = ' ';
    }
  }
  strcpy(temp, "THEN");                        
  loc = 0;
  while(loc >= 0)
  {
    loc = find_strng(temp);
    loc--;
    if(loc > 0)
    {
      p_string[loc] = '\n';                
      p_string[(loc+1)] = '\0';
    }
  }
  strcpy(temp, "Then");                        
  loc = 0;
  while(loc >= 0)
  {
    loc = find_strng(temp);
    loc--;
    if(loc > 0)
    {
      p_string[loc] = '\n';               
      p_string[(loc+1)] = '\0';
    }
  }
 strcpy(temp_prog[ndx], p_string);
}
/*---------- end token_if ----------*/


void str_funn(int ndx)                    
{
   char ch, temp[VAR_NAME]; 	            
   int pi=0, len;

   strcpy(p_string, temp_prog[ndx]);
   while(IsEqu(pi) == 0)		            
   {
      pi = e_pos;
      pi++;
   }
   pi = e_pos;	       
   len = strlen(p_string);
   pi++;                                   
   while(pi < len)
   {
     pi = iswhiter(pi);                 
     ch = p_string[pi];                  
     if(ch == '\"')                      
     {
       pi = get_quote(pi, len);
     }
     else
     {    
       /* get_upper Start */
       ch = p_string[pi];
       while((isupper(ch) == 0) && (pi < len))
       {
         pi++;
         ch = p_string[pi];
       }
       /* get_upper Stop */
       if(pi < len)
       {
          e_pos = pi;
          strcpy(temp, get_varname());     
          s_pos = e_pos;
          ch = p_string[s_pos];
          /* printf("spos=%d, ch=%c, name=%s\n", s_pos, ch, temp);*/
          if(ch == '$')                    
          {
            e_pos = pi;
            get_strfunc(temp,ndx);      
          }
          else
          {
            e_pos = pi;
            get_mathfunc(temp,ndx);	     
          }
          pi = e_pos;
          pi++;
        }
      }
   }
}
/*---------- end str_functn ----------*/


void str_fun2(int ndx)
{   
   char ch, quote='\"', temp[VAR_NAME];         
   int pi=0, len;		                         

   strcpy(p_string, temp_prog[ndx]);
   len = strlen(p_string);
   /* --- loop --- */
   while(pi < len)
   {
     ch = p_string[pi];
     if(ch == quote)
     {
       pi= get_quote(pi, len);
     }
     else
     {
        /* get_upper Start */
        ch = p_string[pi];
        while((isupper(ch) == 0) && (pi < len))
        {
          pi++;
          ch = p_string[pi];
        }
        /* get_upper Stop */
        if(pi < len)
        {
          e_pos = pi;
          strcpy(temp, get_varname());	
          s_pos = e_pos;
          ch = p_string[s_pos];
          if(ch == '$')                    
          {
             e_pos = pi;
             get_strfunc(temp,ndx);	     
          }
          else
          {
             e_pos = pi;
             get_mathfunc(temp,ndx);      
          }
          pi = e_pos;
          pi++;
        }
      }
   }
}
/*---------- end str_funct2 ----------*/


void get_strfunc(char *varname,int ndx)		     
{   
   char temp[TOKEN_LEN];

   temp[0] = '\0';

   /* --- now compare to functions --- */
   if(strcmp(varname, "CHR") == 0)
   {
      strcpy(temp, "   1");	                 
   }
   else if(strcmp(varname, "LEFT") == 0)
   { 
      strcpy(temp, "    2");	               
   }
   else if(strcmp(varname, "RIGHT") == 0)
   {
      strcpy(temp, "     3");	                 
   }
   else if(strcmp(varname, "MID") == 0)
   {
      strcpy(temp, "   4");	                 
   }
   else if(strcmp(varname, "SPACE") == 0)
   {
      strcpy(temp, "     5");	                 
   }
   else if(strcmp(varname, "STR") == 0)
   {
      strcpy(temp, "   6");	                 
   }
   else if(strcmp(varname, "STRING") == 0)
   {
      strcpy(temp, "      7");                 
   }
   else if(strcmp(varname, "INKEY") == 0)
   {
      strcpy(temp, "     8");                 
   }
   else if(strcmp(varname, "INPUT") == 0)
   {
      strcpy(temp, "     9");                  
   }
   else if(strcmp(varname, "MKD") == 0)
   {
      strcpy(temp, "  10");                   
   }
   else if(strcmp(varname, "MKI") == 0)
   {
      strcpy(temp, "  11");                    
   }
   else if(strcmp(varname, "MKS") == 0)
   {
      strcpy(temp, "  12");                    
   }
   else if(strcmp(varname, "UCASE") == 0)
   { 
      strcpy(temp, "    13");                  
   }
   else if(strcmp(varname, "LCASE") == 0)
   {
      strcpy(temp, "    14");                  
   }
   else if(strcmp(varname, "TIME") == 0)
   {
      strcpy(temp, "   15");                   
   }
   else if(strcmp(varname, "DATE") == 0)
   {
      strcpy(temp, "   16");                   
   }
   str_copy(temp, ndx);		            
}
/*---------- end get_strfunc ----------*/


void get_mathfunc(char *varname, int ndx)        
{   
   char temp[TOKEN_LEN];

   temp[0] = '\0';
   /* --- now compare to functions --- */
   if(strcmp(varname, "ABS") == 0)
   {
      strcpy(temp, " ?1");		             
   }
   else if(strcmp(varname, "ASC") == 0)
   {
      strcpy(temp, " ?2");		             
   }
   else if(strcmp(varname, "ATN") == 0)
   {
      strcpy(temp, " ?3");		             
   }
   else if(strcmp(varname, "COS") == 0)
   {
      strcpy(temp, " ?4");		             
   }
   else if(strcmp(varname, "SIN") == 0)
   {
      strcpy(temp, " ?5");		             
   }
   else if(strcmp(varname, "TAN") == 0)
   {
      strcpy(temp, " ?6");		             
   }
   else if(strcmp(varname, "SQRT") == 0)
   {
      strcpy(temp, "  ?7");		             
   }
   else if(strcmp(varname, "INT") == 0)
   {
      strcpy(temp, " ?8");		             
   }
   else if(strcmp(varname, "LEN") == 0)
   {
      strcpy(temp, " ?9");		             
   }
   else if(strcmp(varname, "LOF") == 0)
   {
      strcpy(temp, "?10");		             
   }
   else if(strcmp(varname, "LOC") == 0)
   {
      strcpy(temp, "?11");		             
   }
   else if(strcmp(varname, "CVD") == 0)
   {
      strcpy(temp, "?12");		            
   }
   else if(strcmp(varname, "CVI") == 0)
   {
      strcpy(temp, "?13");		             
   }
   else if(strcmp(varname, "CVS") == 0)
   {
      strcpy(temp, "?14");		             
   }
   else if(strcmp(varname, "EOF") == 0)
   {
      strcpy(temp, "?15");		             
   }
   else if(strcmp(varname, "VAL") == 0)
   {
      strcpy(temp, "?16");		             
   }
   else if(strcmp(varname, "CLOCK") == 0)
   {
      strcpy(temp, "  ?17");                  
   }
   else if(strcmp(varname, "RAND") == 0)
   {
      strcpy(temp, " ?18");                    
   }
   else if(strcmp(varname, "LOG") == 0)
   {   
      strcpy(temp, "?19");                     
   }
   else if(strcmp(varname, "LOG10") == 0)
   {
      strcpy(temp, "  ?20");                   
   }
   else if(strcmp(varname, "SECONDS") == 0)
   {
      strcpy(temp, "    ?21");                 
   }
   else if(strcmp(varname, "EXP") == 0)
   {
      strcpy(temp, "?23");                     
   }
   else if(strcmp(varname, "ACOS") == 0)
   {
      strcpy(temp, " ?24");                    
   }
   else if(strcmp(varname, "ASIN") == 0)
   {
      strcpy(temp, " ?25");                    
   }
   else if(strcmp(varname, "CEIL") == 0)
   {
      strcpy(temp, " ?26");                   
   }
   else if(strcmp(varname, "COSH") == 0)
   {
      strcpy(temp, " ?27");                    
   }
   else if(strcmp(varname, "FABS") == 0)
   {
      strcpy(temp, " ?28");                    
   }
   else if(strcmp(varname, "FLOOR") == 0)
   {
      strcpy(temp, "  ?29");                   
   }
   else if(strcmp(varname, "FMOD") == 0)
   {
      strcpy(temp, " ?30");                    
   }
   else if(strcmp(varname, "HYPOT") == 0)
   {
      strcpy(temp, "  ?31");                   
   }
   else if(strcmp(varname, "LDEXP") == 0)
   {
      strcpy(temp, "  ?32");                   
   }
   else if(strcmp(varname, "MODF") == 0)
   {
      strcpy(temp, " ?33");                    
   }
   else if(strcmp(varname, "POW") == 0)
   {
      strcpy(temp, "?34");                     
   }
   else if(strcmp(varname, "POW10") == 0)
   {
      strcpy(temp, "  ?35");                   
   }
   else if(strcmp(varname, "SINH") == 0)
   {
      strcpy(temp, " ?36");                    
   }
   else if(strcmp(varname, "TANH") == 0)
   {
      strcpy(temp, " ?37");                    
   }
   else if(strcmp(varname, "ATAN2") == 0)
   {
      strcpy(temp, "  ?38");                   
   }
   else if(strcmp(varname, "FREXP") == 0)
   { 
      strcpy(temp, "  ?39");                   
   }
   else if(strcmp(varname, "LABS") == 0)
   {
      strcpy(temp, " ?40");                    
   }
   else if(strcmp(varname, "TIMER") == 0)
   {
      strcpy(temp, "  ?42");                   
   }
   else if(strcmp(varname, "SGN") == 0)
   {
      strcpy(temp, "?43");                     
   }
   else if(strcmp(varname, "CINT") == 0)
   {
      strcpy(temp, " ?48");                    
   }
   else if(strcmp(varname, "CDBL") == 0)
   {
      strcpy(temp, " ?49");                    
   }
   else if(strcmp(varname, "CSNG") == 0)
   {
      strcpy(temp, " ?50");                    
   }
   else if(strcmp(varname, "CLNG") == 0)
   {
      strcpy(temp, " ?51");                   
   }
   str_copy(temp, ndx);		   
}
/*---------- end get_mathfunc ----------*/


void str_copy(char *temp,int ndx)
{   
   char ch, tok[TOKEN_LEN];	            
   int pi, si=0;

   strcpy(tok, temp);
   pi = e_pos;
   ch = tok[si];
   if(ch != '\0')
   {
     while(ch != '\0')
     {
       p_string[pi] = ch;
       si++;
       pi++;
       ch = tok[si];
     }
     strcpy(temp_prog[ndx], p_string);
     e_pos = pi;
  }
  else
  {
     e_pos = s_pos;		                     
  }
}
/*---------- end str_copy ----------*/


int IsEqu(int pi)
{   
   char ch;			                         
   int ibool=0;

   pi = iswhite(pi);
   e_pos = pi;
   ch = p_string[pi];
   if(ch == '=')
   {
     ibool = 1;
   }
   return ibool;
}
/*---------- end IsEqu ----------*/


void str_fun3(int ndx)
{   
   char ch, quote='\"', temp[VAR_NAME];        
   int pi, len;		                        

   strcpy(p_string, temp_prog[ndx]);
   len = strlen(p_string);
   pi = 0;
   /* --- loop --- */
   while(pi <= len)
   {
     ch = p_string[pi];
     if(ch == quote)
     {
       pi= get_quote(pi, len);
     }
     else if(isupper(ch) != 0)
     {
       e_pos = pi;
       strcpy(temp, get_varname());	       
       s_pos = e_pos;
       ch = p_string[s_pos];
       if(ch == '$')                        
       {
         e_pos = pi;
         get_strfunc(temp,ndx);	         
       }
       else
       {
         e_pos = pi;
         get_mathfunc(temp,ndx);          
       }
       pi = e_pos;
       /* pi++; */
     }
     else
     {
       pi++;
     }
  }
}
/*---------- end str_funct3 ----------*/
