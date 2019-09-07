# Long Factorial!

## О проекте:
**Задача**: Необходимо посчитать и вывести на экран большой факториал (например 2000!).  
**Решение**: Длинная арифметика для задачи была реализована двумя способами:  
+ с помощью std::bitset  
+ с помощью std::deque  


## Bitset
Длинная арифметика через bitset реализована следубщим образом. 
Создан bitset на 20032 бита (этого количества достаточно, чтобы вместить 2000!). Арифметические операции были реализованы через битовые.

## Deque
Длинная арифметика через deque реализована следующим образом.  
Создан deque, из 64-битных интов. Deque использовался по причине того, что одновременно был нужен и push_back и push_front.
Число в каждой ячейке дека ограничено 10^18. Это число должно быть степенью десятки для удобного вывода. Должно быть большим, чтобы минимизировать количество операций, и должно быть достаточно маленьким, чтобы сумма двух ячеек не переполняла uint64.  
Далее все арифметические операции выполнялись в системе исчисления с основанием 10^18.  

## Deque vs Bitset
Решение с помощью deque показало себя гораздо лучше по ряду причин.

У реализации через bitset есть только один очевидный плюс. Это возможность выполнять умножение как сумму битовых сдвигов.  
Также у неё есть огромный минус: так как нам требуется вывести полученный факториал на экран, то приходится выполнять перевод из двочиной системы в десятичную. Так как, по очевидным причинам, воспользоваться классическим алгоритмом через умножение мы не можем, я решил производить перевод производя последовательное деление на степень десятки. Полученные остатки от деления сохранялись в вектор, а затем печатались в обратном порядке.  
Деление занимало 99% времени работы программы.  
Но даже без вывода на экран реализация через bitset оказалась медленнее.  
`2000! через deque считается и выводится за  0.3с.`  
`2000! через bitset только считается за  1.1с`  

Deque позволяет печатать полученный факториал очень быстро, поочередно печатая его элементы.  

## Умножение по принципу "разделяй и властвуй"  
Для версии с деком был написан ускоренный алгоритм перемножения членов факториала.  
Мотивом послужило то, что умножение чисел примерно одинаковой величины происходит быстрее, а также желание выполнить, как можно больше операций не прибегая к длинной арифметике.  

Множители факториала складываются в массив, затем перемножаются попарно. Если их значение превысило UINT32_MAX (то есть существует риск переполнения uint64), то их результат откладывается в массив, который уже будет перемножаться при помощи длинной арифметики. В ином случае результат произведения складывается в другой временный массив. Затем данные временного массива перекладываются в основной.  
Эти действия происходят циклически до тех пор, пока в основном массиве есть более 1 элемента. Оставшийся элемент (если он есть) также перекладывается в массив для длинной арифтметики.  
По итогам этого цикла будет получен массив, состоящий только из больших чисел. Они уже перемножаются тем же алгоритмом (За исколючением того, что больше не происходит сравнения с UINT32_MAX и последующего перекладывания).  
В результате, в оставшемся элементе массива и лежит искомый факториал.  

Данная оптимизация значительно ускорила алгоритм:  
+ 0.06с против 0.30с на 2000!
+ 0.90с против 6.90с на 5000!  

## Итоги  
Не исключено, что более оптимальный алгоритм расчёта факториала и более оптимальный алгоритм деления помогли бы значительно ускорить реализацию через bitset. Но написание этих алгоритмов потребовало бы большого количества времени и сил, при том, что реализация с деком пишется быстро и показывает достаточно хороший результат.  
Однако она не идёт ни в какое сравнениу с python, а именно его math.factorial().  
Он считает 10000! за 0.1c, в то время как моя реализация работает за 9.1с.  

## Замеры времени и доказательство правильности
#### Deque
![deque](https://raw.githubusercontent.com/liftchampion/long_factorial/master/deque/deque_factorial.png)
#### Bitset
![bitset](https://raw.githubusercontent.com/liftchampion/long_factorial/master/bitset/bitset_factorial.png)

