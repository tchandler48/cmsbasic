USERID CMSUSER
/* cmsbasic : Fileio.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011           */
/* Modified T. Chandler - CMSBASIC fileio.c   */


void reset_handle(int ndx)
{
  FILE *handle;

  handle = fp[ndx].fptr;           
  fclose(handle);
  zero_handle(ndx);
}
/*------ end reset_handle -------*/


void zero_handle(int ndx)
{
  fp[ndx].path[0] = '\0';              
  fp[ndx].mode = '\0';
  fp[ndx].fptr = '\0';
}
/*------ end zero_handle -------*/


void parse_open()
{   
  int pi, len, ab_code=20, x=line_ndx;
  char ch;

  len = strlen(p_string);
  pi = e_pos;
  /* get_upper Start */
  ch = p_string[pi];
  while((isupper(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_upper Stop */
  err_hndlr(ab_code, x, 1, pi, len);     
  e_pos = pi;
  get_iomode(len);
}
/*------ end parse_open -------*/


void get_iomode(int len)
{   
  char ch, io_mode;
  int pi, ndx, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=20;
  double file_no;

  pi = e_pos;
  ch = p_string[pi];
  io_mode = ch;

  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }

  /* get_digit Stop */
  err_hndlr(ab_code, x, 2, pi, len);    
  e_pos = pi;
  file_no = get_avalue();
  ndx = (int) file_no;
  ndx--;
  err_hndlr(ab_code, x, 3, ndx, maxfiles); 
  err_hndlr(ab_code, x, 4, ndx, 0);        
  fopen_short(io_mode, ndx, len);
}
/*------ end get_iomode -------*/


void fopen_short(char io_mode, int ndx, int len)
{
  char ch, quote='\"', io_path[PATH], varname[VAR_NAME];
  int pi, indx, x=line_ndx, ab_code=20;
  FILE *handle;

  pi = e_pos;
  ch = p_string[pi];
  while((ch != quote) && (isalpha(ch) == 0) && (pi < len))
  {
    pi++;                      
    ch = p_string[pi];              
  }
  err_hndlr(ab_code, x, 5, pi, len);        
  e_pos = pi;
  if(ch == quote)			    
  {
    strng_assgn();
    strcpy(io_path, s_holder);
  }
  else				 
  {
    strcpy(varname, get_varname());
    indx = get_strndx(varname);
    strcpy(io_path, Gtbl[indx].Str);
  }
  fp[ndx].mode = io_mode;                    
  strcpy(fp[ndx].path, io_path);
  switch(io_mode)
  {
    case 'I':			       
      handle = fopen(io_path, "r");
      err_hndlr(ab_code, x, 6, pi, len); 
      break;

    case 'O':			      
      handle = fopen(io_path, "w");
      err_hndlr(ab_code, x, 6, pi, len);
      break;

    case 'A':			      
      handle = fopen(io_path, "a");
      err_hndlr(ab_code, x, 6, pi, len);
      break;
 
    case 'R':			      
      handle = fopen(io_path, "r+");
      if(handle == NULL)
      {
        handle = fopen(io_path, "w+");
      }
      random_fio(ndx, len);
      err_hndlr(ab_code, x, 6, pi, len);
      break;

    default:			  
      err_hndlr(ab_code, x, 1, 0, 0);
      break;
  }
  if(handle == NULL)
  {
    a_bort(ab_code,x);                    
  }
  else
  {
    fp[ndx].fptr = handle;
  }
}
/*------ end fopen_short -------*/


void do_fclose()
{   
  char ch;
  int ii, pi, ndx, len, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=22;
  double file_no;

  len = strlen(p_string);
  pi = e_pos;

  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }

  /* get_digit Stop */
  if(pi == len)			      
  {
    for(ii=0; ii<IOARRAY; ii++)
    {
      if(fp[ii].path[0] != '\0')	 
      {
        reset_handle(ii);
      }
    }
  }
  else
  {
    ch = p_string[pi];
    while(pi < len)
    {
      if(isdigit(ch) == 0)
      {
        /* get_digit Start */
        ch = p_string[pi];
        while((isdigit(ch) == 0) && (pi < len))
        {
          pi++;
          ch = p_string[pi];
        }
        /* get_digit Stop */
      }
      if(pi < len)
      {
        e_pos = pi;
        file_no = get_avalue();
        ndx = (int) file_no;
        ndx--;
        err_hndlr(ab_code, x, 3, ndx, maxfiles);
        if(fp[ndx].path[0] != '\0')     
        {
          reset_handle(ndx);
        }
        pi = e_pos;
        ch = p_string[pi];
        }
      }
  }
}
/*------ end do_fclose -------*/


void input_io()
{
  char ch;
  int pi, port, len, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=21;
  double file_no;

  len = strlen(p_string);
  pi = e_pos;
  ch = p_string[pi]; 

  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }

  /* get_digit Stop */
  err_hndlr(ab_code, x, 2, pi, len);        
  e_pos = pi;
  file_no = get_avalue();
  port = (int) file_no;
  port--;
  err_hndlr(ab_code, x, 3, port, maxfiles);  
  err_hndlr(ab_code, x, 7, port, 0);     
  get_finput(port, len, ch);
}
/*------- end input_io ----------*/


void get_finput(int port, int len, char chx)
{   
  char ch, varname[VAR_NAME];
  int pi, type;

  pi = e_pos;
  ch = p_string[pi];
  while((pi < len) && (ch != '\n'))  
  {
    if(isalpha(ch) == 0)
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
    }
    if(pi < len)
    {
      e_pos = pi;
      type = get_vtype(pi);
      e_pos = pi;
      strcpy(varname, get_varname());  
      if(chx == '@')               
      {
        read_fline(port, varname);
        break;
      }
      else if(type == 3)           
      {
        read_fstring(port, varname);
      }
      else                    
      {
        read_fvalue(port, varname);
      }
      pi = e_pos;
      ch = p_string[pi];
    }
  }
}
/*------- end get_finput ----------*/


void read_fstring(int port, char *varname)
{
  char chIn='\0', temp[BUFSIZE];
  int ii=0, ndx=0, indx=0, xsize;
  FILE *handle;

  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);       
  }
  handle = fp[port].fptr;
  while((chIn != '\"') && (!feof(handle)))
  {
    ii = fgetc(handle);
    chIn = (char) ii;
  }
  chIn = '\0';
  if(!feof(handle))
  {
    while((chIn != '\"') && (!feof(handle)))
    {
      ii = fgetc(handle);
      chIn = (char) ii;
      if(chIn != '\"')
      {
        temp[indx] = chIn;
        indx++;
      }
    }
  }
  temp[indx] = '\0';
  xsize = strlen(temp);
  xsize++;
  Gtbl[ndx].Str = realloc(Gtbl[ndx].Str, xsize * sizeof(char));
  strcpy(Gtbl[ndx].Str, temp);
}
/*------- end read_fstring ----------*/


void read_fvalue(int port, char *varname)
{   
  char chi='\0', temp[BUFSIZE];
  int pi, type, ii=0, ndx=0, indx=0;
  FILE *handle;

  pi = e_pos;
  type = get_Nvtype(pi);
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  handle = fp[port].fptr;
  while((isdigit(chi) == 0) && (!feof(handle)))
  {
    ii = fgetc(handle);       
    chi = (char) ii;
    if((chi == '-') || (chi == '.'))
    {
      temp[indx] = chi;
      indx++;
    }
  }
  while((isdigit(chi) != 0) || (chi == '.') && (!feof(handle)))
  {
    temp[indx] = chi;
    indx++;
    ii = fgetc(handle);
    chi = (char) ii;
  }
  temp[indx] = '\0';
  switch(type)
  {
    case 4:
      Gtbl[ndx].Dbl = (double) atof(temp);
      break;
    
    case 3:
      Gtbl[ndx].Flt = atof(temp);
      break;

    case 2:
      Gtbl[ndx].Lng = atol(temp);
      break;

    default:			     
      Gtbl[ndx].Int = atoi(temp);
      break;
  }
}
/*------- end read_fvalue ----------*/


void read_fline(int port, char *varname)
{
  char temp[BUFSIZE];
  int ndx, xsize;
  FILE *handle;

  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  temp[0] = '\0';
  handle = fp[port].fptr;
  if(!feof(handle))
  {
    fgets(temp, BUFSIZE, handle);
  }
  xsize = strlen(temp);
  xsize++;
  if(xsize > 2)
  {
    temp[(xsize-2)] = '\0';              
  }
  Gtbl[ndx].Str = realloc(Gtbl[ndx].Str, xsize * sizeof(char));
  strcpy(Gtbl[ndx].Str, temp);
}
/*------- end read_fline ----------*/


void print_io()
{   
  char ch, chmode, quote = '\"', nl='\n';
  char varname[VAR_NAME], temp[BUFSIZE];
  int pi, len, port, si, type, indx, nDims, offset;
  int maxfiles=(IOARRAY-1), x=line_ndx, ab_code=24;
  int *Subscripts;
  double file_no;
  FILE *handle;

  len = strlen(p_string);
  pi = e_pos;
  ch = p_string[pi];
  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_digit Stop */
  err_hndlr(ab_code, x, 2, pi, len);    
  e_pos = pi;
  file_no = get_avalue();
  port = (int) file_no;
  port--;
  chmode = fp[port].mode;              
  err_hndlr(ab_code, x, 3, port, maxfiles); 
  err_hndlr(ab_code, x, 8, chmode, 0);  
  while(((isalpha(ch)== 0) && (ch != '\"')) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  e_pos = pi;
  ch = p_string[pi];
  if(ch == quote)							
  {
    pi++;
    ch = p_string[pi];
    si = 0;
    while((ch != quote) && (pi < len))
    {
      xstring[si] = ch;
      pi++;
      si++;
      ch = p_string[pi];
    }
    xstring[si] = '\0';
    strcpy(temp, xstring);
    handle = fp[port].fptr;
    fprintf(handle, "%s", temp);
  }
  else								
  {
    pi = e_pos;
    strcpy(varname, get_varname());
    type = get_objtype(pi);
    if(type == 0)
    {
      print_fstring(port,varname); 	
    }
    else if(type == 6)
    {
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
      strcpy(temp, strArry[indx].elem[offset]);
      handle = fp[port].fptr;
      fprintf(handle, "%s", temp);
    }
  }
  handle = fp[port].fptr;
  fprintf(handle, "%c", nl);
}
/*------- end print_io ----------*/


void write_io()
{   
  char ch, chmode;
  int pi, len, port, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=24;
  double file_no;

  len = strlen(p_string);
  pi = e_pos;
  ch = p_string[pi];
  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_digit Stop */
  err_hndlr(ab_code, x, 2, pi, len);     
  e_pos = pi;
  file_no = get_avalue();
  port = (int) file_no;
  port--;
  chmode = fp[port].mode;             
  err_hndlr(ab_code, x, 3, port, maxfiles);  
  err_hndlr(ab_code, x, 8, chmode, 0);  
  get_foutput(port, len, ch);
}
/*------- end write_io ----------*/


void get_foutput(int port, int len, char chx)
{   
  char ch, nl='\n', varname[VAR_NAME];
  int pi, type, wflag=0, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=24;
  FILE *handle;

  pi = e_pos;
  ch = p_string[pi];
  while((pi < len) && (ch != '\n'))	
  {
    if(isalpha(ch) == 0)
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
    }
    if(pi < len)
    {
      e_pos = pi;
      type = get_vtype(pi);
      e_pos = pi;
      strcpy(varname, get_varname());
      if(type == 3)			   				
      {
        wflag = write_fstring(wflag,port,varname);
      }
      else			  						
      {
        wflag = write_fvalue(wflag,port,varname);
      }
      pi = e_pos;
      ch = p_string[pi];
    }
  }
  handle = fp[port].fptr;
  fprintf(handle, "%c", nl);
}
/*------- end get_foutput ----------*/


int write_fstring(int wflag, int port, char *varname)
{
  char quote='\"', comma=',', temp[BUFSIZE];
  int ndx;
  FILE *handle;

  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);        
  }
  strcpy(temp, Gtbl[ndx].Str);
  handle = fp[port].fptr;
  if(wflag > 0)
  {
    fprintf(handle, "%c", comma);
  }
  fprintf(handle, "%c%s%c", quote, temp, quote);
  wflag++;
  return wflag;
}
/*------- end write_fstring ----------*/


int write_fvalue(int wflag, int port, char *varname)
{
  char ch, comma=',', temp[BUFSIZE];
  int pi, type, ndx=0, indx=0, len, idx;
  int ivalue;
  long lvalue;
  float fvalue;
  long double dvalue;
  FILE *handle;

  pi = e_pos;
  type = get_Nvtype(pi);
  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);       
  }
  switch(type)
  {
    case 4:
      dvalue = Gtbl[ndx].Dbl;
      sprintf(temp, "%Lf", dvalue);    
      break;
    
    case 3:
      fvalue = Gtbl[ndx].Flt;
      sprintf(temp, "%f", fvalue);     
      break;
 
    case 2:
      lvalue = Gtbl[ndx].Lng;
      break;
     
    default:			     
      ivalue = Gtbl[ndx].Int;
      sprintf(temp, "%d", ivalue);     
      break;
  }
  len = strlen(temp);
  idx = (len-1);
  ch = temp[idx];
  if((type == 4) || (type == 3))
  {
    if(ch == '0')
    {
      while(ch == '0')
      {
        temp[idx] = '\0';
        idx--;
        ch = temp[idx];
        if(ch == '.')
        {
          temp[idx] = '\0';
        }
      }
    }
  }
  handle = fp[port].fptr;
  if(wflag > 0)
  {
    fprintf(handle, "%c", comma);
  }
  fprintf(handle, "%s", temp);
  wflag++;
  return wflag;
}
/*------- end write_fvalue ----------*/


void print_fstring(int port, char *varname)
{
  char temp[BUFSIZE];
  int ndx;
  FILE *handle;

  if(callFlag == 0)
  {
    ndx = get_vndx(varname);
  }
  else
  {
    ndx = get_llvarndx(varname);       
  }
  strcpy(temp, Gtbl[ndx].Str);
  handle = fp[port].fptr;
  fprintf(handle, "%s", temp);
}
/*------- end print_fstring ----------*/


void random_fio(int ndx, int len)
{   
  int pi, bffrlen;
  char ch;
  double dbuffer;
  unsigned size;

  pi = e_pos;
  /* get_alnum Start */
  ch = p_string[pi];
  while((isalnum(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  if(pi == len)
  {
    bffrlen = REC_LEN;
  }
  else
  {
    e_pos = pi;
    dbuffer = get_avalue();
    bffrlen = (int) dbuffer;
  }
  size = bffrlen;
  size++;                              
  fld_bffr[ndx].bfr_size = bffrlen;      
  fld_bffr[ndx].f_bffr = realloc(fld_bffr[ndx].f_bffr, size * sizeof(char));
  fld_bffr[ndx].f_bffr[0] = '\0';
  fld_bffr[ndx].record = 1;
  fld_bffr[ndx].flag = 0;
}
/*------ end random_fio -------*/


void do_field()
{
  int pi, ii, ndx, len, x=line_ndx, ab_code=25;
  int cnt=0, maxfiles=(IOARRAY-1);
  double file_no;
  char ch;

  len = strlen(p_string);      
  pi = e_pos;
  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_digit Stop */
  err_hndlr(ab_code, x, 10, pi, len);       
  e_pos = pi;
  file_no = get_avalue();
  ndx = (int) file_no;
  ndx--;
  err_hndlr(ab_code, x, 3, ndx, maxfiles);  
  err_hndlr(ab_code, x, 9, ndx, 0);        
  cnt = fld_bffr[ndx].fld_count;    
  if(cnt > 0) 	      
  {
    free(fld_bffr[ndx].str_len);
    for(ii = 0; ii < cnt; ii++)
    {
      free(fld_bffr[ndx].str_name[ii]);
    }
    free(fld_bffr[ndx].str_name);
    fld_bffr[ndx].fld_count = 0;
    cnt = 0;
  }
  cnt_field(ndx, cnt, len);
}
/*------- end do_field ----------*/


void cnt_field(int ndx,int cnt,int len)
{
  char temp[VAR_NAME];
  int pi, ii, mark=1, x=line_ndx, ab_code=25;
  unsigned size;

  strcpy(temp, "AS");      
  s_pos = 1;                
  while(mark > 0)
  {
    mark = find_strng(temp);                  
    if(mark > 0)
    {
      cnt++;
      pi = mark;
      pi++;
      s_pos = pi;
    }
  }
  err_hndlr(ab_code, x, 10, cnt, 0);         
  size = cnt;                
  fld_bffr[ndx].fld_count = cnt;
  fld_bffr[ndx].str_len = malloc(size * sizeof(int));
  fld_bffr[ndx].str_name = malloc(size * sizeof(char *));
  for(ii = 0; ii < size; ii++)
  {
    fld_bffr[ndx].str_name[ii] = malloc(VAR_NAME * sizeof(char));
    fld_bffr[ndx].str_name[ii][0] = '\0';
  }
  asn_field(ndx, len);
}
/*------- end cnt_field ----------*/


void asn_field(int ndx,int len)
{
  char ch, temp[VAR_NAME];
  int pi, ii, cnt, fld_len, str_ndx, x=line_ndx, ab_code=25;
  double dvalue;
    
  pi = 0;
  /* get_digit Start */
  ch = p_string[pi];
  while((isdigit(ch) == 0) && (pi < len))
  {
    pi++;
    ch = p_string[pi];
  }
  /* get_digit Stop */
  pi = while_isalnum(pi);
  ch = p_string[pi];
  cnt = 0;
  while(pi < len)
  {
    /* get_digit Start */
    ch = p_string[pi];
    while((isdigit(ch) == 0) && (pi < len))
    {
      pi++;
      ch = p_string[pi];
    }
    /* get_digit Stop */
    ch = p_string[pi];
    if(pi == len)
    {
      break;
    }
    else if(isdigit(ch))
    {
      e_pos = pi;
      dvalue = get_avalue();
      str_ndx = (int) dvalue;
      err_hndlr(ab_code, x, 11, str_ndx, 1);  
      fld_bffr[ndx].str_len[cnt] = str_ndx;
      pi = e_pos;
      pi = iswhite(pi);
      pi += 2;
      /* get_alpha Start */
      ch = p_string[pi];
      while((isalpha(ch) == 0) && (pi < len))
      {
        pi++;
        ch = p_string[pi];
      }
      /* get_alpha Stop */
      ch = p_string[pi];
      ii = 0;
      while(isalnum(ch) != 0)
      {
        temp[ii] = ch;
        ii++;
        pi++;
        ch = p_string[pi];
      }
      temp[ii] = '\0';
      strcpy(fld_bffr[ndx].str_name[cnt], temp);
      cnt++;
    }
    else
    {
      err_hndlr(ab_code, x, 11, 0, 1);   
    }
  }
  cnt = fld_bffr[ndx].fld_count;
  len = 0;
  for(ii=0; ii< cnt; ii++)
  {
    len += fld_bffr[ndx].str_len[ii];
  }
  fld_len = fld_bffr[ndx].bfr_size;
  err_hndlr(ab_code, x, 12, len, fld_len); 
}
/*------- end asn_field ----------*/


void do_lset()
{   
  char *temp;
  int ii, len, fld_len, ndx, indx, cnt, ab_code=26;
  unsigned size;

  parse_let();               
  get_ndxcnt(ab_code);        
  ndx = lrs.ndx;              
  cnt = lrs.cnt;
  fld_len = fld_bffr[ndx].str_len[cnt];
  size = (fld_len+1);
  temp = malloc(size * sizeof(char));
  indx = lset_ndx;
  len = strlen(Gtbl[indx].Str);
  if(len > fld_len)
  {
    for(ii=0; ii < fld_len; ii++)
    {
      temp[ii] = Gtbl[indx].Str[ii];
    }
    temp[ii] = '\0';
  }
  else
  {
    strcpy(temp, Gtbl[indx].Str);
  }
  Gtbl[indx].Str = realloc(Gtbl[indx].Str, size * sizeof(char));
  strcpy(Gtbl[indx].Str, temp);
  free(temp);
  if(fld_len > len)		     
  {
    for(ii=len; ii < fld_len; ii++)
    {
      Gtbl[indx].Str[ii] = ' ';                
    }
    Gtbl[indx].Str[ii] = '\0';
  }
}
/*------- end do_lset ----------*/


void do_rset()
{   
  char *temp;
  int ii, len, fld_len, pad, ndx, indx, cnt, ab_code=27;
  unsigned size;

  parse_let();                
  get_ndxcnt(ab_code);        
  ndx = lrs.ndx;              
  cnt = lrs.cnt;
  fld_len = fld_bffr[ndx].str_len[cnt];
  size = (fld_len+1);
  temp = malloc(size * sizeof(char));
  indx = lset_ndx;
  len = strlen(Gtbl[indx].Str);
  if(len > fld_len)
  {
    for(ii=0; ii < fld_len; ii++)
    {
      temp[ii] = Gtbl[indx].Str[ii];
    }
    temp[ii] = '\0';
  }
  else
  {
    pad = (fld_len - len);                
    for(ii=0; ii < pad; ii++)           
    {
      temp[ii] = ' ';
    }
    temp[ii] = '\0';
    strcat(temp, Gtbl[indx].Str);
  }
  Gtbl[indx].Str = realloc(Gtbl[indx].Str, size * sizeof(char));
  strcpy(Gtbl[indx].Str, temp);
  free(temp);
}
/*------- end do_rset ----------*/


void get_ndxcnt(int xcode)
{   
  char *stack, *buffer;
  int ii, fld_len, x=line_ndx, ab_code=xcode;
  int test=0, ndx=0, indx, cnt=0;

  indx = lset_ndx;
  stack = Gtbl[indx].Nam;
  while((test == 0) && (ndx < IOARRAY))
  {
    if(fp[ndx].mode == 'R')
    {
      fld_len = fld_bffr[ndx].fld_count;
      for(ii=0; ii < fld_len; ii++)
      {
        buffer = fld_bffr[ndx].str_name[ii];
        if(strcmp(stack, buffer) == 0)
        {
          test = 1;         
          cnt = ii;
          ii = fld_len;
        }
      }
      if(test == 0)
      {
  	 ndx++;
      }
    }
    else
    {
      ndx++;
    }
  }
  err_hndlr(ab_code, x, 13, test, ndx);   
  lrs.ndx = ndx;                    
  lrs.cnt = cnt;
  fld_bffr[ndx].flag++;             
}
/*------- end get_ndxcnt ----------*/


void do_put()
{   
  int len, pi, ndx, maxfiles=(IOARRAY-1), x=line_ndx, ab_code=28;
  double file_no;
  char ch;

  len = strlen(p_string);      
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
  file_no = get_avalue();       
  ndx = (int) file_no;
  ndx--;
  err_hndlr(ab_code, x, 3, ndx, maxfiles);  
  err_hndlr(ab_code, x, 9, ndx, 0);        
  lod_bffr(ndx,len);
}
/*------- end do_put ----------*/


void lod_bffr(int ndx, int len)
{   char temp[VAR_NAME], ch;
    int pi, ii=0, indx=0, cnt, bfr_len;
    long fil_rcrd, tmp_rcrd;
    double this_rcrd;
    FILE *handle;


    if(fld_bffr[ndx].flag == 0) 	     
    {
        bfr_len = fld_bffr[ndx].bfr_size;
        memset(fld_bffr[ndx].f_bffr, 32, bfr_len);  
        fld_bffr[ndx].f_bffr[bfr_len] = '\0';
    }
    else
    {
        cnt = fld_bffr[ndx].fld_count;    
        fld_bffr[ndx].f_bffr[0] = '\0';

        for(; ii < cnt; ii++)
        {
            indx = 0;
            strcpy(temp, fld_bffr[ndx].str_name[ii]);

        while((ndx < glb_vct) && (strcmp(Gtbl[indx].Nam, temp) != 0))
            {
                indx++;
            }
            strcat(fld_bffr[ndx].f_bffr, Gtbl[indx].Str);
        }
    }

    pi = e_pos;
    /* get_alnum Start */
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    /* get_alnum Stop */
    if(pi < len)                    
    {
        e_pos = pi;
        this_rcrd = get_avalue();
        fil_rcrd = (long) this_rcrd;
    }
    else                           
    {
        fil_rcrd = fld_bffr[ndx].record;
    }

    tmp_rcrd = fil_rcrd;                    
    handle = fp[ndx].fptr;
    bfr_len = fld_bffr[ndx].bfr_size;

    fil_rcrd--;                            
    fil_rcrd = (fil_rcrd * bfr_len);    

    fseek(handle, fil_rcrd, SEEK_SET);            
    fputs(fld_bffr[ndx].f_bffr, handle);       

    tmp_rcrd++;                            
    fld_bffr[ndx].record = tmp_rcrd;       
    /**/
    fld_bffr[ndx].flag = 0;               
}
/*------- end lod_bffr ----------*/



void do_get()
{   int len, pi, ndx;
    int maxfiles=(IOARRAY-1), x=line_ndx, ab_code=29;
    double file_no;
    char ch;


    len = strlen(p_string);            
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

    file_no = get_avalue();           
    ndx = (int) file_no;
    ndx--;

    err_hndlr(ab_code, x, 3, ndx, maxfiles);  
    err_hndlr(ab_code, x, 9, ndx, 0);       

    fil_bffr(ndx,len);
}
/*------- end do_get ----------*/



void fil_bffr(int ndx, int len)
{   char varname[VAR_NAME], ch;
    int pi, ii, indx, ndxb, cnt, bfr_len;
    long fil_rcrd, tmp_rcrd;
    unsigned size;
    double this_rcrd;
    FILE *handle;


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

    if(pi < len)		    
    {
        e_pos = pi;
        this_rcrd = get_avalue();
        fil_rcrd = (long) this_rcrd;
    }
    else				
    {
        fil_rcrd = fld_bffr[ndx].record;
    }

    tmp_rcrd = fil_rcrd;                   
    /*-------------------*/

    handle = fp[ndx].fptr;
    bfr_len = fld_bffr[ndx].bfr_size;

    fil_rcrd--;                            
    fil_rcrd = (fil_rcrd * bfr_len);    
    fseek(handle, fil_rcrd, SEEK_SET);            

    bfr_len++;                        
    fgets(fld_bffr[ndx].f_bffr, bfr_len, handle);
    /*-------------------*/

    tmp_rcrd++;                           
    fld_bffr[ndx].record = tmp_rcrd;       
    cnt = fld_bffr[ndx].fld_count;       
    size = 1;
    ndxb = 0;

    /* --- copy from buffer to strings --- */
    for(ii=0; ii < cnt; ii++)
    {
        indx = 0;
        size = fld_bffr[ndx].str_len[ii];
        strcpy(varname, fld_bffr[ndx].str_name[ii]);

        if(callFlag == 0)
        {
            indx = get_vndx(varname);
        }
        else
        {
            indx = get_llvarndx(varname);        
        }

        strcpy(Gtbl[indx].Nam, varname);      
        Gtbl[indx].Str = realloc(Gtbl[indx].Str, size * sizeof(char));

        /* --- move (size) chars to string --- */
        for(pi=0; pi < size; pi++)
        {
            Gtbl[indx].Str[pi] = fld_bffr[ndx].f_bffr[ndxb];
            ndxb++;
        }
        Gtbl[indx].Str[pi] = '\0';
    }
}
/*------- end fil_bffr ----------*/



void do_kill()
{
    get_pnam();    

    remove(s_holder);

}
/*---------- end do_kill ----------*/

