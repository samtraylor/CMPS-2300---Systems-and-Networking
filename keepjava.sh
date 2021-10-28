#!/bin/bash
directory={1}
cd ${1}
for file in *; do
	if [[ ${file: -5} != ".java" ]]; then
		rm -rf ${file}
	fi
done
echo "done"
exit