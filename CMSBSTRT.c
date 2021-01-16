USERID GCCCMS


/* bxbasic.c : structs.c : alpha version.20.3.1 */
/* Copyright:(c) sarbayo, 2001-2011 */


/***********************
   variable types:
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
***********************/



double get_UDTlfd(char *name)
{
    char varname[VAR_NAME];
    char ch, *ptr;
    int pi, len, ndx, indx, vcount, offset, type;

    long lvalue;
    float fvalue;
    double dvalue;


    ndx = get_UDTndx();                         

    len = strlen(name);
    pi = e_pos - len;
    pi--;
    pi += udtpi;
    pi++;

    e_pos = pi;
    strcpy(varname, get_varname());	        
    pi = e_pos;
    pi++;                                   
    e_pos = pi;

    vcount = UDT[ndx].numVars;         

    indx = get_UdtvNamIdx(varname, ndx, vcount);

    offset = UDT[ndx].offset[indx];
    type = UDT[ndx].type[indx];

    ptr = UDT[ndx].data;
    ptr += offset;

    switch(type)
    {
        case 2:           /* lval2 = *(unsigned long *) &myarray[5]; */
            lvalue = *(unsigned long *) ptr;
            dvalue = (double) lvalue;
            break;
        case 3:           /* fval2 = *(float *) &myarray[9]; */
            fvalue = *(float *) ptr;
            dvalue = (double) fvalue;
            break;
        case 4:           /* dval2 = *(double *) &myarray[13]; */
            dvalue = *(double *) ptr;
            break;
    }

    return dvalue;
}
/*------ end get_UDTlfd ------*/



double get_Uval(char *name)
{
    char varname[VAR_NAME];
    char ch, *ptr;
    int pi, len, ndx, indx, vcount, offset;

    int ivalue;
    double dvalue;


    ndx = get_UDTndx();                    

    len = strlen(name);
    pi = e_pos - len;
    pi += udtpi;
    pi++;
    e_pos = pi;
    strcpy(varname, get_varname());	        

    vcount = UDT[ndx].numVars;         

    indx = get_UdtvNamIdx(varname, ndx, vcount); 

    offset = UDT[ndx].offset[indx];
    ptr = UDT[ndx].data;
    ptr += offset;

    ivalue = *(unsigned int *) ptr;
    dvalue = (double) ivalue;

    return dvalue;
}
/*------ end get_UDTval ------*/



void get_UDTstr()
{
    char varname[VAR_NAME];
    char ch, *ptr;
    int pi, ndx, indx, vcount, offset, size;


    ndx = get_UDTndx();                     

    pi = udtpi;
    pi++;
    e_pos = pi;
    strcpy(varname, get_varname());	        

    vcount = UDT[ndx].numVars;         

    indx = get_UdtvNamIdx(varname, ndx, vcount); 

    offset = UDT[ndx].offset[indx];
    size = UDT[ndx].size[indx];

    /* --- make string assignment --- */
    ptr = UDT[ndx].data;
    ptr += offset;

    memcpy(s_holder, ptr, size * sizeof(char));

/*    memcpy(string2, &myarray[21], len * sizeof(char));
      memcpy(ptr, &temp, size * sizeof(char)); */
}
/*------ end get_UDTstr ------*/



void parse_UDTstr()
{
    char temp[BUFSIZE], varname[VAR_NAME];
    char ch, *ptr;
    int pi, ndx, indx, vcount, offset, size;


    ndx = get_UDTndx();                     

    pi = udtpi;
    pi++;
    e_pos = pi;
    strcpy(varname, get_varname());	        
    pi = e_pos;
    vcount = UDT[ndx].numVars;         

    indx = get_UdtvNamIdx(varname, ndx, vcount); 

    offset = UDT[ndx].offset[indx];

    if(IsEqu(pi) == 0)                           
    {
        pi++;
        pi = iswhite(pi);
        e_pos = pi;
    }

    /* --- now get assignment string --- */
    Match('=');

    strcpy(temp, str_express());

    /* --- make string assignment --- */
    size = strlen(temp);
    size++;
    ptr = UDT[ndx].data;
    ptr += offset;

    memcpy(ptr, &temp, size * sizeof(char));
}
/*------ end parse_UDTstr ------*/



void assn_UDTval()
{
    char varname[VAR_NAME];
    char *ptr;
    int pi, ndx, indx, vcount, type, offset=0;

    int    iresult;
    long   lresult;
    float  fresult;
    double dresult;


    ndx = get_UDTndx();                    

    pi = udtpi;
    pi++;
    e_pos = pi;
    strcpy(varname, get_varname());	        
    pi = e_pos;
    vcount = UDT[ndx].numVars;         

    indx = get_UdtvNamIdx(varname, ndx, vcount); 

    type = UDT[ndx].type[indx];
    offset = UDT[ndx].offset[indx];
    ptr = UDT[ndx].data;
    ptr += offset;

    if(IsEqu(pi) == 0)                           
    {
        pi++;
        pi = iswhite(pi);
        e_pos = pi;
    }

    Match('=');                                  

    switch(type)
    {                                  
        case 1:                        
            iresult = (int) rdp_main();
            memcpy(ptr, &iresult, sizeof(unsigned int));
            break;
        case 2:
            lresult = (long) rdp_main();
            memcpy(ptr, &lresult, sizeof(unsigned long));
            break;
        case 3:
            fresult = (float) rdp_main();
            memcpy(ptr, &fresult, sizeof(float));
            break;
        case 4:
            dresult = (double) rdp_main();
            memcpy(ptr, &dresult, sizeof(double));
            break;
    }
}
/*------ end assn_UDTval ------*/



int get_UdtvNamIdx(char *Name, int Ndx, int Cnt)
{
    int indx=0;
    int ab_code=132, x=line_ndx;


    while((indx < Cnt) && (strcmp(Name, UDT[Ndx].varNames[indx]) != 0))
    {
        indx++;
    }

    if(indx >= Cnt)
    {
        a_bort(ab_code, x);                 
    }

    return indx;
}
/*------ end get_UdtvNamIdx ------*/



int get_UDTndx()
{
    char udtName[VAR_NAME];
    int ndx;


    strcpy(udtName, udtTmpName);     
    ndx = 0;

    while((ndx < UdtCnt) && (strcmp(udtName, UDT[ndx].udtName) != 0))
    {
        ndx++;
    }

    return ndx;
}
/*------ end get_UDTndx ------*/



int isThisUdt(char *varname, int type)
{
    char udtName[VAR_NAME];
    char ch, dot='.';
    int pi, len, ndx;

    strcpy(udtName, varname);
    len = strlen(udtName);
    pi = 0;
    ch = udtName[pi];

    while((ch != dot) && (pi < len))
    {
        pi++;
        ch = udtName[pi];
    }

    if(ch == dot)
    {
        udtName[pi] = '\0';
        ndx = 0;

        while((ndx < UdtCnt) && (strcmp(udtName, UDT[ndx].udtName) != 0))
        {
            ndx++;
        }

        if(ndx < UdtCnt)
        {
            type += 10;
            udtpi = pi;
            strcpy(udtTmpName, udtName);
        }
    }

    return type;
}
/*------ end isThisUdt ------*/



void struct_Udt()
{   char varname[VAR_NAME], udtName[VAR_NAME], ch;
    char **elementName;
    int *elemType, *elemSize, *elemOffset;
    int pi, len, ii, indx, vcount=0;
    int thistoken=0, curline=line_ndx, ndx=line_ndx;
    int type, varsize, offset=0, length;
    int ab_code=131, x=line_ndx;
    int result;
    unsigned size;


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

/* ---------- begin collecting struct info -------------- */

    strcpy(udtName, get_varname());	            
    pi = e_pos;

/* ------------------------------------------------------ */
    indx = 0;                          

    if(UdtCnt > 0)                     
    {
        while((strcmp(udtName, UDT[indx].udtName) != 0) && (indx < UdtCnt))
        {
            indx++;
        }

        if(indx < UdtCnt)                        
        {
            ab_code = 133;
            a_bort(ab_code, x);
        }
    }

    /* --- dynamically create array structures --- */
/*    UDT = malloc(1 * sizeof(struct tag_UDT));   */

    if(UdtCnt == 0)
    {
        size = 1;                                
        UDT = malloc(size * sizeof(struct tag_UDT));
    }
    else
    {
        size = UdtCnt + 1;                       
        UDT = realloc(UDT, size * sizeof(struct tag_UDT));
    }

/* ------------------------------------------------------ */

/* --------- loop: count the number of elements --------*/

    while(thistoken != 127)
    {
        ndx++;
        thistoken = byte_array[ndx];

        if(thistoken == 1)
        {
            vcount++;                            
        }
    }

/* ----------- collect udt elements info ------------- */

    ndx = curline + 1;
    thistoken=0;
    size = vcount;
    elementName = malloc(size * sizeof(char *));
    size = VAR_NAME;

    for(ii=0; ii < vcount; ii++)
    {
        elementName[ii] = malloc(size * sizeof(char));
    }

    size = vcount;
    elemType = malloc(size * sizeof(int *));
    elemSize = malloc(size * sizeof(int *));
    elemOffset = malloc(size * sizeof(int *));

    for(ii=0; ii < vcount; ii++)
    {
        thistoken = byte_array[ndx];

        if(thistoken == 1)
        {
            strcpy(p_string, array1[ndx]);
            e_pos = 0;
            strcpy(varname, get_varname());      
            strcpy(elementName[ii], varname);
            pi = e_pos;

            type = get_objtype(pi);              
            elemType[ii] = type;

            switch(type)
            {
                case 0:
                    len = strlen(p_string);
                    /* get_digit Start */
                    ch = p_string[pi];
                    while((isdigit(ch) == 0) && (pi < len))
                    {
                      pi++;
                      ch = p_string[pi];
                    }
                    /* get_digit Stop */

                    e_pos = pi;
                    varsize = get_avalue();
                    varsize++;
                    elemSize[ii] = varsize;
                    elemOffset[ii] = offset;
                    break;
                case 1:
                    varsize = sizeof(int);
                    elemSize[ii] = varsize;
                    elemOffset[ii] = offset;
                    break;
                case 2:
                    varsize = sizeof(long);
                    elemSize[ii] = varsize;
                    elemOffset[ii] = offset;
                    break;
                case 3:
                    varsize = sizeof(float);
                    elemSize[ii] = varsize;
                    elemOffset[ii] = offset;
                    break;
                case 4:
                    varsize = sizeof(double);
                    elemSize[ii] = varsize;
                    elemOffset[ii] = offset;
                    break;
            }
            offset += varsize;
        }
        ndx++;
    }

    length = offset;

/* ------------------------------------------------------ */

    strcpy(UDT[indx].udtName, udtName);
    UDT[indx].numVars = vcount;

    size = vcount;
    UDT[indx].varNames = malloc(size * sizeof(char *));
    size = VAR_NAME;

    for(ii=0; ii < vcount; ii++)
    {
        UDT[indx].varNames[ii] = malloc(size * sizeof(char));
    }

    for(ii=0; ii < vcount; ii++)
    {
        strcpy(UDT[indx].varNames[ii], elementName[ii]);
    }

    size = vcount;
    UDT[indx].type = malloc(size * sizeof(int));
    UDT[indx].size = malloc(size * sizeof(int));
    UDT[indx].offset = malloc(size * sizeof(int));

    for(ii=0; ii < vcount; ii++)
    {
        UDT[indx].type[ii] = elemType[ii];
        UDT[indx].size[ii] = elemSize[ii];
        UDT[indx].offset[ii] = elemOffset[ii];
    }

    UDT[indx].length = length;
    size = length;
    UDT[indx].data = malloc(size * sizeof(char));

    free(elemOffset);
    free(elemSize);
    free(elemType);
    free(elementName);

    UdtCnt++;                       

    line_ndx = ndx;

}
/*------ end struct_Udt ------*/

