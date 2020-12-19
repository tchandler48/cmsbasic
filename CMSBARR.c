USERID GCCCMS

/* bxbasic : Arrays.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011          */
/* Modified T.Chandler CMSBASIC - arrays.c   */

/* variable types:
    int    = no symbol,
    long   = %,
    float  = !,
    double = #,
    string = $
  ---------------
   array types:
    long   = %,
    float  = !,
    double = #,
    string = $
*/


void do_dim()
{   
  char varname[VAR_NAME],ch;
  int pi, len, type, ab_code=33, x=line_ndx;

  len = strlen(p_string);
  pi = e_pos;
  /* get_alpha Start */
  ch = p_string[pi];
  while((isalpha(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }

  /* get_alpha Stop */
  if(pi == len)						
  {
    a_bort(ab_code, x);
  }

  e_pos = pi;
  strcpy(varname, get_varname());			
  pi = e_pos;
  /* --- get array type --- */
  type = get_Arrytype(pi);				
  if(type < 6)
  {
    a_bort(ab_code, x);
  }
  else if(type == 6)					
  {
    if(fre_str > 0)
    {
      reuse_strarry(varname, type);
    }
    else
    {
      dim_strarry(varname, len, type);
    }
  }
  else if(type == 7)					
  {
    if(fre_int > 0)
    {
      reuse_intarry(varname, type);
    }
    else
    {
      dim_intarry(varname, len, type);
    }
  }
  else if(type == 8)					
  {
    if(fre_flt > 0)
    {
      reuse_fltarry(varname, type);
    }
    else
    {
      dim_fltarry(varname, len, type);
    }
  }
  else if(type == 9)					
  {
    if(fre_dbl > 0)
    {
      reuse_dblarry(varname, type);
    }
    else
    {
      dim_dblarry(varname, len, type);
    }
  }
  else
  {
    /* other array types */
  }
}
/*------- end do_dim -------*/


void dim_intarry(char *varname, int len, int type)
{   
  int pi, indx, param, subscript, ab_code, x=line_ndx;
  unsigned multiplier, size;
  char ch;

  pi = e_pos;
  /*--- integer array ---*/
  if(iArryCnt > 0)
  {
    indx = 0;
    while((strcmp(varname, intArry[indx].name) != 0) && (indx < iArryCnt))
    {
      indx++;
    }
    if(indx < iArryCnt)		
    {
      ab_code = 34;
      a_bort(ab_code, x);
    }
  }

  if(iArryCnt == 0)
  {
    size = 1;
    intArry = malloc(size * sizeof(struct integer_array));
  }
  else
  {
    size = iArryCnt + 1;
    intArry = realloc(intArry, size * sizeof(struct integer_array));
  }

  strcpy(intArry[iArryCnt].name, varname);
  param = get_paramsCount(pi, len);	
  intArry[iArryCnt].dim = param;
  Sav_ObjName(varname, type, param);
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
    intArry[iArryCnt].sub[indx] = subscript;
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

  intArry[iArryCnt].elem = malloc(multiplier * sizeof(long));
  iArryCnt++;					
}
/*------- end dim_intarry -------*/


void dim_fltarry(char *varname, int len, int type)
{   
  int pi, indx, param, subscript, ab_code, x=line_ndx;
  unsigned multiplier, size;
  char ch;

  pi = e_pos;
  /*--- float array ---*/
  if(fArryCnt > 0)
  {
    indx = 0;
    while((strcmp(varname, fltArry[indx].name) != 0) && (indx < fArryCnt))
    {
      indx++;
    }
    if(indx < fArryCnt)		
    {
      ab_code = 34;
      a_bort(ab_code, x);
    }
  }

  if(fArryCnt == 0)
  {
    size = 1;
    fltArry = malloc(size * sizeof(struct float_array));
  }
  else
  {
    size = fArryCnt + 1;
    fltArry = realloc(fltArry, size * sizeof(struct float_array));
  }

  strcpy(fltArry[fArryCnt].name, varname);
  param = get_paramsCount(pi, len);	
  fltArry[fArryCnt].dim = param;
  Sav_ObjName(varname, type, param);
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
    fltArry[fArryCnt].sub[indx] = subscript;
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

  fltArry[fArryCnt].elem = malloc(multiplier * sizeof(float));
  fArryCnt++;					
}
/*------- end dim_fltarry -------*/


void dim_dblarry(char *varname, int len, int type)
{   
  int pi, indx, param, subscript, ab_code, x=line_ndx;
  unsigned multiplier, size;
  char ch;

  pi = e_pos;
  /*--- float array ---*/
  if(dArryCnt > 0)
  {
    indx = 0;
    while((strcmp(varname, dblArry[indx].name) != 0) && (indx < dArryCnt))
    {
      indx++;
    }
    if(indx < dArryCnt)		
    {
      ab_code = 34;
      a_bort(ab_code, x);
    }
  }

  if(dArryCnt == 0)
  {
    size = 1;
    dblArry = malloc(size * sizeof(struct double_array));
  }
  else
  {
    size = dArryCnt + 1;
    dblArry = realloc(dblArry, size * sizeof(struct double_array));
  }

  strcpy(dblArry[dArryCnt].name, varname);
  param = get_paramsCount(pi, len);	
  dblArry[dArryCnt].dim = param;
  Sav_ObjName(varname, type, param);
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
    dblArry[dArryCnt].sub[indx] = subscript;
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

  dblArry[dArryCnt].elem = malloc(multiplier * sizeof(double));
  dArryCnt++;					
}
/*------- end dim_dblarry -------*/


void reuse_intarry(char *name, int type)
{  
  char varname[VAR_NAME];             
  int ndx, indx;

  varname[0] = '\0';
  indx = get_iarrayndx(varname);
  ndx = 0;
  while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != '\0'))
  {
    ndx++;
  }
  strcpy(ObjIndx[ndx], name);
  ObjType[ndx][0] = type;
  strcpy(varname, name);
  strcpy(intArry[indx].name, varname);
  redim_intarry(varname);
  fre_int--;
}
/*------- end reuse_intarry -------*/


void reuse_fltarry(char *name, int type)
{   
  char varname[VAR_NAME];             
  int ndx, indx;

  varname[0] = '\0';
  indx = get_farrayndx(varname);
  ndx = 0;
  while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != '\0'))
  {
    ndx++;
  }
  strcpy(ObjIndx[ndx], name);
  ObjType[ndx][0] = type;
  strcpy(varname, name);
  strcpy(fltArry[indx].name, varname);
  redim_fltarry(varname);
  fre_flt--;
}
/*------- end reuse_fltarry -------*/


void reuse_dblarry(char *name, int type)
{   
  char varname[VAR_NAME];             
  int ndx, indx;

  varname[0] = '\0';
  indx = get_darrayndx(varname);
  ndx = 0;
  while((ndx < ObjNdxCnt) && (strcmp(varname, ObjIndx[ndx]) != '\0'))
  {
    ndx++;
  }
  strcpy(ObjIndx[ndx], name);
  ObjType[ndx][0] = type;
  strcpy(varname, name);
  strcpy(dblArry[indx].name, varname);
  redim_dblarry(varname);
  fre_dbl--;
}
/*------- end reuse_dblarry -------*/


void parse_intarry(char *varname)
{   
  int pi, len, indx, nDims, offset;
  char ch;
  int *Subscripts;

  indx = get_iarrayndx(varname); 
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
  Subscripts = &intArry[indx].sub[0];     
  nDims = intArry[indx].dim;             
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  Match('=');
  intArry[indx].elem[offset] = (long) rdp_main();
}
/*---------- end parse_intarry ----------*/


void parse_fltarry(char *varname)
{   
  int pi, len, indx, nDims, offset;
  char ch;
  int *Subscripts;

  indx = get_farrayndx(varname);
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
  Subscripts = &fltArry[indx].sub[0];     
  nDims = fltArry[indx].dim;              
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  Match('=');
  fltArry[indx].elem[offset] = (float) rdp_main();
}
/*---------- end parse_fltarry ----------*/


void parse_dblarry(char *varname)
{
  int pi, len, indx, nDims, offset;
  char ch;
  int *Subscripts;

  indx = get_darrayndx(varname);
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
  Subscripts = &dblArry[indx].sub[0];     
  nDims = dblArry[indx].dim;              
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  /* --- now get assignment value --- */
  Match('=');
  dblArry[indx].elem[offset] = (double) rdp_main();
}
/*---------- end parse_dblarry ----------*/


void do_redim()
{
  char varname[VAR_NAME],ch;
  int pi, len, ndx=0, type, ab_code=11, x=line_ndx;

  len = strlen(p_string);
  pi = e_pos;
  /* get_alpha Start */
  ch = p_string[pi];
  while((isalpha(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_alpha Stop */
  if(pi == len)                     
  {
    a_bort(ab_code, x);
  }
  e_pos = pi;
  strcpy(varname, get_varname());		
  pi = e_pos;
  type = get_Arrytype(pi);				
  if(type < 6)
  {
    ab_code = 13;
    a_bort(ab_code, x);
  }
  e_pos = pi;
  switch(type)
  {
    case 6:						
      redim_strarry(varname);
      break;

    case 7:						
      redim_intarry(varname);
      break;

    case 8:						
      redim_fltarry(varname);
      break;

    case 9:						
      redim_dblarry(varname);
      break;
  }
}
/*-------- end do_redim ---------*/


void redim_intarry(char *varname)
{   
  int pi, len, ii, ndx, indx, param, subscript;
  unsigned multiplier;
  char ch;

  indx = get_iarrayndx(varname);
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
  param = get_paramsCount(pi, len);    
  intArry[indx].dim = param;
  set_ObjectParam(varname, param);
  e_pos = pi;
  multiplier = 1;
  for(ii = 0; ii < 10; ii++)
  {                                    
    intArry[indx].sub[ii] = '\0';
  }
  for(ndx=0; ndx < param; ndx++)
  {
    subscript = (int) get_avalue();
    intArry[indx].sub[ndx] = subscript;
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
  intArry[indx].elem = realloc(intArry[indx].elem, 
                      multiplier * sizeof(long));
}
/*------- end redim_intarry -------*/


void redim_fltarry(char *varname)
{   
  int pi, len, ii, ndx, indx, param, subscript;
  unsigned multiplier;
  char ch;

  indx = get_farrayndx(varname);
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
  param = get_paramsCount(pi, len);    
  fltArry[indx].dim = param;
  set_ObjectParam(varname, param);
  e_pos = pi;
  multiplier = 1;
  for(ii = 0; ii < 10; ii++)
  {                                    
    fltArry[indx].sub[ii] = '\0';
  }
  for(ndx=0; ndx < param; ndx++)
  {
    subscript = (int) get_avalue();
    fltArry[indx].sub[ndx] = subscript;
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
  fltArry[indx].elem = realloc(fltArry[indx].elem, 
                       multiplier * sizeof(float));
}
/*------- end redim_fltarry -------*/


void redim_dblarry(char *varname)
{   
  int pi, len, ii, ndx, indx, param, subscript;
  unsigned multiplier;
  char ch;

  indx = get_darrayndx(varname);
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
  param = get_paramsCount(pi, len);   
  dblArry[indx].dim = param;
  set_ObjectParam(varname, param);
  e_pos = pi;
  multiplier = 1;
  for(ii = 0; ii < 10; ii++)
  {                                    
    dblArry[indx].sub[ii] = '\0';
  }
  for(ndx=0; ndx < param; ndx++)
  {
    subscript = (int) get_avalue();
    dblArry[indx].sub[ndx] = subscript;
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
  dblArry[indx].elem = realloc(dblArry[indx].elem, 
                   multiplier * sizeof(double));
}
/*------- end redim_dblarry -------*/


void erase_array()
{   
  char varname[VAR_NAME],ch;
  int pi, len, type;
  int ab_code=32, x=line_ndx;

  len = strlen(p_string);
  pi = 0;
  /* get_alpha Start */
  ch = p_string[pi];
  while((isalpha(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_alpha Stop */
  if(pi == len)					
  {
    a_bort(ab_code, x);
  }
  e_pos = pi;
  strcpy(varname, get_varname());			
  pi = e_pos;
  type = get_Arrytype(pi);
  if(type < 6)
  {
    ab_code = 36;
    a_bort(ab_code, x);
  }
  else if(type == 6)					
  {
    erase_strArray(varname);
  }
  else if(type == 7)					
  {
    erase_intArray(varname);
  }
  else if(type == 8)                 
  {
    erase_fltArray(varname);
  }
  else if(type >= 9)                
  {
    erase_dblArray(varname);
  }
}
/*------- end erase_array -------*/


void erase_dblArray(char *varname)
{   
  int indx, ii;

  indx = get_darrayndx(varname);
  free(dblArry[indx].elem);
  dblArry[indx].name[0] = '\0';
  for(ii = 0; ii < 10; ii++)
  {                                    
    dblArry[indx].sub[ii] = '\0';
  }
  indx = 0;
  while((indx < ObjNdxCnt) && (strcmp(varname, ObjIndx[indx]) != 0))
  {
    indx++;
  }
  ObjIndx[indx][0] = '\0';
  ObjType[indx][0] = 0;
  ObjType[indx][1] = 0;
  fre_dbl++;                    
}
/*------- end erase_dblArray -------*/


void erase_fltArray(char *varname)
{   
  int indx, ii;

  indx = get_farrayndx(varname);
  free(fltArry[indx].elem);
  fltArry[indx].name[0] = '\0';
  for(ii = 0; ii < 10; ii++)
  {                                    
    fltArry[indx].sub[ii] = '\0';
  }
  indx = 0;
  while((indx < ObjNdxCnt) && (strcmp(varname, ObjIndx[indx]) != 0))
  {
    indx++;
  }
  ObjIndx[indx][0] = '\0';
  ObjType[indx][0] = 0;
  ObjType[indx][1] = 0;
  fre_flt++;                      
}
/*------- end erase_fltArray -------*/


void erase_intArray(char *varname)
{   
  int indx, ii;

  indx = get_iarrayndx(varname);
  free(intArry[indx].elem);
  intArry[indx].name[0] = '\0';
  for(ii = 0; ii < 10; ii++)
  {                                    
    intArry[indx].sub[ii] = '\0';
  }
  indx = 0;
  while((indx < ObjNdxCnt) && (strcmp(varname, ObjIndx[indx]) != 0))
  {
    indx++;
  }
  ObjIndx[indx][0] = '\0';
  ObjType[indx][0] = 0;
  ObjType[indx][1] = 0;
  fre_int++;                      
}
/*------- end erase_intArray -------*/


double let_intarray(char *varname)
{   
  int pi, len, indx, nDims, offset;
  int *Subscripts;
  char ch;
  double value;

  e_pos = s_pos;
  indx = get_iarrayndx(varname);
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
  Subscripts = &intArry[indx].sub[0];     
  nDims = intArry[indx].dim;              
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  value = (double) intArry[indx].elem[offset];
  return value;
}
/*-------- end let_intarray --------*/


double let_fltarray(char *varname)
{
  int pi, indx, len, nDims, offset;
  int *Subscripts;
  char ch;
  double value;

  e_pos = s_pos;
  indx = get_farrayndx(varname);
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
  Subscripts = &fltArry[indx].sub[0];    
  nDims = fltArry[indx].dim;             
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  value = (double) fltArry[indx].elem[offset];
  return value;
}
/*-------- end let_fltarray --------*/


double let_dblarray(char *varname)
{   
  int pi, indx, len, nDims, offset;
  int *Subscripts;
  char ch;
  double value;

  e_pos = s_pos;
  indx = get_darrayndx(varname);
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
  Subscripts = &dblArry[indx].sub[0];     
  nDims = dblArry[indx].dim;              
  offset = get_offset2(Subscripts, nDims, len);
  pi = e_pos;
  pi++;
  pi = iswhiter(pi);
  e_pos = pi;
  value = dblArry[indx].elem[offset];
  return value;
}
/*-------- end let_dblarray --------*/

