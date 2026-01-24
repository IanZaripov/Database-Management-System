#!/bin/bash
set -e


until pg_isready -h db -p 5432 -U employee_user -d employee_db; do
  sleep 2
done


mkdir -p build
cd build
cmake .. && make

echo "Running application with arguments: $@"
./app "$@"
