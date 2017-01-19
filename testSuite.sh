#! /bin/sh

tests=`find tests -type f`

for test in $tests; do
	echo Executing test $test
	src/testresid $test | grep Fail
done
