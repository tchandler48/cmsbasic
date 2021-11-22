USERID GCCCMS

/* bxbasic : Variable.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011 */
/* CMSBASIC port, by tchandler48@gmail.com */


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

void do_dim_var()
{   
  int test, pi, len;           

  pi = 0;
  e_pos = pi;
  len = strlen(p_string);
  test = isthis_anarray(pi, len);
  if(test == 0)                 
  {
    dim_var();                
  }
  else
  {                             
    do_dim();
  }
}
/*---------- end do_dim_var -----------*/


void dim_var()
{   
  char ch;
  int pi, len;

  len = strlen(p_string);
  pi = e_pos;
  ch = p_string[pi];
  while((ch != '\n') && (pi < len))
  {
    if(isalpha(ch))
    {
      parse_dim();
      pi = e_pos;
    }
    else
    {
      /* get_alpha Start */
      ch = p_string[pi];
      while((isalpha(ch) == 0) && (pi < len))
      {
        pi++;
        ch = p_string[pi];
      }
      /* get_alpha Stop */
      ch = p_string[pi];
      e_pos = pi;
    }
    ch = p_string[pi];
  }
}
/*---------- end dim_var -----------*/


void parse_dim()
{   
  char varname[VAR_NAME], ch;
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
  type = get_objtype(pi);
  e_pos = pi;
  switch(type)
  {
    case 0:						
      dim_gstr(varname);
      break;
 
    case 1:                     
      dim_gint(varname);
      break;

    case 2:						
      dim_glong(varname);
      break;

    case 3:						
      dim_gsingle(varname);
      break;

    case 4:						
      dim_gdouble(varname);
      break;
  }
}
/*-------- end parse_dim ---------*/


void dim_gdouble(char *varname)
{   
  int pi, ndx;

  pi = e_pos;
  ndx = get_var_index(varname);
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Gtbl[ndx].ActSub = ActvSubs;   
  Match('=');					
  Gtbl[ndx].Dbl = (double) rdp_main();
}
/*-------- end dim_gdouble --------*/


void dim_gsingle(char *varname)
{   
  int pi, ndx;

  pi = e_pos;
  ndx = get_var_index(varname);
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Gtbl[ndx].ActSub = ActvSubs;   
  Match('=');					
  Gtbl[ndx].Flt = (float) rdp_main();
}
/*-------- end dim_gsingle --------*/


void dim_glong(char *varname)
{   
  int pi, ndx=0;

  pi = e_pos;
  ndx = get_var_index(varname);
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Gtbl[ndx].ActSub = ActvSubs;   
  Match('=');					
  Gtbl[ndx].Lng = (long) rdp_main();
}
/*-------- end dim_glong --------*/


void dim_gint(char *varname)
{   
  int pi, ndx;               

  pi = e_pos;
  ndx = get_var_index(varname);
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Gtbl[ndx].ActSub = ActvSubs;   
  Match('=');					
  Gtbl[ndx].Int = (int) rdp_main();
}
/*-------- end dim_gint --------*/


void bld_global_table()
{   
  unsigned size;

  if(glb_vct == 0)
  {                            
    glb_vct++;
    size = glb_vct;
    Gtbl = (struct Global_Table *) 
              malloc(size * sizeof(struct Global_Table));
  }
  else
  {                            
    glb_vct++;
    size = glb_vct;
    Gtbl = (struct Global_Table *) realloc(Gtbl, \
                    size * sizeof(struct Global_Table));
  }
}
/*---------- end bld_global_table -----------*/


int get_gvarndx(char *varname)
{   
  int ndx;      

  if(glb_vct > 0)
  {
    ndx = 0;
    while((ndx < glb_vct) && (strcmp(varname, Gtbl[ndx].Nam) != 0))
    {
      ndx++;
    }
    if(ndx == glb_vct)
    {
      bld_global_table();             
      ndx = glb_vct - 1;
      strcpy(Gtbl[ndx].Nam, varname); 
    }
  }
  else
  {
    bld_global_table();
    ndx = glb_vct - 1;
    strcpy(Gtbl[ndx].Nam, varname);     
  }
  return ndx;
}
/*-------- end get_gvarndx --------*/


int get_lvarndx(char *varname)
{   
  int ndx;       

  bld_global_table();
  ndx = glb_vct - 1;
  strcpy(Gtbl[ndx].Nam, varname);     
  return ndx;
}
/*-------- end get_lvarndx --------*/


int get_var_index(char *varname)
{  
  int ndx;                        
                                     
  if(ActvSubs > 0)
  {
    ndx = get_lvarndx(varname);
    rStk[sub_ndx].Vrcnt++;       
  }
  else
  {
    ndx = get_gvarndx(varname);
  }
  return ndx;
}
/*-------- end get_var_index --------*/


void parse_let()
{   
  char varname[VAR_NAME], ch;
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
  type = get_objtype(pi);
  e_pos = pi;
  if((UdtCnt > 0) && (type < 6))     
  {
    type = isThisUdt(varname, type);
  }
  switch(type)
  {
    case 0:                        
      parse_st(varname);
      break;
  
    case 1:                        
      let_int(varname);
      break;

    case 2:                        
      let_long(varname);
      break;

    case 3:                       
      let_single(varname);
      break;

    case 4:                        
      let_double(varname);
      break;
  
    case 5:                        
      break;
 
    case 6:                       
      parse_sa(varname);
      break;

    case 7:                        
      parse_intarry(varname);
      break;
 
    case 8:                        
      parse_fltarry(varname);
      break;

    case 9:                        
      parse_dblarry(varname);
      break;

    case 10:                       
      parse_UDTstr();
      break;

    case 11:                       
    case 12:                       
    case 13:                       
    case 14:                      
      assn_UDTval();
      break;
  }
}
/*-------- end parse_let ---------*/


void let_double(char *varname)
{   
  int pi, ndx;

  pi = e_pos;
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Match('=');					
  Gtbl[ndx].Dbl = (double) rdp_main();
}
/*-------- end let_double --------*/


void let_single(char *varname)
{   
  int pi, ndx;

  pi = e_pos;
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Match('=');					
  Gtbl[ndx].Flt = (float) rdp_main();
}
/*-------- end let_single --------*/


void let_long(char *varname)
{   
  int pi, ndx;
  long lvalue;
  double dvalue;

  pi = e_pos;
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Match('=');					
  Gtbl[ndx].Lng = (long) rdp_main();
}
/*-------- end let_long --------*/


void let_int(char *varname)
{   
  int pi, ndx;

  pi = e_pos;
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);         
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  if(IsEqu(pi) == 0)                 
  {
    pi++;
    pi = iswhite(pi);
    e_pos = pi;
  }
  Match('=');					
  Gtbl[ndx].Int = (int) rdp_main();
}
/*-------- end let_int --------*/


int get_vndx(char *varname)
{   
  int ndx, ab_code=13, x=line_ndx;

  if(glb_vct > 0)
  {
    ndx = 0;
    while((ndx < glb_vct) && (strcmp(varname, Gtbl[ndx].Nam) != 0))
    {
      ndx++;
    }
    if(ndx >= glb_vct)
    {
      a_bort(ab_code, x);
    }
  }
  else
  {
    a_bort(ab_code, x);
  }
  return ndx;
}
/*--------- end get_varndx ----------*/


int get_llvarndx(char *varname)
{  
  int ndx, sndx, sub, ab_code=13, x=line_ndx;
                                              
  if(glb_vct > 0)
  {
    sndx = ActvSubs;
    ndx = (glb_vct - 1);
    sub = Gtbl[ndx].ActSub;               
    while((ndx > 0) && (sub == sndx) && \
              (strcmp(varname, Gtbl[ndx].Nam) != 0))
    {
      ndx--;                             
      sub = Gtbl[ndx].ActSub;           
    }
    if((sub != sndx) || (strcmp(varname, Gtbl[ndx].Nam) != 0))
    {                                      
      ndx = 0;
      sub = Gtbl[ndx].ActSub;           
      while((sub == 0) && (strcmp(varname, Gtbl[ndx].Nam) != 0))
      {
        ndx++;                        
        sub = Gtbl[ndx].ActSub;        
      }
      if((sub != 0) || (strcmp(varname, Gtbl[ndx].Nam) != 0))
      {                                
        a_bort(ab_code, x);
      }
    }
  }
  else
  {
    a_bort(ab_code, x);
  }
  return ndx;
}
/*--------- end get_llvarndx ----------*/


char *get_varname()
{   
  char ch;
  static char varname[VAR_NAME];
  int pi, si=0;

  pi = e_pos;
  ch = p_string[pi];
  while((isalnum(ch) != 0) || (strchr("._", ch)))
  {
    varname[si] = ch;
    si++;
    pi++;
    ch = p_string[pi];
  }
  varname[si] = '\0';
  e_pos = pi;
  return varname;
}
/*---------- end get_varname ----------*/


double get_varvalue()
{   
  char varname[VAR_NAME];
  int pi, pii, ndx=0, type;
  int ab_code=13, x=line_ndx;
  double value;

  strcpy(varname, s_holder);
  pi = e_pos;
  var_type = p_string[pi];
  type = get_objtype(pi);	                     
  if((UdtCnt > 0) && (type < 6))          
  {
    type = isThisUdt(varname, type);
  }
  s_pos = e_pos;
  switch(type)
  {
    case 0:
    case 2:
    case 3:
    case 4:
      _GetChar();
      break;

    case 12:
    case 13:
    case 14:
      _GetChar();
      break;
  }
  if(type < 6)
  {
    if(callFlag == 0)
    {
      ndx = get_vndx(varname);
    }
    else
    {
      ndx = get_llvarndx(varname);             
    }
  }
  switch(type)
  {
    case 0:
      value = atof(Gtbl[ndx].Str);
      break;

    case 1:
      value = (double) Gtbl[ndx].Int;
      break;

    case 2:
      value = (double) Gtbl[ndx].Lng;
      break;

    case 3:
      value = (double) Gtbl[ndx].Flt;
      break;

    case 4:
      value = (double) Gtbl[ndx].Dbl;
      break;

    case 7:
      value = let_intarray(varname);
      break;

    case 8:
      value = let_fltarray(varname);
      break;

    case 9:
      value = let_dblarray(varname);
      break;

    case 11:                           
      value = get_Uval(varname);
      break;
 
    case 12:                            
    case 13:                           
    case 14:                            
      value = get_UDTlfd(varname);
      break;
  }
  return value;
}
/*--------- end get_varvalue ----------*/


double get_avalue()
{  
  char ch, varname[VAR_NAME];
  int pi, si=0;
  double value=0;

  pi = e_pos;
  ch = p_string[pi];
  if(isalpha(ch))                   
  {
    e_pos = pi;
    s_pos = pi;
    strcpy(s_holder, get_varname());
    value = get_varvalue();
    pi = e_pos;
  }
  else if((isdigit(ch)) || (IsAddop(ch))) 
  {
    if(IsAddop(ch))
    {
      varname[si] = ch;
      si++;
      pi++;
      ch = p_string[pi];
    }
    while(isdigit(ch) != 0)
    {
      varname[si] = ch;
      pi++;
      si++;
      ch = p_string[pi];
    }
    varname[si] = '\0';
    value = atof(varname);      
  }
  pi = iswhite(pi);
  e_pos = pi;
  return value;
}
/*-------- end get_avalue --------*/


