USERID CMSUSER

/* bxbasic : prototyp.h : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011            */
/* modified T. Chandler CMSBASIC - prototyp.h  */

/*------ Main.c ------*/
    void pgm_parser(void);
    void parser(void);

/*------ Error.c ------*/
    void a_bort(int,int);
    void err_hndlr(int,int,int,int,int);
 
/*------ Input.c ------*/
    void line_cnt(char *argv[]);
    void load_src(void);
    void tmp_byte(int);
    void loader_1(void);
    void tmp_label(int);
    void tmp_byte(int);
     int get_byte(int);
    void tmp_prog(int);
    void loader_2(void);
    void get_MOD(int);
    void token_if(int);
    void str_funn(int);
     int IsEqu(int);
    void get_strfunc(char *,int);
    void str_copy(char *,int);
    void str_fun2(int);
    void get_mathfunc(char *,int);
    void preproc_sub(int);
    void str_fun3(int ndx);
 

/*------ Output.c ------*/
    void get_prnstring(void);
    void get_prnvar(void);
    char *value2strng(double);
    void get_strvar(char *);
    void parse_print(void);
    void set_TabNl(int);
    void prn_strfunc(void);
    void proc_digit(void);
    void get_strarray(char *);
    void get_strUDT(void);


/*------ Utility.c ------*/
      int iswhite(int);
     int iswhiter(int);
     int find_strng(char *);
     int get_Nvtype(int);
     int while_isalnum(int);
     int while_dd(int pi);
     int get_quote(int,int);
     int get_vtype(int);
     int get_Arrytype(int);
     int get_paramsCount(int,int);
     int get_objtype(int);
     int get_offset2(int *,int,int);
     int get_arrayndx(char *);
     int get_ObjectType(char *);
    void Sav_ObjName(char *,int,int);
    void InitObj(void);
     int get_iarrayndx(char *);
     int get_farrayndx(char *);
     int get_darrayndx(char *);
    char *local_var(char *);
     int isthis_anarray(int, int);
    char *global_var(char *);
    void set_ObjectParam(char *, int);
    void get_pnam(void);


/*------ Strings.c ------*/
    void dim_gstr(char *);
    void parse_str(char *);
    void strng_assgn(void);
    void strvar_assgn(void);
    void asn_function(void);
     int get_strndx(char *);
    char *str_express(void);
    void inputstr(void);
    void mkdstr(void);
    void parse_strarry(char *);
    void dim_strarry(char *,int,int);
    void redim_strarry(char *);
    void erase_strArray(char *);
    void reuse_strarry(char *,int);
 

/*------ Variable.c ------*/
    void parse_let(void);
  double get_varvalue(void);
    char *get_varname(void);
     int get_vndx(char *);
     int get_llvarndx(char *);
  double get_avalue(void);
    void do_dim_var(void);
    void dim_var(void);
    void parse_dim(void);
    void dim_gint(char *);
    void dim_glong(char *);
    void dim_gsingle(char *);
    void dim_gdouble(char *);
    void let_int(char *);
    void let_long(char *);
    void let_single(char *);
    void let_double(char *);
    void bld_global_table(void);
     int get_gvarndx(char *);
     int get_lvarndx(char *);
     int get_var_index(char *);
 

/*------ Rdparser.c ------*/
  double rdp_main(void);
  double Expression(void);
  double Term(void);
  double Factor(void);
    void Match(char);
    void _GetChar(void);
  double GetNum(void);
     int IsAddop(char);
     int IsMultop(char);
     int Is_White(char);
    void SkipWhite(void);
  double asc_2_dbl(void);
  double math_functn(void);


/*------ Arrays.c ------*/
    void do_dim(void);
    void dim_intarry(char *,int,int);
    void dim_fltarry(char *,int,int);
    void dim_dblarry(char *,int,int);
    void reuse_intarry(char *,int);
    void reuse_fltarry(char *,int);
    void reuse_dblarry(char *,int);
    void parse_intarry(char *);
    void parse_fltarry(char *);
    void parse_dblarry(char *);
    void erase_array(void);
    void erase_intArray(char *);
    void erase_fltArray(char *);
    void erase_dblArray(char *);
    void do_redim(void);
    void redim_intarry(char *);
    void redim_fltarry(char *);
    void redim_dblarry(char *);
  double let_intarray(char *);
  double let_fltarray(char *);
  double let_dblarray(char *);


/*------ Loops.c ------*/
    void go_to(void);
    void do_gosub(void);
    void do_return(void);
    void do_for(void);
    void do_next(void);
     int get_From(void);
     int get_To(void);
     int get_Step(void);
    void do_While(void);
    void do_Wend(void);
     int find_wend(int);
    void do_DoWhile(void);
    void do_WDo(void);
   

/*------ Subs.c ------*/
    void do_declare(void);
    void save_sub(char *, int);
    void stor_paramType(int, int, int);
    void do_callsub(void);
    void push_call(char *);
     int push_params(void);
    void enter_sub(void);
    void do_retsb(void);
    void garbage_col(void);
  

/*------ Ifendif.c ------*/
    void do_if(void);
     int boolexpress(void);
     int Nboolterm(int);
     int Nrelation(double);
     int eval_value(double,double,int);
     int AndOrBoolExp(void);
     int IsAndOrOp(void);
     int Sboolterm(int);
     int Srelation(char *);
     int eval_string(char *,char *,int);
     int get_type(void);
     int get_string(void);
    void get_qstring(void);
     int get_op(void);
     int find_if(int);
     int find_else(int);
     int if_eof(void);
     int is_eof(void);
    void do_Switch(void);
    void do_Case(void);
     int find_case(int);
     int find_sw(int);
     int sw_boolexpres(void);


/*------ Getinput.c ------*/
    void get_input(void);
    void input_str(char *,int);
    void input_val(char *,int);
    void get_lninput(void);


/*------ Fileio.c ------*/
    void reset_handle(int);
    void zero_handle(int);
    void parse_open(void);
    void get_iomode(int);
    void fopen_short(char,int,int);
    void do_fclose(void);
    void input_io(void);
    void get_finput(int,int,char);
    void read_fstring(int,char *);
    void read_fvalue(int,char *);
    void read_fline(int,char *);
    void print_io(void);
    void write_io(void);
    void get_foutput(int,int,char);
     int write_fstring(int,int,char *);
     int write_fvalue(int,int,char *);
    void print_fstring(int,char *);
    void random_fio(int,int);
    void init_fldbffrs(void);
    void do_field(void);
    void cnt_field(int,int,int);
    void asn_field(int,int);
    void do_lset(void);
    void do_rset(void);
    void get_ndxcnt(int);
    void do_put(void);
    void lod_bffr(int,int);
    void do_get(void);
    void fil_bffr(int,int);
    void do_kill(void);
 

/*------ Structs.c ------*/
    void struct_Udt(void);
     int isThisUdt(char *, int);
    void parse_UDTstr(void);
    void assn_UDTval(void);
     int get_UDTndx(void);
     int get_UdtvNamIdx(char *, int, int);
    void get_UDTstr(void);
  double get_Uval(char *);
  double get_UDTlfd(char *);
