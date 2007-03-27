void put_long(char *cp, long lval);
extern long get_long(char *cp);
extern int get_short(char *cp);
void put_short(char *cp, int sval);
void put_double(char *cp, double fval);
extern double get_double(char *cp);
void copy_fill(char *dp, char *sp, int len);
void copy_crimp(char *dp, char *sp, int len);
void db_set_date(char *cp, int year, int month, int day);
extern int db_date_year(char *cp);
extern int db_date_month(char *cp);
extern int db_date_day(char *cp);
extern char *db_cur_date(char *cp);
