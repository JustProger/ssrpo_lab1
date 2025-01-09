#!/bin/bash

# Задача compile
compile() {
    echo "Собираем..."
    ./configure
    make
}

# Задача test
test_task() {
    echo "Запускаем тесты..."
    chmod +x test/test*
    test/make-result
    diff test/test-result.sample test/test-result.out
}

# Задача delivery
delivery() {
    echo "Готовим релиз..."
    doxygen doc/Doxyfile.cfg

    echo "Прогоняем сборку..."
    ./configure
    make

    echo "Прогоняем тесты..."
    test/make-result

    echo "Строим отчёт покрытия..."
    lcov -t "lab" -o lab.info -c -d . --no-external
    genhtml -o coverage lab.info

    echo "Деплоим..."
    mv doc/html/ public/
    mv coverage/ public/coverage/
}

# Главная задача, выполняющая три подзадачи
all_tasks() {
    echo "Запуск всех задач последовательно..."
    compile
    test_task
    delivery
    echo "Все задачи завершены."
}

# Проверяем аргументы командной строки
if [ "$1" == "compile" ]; then
    compile
elif [ "$1" == "test" ]; then
    test_task
elif [ "$1" == "delivery" ]; then
    delivery
elif [ "$1" == "all" ]; then
    all_tasks
else
    echo "Usage: $0 {compile|test|delivery|all}"
    exit 1
fi
