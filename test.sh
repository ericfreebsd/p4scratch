#!/bin/sh

set -e
set -x

cp perl /tmp/perl-test-bin
cd t
/tmp/perl-test-bin testall.pl
rmdir tmp
cd ..
