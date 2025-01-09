#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # Без цвета (сброс)

delete_all() {
    echo -e "${YELLOW}Удаление...${NC}"
    rm -rf public
}

# Задача compile
compile() {
    echo -e "${GREEN}Собираем...${NC}"
    ./configure
    make
}

# Задача test
test_task() {
    echo -e "${GREEN}Запускаем тесты...${NC}"
    chmod +x test/test*
    test/make-result
    diff test/test-result.sample test/test-result.out
}

# Задача delivery
delivery() {
    echo -e "${GREEN}Готовим релиз...${NC}"
    doxygen doc/Doxyfile.cfg

    delete_all

    compile

    test_task

    echo -e "${GREEN}Строим отчёт покрытия...${NC}"
    lcov -t "lab" -o lab.info -c -d . --no-external
    genhtml -o coverage lab.info

    echo -e "${GREEN}Деплоим...${NC}"
    mv doc/html/ public/
    mv coverage/ public/coverage/
}

# Главная задача, выполняющая три подзадачи
all_tasks() {
    echo -e "${YELLOW}Запуск всех задач последовательно...${NC}"
    compile
    test_task
    delivery
    echo -e "${GREEN}Все задачи завершены.${NC}"
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
