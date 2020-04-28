#!/bin/bash

test -d abc || mkdir abc 
test -d 123 || mkdir 123 
test -d abc123 || mkdir abc123


touch a{a..z}
touch {0..3}{0..9}
touch {a..c}{0..9};


echo "Создал 100 радомных файлов"

for i in $(find -name "[0-9][0-9]"); do
cp $i ./123/
done
echo "---Переместил файлы с циферными названиями в папку 123---"

for i in $(find -name "[a-z][a-z]"); do
cp $i ./abc/
done
echo "---Переместил файлы с буквенными названиями в папку abc---"

for i in $(find -name "[a-z][0-9]"); do
cp $i ./abc123/
done
echo "---Переместил файлы с буквенно-циферными названиями в папку abc123---"










