#!/bin/bash
path={1}
newName=""
cd ${1}
for file in *; do
	echo "$file is file name, cutting:"
	newName=$(echo $file | cut -d'_' -f 2)
	echo "cut name = $newName"
	newName="$newName.py"
	echo $newName
	
mv ${file} $newName
	newName=""
done
exit