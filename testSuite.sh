#! /bin/sh

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 [resid|residfp]" >&2
  exit 1
fi

tests=`find tests -type f`
engine=$1

for test in $tests; do
	echo -n Executing test $test...
	src/testresid --engine=$engine $test > /dev/null
	status=$?
	if test $status -eq 0
	then
		echo "OK"
	else
		echo "FAIL"
	fi
done
