#!/bin/sh

if [ $# -ne 2 ]
then
	echo gen_project project_name version
	exit
fi

PROJECT_NAME=$1
VERSION=$2
UPPER_PROJECT_NAME=`echo ${PROJECT_NAME} | tr '[:lower:]' '[:upper:]'`

echo "##1. get a copy from repository..."
cp -rf ssdb-master ssdb-master.work

echo "##2. rename file..."
cd ssdb-master.work
mv ./src/conf/ssdb.conf ./src/conf/${PROJECT_NAME}.conf
mv ./src/client/SSDB_client.h ./src/client/${UPPER_PROJECT_NAME}_client.h
mv ./src/client/SSDB_impl.cpp ./src/client/${UPPER_PROJECT_NAME}_impl.cpp
mv ./src/client/hello-ssdb.cpp ./src/client/hello-${PROJECT_NAME}.cpp
mv ./src/client/SSDB_impl.h ./src/client/${UPPER_PROJECT_NAME}_impl.h
mv ./src/ssdb-server.cpp ./src/${PROJECT_NAME}-server.cpp

echo "##3. replace strings in files..."
sed -i "s/ssdb/${PROJECT_NAME}/g" `grep -io 'ssdb' * -r | grep -v Binary | gawk -F':' '{print $1}'`
sed -i "s/SSDB/${UPPER_PROJECT_NAME}/g" `grep -io 'ssdb' * -r | grep -v Binary | gawk -F':' '{print $1}'`
echo ${VERSION}>version

echo "##4. rename project..."
cd ..
mv ssdb-master.work ${PROJECT_NAME}-master

echo "##all step has been finished!!!"
