# Настройка сборки
## Настройка сборки Windows

* Зайти в настройки сборки проекта
* Добавить особый шаг сборки вида
```
xcopy
/s /e /i /y %{sourceDir}\Resources\HSK %{buildDir}\HSK
```

# Windows Deploy

* Скопировать в целевую папку исполняемый файл.
* Выполнить команду вида:
```
c:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe ForeignLanguageTrainer_2.exe
```
