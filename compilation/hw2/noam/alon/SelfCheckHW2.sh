#!/bin/bash 

makefileurl="https://webcourse.cs.technion.ac.il/fc159753hw_236360_201802/hw/WCFiles/Makefile"
#	number of tests: 
numtests=$2 
hostname="csl3"
if [ $( hostname ) != "$hostname" ]
	then 
	echo "This script is only intended to run on "$hostname" or "$hostname2"!" 
	exit 
fi 

if [ -z "$1" ]
	then 
	echo "Usage: ./"$( basename "$0" )" " 
	exit 
fi

if [ ! -f "$1" ] 
	then
	echo "Submission zip file not found!" 
	exit 
fi 

if [ ! -f hw2.cpp ] 
	then
	echo "File hw2.cpp not found!"
	exit
fi

wget --no-check-certificate "$makefileurl" &> /dev/null
if [ ! -f Makefile ]
	then
		echo "Unable to download Makefile!"
		exit
fi

make

if [ ! -f hw2 ] 
	then 
	echo "Cannot build submission!" 
	exit 
fi 

echo "Running $numtests tests..."
i="1" 

while [ $i -le $numtests ] 
	do 
	eval python3 penv/generate.py
	eval ./hw2 < generated.in &> generated.res 
	diff generated.res generated.out &> /dev/null 
	if [[ $? != 0 ]] 
		then
		echo "Failed test #"$i"!"
		echo "========================"
		echo "Generated test is:"
		cat generated.in
		echo -e "Expected output:"
		cat generated.out
		echo -e "Your output:"
		cat generated.res
		echo -e "All results are stored in generated.in/out/res"
		rm -rf Makefile.* 
		exit 
	fi 
	echo "Test $i passed"
	i=$[$i+1] 
done 

cd - &> /dev/null 
rm -rf Makefile.* 
echo "All tests passed!" 
exit
