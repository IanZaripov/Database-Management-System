#!/bin/bash
set -e

echo "Waiting for database to be ready..."

until pg_isready -h db -p 5432 -U employee_user -d employee_db; do
  echo "Waiting for database..."
  sleep 2
done

echo "Database is ready! Building application..."

mkdir -p build
cd build
cmake .. && make

echo "Running application with arguments: $@"
./app "$@"