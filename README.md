# Что это?
Это графический движок, дополнительный слой абстракции над `Win API`. Отлично подходит для статических, классических десктопных приложений под Windows.
## Примеры проектов, выполненных на этом движке:
  - 📈 Приложение на **моем движке**, в котором я подбирая коэффициенты к функции по значениям, познаю градиентный спуск и обратное распространение ошибки (очень важные темы в эпоху нейросетей). [🔗](https://github.com/quqveik1/GradientDescent)
  - 📉 Приложение на **моем движке**, на котором я изучал сплайны. [🔗](https://github.com/quqveik1/Splines)
  - ➗ Решатель квадратных уравнений на **моем графическом движке**, с документацией. [🔗](https://github.com/quqveik1/QuadraticCalc)
  - 🧮 Изначально проект по работе со строками в `C++`, но потом прибавилось сравнение алгоритмов сортировки, но уже на моем движке. [🔗](https://github.com/quqveik1/StringSort)
    
# Архитектура
Приложение основано на ООП. 
## [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h)
Всё управление окнами происходит через главный класс [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h). Этот класс хранит в себе указатель на главное окно, и соотвенно передаёт ему все действия. Перерисовка картинки, обработка нажатий - задача главного окна(по умолчанию рекомендуется использовать [`MainWindow`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/MainWindow.h). [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h) предоставляет всю техническую часть, собственно все API, для рисования, обработки касаний, работы со строками, холстами и кистями.
## Окна
Конечным родителем для всех кнопок является класс [`Window`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Window.h)
