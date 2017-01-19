#! /bin/sh

tests=`find tests -type f`

for test in $tests; do
	echo -n Executing test $test...
	src/testresid $test > /dev/null
	status=$?
	if test $status -eq 0
	then
		echo "OK"
	else
		echo "FAIL"
	fi
done
