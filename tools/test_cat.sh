#! /bin/bash

if [ -e ~/s21_cat ]
	then
		echo ""
	else 
		echo "Для начала соберите проект: make"
		exit
fi

echo "Запуск тестирования новой утилиты s21_cat..."
read -p "Введите файл, на котором будет происходить тестирование: " test_file

test_file=$(echo $test_file | cut -f 1 -d ' ')

if [ -e $test_file ]
	then
		echo ""
	else
		echo "Такого файла не существует, программа завершает свою работу..."
		exit 0
fi

file_s21="out21cat.txt"
file_cat="outcat.txt"

n=1
succ=0
fail=0
for flag in "b" "e" "n" "s" "t" "v" "sE" "T" "veb" "enssv" "ETsvb" "sbetvET"
	do 
		echo -ne "TEST $n. Flag = $flag\t:"
		~/s21_cat -$flag $test_file > $file_s21 
		cat -$flag $test_file > $file_cat

		result=$(diff $file_s21 $file_cat)
		len=${#result}
		if [[ len -eq 0 ]]
			then 
				echo -e  "\033[32m" SUCCESFULL" \033[0m"
				succ=$((succ + 1))
			else 
				echo -e "\033[31m" "   FAIL" "\033[0m"
				fail=$((fail + 1))
		fi
		
		# echo $result
		n=$((n + 1))
	done

percent=$(($((succ * 100)) / $((succ + fail))))
echo ""
echo "Успехов: $succ, неудач: $fail"
echo "Прохождение теста: $percent%"

rm $file_s21
rm $file_cat
echo "Тесты завершены!"
exit 0 
