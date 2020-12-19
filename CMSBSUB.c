USERID GCCCMS


/* bxbasic : Subs.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011 */


void do_declare()
{   char varname[VAR_NAME], ch;                   
    int pi, len, param;
    int ab_code=42, xx = line_ndx;


    len = strlen(p_string);
    pi = e_pos;
    strcpy(varname, get_varname());          

    pi = e_pos;
    pi = iswhite(pi);
    e_pos = pi;

    if(strcmp(varname, "SUB") == 0)
    {
        strcpy(varname, get_varname());
        pi = e_pos;
        /* get_paren Start */
        ch = p_string[pi];
        while((strchr("()", ch) == 0) && (pi < len))
        {
          pi++;
          ch = p_string[pi];
        }
        /* get_paren Stop */

        param = get_paramsCount(pi, len);	

        save_sub(varname, param);           
    }
    else if(strcmp(varname, "FUNCTION") == 0)
    {
        /*strcpy(varname, get_varname());*/
        ab_code = 43;
        a_bort(ab_code, xx);
    }
    else
    {   a_bort(ab_code, xx);            
    }


}
/*------- end do_declare -------*/



void save_sub(char *varname, int param)
{   int pi, ndx;                   
    unsigned size;                 

    ndx = subCnt;

    if(ndx == 0)
    {                              
        size = 1;
        SubR = (struct Sub_Routines *) 
               malloc(size * sizeof(struct Sub_Routines));
        Sndx = (struct Sub_Index *) malloc(size * sizeof(struct Sub_Index));
    }
    else
    {                            
        size = ndx + 1;
        SubR = (struct Sub_Routines *) 
                 realloc(SubR, size * sizeof(struct Sub_Routines));
        Sndx = (struct Sub_Index *) 
                 realloc(Sndx, size * sizeof(struct Sub_Index));
    }
    /**/
    strcpy(SubR[ndx].SubName, varname);    
    strcpy(Sndx[ndx].SubName, varname);    

    SubR[ndx].paramCnt = param;            
    Sndx[ndx].index = ndx;                 

    pi = 0;
    stor_paramType(pi, ndx, param);     

    subCnt++;                           

}
/*------- end save_sub -------*/



void stor_paramType(int pi, int ndx, int param)
{   int len, ii, type; 
    char ch;              


    len = strlen(p_string); 
    /* get_paren Start */
    ch = p_string[pi];
    while((strchr("()", ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    /* get_paren Stop */
 
    /* get_alnum Start */
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    /* get_alnum Stop */

    if(param > 0)
    {
        for(ii = 0; ii < param; ii++)
        {
            pi = while_isalnum(pi);
            type = get_objtype(pi);
            SubR[ndx].paramType[ii] = type;
            /**/
            /* get_alnum Start */
            ch = p_string[pi];
            while((isalnum(ch) == 0) && (pi < len))
            {
              pi++;
              ch = p_string[pi];
            }
            /* get_alnum Stop */
        }
    }
    else
    {
        for(ii = 0; ii < 10; ii++)
        {
            SubR[ndx].paramType[ii] = '\0';
        }
    }
}
/*------- end stor_paramType -------*/



void do_callsub()
{   char varname[VAR_NAME];              
    int pi, ab_code=38, xx = line_ndx;


    if(subCnt == 0)
    {   a_bort(ab_code, xx);             
    }

    pi = 0;
    e_pos = pi;
    strcpy(varname, get_varname());			

    push_call(varname);                     

    callFlag++;
    e_pos = 0;

    go_to();
}
/*------- end do_callsub -------*/


void push_call(char *varname)
{   int ndx, addr, params, type, sndx;    
    int ab_code=39, xx = line_ndx;
    unsigned size;


    ndx = 0;                              

    while((ndx < subCnt) && (strcmp(varname, Sndx[ndx].SubName) != 0))
    {
        ndx++;
    }

    if(ndx >= subCnt)
    {   a_bort(ab_code, xx);             
    }

    addr = Sndx[ndx].index;              
    params = SubR[addr].paramCnt;       

    if(params > 0)                          
    {                                       
        size = PARAM_STK;                   
     pStk = (struct Push_Stack *) malloc(size * sizeof(struct Push_Stack));

        ndx = 0;

        for(ndx = 0; ndx < params; ndx++)
        {
            type = SubR[addr].paramType[ndx];   
            sndx = push_params();              

            switch(type)
            {
                case 0:
                    size = strlen(Gtbl[sndx].Str);
                    size++;

                    pStk[ndx].Str = malloc(size * sizeof(char));
                    strcpy(pStk[ndx].Str, Gtbl[sndx].Str);
                    pStk[ndx].Typ = 0;
                    break;
                case 1:
                    pStk[ndx].Int = Gtbl[sndx].Int;
                    pStk[ndx].Typ = 1;
                    break;
                case 2:
                    pStk[ndx].Lng = Gtbl[sndx].Lng;
                    pStk[ndx].Typ = 2;
                    break;
                case 3:
                    pStk[ndx].Flt = Gtbl[sndx].Flt;
                    pStk[ndx].Typ = 3;
                    break;
                case 4:
                    pStk[ndx].Dbl = Gtbl[sndx].Dbl;
                    pStk[ndx].Typ = 4;
                    break;
                default:
                    printf("\nerror! push_call\n");
                    exit(0);
            }
        }
    }

    if(subCnt == 0)
    {                           
        size = 1;
        rStk = (struct Return_Stack *) 
                 malloc(size * sizeof(struct Return_Stack));
    }
    else
    {
        size = ActvSubs + 1;
        rStk = (struct Return_Stack *) 
                 realloc(rStk, size * sizeof(struct Return_Stack));
    }

    ndx = ActvSubs;
    rStk[ndx].ret_Addr = line_ndx;       

}
/*------- end push_call -------*/



int push_params()
{   char varname[VAR_NAME], ch;
    int pi, len, ndx, thsSb, indx;
    int ab_code=44, xx = line_ndx;


    pi = e_pos;                 
    len = strlen(p_string);     

    /* get_alnum Start */
    ch = p_string[pi];
    while((isalnum(ch) == 0) && (pi < len))
    {
        pi++;
        ch = p_string[pi];
    }
    /* get_alnum Stop */
  
    e_pos = pi;                     
    strcpy(varname, get_varname());     

    if(varname[0] == '\0')
    {                               
        ab_code = 45;
        a_bort(ab_code, xx);
    }

    ndx = glb_vct - 1;             
    thsSb = ActvSubs;                     
    indx = Gtbl[ndx].ActSub;             

    while((ndx > 0) && (strcmp(varname, Gtbl[ndx].Nam) != 0) 
                                         && (thsSb == indx))
    {                                          
        ndx--;                                 
        indx = Gtbl[ndx].ActSub;              
    }

    if(strcmp(varname, Gtbl[ndx].Nam) != 0)
    {                                    
        strcpy(s_holder, varname);
        a_bort(ab_code, xx);
    }

    return ndx;
}
/*------- end push_params -------*/





void enter_sub()
{   char varname[VAR_NAME], xp_string[BUFSIZE], ch;
    int pi, len, ii, type, xpi, ndx, addr, params;
    int ab_code=39, xx = line_ndx;
    unsigned size;


    ActvSubs++;                  

    pi = 0;
    e_pos = pi;
    strcpy(varname, get_varname());			

    ndx = 0;

    while((ndx < subCnt) && (strcmp(varname, Sndx[ndx].SubName) != 0))
    {
        ndx++;
    }

    if(ndx > subCnt)
    {   a_bort(ab_code, xx);             
    }

    addr = Sndx[ndx].index;              
    params = SubR[addr].paramCnt;        

    addr = (ActvSubs - 1);
    rStk[addr].Vrcnt = params;           
    sub_ndx = addr;                      

    pi = e_pos;
    len = strlen(p_string);

    if(params > 0)
    {                                   
        for(ii=0; ii < params; ii++)	
        {
            /* get_alnum Start */
            ch = p_string[pi];
            while((isalnum(ch) == 0) && (pi < len))
            {
              pi++;
              ch = p_string[pi];
            }
            /* get_alnum Stop */
            e_pos = pi;
            strcpy(varname, get_varname());

            if(varname[0] == '\0')
            {                            
                ab_code = 46;
                a_bort(ab_code, xx);
            }

            strcpy(xp_string, p_string); 
            xpi = e_pos;

            ndx = get_lvarndx(varname);  

            type = pStk[ii].Typ;         
                                         
            switch(type)
            {
                case 0:
                    size = strlen(pStk[ii].Str);
                    size++;

                    Gtbl[ndx].Str = malloc(size * sizeof(char));
                    strcpy(Gtbl[ndx].Str, pStk[ii].Str);

                    break;
                case 1:
                    Gtbl[ndx].Int = pStk[ii].Int;

                    break;
                case 2:
                    Gtbl[ndx].Lng = pStk[ii].Lng;

                    break;
                case 3:
                    Gtbl[ndx].Flt = pStk[ii].Flt;

                    break;
                case 4:
                    Gtbl[ndx].Dbl = pStk[ii].Dbl;

                    break;
            }

            Gtbl[ndx].ActSub = ActvSubs;  

            strcpy(p_string, xp_string);
            pi = xpi;
        }

        free(pStk);                      
    }
}
/*------- end enter_sub -------*/



void do_retsb()
{   int ndx;
    unsigned size;


    garbage_col();                 

    ActvSubs--;                   
    callFlag--;

    ndx = ActvSubs;
    line_ndx = rStk[ndx].ret_Addr;       

    size = ActvSubs;
    rStk = (struct Return_Stack *) 
              realloc(rStk, size * sizeof(struct Return_Stack));

}
/*------- end do_returnsub -------*/




void garbage_col()
{   int ndx, indx, sub, totVars;      
    unsigned size;


    ndx = (ActvSubs - 1);
    totVars = rStk[ndx].Vrcnt;           

    if(totVars > 0)
    {
        indx = glb_vct - 1;
        sub = Gtbl[indx].ActSub;             
        ndx++;

        while((indx > 0) && (sub == ndx))
        {
          /*  free(Gtbl[indx].Str); */
            indx--;                             
            sub = Gtbl[indx].ActSub;          
        }

        size = glb_vct - totVars;     
        Gtbl = (struct Global_Table *) 
               realloc(Gtbl, size * sizeof(struct Global_Table));
    }

    glb_vct = glb_vct - totVars;
}
/*------- end grbge_cllctr -------*/

