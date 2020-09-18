#!/bin/bash 
# change these per each homework 
#	link to tests:
#testsurl="https://webcourse.cs.technion.ac.il/fc159753hw_236360_201802/hw/WCFiles/hw2-tests.zip"
makefileurl="https://webcourse.cs.technion.ac.il/fc159753hw_236360_201802/hw/WCFiles/Makefile"
#	number of tests: 
numtests=6 
#	command to execute test: 

hostname="csl3"
#tmpdir="selfcheck_tmp"
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

#rm -rf "$tmpdir" &> /dev/null 

#if [ -d "$tmpdir" ] 
#	then 
#	echo "Cannot clear tmp directory. Please delete '"$tmpdir"' manually and try again" 
#	exit 
#fi 

#mkdir "$tmpdir" &> /dev/null 
#unzip "$1" -d "$tmpdir" &> /dev/null 

#if [[ $? != 0 ]] 
#	then 
#	echo "Unable to unzip submission file!" 
#	exit
#fi

#cd "$tmpdir"

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

#wget --no-check-certificate "$testsurl" &> /dev/null 
#if [ ! -f $( basename "$testsurl" ) ] 
#	then 
#	echo "Unable to download tests!" 
#	exit 
#fi

#unzip $( basename "$testsurl" ) &> /dev/null

#if [[ $? != 0 ]]
#	then 
#	echo "Unable to unzip tests!" 
#	exit 
#fi 

i="1" 

while [ $i -le $numtests ] 
	do 
	eval ./hw2 < tests/t${i}.in >& tests/t${i}.res 
	diff tests/t${i}.res tests/t${i}.out &> /dev/null 
	if [[ $? != 0 ]] 
		then
		echo "Failed test #"$i"!" 
		exit 
	fi 
	i=$[$i+1] 
done 

cd - &> /dev/null 
#rm -rf "$tmpdir" 
echo "Ok to submit :)" 
exit
