#!/bin/sh

rm -f *.o

if [ -e perl ]; then
  rm perl
fi

if [ -d t/tmp ]; then
  rmdir t/tmp
fi

if [ -e /tmp/perl-test-bin ]; then
  rm /tmp/perl-test-bin
fi
