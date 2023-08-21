#!/bin/sh

for dir in ./Design_*/;
do
    echo "cp io_map $dir";
    echo "cp io_map.csv $dir;"
    cp io_map $dir;
    cp io_map.csv $dir;
    echo "cd $dir;"
    cd $dir;
    echo "./io_map >& place_io.tcl"
    ./io_map >& place_io.tcl
    echo "rm io_map;"
    echo "rm io_map.csv;"
    rm io_map;
    rm io_map.csv;
    echo "cd ..;"
    cd ..;
done
