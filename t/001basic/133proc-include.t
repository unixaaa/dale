#!/usr/bin/env perl

use warnings;
use strict;
$ENV{"DALE_TEST_ARGS"} ||= "";
my $test_dir = $ENV{"DALE_TEST_DIR"} || ".";
$ENV{PATH} .= ":.";

use Data::Dumper;
use Test::More tests => 3;

my @res = `dalec $ENV{"DALE_TEST_ARGS"} -I. -lm $test_dir/t/src/proc-include-test.dt -o proc-include-test`;
is(@res, 0, 'No compilation errors');

@res = `./proc-include-test`;
is($?, 0, 'Program executed successfully');

chomp for @res;
is_deeply(\@res, [qw(test)],
    'Got expected results');

`rm proc-include-test`;

1;
