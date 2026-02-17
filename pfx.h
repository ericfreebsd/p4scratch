/*
 * The overhead on a block is at least 4 bytes.  When free, this space
 * contains a pointer to the next free block, and the bottom two bits must
 * be zero.  When in use, the first byte is set to MAGIC, and the second
 * byte is the size index.  The remaining bytes are for alignment.
 * If range checking is enabled and the size of the block fits
 * in two bytes, then the top two bytes hold the size of the requested block
 * plus the range checking words, and the header word MINUS ONE.
 */
union   overhead {
        union   overhead *ov_next;      /* when free */
#if ALIGN_BYTES > 4
        double  strut;                  /* alignment problems */
#endif
        struct {
                u_char  ovu_magic;      /* magic number */
                u_char  ovu_index;      /* bucket # */
#ifdef RCHECK
                u_short ovu_size;       /* actual block size */
                u_int   ovu_rmagic;     /* range magic number */
#endif
        } ovu;
#define ov_magic        ovu.ovu_magic
#define ov_index        ovu.ovu_index
#define ov_size         ovu.ovu_size
#define ov_rmagic       ovu.ovu_rmagic
};

int do_eval(STR *str, int optype, HASH *stash, int savecmd, int gimme, int *arglast);

unsigned long scanhex(char *start, int len, int *retlen);
unsigned long scanoct(char *start, int len, int *retlen);
void repeatcpy(register char *to, register char *from, int len, register int count);
void pidgone(int pid, int status);
int wait4pid(int pid, int *statusp, int flags);
int mypclose(FILE *ptr);
bool astore(register ARRAY *ar, int key, STR *val);
STR *afetch(register ARRAY *ar, int key, int lval);
FILE *mypopen(char *cmd, char *mode);
void hclear(register HASH *tb, int dodbm);
void str_numset(register STR *str, double num);
STR *stab_str(STR *str);
STAB *stabent(register char *name, int add);
bool do_exec(char *cmd);
int envix(char *nam);
void my_setenv(char *nam, char *val);
void str_cat(register STR *str, register char *ptr);
void str_set(register STR *str, register char *ptr);
STR *str_mortal(STR *oldstr);
void growstr(char **strptr, int *curlen, int newlen);
char *nsavestr(char *str, register int len);
char *savestr(char *str);
char *screaminstr(STR *bigstr, STR *littlestr);
char *fbminstr(unsigned char *big, register unsigned char *bigend, STR *littlestr);
void fbmcompile(STR *str, int iflag);

char *str_grow(register STR *str, register int newlen);

char *rninstr(register char *big, char *bigend, char *little, char *lend);
char *ninstr(register char *big, register char *bigend, char *little, char *lend);
char *instr(register char *big, register char *little);
char *cpytill(register char *to, register char *from, register char *fromend, register int delim, int *retlen);
void str_ncat(register STR *str, register char *ptr, register STRLEN len);
int yyerror(char *s);
void str_reset(register char *s, HASH *stash);
char *str_2ptr(register STR *str);
void str_nset(register STR *str, register char *ptr, register STRLEN len);

/****                terrible but works for now
STR *str_new(STRLEN len);
****/
STR *str_new();

char *str_gets(register STR *str, register FILE *fp, int append);
char *scanstr(char *start, int in_what);
void str_free(register STR *str);
void str_sset(STR *dstr, register STR *sstr);
STR *str_smake(register STR *old);
char *str_append_till(register STR *str, register char *from, register char *fromend, register int delim, char *keeplist);
void str_scat(STR *dstr, register STR *sstr);
void str_replace(register STR *str, register STR *nstr);
STR *str_make(char *s, STRLEN len);

STAB *aadd(register STAB *stab);

void fatalx(int argc, char *pat, ... );
void warnx(int argc, char *pat, ... );

ARG *op_new(int numargs);

char *scantrans(char *start);
char *scansubst(char *start);

void arg_free(register ARG *arg);

ARG *make_op(int type, int newlen, ARG *arg1, ARG *arg2, ARG *arg3);
ARG *l(register ARG *arg);

ARG *stab2arg(int atype, register STAB *stab);
ARG *make_match(int type, ARG *expr, SPAT *spat);

int str_eq(register STR *str1, register STR *str2);
double str_2num(register STR *str);

void hoistmust(register SPAT *spat);

regexp *regcomp(char *exp, char *xend, int fold);

char *scanident(register char *s, register char *send, char *dest, STRLEN destlen);
void checkcomma(register char *s, char *name, char *what);

char *scanpat(register char *s);

STAB *hadd(register STAB *stab);

void savelong(long *longp);
void saveitem(register STR *item);

void scanconst(SPAT *spat, char *string, int len);

char *skipspace(register char *s);

int alen(register ARRAY *ar);
void afree(register ARRAY *ar);
STR *ashift(register ARRAY *ar);
void aunshift(register ARRAY *ar, register int num);
STR *apop(register ARRAY *ar);
bool apush(register ARRAY *ar, STR *val);
void aclear(register ARRAY *ar);
ARRAY *afake(STAB *stab, register int size, register STR **strp);
ARRAY *anew(STAB *stab);
ARRAY *saveary(STAB *stab);
void afill(register ARRAY *ar, int fill);
int copyopt(register CMD *cmd, register CMD *which);
int cmd_exec(CMD *VOLATILE cmdparm, VOLATILE int gimme, VOLATILE int sp);

void restorelist(int base);
void savelist(register STR **sarg, int maxsarg);

void stab_clear(register STAB *stab);
void stabset(register STR *mstr, STR *str);
void savenostab(STAB *stab);

void hfree(register HASH *tb, int dodbm);
HASH *savehash(STAB *stab);

void saveaptr(ARRAY **aptr);
void savehptr(HASH **hptr);
void savesptr(STR **sptr);
void saveint(int *intp);

int eval(register ARG *arg, int gimme, register int sp);

bool do_close(STAB *stab, bool explicit);

FILE *nextargv(register STAB *stab);

static int spat_common(register SPAT *spat, int exprnum, int marking);
static int arg_common(register ARG *arg, int exprnum, int marking);
static int nothing_in_common(ARG *arg1, ARG *arg2);
ARG *cmd_to_arg(CMD *cmd);
void free_arg(ARG *arg);

void dehoist(ARG *arg, int i);
ARG *addflags(int i, int flags, register ARG *arg);
ARG *rcatmaybe(ARG *arg);
ARG *localize(ARG *arg);
ARG *cval_to_arg(register char *cval);

ARG *listish(ARG *arg);
ARG *maybelistish(int optype, ARG *arg);
ARG *jmaybe(register ARG *arg);
ARG *make_list(register ARG *arg);
ARG *hide_ary(ARG *arg);
ARG *fixl(int type, ARG *arg);
ARG *evalstatic(register ARG *arg);

int do_match(STR *str, register ARG *arg, int gimme, int *arglast);

ARG *mod_match(int type, register ARG *left, register ARG *pat);

ARG *make_split(register STAB *stab, register ARG *arg, ARG *limarg);

int looks_like_number(STR *str);

static int spat_tosave(register SPAT *spat);
static int arg_tosave(register ARG *arg, int willsave);
static int cmd_tosave(register CMD *cmd, int willsave);
void spat_free(register SPAT *spat);
CMD *make_acmd(int type, STAB *stab, ARG *cond, ARG *arg);
CMD *make_ccmd(int type, int debuggable, ARG *arg, struct compcmd cblock);
CMD *make_icmd(int type, ARG *arg, struct compcmd cblock);
void cmd_free(register CMD *cmd);
CMD *over(STAB *eachstab, register CMD *cmd);
CMD *wopt(register CMD *cmd);
void while_io(register CMD *cmd);
CMD *invert(CMD *cmd);
CMD *addloop(register CMD *cmd, register ARG *arg);
CMD *dodb(CMD *cur);
void cpy7bit(register char *d, register char *s, register int l);
CMD *addcond(register CMD *cmd, register ARG *arg);
CMD *add_label(char *lbl, register CMD *cmd);
void opt_arg(register CMD *cmd, int fliporflop, int acmd);
CMD *append_line(register CMD *head, register CMD *tail);
static void make_nswitch(register CMD *head, int count);
static void make_cswitch(register CMD *head, int count);

void regfree(struct regexp *r);

STR *hdelete(register HASH *tb, char *key, unsigned int klen);

STR *str_nmake(double n);
void str_magic(register STR *str, STAB *stab, int how, char *name, STRLEN namlen);

CMD *block_head(register CMD *tail);
void make_form(STAB *stab, FCMD *fcmd);
SUBR *make_sub(char *name, CMD *cmd);

bool hstore(register HASH *tb, char *key, unsigned int klen, STR *val, register int hash);

void stab_efullname(STR *str, STAB *stab);

SUBR *make_usub(char *name, int ix, int (*subaddr)(), char *filename);

STAB *fstab(char *name);

int do_dirop(int optype, STAB *stab, int gimme, int *arglast);
void do_pipe(STR *str, STAB *rstab, STAB *wstab);
bool do_open(STAB *stab, register char *name, int len);
int ingroup(int testgid, int effective);
int cando(int bit, int effective, register struct stat *statbufp);
int apply(int type, int *arglast);

int do_caller(ARG *arg, int maxarg, int gimme, int *arglast);
int do_each(STR *str, HASH *hash, int gimme, int *arglast);
int do_grep(register ARG *arg, STR *str, int gimme, int *arglast);
int do_kv(STR *str, HASH *hash, int kv, int gimme, int *arglast);
int do_range(int gimme, int *arglast);
int do_repeatary(int *arglast);
int do_reverse(int *arglast);
int do_sort(STR *str, ARG *arg, int gimme, int *arglast);
int do_slice(STAB *stab, STR *str, int numarray, int lval, int gimme, int *arglast);
int do_splice(register ARRAY *ary, int gimme, int *arglast);
int do_split(STR *str, register SPAT *spat, register int limit, int gimme, int *arglast);
int do_time(STR *str, struct tm *tmbuf, int gimme, int *arglast);
int do_tms(STR *str, int gimme, int *arglast);
int do_unpack(STR *str, int gimme, int *arglast);

void do_vop(int optype, STR *str, STR *left, STR *right);

int do_defined(STR *str, register ARG *arg, int gimme, int *arglast);

static int findbucket(union overhead *freep, int srchlen);

int do_connect(STAB *stab, int *arglast);
int do_bind(STAB *stab, int *arglast);
bool do_eof(STAB *stab);
int do_getsockname(int optype, STAB *stab, int *arglast);
int do_ctl(int optype, STAB *stab, int func, STR *argstr);

int do_syscall(int *arglast);

int do_ggrent(int which, int gimme, int *arglast);
int do_ghent(int which, int gimme, int *arglast);
int do_select(int gimme, int *arglast);
int do_truncate(STR *str, register ARG *arg, int gimme, int *arglast);
int do_gpwent(int which, int gimme, int *arglast);
int do_gsent(int which, int gimme, int *arglast);
int do_gnent(int which, int gimme, int *arglast);
int do_gpent(int which, int gimme, int *arglast);
int do_listen(STAB *stab, int *arglast);
int do_shutdown(STAB *stab, int *arglast);
int do_socket(STAB *stab, int *arglast);
int do_sopt(int optype, STAB *stab, int *arglast);
int do_spair(STAB *stab1, STAB *stab2, int *arglast);

void do_pack(register STR *str, int *arglast);
int do_subst(STR *str, ARG *arg, int sp);

int do_study(STR *str, ARG *arg, int gimme, int *arglast);
int do_undef(STR *str, register ARG *arg, int gimme, int *arglast);
int do_vec(int lvalue, STR *astr, int *arglast);

int do_sreverse(STR *str, int *arglast);

int do_try(CMD *cmd, int gimme, int *arglast);

int mylstat(ARG *arg, STR *str);
int mystat(ARG *arg, STR *str);

void str_dec(register STR *str);
void str_inc(register STR *str);
static void ucase(register char *s, register char *send);
static void lcase(register char *s, register char *send);
void str_chop(register STR *str, register char *ptr);

void do_chop(register STR *astr, register STR *str);

static int regtry(regexp *prog, char *string);
static int regmatch(char *prog);
static int regrepeat(char *p, int max);
int regexec(register regexp *prog, char *stringarg, register char *strend, char *strbeg, int minend, STR *screamer, int safebase);

HASH *hnew(unsigned int lookat);
STR *hfetch(register HASH *tb, char *key, unsigned int klen, int lval);

void do_vecset(STR *mstr, STR *str);
void do_join(register STR *str, int *arglast);
int do_trans(STR *str, ARG *arg);

static void doencodes(register STR *str, register char *s, register int len);

int do_stat(STR *str, register ARG *arg, int gimme, int *arglast);
bool do_print(register STR *str, FILE *fp);

int do_assign(register ARG *arg, int gimme, int *arglast);

int hiterinit(register HASH *tb);
char *hiterkey(register HENT *entry, int *retlen);
STR *hiterval(register HASH *tb, register HENT *entry);
HENT *hiternext(register HASH *tb);

int whichsig(char *sig);

void do_write(struct outrec *orec, STAB *stab, int sp);

bool do_aprint(register ARG *arg, register FILE *fp, int *arglast);

static char *regatom(int *flagp);
static void regtail(char *p, char *val);
static void reginsert(char op, char *opnd);

static char *regpiece(int *flagp);
static char *regnode(char op);
static char *reganode(char op, unsigned short arg);

char *regnext(register char *p);

static void regc(char b);
static int regcurly(register char *s);
static void regoptail(char *p, char *val);
static void regset(char *bits, int def, register int c);
static char *regbranch(int *flagp);
static char *reg(int paren, int *flagp);
static char *regclass(void);
