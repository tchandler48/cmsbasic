USERID GCCCMS

/* bxbasic : Strings.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011           */
/* Modified T. Chandler CMSBASIC - CMSBSTRG.c */


void dim_gstr(char *varname)
{   
   char temp[BUFSIZE];
   int pi, ndx;
   unsigned size;

   pi = e_pos;
   ndx = get_var_index(varname);
   lset_ndx = ndx;                   
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   Gtbl[ndx].ActSub = ActvSubs;   
   /* --- now get assignment string --- */
   Match('=');
   strcpy(temp, str_express());
   /* --- make string assignment --- */
   size = strlen(temp);
   size++;
   Gtbl[ndx].Str = malloc(size * sizeof(char));
   if(size == 1)
   {
     Gtbl[ndx].Str[0] = '\0';
   }
   else
   {
     strcpy(Gtbl[ndx].Str, temp);
   }
}
/*---------- end dim_gstr ----------*/


void parse_st(char *varname)
{   
   char temp[BUFSIZE];
   int pi, ndx;
   unsigned size;

   pi = e_pos;
   if(callFlag == 0)
   {
     ndx = get_vndx(varname);
   }
   else
   {
     ndx = get_llvarndx(varname);        
   }
   lset_ndx = ndx;                   
   pi++;
   pi = iswhite(pi);
   e_pos = pi;
   /* --- now get assignment string --- */
   Match('=');
   strcpy(temp, str_express());
   /* --- make string assignment --- */
   size = strlen(temp);
   size++;
   Gtbl[ndx].Str = realloc(Gtbl[ndx].Str, size * sizeof(char));
   strcpy(Gtbl[ndx].Str, temp);
}
/*---------- end parse_str ----------*/


char *str_express()
{   
   char ch;
   static char temp[BUFSIZE];
   int pi, len;

   temp[0] = '\0';
   len = strlen(p_string);
   pi = e_pos;
   while(pi < len)
   {
     ch = p_string[pi];
     if(ch == '\"')
     {
       strng_assgn();                  
     }
     else if(isdigit(ch))
     {
       asn_function();                 
     }
     else
     {
       strvar_assgn();                
     }
     strcat(temp, s_holder);           
     pi = e_pos;
     pi++;
     pi = iswhite(pi);
     e_pos = pi;
     ch = p_string[pi];
     if(ch == ',')
     {
       break;                          
     }
     else if(pi < len)
     {
       Match('+');                     
       pi = e_pos;
     }
  }
  return temp;
}
/*---------- end str_express ----------*/


void asn_function()
{   
  int type;
  char varname[VAR_NAME], ch, ztime[30];
  char char_x, quote='\"';
  int i, pi, indx, count, len, ii, left, ivalue;
  double fvalue,  value;
  time_t xtime;

  type = (int) get_avalue();

  switch(type)
  {
    case 1:		/* CHR$ */
      pi = e_pos;              
      pi++;                    
      pi = iswhite(pi);
      e_pos = pi;
      fvalue = get_avalue();
      ivalue = fvalue;
      s_holder[0] = ivalue;
      s_holder[1] = '\0';
      break;

    case 2:		/* LEFT$  */
      pi = e_pos;                  
      pi++;                    
      pi = iswhite(pi);
      e_pos = pi;
      strcpy(varname, get_varname());
      if(callFlag == 0)
      {
        indx = get_vndx(varname);
      }
      else
      {
        indx = get_llvarndx(varname);        
      }
      pi = e_pos;              
      pi += 2;                    
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      len = strlen(Gtbl[indx].Str);
      if(count > len)
      {
        count = len;
      }
      for(i=0; i < count; i++)
      {
        s_holder[i] = Gtbl[indx].Str[i];
      }
      s_holder[count] = '\0';
      break;
    
    case 3:		/* RIGHT$ */
      pi = e_pos;                 
      pi++;                   
      pi = iswhite(pi);
      e_pos = pi;
      strcpy(varname, get_varname());
      if(callFlag == 0)
      {
        indx = get_vndx(varname);
      }
      else
      {
        indx = get_llvarndx(varname);        
      }
      pi = e_pos;              
      pi += 2;                   
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      len = strlen(Gtbl[indx].Str);
      if(count > len)
      {
        count = len;
      }
      left = (len - count);
      for(ii=0; ii < count; ii++, left++)
      {
        s_holder[ii] = Gtbl[indx].Str[left];
      }
      s_holder[count] = '\0';
      break;

    case 4:		/* MIDSTR$ */
      pi = e_pos;               
      pi++;                   
      pi = iswhite(pi);
      e_pos = pi;
      strcpy(varname, get_varname());
      if(callFlag == 0)
      {
        indx = get_vndx(varname);
      }
      else
      {
        indx = get_llvarndx(varname);        
      }
      pi = e_pos;               
      pi += 2;                  
      pi = iswhite(pi);
      e_pos = pi;
      left = (int) get_avalue();
      pi = e_pos;              	
      pi = iswhite(pi);           
      ch = p_string[pi];
      e_pos = pi;
      if(ch == ')')
      {
        count = 255;          
      }
      else
      {
        pi++;                 
        pi = iswhite(pi);
        e_pos = pi;
        count = (int) get_avalue();
      }
      if(count < 1)
      {
        count = 0;
      }
      len = strlen(Gtbl[indx].Str);
      left--;		    		
      if((left + count) > len)
      {
        count = (len - left);
      }
      for(ii=0; ii < count; ii++, left++)
      {
        s_holder[ii] = Gtbl[indx].Str[left];
      }
      s_holder[count] = '\0';
      break;
       
    case 5:		/* SPACESTR$ */
      pi = e_pos;               
      pi++;                  
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      else if(count > 255)
      {
        count = 255;
      }
      for(ii=0; ii < count; ii++)
      {
        s_holder[ii] = ' ';
      }
      s_holder[count] = '\0';
      break;
      
    case 6:		/* STR$ */
      pi = e_pos;              
      pi++;                    
      pi = iswhite(pi);
      e_pos = pi;
      value = get_avalue();
      strcpy(s_holder, value2strng(value));
      break;

    case 7:		/* STRINGS$ */
      pi = e_pos;           
      pi++;                
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      else if(count > 255)
      {
        count = 255;
      }
      pi = e_pos;                
      pi++;
      pi = iswhite(pi);
      e_pos = pi;
      ch = p_string[pi];
      if(ch == quote)               
      {
        pi++;
        ch = p_string[pi];
        char_x = ch;
        while(ch != ')')          
        {
            pi++;
            ch = p_string[pi];
        }
        e_pos = pi;
      }
      else
      {
        fvalue = get_avalue();
        ivalue = fvalue;
      }
      for(ii=0; ii < count; ii++)
      {
        s_holder[ii] = ivalue;
      }
      s_holder[count] = '\0';
      break;

    case 9:	/* a$ = INPUT$(n) */
	

    /*        inputstr();	*/	
            break;
        case 10:	/* a$ = MKD$(n) */
	
        case 11:	/* a$ = MKI$(n) */
	
        case 12:	/* a$ = MKS$(n) */
	
    /*        mkdstr();	*/
            break;
   
    case 13:		/* a$ = UCASE$(x$) */
      pi = e_pos;                  
      pi++;                    
      pi = iswhite(pi);
      e_pos = pi;  
      strcpy(varname, get_varname());
      indx = get_strndx(varname);
      pi = e_pos;               
      pi += 2;                    
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      len = strlen(Gtbl[indx].Str);
      count = len;
      for(i=0; i < count; i++)
      {
        s_holder[i] = toupper(Gtbl[indx].Str[i]);
      }
      s_holder[count] = '\0';
      break;

    case 14:		/* a$ = LCASE$(x$) */
      pi = e_pos;                  
      pi++;                    
      pi = iswhite(pi);
      e_pos = pi;
      strcpy(varname, get_varname());
      indx = get_strndx(varname);
      pi = e_pos;               
      pi += 2;                    
      pi = iswhite(pi);
      e_pos = pi;
      count = (int) get_avalue();
      if(count < 1)
      {
        count = 0;
      }
      len = strlen(Gtbl[indx].Str);
      count = len;
      for(i=0; i < count; i++)
      {
        s_holder[i] = tolower(Gtbl[indx].Str[i]);
      }
      s_holder[count] = '\0';
      break;

    case 15:		/* a$ = TIME$ */
      time(&xtime);
      strcpy(ztime, ctime(&xtime));
      len = strlen(ztime);
      ztime[len-1] = '\0';
      left = 11;
      count = 8;
      for(ii=0; ii < count; ii++, left++)
      {
        s_holder[ii] = ztime[left];
      }
      s_holder[count] = '\0';
      break;

    case 16:		 /* a$ = DATE$ */
      time(&xtime);
      strcpy(ztime, ctime(&xtime));
      len = strlen(ztime);
      ztime[len-1] = '\0';
      left = 0;
      count = 10;
      for(ii=0; ii < count; ii++, left++)
      {
        s_holder[ii] = ztime[left];
      }
      s_holder[count] = '\0';
      left = 19;
      count = 15;
      for(ii=10; ii < count; ii++, left++)
      {
        s_holder[ii] = ztime[left];
      }
      s_holder[count] = '\0';
      break;

    default:
      /* error */
      break;
  }
}
/*---------- end asn_function ----------*/


/*
void mkdstr()                       
{                                   
  strsval();                      
}
*/
/*------ end mkdstr ------*/


/*
void inputstr()
{   
  char ch;
  int pi, count, i;

  pi = e_pos;                      
  pi++;                            
  e_pos = pi;
  count = (int) get_avalue();

  for(i=0; i <= count; i++)
  {
    s_holder[i] = '\0';
  }

  i = 0;
  while(i < count)
  {
    ch = getche();
    if((ch > 31) && (ch < 127))	
    {
      s_holder[i] = ch;
      i++;
    }
    else if((ch == 8) && (i > 0))	
    {
      s_holder[i] = '\0';
      i--;
    }
  }
  s_holder[count] = '\0';
}
*/
/*---------- end inputstr ----------*/


void strng_assgn()
{   
   char ch, quote='\"';
   int pi, stlen, si=0, ab_code=6, x=line_ndx;

   stlen = strlen(p_string);
   pi = e_pos;                       
   pi++;
   ch = p_string[pi];
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
   e_pos = pi;
}
/*---------- end strng_assgn ----------*/


int get_strndx(char *varname)
{   
   int indx=0;

   if(callFlag == 0)
   {
     indx = get_vndx(varname);
   }
   else
   {
     indx = get_llvarndx(varname);        
   }
   return indx;
}
/*---------- end get_strndx ----------*/


void strvar_assgn()
{
  char varname[VAR_NAME], ch;
  int pi, pii, len, type, indx, nDims, offset;
  int *Subscripts;

  pi = e_pos;
  pii = pi;                               
  strcpy(varname, get_varname());
  pi = e_pos;
  type = get_objtype(pi);

  if((UdtCnt > 0) && (type == 0))         
  {
    type = isThisUdt(varname, type);
    udtpi += pii;                       
  }

  switch(type)
  {
    case 0:                                  
      if(callFlag == 0)
      {
        indx = get_vndx(varname);
      }
      else
      {
        indx = get_llvarndx(varname);    
      }
      strcpy(s_holder, Gtbl[indx].Str);
      break;

    case 6:                                  
      indx = get_arrayndx(varname);
      Subscripts = &strArry[indx].sub[0];  
      nDims = strArry[indx].dim;           
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
      pi++;
      e_pos = pi;
      offset = get_offset2(Subscripts, nDims, len);
      strcpy(s_holder, strArry[indx].elem[offset]);
      /* get_paren Start */
      ch = p_string[pi];
      while((strchr("()", ch) == 0) && (pi < len))
      {
        pi++;
        ch = p_string[pi];
      }
      /* get_paren Stop */
      e_pos = pi;
      break;

    case 10:
      e_pos = pi;
      get_UDTstr();
      break;
  }
}
/*---------- end strvar_assgn ----------*/


void dim_strarry(char *varname, int len, int type)
{   int pi, ii, indx, param, subscript, ab_code=34, x=line_ndx;
    unsigned multiplier, size;
    char ch;

    pi = e_pos;

    /*---- string array ----*/
    if(sArryCnt > 0)
    {
        indx = 0;

        while((strcmp(varname, strArry[indx].name) != 0)
                                    && (indx < sArryCnt))
        {   indx++;
        }

        if(indx < sArryCnt)		
        {   a_bort(ab_code, x);
        }
    }
    /* --- dynamically create array structures --- */

    if(sArryCnt == 0)
    {
        size = 1;
        strArry = malloc(size * sizeof(struct string_array));
    }
    else
    {
        size = sArryCnt + 1;
        strArry = realloc(strArry, 
                 size * sizeof(struct string_array));
    }

    /**/
    strcpy(strArry[sArryCnt].name, varname);
    param = get_paramsCount(pi, len);	
    strArry[sArryCnt].dim = param;
    Sav_ObjName(varname, type, param);

    /**/
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
    multiplier = 1;

    for(indx=0; indx < param; indx++)
    {
        subscript = (int) get_avalue();
        strArry[sArryCnt].sub[indx] = subscript;
        multiplier = multiplier * subscript;
        pi = e_pos;
        /* get_digit Start */
        ch = p_string[pi];
        while((isdigit(ch) == 0) && (pi < len))
        {
          pi++;
          ch = p_string[pi];
        }
        /* get_digit Stop */
        e_pos = pi;
    }

    strArry[sArryCnt].elem = malloc(multiplier * sizeof(char *));

    /* initialize array */
    for(ii=0; ii < multiplier; ii++)
    {
        strArry[sArryCnt].elem[ii] = malloc(1 * sizeof(char));
    }

    sArryCnt++;					

}
/*------- end dim_strarry -------*/


void reuse_strarry(char *name, int type)
{   char varname[VAR_NAME];             
    int ndx, indx;


    varname[0] = '\0';
    indx = get_arrayndx(varname);
    ndx = 0;

    while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != '\0'))
    {   ndx++;
    }

    strcpy(ObjIndx[ndx], name);
    ObjType[ndx][0] = type;

    strcpy(varname, name);
    strcpy(strArry[indx].name, varname);

    redim_strarry(varname);

    fre_str--;

}
/*------- end reuse_strarry -------*/



void parse_sa(char *varname)
{   char temp[BUFSIZE], ch;
    int pi, len, indx, nDims, offset;
    int *Subscripts;
    unsigned size;


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
    e_pos = pi;

    Match('=');         

    strcpy(temp, str_express());

    size = strlen(temp);    
    size++;
    strArry[indx].elem[offset] = realloc(strArry[indx].elem[offset], 
                                              size * sizeof(char));

    strcpy(strArry[indx].elem[offset], temp);

}
/*---------- end parse_strarry ----------*/



void redim_strarry(char *varname)
{   int pi, len, ii, ndx, indx, param, subscript;
    unsigned multiplier;
    char ch;

    indx = get_arrayndx(varname);
    param = strArry[indx].dim;
    multiplier = 1;

    /* --- free existing array structure --- */
    for(ii=0; ii < param; ii++)
    {
        subscript = strArry[indx].sub[ii];
        multiplier = multiplier * subscript;
    }

    multiplier--;

    for(ii=multiplier; ii >= 0; ii--)
    {
        if(strArry[indx].elem[ii] != NULL)
        {
            free(strArry[indx].elem[ii]);
        }
    }

    /* --- dynamically recreate array structures --- */
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
    pi++;
    e_pos = pi;
    /**/
    param = get_paramsCount(pi, len);    
    strArry[indx].dim = param;
    set_ObjectParam(varname, param);
    /**/
    e_pos = pi;
    multiplier = 1;

    for(ii = 0; ii < 10; ii++)
    {                                    
        strArry[indx].sub[ii] = '\0';
    }

    for(ndx=0; ndx < param; ndx++)
    {
        subscript = (int) get_avalue();
        strArry[indx].sub[ndx] = subscript;
        multiplier = multiplier * subscript;
        pi = e_pos;
        /* get_digit Start */
        ch = p_string[pi];
        while((isdigit(ch) == 0) && (pi < len))
        {
          pi++;
          ch = p_string[pi];
        }
        /* get_digit Stop */
        e_pos = pi;
    }

    strArry[indx].elem = realloc(strArry[indx].elem, 
                       multiplier * sizeof(char *));

    /* initialize array */
    for(ii=0; ii < multiplier; ii++)
    {
        strArry[indx].elem[ii] = malloc(1 * sizeof(char));
    }

}
/*------- end redim_strarry -------*/



void erase_strArray(char *varname)
{   int indx, params, ii, multiplier, subscript;


    indx = get_arrayndx(varname);

    params = strArry[indx].dim;
    multiplier = 1;

    for(ii=0; ii < params; ii++)
    {
        subscript = strArry[indx].sub[ii];
        multiplier = multiplier * subscript;
    }

    multiplier--;

    for(ii=multiplier; ii > 0; ii--)
    {
        free(strArry[indx].elem[ii]);
    }
    strArry[indx].name[0] = '\0';

    for(ii = 0; ii < 10; ii++)
    {                                   
        strArry[indx].sub[ii] = '\0';
    }

    /**/
    indx = 0;

    while((indx < ObjNdxCnt) && (strcmp(varname, ObjIndx[indx]) != 0))
    {   indx++;
    }

    ObjIndx[indx][0] = '\0';
    ObjType[indx][0] = 0;
    ObjType[indx][1] = 0;

    fre_str++;                    

}
/*------- end erase_strArray -------*/

