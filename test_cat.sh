#! /bin/bash

echo "Запуск тестирования новой утилиты s21_cat..."

if [[ $# -lt 1 ]]
	then 
		echo "Необходимо указать тестовый файл!"
		exit 0
fi 
if [[ $# -gt 2 ]]
	then
		echo "Слишком много аргументов командной строки!"
		exit 0
fi

file_s21="out21cat.txt"
file_cat="outcat.txt"

test_file=$1
n=1
for flag in "b" "e" "n" "s" "t" "v" "sE" "T" "veb" "enssv" "ETsvb" "sbentvET"
	do 
		echo -n "TEST $n. Flag = $flag : "
		./s21_cat -$flag $test_file > $file_s21 
		cat -$flag $test_file > $file_cat

		result=$(diff $file_s21 $file_cat)
		len=${#result}
		echo -n " (len = $len) "
		if [[ len -eq 0 ]]
			then 
				echo -e  "\033[32m" SUCCESFULL" \033[0m"
			else 
				echo -e "\033[31m" "   FAIL" "\033[0m"
		fi
		
		# echo $result
		n=$((n + 1))
	done

rm $file_s21
rm $file_cat
echo "Тесты завершены!"
exit 0 
