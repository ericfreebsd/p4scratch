#!/bin/sh

set -e
set -x

UNAMES=`uname -s`
CC=cc
ADLIB="-lm -lcrypt"
if [ "x$UNAMES" = "xDragonFly" ]; then
    CC='gcc -DHAS_SETRGID -DHAS_SETRUID -DHAS_SYSCALL -DPWCHANGE -DPWCLASS -DPWEXPIRE -DHAS_SETPGRP -DCSH="/bin/csh"'
fi
if [ "x$UNAMES" = "xOpenBSD" ]; then
    CC=clang
    ADLIB="-lm -lcrypto"
fi
if [ "x$UNAMES" = "xFreeBSD" ]; then
    CC='clang -DHAS_SETRGID -DHAS_SETRUID -DHAS_SYSCALL -DPWCHANGE -DPWCLASS -DPWEXPIRE -DHAS_SETPGRP -DCSH="/bin/csh" -Wno-int-conversion'
fi
if [ "x$UNAMES" = "xNetBSD" ]; then
    CC='gcc -DHAS_SETRGID -DHAS_SETRUID -DHAS_SYSCALL -DPWCHANGE -DPWCLASS -DPWEXPIRE -DHAS_SETPGRP -DCSH="/bin/csh"'
fi
if [ "x$UNAMES" = "xLinux" ]; then
    CC="gcc -DI_TIME -DI_GDBM -DHAS_GDBM -DHAS_SYSCALL"
    ADLIB="-lgdbm -lm -lcrypt"
fi
if [ "x$UNAMES" = "xDarwin" ]; then
    CC=clang
    ADLIB="-lm -lcrypto"
fi

idir=`pwd`

$CC -O -pipe  -I$idir     -c array.c
$CC -O -pipe  -I$idir     -c cmd.c
$CC -O -pipe  -I$idir     -c cons.c
$CC -O -pipe  -I$idir     -c consarg.c
$CC -O -pipe  -I$idir     -c doarg.c
$CC -O -pipe  -I$idir     -c doio.c
$CC -O -pipe  -I$idir     -c dolist.c
$CC -O -pipe  -I$idir     -c dump.c
$CC -O -pipe  -I$idir     -c eval.c
$CC -O -pipe  -I$idir     -c form.c
$CC -O -pipe  -I$idir     -c hash.c
$CC -O -pipe  -I$idir     -c malloc.c
$CC -O -pipe  -I$idir     -c perl.c
$CC -O -pipe  -I$idir     -c perly.c
$CC -O -pipe  -I$idir     -c regcomp.c
$CC -O -pipe  -I$idir     -c regexec.c
$CC -O -pipe  -I$idir     -c stab.c
$CC -O -pipe  -I$idir     -c str.c
$CC -O -pipe  -I$idir     -c toke.c
$CC -O -pipe  -I$idir     -c util.c
$CC -O -pipe  -I$idir     -c usersub.c
cc -O -pipe -o perl array.o cmd.o cons.o consarg.o doarg.o doio.o dolist.o dump.o eval.o form.o hash.o malloc.o perl.o perly.o regcomp.o regexec.o stab.o str.o toke.o util.o usersub.o $ADLIB

#gzip -cn perl.1 > perl.1.gz

ls -l perl
