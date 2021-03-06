# Система управления базами данных AAASQL  
## Сборка проекта  
Зайти в корневую папку проекта и запустить следующую команду:  
```bash
$ make build
```  
В поддиректориях, отражающих названия модулей проекта появятся исполняемые файлы (в случае interface-module запускать предполагается .py файл).  
## Запуск
Для работы нужно запустить следующую команду:  
```bash
$ ./aaasql
```  
## Структура проекта
Каждый модуль можно запускать как отдельно, так и в составе общего проекта.  
Проект имеет следующую структуру:  
`fs-module → intermediate-module → interface-module`  
Модуль интерфейса вызывает промежуточный модуль, который вызывает модуль файловой системы.  
### Взаимодействие с модулями
- Модуль интерфейса предоставляет командную оболочку для ввода запросов на диалекте языка SQL.  
- Промежуточный модуль принимает в стандартный ввод SQL запросы и возвращает ответ в формате json с нужными столбцами и/или результатом.
- Модуль файловой системы принимает и возвращает json-запросы.
## Copyright
###### Алексей Привезенов, Александра Коврова, Андрей Ломовцев
