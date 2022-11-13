# Архитектура вычислительных систем
## Индивидуальное домашнее задание №2
### Вариант 13

### Вишняков Родион Сергеевич 
##### группа БПИ213
###### 12 октября 2022 г.
[![Typing SVG](https://readme-typing-svg.herokuapp.com?color=%2336BCF7&lines=Faculty+of+Computer+science+student)](https://git.io/typing-svg)


Задание: Разработать программу, заменяющую все строчные буквы в заданной ASCII-строке прописными, а прописные буквы — строчными.

### Отчёт
![img](/p1.png)

### 4 балла
•	Приведено решение задачи на C.

Код находится в файле 4.c
Далее в командную строку вводим данные команды для получения искомого ассемблерского файла, а также исполняемого файла.


$gcc -O0 -Wall -fno-asynchronous-unwind-tables 4.c -o 4


$gcc -O0 -Wall -fno-asynchronous-unwind-tables -S 4.c -o 4.s


$gcc 4.s -o

Лишние макросы были убраны за счёт использования аргументов командной строки. 

`gcc -masm=intel -fno-asynchronous-unwind-tables -fno-jump-tables -fno-stack-protector -fno-exceptions -S 4.c`

Необходимые комментарии находятся в 4.s


Файл | Тест           | Результат | Соотвествие 
-----------|----------------|:---------:|------------:
4.c     | abcd    | ABCD |        True | 
4.s     | abcd    | ABCD |        True |
4.c     | abaABA	   | ABAaba |       True      |
4.s     | abaABA   | ABAaba |       True      |
4.c     | MdMa	  | mDmA |      True       |
4.s     | MdMa	  | mDmA |     True        |
4.c     | mmm123mmm	 | MMM123MMM |      True       |
4.s     | mmm123mmm	  | MMM123MMM |     True        |


Представлено полное тестовое покрытие, дающее одинаковый результат на обоих программах.
После тестирования программ можно сделать вывод, что работа программы является корректной и эквивалентной.


Для проверки ввести команды:
#### gcc 4.s
#### gcc ./a.out

### 5	баллов
В дополнение к требованиям на предыдущую оценку

•	В реализованной программе я использовал функции с передачей данных через параметры.
![img](/p2.png)

Измененная программа была сохранена в файле 5.c

Функциональность:


get_string()  - функция принимает на вход указатели на len(переменная в которую будет записан результат подсчета длины строки) и test(переменная, которая показывает корректность ввода). Функция возвращает указатель на начало введенной строки.


change() - функция принимает на вход строку, над которой производятся изменения и длина строки.


Комментарии:
В ассемблерскую программу при вызову функций были добавлены комментарии, которые описывают передачу фактических параметров и перенос возвращаемого результат, в случае когда функция ничего не возвращает был добавлен комментарий (void)
В этой программе не использовались формальные параметры.

### 6 баллов
В дополнение к требованиям на предыдущую оценку
Я сделал рефакторинг программы на ассемблере за счет максимального использования регистров процессора. Измененная программа сохранена в файле “6.s”. В основном были использованы регистры: r12, r13, r14, r15. В процессе рефакторинга соотвественно были изменены команды (например movl -> movq), а также были изменены регистры, которые контактировали с “новыми” регистрами (например: movl eax, -24(%rbp) -> movq rax, r12).
При работе с char, символы сохраняются в стек и занимают 1 байт, в связи с этим необходимо вручную выравнить стек по ходу работы.
Также были добавлены комментарии, которые поясняют использование регистров в соответсвии с переменными из исходной программы на С.

Файл | Тест           | Результат | Соотвествие
-----------|----------------|:---------:|------------:
5.c     | asd 1 asd    | ASD 1 ASD |        True | 
5.s     | asd 1 asd    | ASD 1 ASD |        True |
6.s     | asd 1 asd	   | ASD 1 ASD |       True      |
5.c     | ilovebpi223    | ILOVEBPI223 |       True      |
5.s     | ilovebpi223 	   | ILOVEBPI223 |      True       |
6.s       | ilovebpi223 	   | ILOVEBPI223 |     True        |
5.c     | aSa1aSa	  | AsA1AsA |      True       |
5.s     | aSa1aSa		  | AsA1AsA |     True        |
6.s     | aSa1aSa		  | AsA1AsA |     True        |

Представлено полное тестовое покрытие, дающее одинаковый результат на всех программах.


Для проверки ввести команды:
#### gcc 6.s
#### gcc ./a.out

#### Размер
 - 5.s программа полученная после компиляции: 222 lines (222 sloc) 4.09 KB
 - 6(1).s программа полученная после рефакторинга: 241 lines (241 sloc)  3.97 KB
 
### 7 баллов
В дополнение к требованиям на предыдущую оценку

Реализация программы на ассемблере, полученной после рефакторинга, в виде двух единиц компиляции (6-1.s & 6-2.s).
Я разделил код ассемблера на файл с функциями и файл с main. Далее скомпилировал полученные файлы и запустил файлы с исходными данными и файла для вывода результатов с использованием аргументов командной строки.


Для проверки ввести команды:
#### gcc 6-1.s 6-2.s
#### gcc ./a.out


![img](/p3.png)
Далее я переделал файл Си, чтобы он брал и записывал данные из вводимых в командную строку файлов. (int argc, char * argv[]) измененная программа была сохранена под названием “7.c”
После чего эта программа была скопилирована в main3.s и разделена на файлы 7-1.s и 7-2.s, в которых были функции и main соответсвенно.


Для проверки ввести команды:
#### gcc 7-1.s 7-2.s
#### gcc ./a.out input.txt output.txt


![img](/p5.png)

### 8 баллов
В дополнение к требованиям на предыдущую оценку

В программу была добавлена функция генератора случайных наборов данных, расширяющих возможности тестирования, а также подключение генератора к программе с выбором в командной строке варианта ввода данных. (./a.out -r).
Также было реализовано расширение анализа командной строки для выбора способа порождения исходных данных.
#### if argv[1] == "-r") -> get_random_string
#### else if argv[1] == "-h" -> help вывод всех ключей с обозначениями
#### else if argv[1] == "-f" -> input.txt output.txt
#### else if argv[1] == "-s" -> ввод из командной строки
Также модификация программы на C и программы на ассемблере, полученной после рефакторинга, для проведения сравнения на производительность.
#### start = clock()
#### end = clock()
#### (double)(end - start) / (CLOCKS_PER_SEC)
Для замедления работы до секунды, я постввил цикл на 10000 повторов в функции change, также поставил больший диапазон генерирования рандомных чисел и увеличил количество элементов в массиве.
### Все изменения были записаны в файл 8.c
![img](/p6.png)

После чего провел несколько вариантов тестовых прогонов.
#### Пришел к выводу, что программа после рефакторинга работает быстрее.
### 9 баллов

### Сравнение и анализ

#### Размер 
Размер .s файла полученного после компиляции с помощью флагов *-masm=intel -fno-asynchronous-unwind-tables -fno-jump-tables -fno-stack-protector -fno-exceptions -Os* состовляет 326 строк, в то время когда с оптимизацией -Ofast 402 строки. 

#### Время 
в следующем пункте проводится подробное сравнение всех программ.

### 10 баллов

#### Выполнено:
 - исходный код на си, скомпилированный с разными опциями, шаги рефакторинга ассемблероного кода пропущены т.к. писалась программа на ассемблере с нуля.
 - сравнительные тесты показывающие скорость работы обоих программ.
 - генератор случайных чисел с указанием границ
 - ввод-вывод из файла
 - измерение времени работы программы
 - текст программы на языке ассемблера без использования си функций
 - ассемблерный код содержит поясняющие комментарии

#### Что где лежит?
В папке "10" находятся все необходимые файлы на эту оценку.
В "10" -> "lib" можно найти 
 - array.s (работа с массивами)
 - io.s (input & output)
 - str.s (работа со строками)
 - time.s (Измерение времени выполнения функции change)
 - rand.s (Рандомная генерация строки)
В "10" -> "main.s" можно найти программа написанная "вручную"

#### Как запустить?
![img](/p8.png)
Для компиляции и построения программы был написан Makefile, введи последовательно эти команды:
*make compile*
*make build*
![img](/p9.png)
Далее необходимо ввести *./main _*, на месте _ введите необходимый ключ:
 - ключ -с (ввод искомой строки из командой строки)
 - ключ -f input.txt output.txt (ввод из входного файла и запись результата в выходной файл)
 - ключ -r N (где N размер рандомной строки, генерируется рандомная строка размером N)
 
#### После проведения тестового покрытия пришел к ввыводу, что результаты тестов совпадают с программами, реализованой на оценку 8 и раньше.
![img](/p7.png)


#### Размер 
Размер .s файла полученного после компиляции с помощью флагов *-masm=intel -fno-asynchronous-unwind-tables -fno-jump-tables -fno-stack-protector -fno-exceptions -Os* состовляет 326 строк, в то время когда с оптимизацией -Ofast 402 строки. В то же время размер программы написанной "вручную" состовляет 320 строк в main файле + 560 строк в вспомогательных файлах, которые лежат в папке lib. Но размер ассемблер файла состовляет 8,7K, а у программы на си 13K, даже учитывая флаг -Os.
