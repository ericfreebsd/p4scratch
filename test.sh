#!/bin/sh

if [ ! -x perl ]; then
  echo looks like perl has not yet been built or failed to build
  exit 3
fi

# skip problematic test under some conditions
if [ "x$GITHUB_RUN_ID" != "x" ]; then
  rm t/op/stat.t
fi

set -e
set -x

cp perl /tmp/perl-test-bin
cd t
/tmp/perl-test-bin testall.pl
rmdir tmp
cd ..

echo SUCCESS AT COMPLETION
