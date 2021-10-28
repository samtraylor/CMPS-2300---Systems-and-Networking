#!/bin/bash
firstParam=${1} #first arg is a file name
secondParam=${2} #second arg is a directory
thirdParam=${3} #third is a number 
fourthParam=${4} #fourth is a number
echo "This line's for the terminal."
echo "This line's going into a file." >> results.txt
echo "The second argument is ${2}"
if [[ ${3} -gt ${4} ]]; then
	echo "The third argument is bigger."
else
	echo "The fourth argument is bigger."
fi
if [[ -e ${1} ]]; then 
	echo "The first provided arg exists."
	if [[ -f ${1} ]]; then
		echo "The first provided arg corresponds to a file"
	else
		echo "The first provided arg corresponds to a directory"
	fi
else
	echo "The first provided file doesn't exist"
fi
if [[ -e ${2} ]]; then 
	echo "The second provided arg does exist."
	if [[ -f ${2} ]]; then
		echo "The second provided arg corresponds to a file."
	else
		echo "The second provided arg corresponds to a directory."
	fi
else
	echo "The second provided arg doesn't exist"
fi
for file in 'ls *.pdf 2> /dev/null'; do
	echo ${file}
done	
exit