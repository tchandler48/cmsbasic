USERID GCCCMS


/* bxbasic : Utility.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011 */


char *global_var(char *name)
{   
  static char varname[VAR_NAME];
  int ii, limit;

  strcpy(varname, name);		
  if(callFlag > 0)
  {
    ii = 0;
    limit = (ObjNdxCnt-1);
    while((ii <= limit) && (strcmp(varname, ObjIndx[ii]) != 0))
    {
      ii++;
    }
    if(ii == ObjNdxCnt)
    {
      strcpy(varname, local_var(varname));
    }
  }
  return varname;
}
/*------- end global_var -------*/


char *local_var(char *name)
{
  static char varname[VAR_NAME];
  int ii, idx;

  strcpy(varname, name);		
  if(callFlag > 0)
  {
    idx = lcl_cnt - 1;
    ii = thissub_vars[submax_cnt];
    while((ii > 0) && (strcmp(varname, Ltbl[idx].Nam) != 0))
    {
      ii--;
    }
  }
  return varname;
}
/*------- end local_var -------*/


void InitObj()			
{
  int ndx;
  unsigned size;

  if(ObjNdxCnt == 0)
  {
    ndx = ObjNdxCnt;
    ObjNdxCnt++;
    size = ObjNdxCnt;
    ObjIndx = malloc(size * sizeof(char *));
    ObjSubVar = malloc(size * sizeof(char *));
    ObjType = malloc(size * sizeof(int *));
    size = VAR_NAME;
    ObjIndx[ndx] = malloc(size * sizeof(char));
    ObjSubVar[ndx] = malloc(size * sizeof(char));
    size = 2;
    ObjType[ndx] = malloc(size * sizeof(int));
  }
  else
  {
    ndx = ObjNdxCnt;
    ObjNdxCnt++;
    size = ObjNdxCnt;
    ObjIndx = realloc(ObjIndx, size * sizeof(char *));
    ObjSubVar = realloc(ObjSubVar, size * sizeof(char *));
    ObjType = realloc(ObjType, size * sizeof(int *));
    size = VAR_NAME;
    ObjIndx[ndx] = malloc(size * sizeof(char));
    ObjSubVar[ndx] = malloc(size * sizeof(char));
    size = 2;
    ObjType[ndx] = malloc(size * sizeof(int));
  }
}
/*---------- end InitObj ----------*/


void Sav_ObjName(char *varname, int type, int parm)
{   
  int ndx=0, ibool=0;

  InitObj();
  ndx = ObjNdxCnt - 1;
  strcpy(ObjIndx[ndx], varname);
  ObjType[ndx][0] = type;
  ObjType[ndx][1] = parm;
  if((type == 11) || (callFlag == 0))
  {
    ObjSubVar[ndx][0] = '\0';
  }
  else
  {
    strcpy(ObjSubVar[ndx], SubName);
  }
}
/*---------- end Sav_ObjName ----------*/


int get_ObjectType(char *varname)	
{
  int ndx=0, type=-1;

  while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != 0))
  {
    ndx++;
  }
  if(ndx < ObjNdxCnt)
  {
    type = ObjType[ndx][0];
  }
  return type;
}
/*---------- end get_ObjectType ----------*/


void set_ObjectParam(char *varname, int param)	
{   
  int ndx=0;

  while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != 0))
  {
    ndx++;
  }
  ObjType[ndx][1] = param;
}
/*---------- end set_ObjectParam ----------*/


int get_arrayndx(char *varname)				
{   
  int indx=0, ab_code=35, x=line_ndx;

  while((strcmp(varname, strArry[indx].name) != 0) && (indx < sArryCnt))
  {
    indx++;
  }
  if(indx == sArryCnt)             
  {
    printf("\n\nArray:\"%s\"", varname);
    a_bort(ab_code, x);
  }
  return indx;
}
/*---------- end get_arrayndx ----------*/


int get_iarrayndx(char *varname)				
{   
  int indx=0, ab_code=35, x=line_ndx;

  while((strcmp(varname, intArry[indx].name) != 0) && (indx < iArryCnt))
  {
    indx++;
  }
  if(indx == iArryCnt)              
  {
    printf("\n\nArray:\"%s\"", varname);
    a_bort(ab_code, x);
  }
  return indx;
}
/*---------- end get_iarrayndx ----------*/


int get_farrayndx(char *varname)				
{   
  int indx=0, ab_code=35, x=line_ndx;

  while((strcmp(varname, fltArry[indx].name) != 0) && (indx < fArryCnt))
  {
    indx++;
  }
  if(indx == fArryCnt)              
  {
    printf("\n\nArray:\"%s\"", varname);
    a_bort(ab_code, x);
  }
  return indx;
}
/*---------- end get_farrayndx ----------*/


int get_darrayndx(char *varname)				
{   
  int indx=0, ab_code=35, x=line_ndx;

  while((strcmp(varname, dblArry[indx].name) != 0) && (indx < dArryCnt))
  {
    indx++;
  }
  if(indx == dArryCnt)              
  {
    printf("\n\nArray:\"%s\"", varname);
    a_bort(ab_code, x);
  }
  return indx;
}
/*---------- end get_darrayndx ----------*/


int get_offset2(int *subScripts, int nDims, int len)
{   
  int pi, i, ii, this_DIM, next_Param, offset;  
  char ch;    

  next_Param = (int) get_avalue();
  next_Param--;
  offset = next_Param;
  ii=1;
  for(i=1; i < nDims; i++)
  {
    this_DIM = subScripts[i];
    pi = e_pos;
    /* get_alnum Start */
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
      pi++;
      ch = p_string[pi];
    }
    /* get_alnum Stop */
    e_pos = pi;
    next_Param = (int) get_avalue();
    next_Param--;
    offset = (offset * this_DIM) + next_Param;
    ii++;
  }
  return offset;
}
/*------ end get_offset2 ------*/


int get_paramsCount(int pi, int len)
{   
  char ch;
  int xcnt=0;

  ch = p_string[pi];
  while((ch != ')') && (pi < len))		
  {
    /* get_alnum Start */
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
      pi++;
      ch = p_string[pi];
    }
    /* get_alnum Stop */
    ch = p_string[pi];
    if(isalnum(ch))
    {
      xcnt++;
      /* get_NextOp Start */
      pi = while_isalnum(pi);
      pi = iswhiter(pi);
      /* get NextOp Stop */
      ch = p_string[pi];
    }
  }
  return xcnt;
}
/*---------- end get_paramsCount ----------*/


int get_objtype(int pi)
{
  char ch, chx;
  int type=-1;

  ch = p_string[pi];
  chx = p_string[(pi+1)];
  if(ch == '$')
  {
    type = 0;
    if(chx == '(')					
    {
      type = 6;					
    }
  }
  else
  {
    type = get_Nvtype(pi);
    if(chx == '(')                  
    {
      switch(ch)
      {
        case '%':
          type = 7;			
          break;

        case '!':
          type = 8;			
          break;
 
        case '#':
          type = 9;			
          break;
      }
    }
  }
  return type;
}
/*------- end get_objtype --------*/


int get_Arrytype(int pi)
{   
  char ch, chx;
  int type=0;

  pi = iswhite(pi);
  ch = p_string[pi];
  chx = p_string[(pi+1)];
  if(ch == '$')
  {
    if(chx == '(')					
    {
      type = 6;					
    }
  }
  else if(strchr("%!#", ch))
  {
    if(chx == '(')				
    {
      switch(ch)
      {
        case '%':
          type = 7;			
          break;
   
        case '!':
          type = 8;			
          break;

        case '#':
          type = 9;			
          break;
      }
    }
  }
  return type;
}
/*------- end get_Arrytype --------*/


int get_vtype(int pi)
{   
  char ch;
  int type=0, f_flag=0;

  pi = while_isalnum(pi);
  ch = p_string[pi];
  if(ch == '$')
  {
    type = 3;			
  }
  else if(strchr(" =<>%!#;", ch))
  {
    type = 1;			
  }
  else if(ch == '\n')     
  {
    type = 1;
  }
  else if(ch == '(')                  
  {
    f_flag = if_eof();             
    f_flag--;
    if(f_flag == s_pos)             
    {
      type = 5;
      e_pos = pi;
    }
  }
  return type;
}
/*------- end get_vtype --------*/


int get_Nvtype(int pi)
{   
  char ch;
  int type=0;

  pi = while_isalnum(pi);
  ch = p_string[pi];
  if(strchr(":;, <>)=+*-/\n", ch))
  {
    type = 1;		
  }
  else if(ch == '%')
  {
    type = 2;		
  }
  else if(ch == '!')
  {
    type = 3;		
  }
  else if(ch == '#')
  {
    type = 4;		
  }
  else if(ch == '~')
  {
    type = 5;		
  }
  return type;
}
/*------- end get_Nvtype --------*/


int isthis_anarray(int pi, int stlen)
{   
  char ch;

  /* get_NextOp Start */
  pi = while_isalnum(pi);
  pi = iswhiter(pi);
  /* get_NextOp Stop */
  ch = p_string[pi];
  if(strchr("$%!#~", ch) != 0)
  {
    pi++;
    pi = iswhiter(pi);
    ch = p_string[pi];
  }
  if(ch != '(')
  {
    pi = 0;
  }
  return pi;
}
/*---------- end isthis_anarray ----------*/


int iswhite(int pi)
{   
  char ch;

  ch = p_string[pi];                  
  while(isspace(ch) != 0)                            
  {
    pi++;
    ch = p_string[pi];
  }
  return pi;
}
/*-------- end iswhite ----------*/


int iswhiter(int pi)
{   
  char ch;

  ch = p_string[pi];                   
  while(ch == ' ')                            
  {
    pi++;
    ch = p_string[pi];
  }
  return pi;
}
/*-------- end iswhiter ---------*/


void clr_arrays()
{   
  int ii;    

  for(ii=0; ii < nrows; ii++)
  {
    free(label_nam[ii]);
    free(array1[ii]);
  }
  free(label_nam);
  free(byte_array);
  free(array1);
}
/*-------- end clr_arrays ----------*/


int find_strng(char *tmp)
{   
  char ch, cx;
  char temp[TOKEN_LEN], xxstring[TOKEN_LEN];
  int pi, i, mark, len, len2;

  strcpy(xxstring, tmp);
  len = strlen(p_string);        
  len2 = strlen(xxstring);
  pi = s_pos;                         
  ch = p_string[pi];
  cx = xxstring[0];             
  while(pi < len)
  {
    while((ch != cx) && (pi < len))        
    {
      if(ch == '\"')            
      {
        pi++;                    
        ch = p_string[pi];
        while(ch != '\"')
        {
          pi++;
          ch = p_string[pi];
         }
       }
       pi++;
       ch = p_string[pi];
     }
     if((pi == len) || (pi > len))
     {
       mark = 0;       
       return mark;
     }
     mark = pi;         
     for(i=0; i < len2; i++)         
     {
       temp[i] = ch;
       pi++;
       ch = p_string[pi];
     }
     temp[i] = '\0';
     if(strcmp(temp, xxstring) != 0)      
     {
       pi = (mark+1);              
       ch = p_string[pi];
     }
     else
     {
       mark++;
       pi = len;
     }
  }
  return mark;
}
/*-------- end find_strng ---------*/


int while_dd(int pi)            
{
  char ch;

  ch = p_string[pi];
  while((isalnum(ch) != 0) || (strchr("._", ch)))
  {
    pi++;
    ch = p_string[pi];
  }
  return pi;
}
/*------ end while_isalnum_dd ------*/


int while_isalnum(int pi)
{
  char ch;

  ch = p_string[pi];
  while(isalnum(ch))
  {
    pi++;
    ch = p_string[pi];
  }
  return pi;
}
/*-------- end while_isalnum ---------*/


int get_quote(int pi, int len)
{   
  char ch;

  pi++;
  ch = p_string[pi];
  while((ch != '\"') && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  if(ch == '\"')
  {
    pi++;
  }
  return pi;
}
/*-------- end get_quote ---------*/


void get_pnam()
{   
  char ch;
  int pi, indx, len, si;

  len = strlen(p_string);
  pi = e_pos;
  ch = p_string[pi];
  if(ch == '\"')
  {
    si = 0;
    pi++;
    ch = p_string[pi];
    while((ch != '\"') && (pi < len))
    {
      s_holder[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
    }
    s_holder[si] = '\0';
    e_pos = pi;
  }
  else
  {
    strcpy(s_holder, get_varname());
    indx = get_strndx(s_holder);       
    strcpy(s_holder, Gtbl[indx].Str);
  }
  /* return param/varname in s_holder */
}
/*---------- end get_param_name ----------*/
