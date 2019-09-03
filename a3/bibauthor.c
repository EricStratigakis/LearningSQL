static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,57,65,77,114,78,68,72,105,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,69,78,83,84,82,65,
 84,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,66,73,66,65,85,84,72,79,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "bibauthor.sqc"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char *gets(char *str);


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 9 "bibauthor.sqc"
 


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 11 "bibauthor.sqc"

   	char db[6] = "cs348";
   	char theauthorname[20], thename[20], thetitle[20], thepublisher[20];
	sqlint32 thepubid, theyear, thevolume, thenumber;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 15 "bibauthor.sqc"


int main(int argc, char *argv[]) {

	if (argc!=2) {
      	printf("Usage: need to be given an author as argument\n");
		exit(1);
	};

	
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 24 "bibauthor.sqc"

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 25 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 25 "bibauthor.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 25 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 25 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)db;
#line 25 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 25 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 25 "bibauthor.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 25 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 25 "bibauthor.sqc"
  sqlastop(0L);
}

#line 25 "bibauthor.sqc"

	printf("Connected to DB2\n");
	strncpy(theauthorname,argv[1],20);	
	
	
/*
EXEC SQL DECLARE pubs CURSOR FOR
	SELECT p.pubid, a.name, p.title
		FROM publication p, author a, wrote w
		WHERE a.name LIKE :theauthorname
			AND w.pubid = p.pubid
			AND w.aid = a.aid
		ORDER BY year DESC;
*/

/*
SQL0206N  "YEAR" is not valid in the context where it is 
used.  SQLSTATE=42703

*/

#line 35 "bibauthor.sqc"


   	
/*
EXEC SQL WHENEVER NOT FOUND GO TO end;
*/

#line 37 "bibauthor.sqc"

	for (;;) {
   		
/*
EXEC SQL FETCH pubs INTO :thepubid, :thename, :thetitle;
*/

{
#line 39 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 39 "bibauthor.sqc"
  sqlaaloc(3,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&thepubid;
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 39 "bibauthor.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 20;
#line 39 "bibauthor.sqc"
      sql_setdlist[1].sqldata = (void*)thename;
#line 39 "bibauthor.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 39 "bibauthor.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 20;
#line 39 "bibauthor.sqc"
      sql_setdlist[2].sqldata = (void*)thetitle;
#line 39 "bibauthor.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 39 "bibauthor.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 39 "bibauthor.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 39 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 39 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 39 "bibauthor.sqc"
  sqlastop(0L);
}

#line 39 "bibauthor.sqc"

		printf("	Pubid: %n\n", &thepubid);
		printf("	Type: book\n");
		printf("	Title: %s\n", thetitle);
		printf("	Authors: ");
	};

end:
	
/*
EXEC SQL CLOSE pubs;
*/

{
#line 47 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 47 "bibauthor.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 47 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 47 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 47 "bibauthor.sqc"
  sqlastop(0L);
}

#line 47 "bibauthor.sqc"

   	
/*
EXEC SQL ROLLBACK;
*/

{
#line 48 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 48 "bibauthor.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 48 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 48 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 48 "bibauthor.sqc"
  sqlastop(0L);
}

#line 48 "bibauthor.sqc"

   	
/*
EXEC SQL CONNECT reset;
*/

{
#line 49 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 49 "bibauthor.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 49 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 49 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 49 "bibauthor.sqc"
  sqlastop(0L);
}

#line 49 "bibauthor.sqc"

	exit(0);

error:
   	check_error("My error",&sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 54 "bibauthor.sqc"

	
/*
EXEC SQL ROLLBACK;
*/

{
#line 55 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 55 "bibauthor.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 55 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 55 "bibauthor.sqc"
  sqlastop(0L);
}

#line 55 "bibauthor.sqc"

   	
/*
EXEC SQL CONNECT reset;
*/

{
#line 56 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 56 "bibauthor.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 56 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 56 "bibauthor.sqc"
  sqlastop(0L);
}

#line 56 "bibauthor.sqc"

   	exit(1);
}
