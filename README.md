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
Конечным родителем для всех кнопок является класс [`Window`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Window.h). Какие события вы можеет переопредлеить, не забудьте про вызов родителськой функции.
```c++
virtual void draw                 ();//internal draw
virtual void print                (M_HDC& finalDC);//put window to parent dc
virtual int  hitTest              (Vector mp);//1 - hit; 0 - miss | it happens, then parrent window, wish to know if it need to send child window(this window) onClick()
virtual void onClick              (Vector mp) {};
virtual int  onClick              (Vector mp, int button) { return 1; };//1- reacted 0 - ignored ; don't use it
virtual int  mbDown               (Vector mp, int button) { if (rect.inRect(mp)) { app->declareReactionOnMSG(1); }; return 0; };  //1 - left, 2 - right
virtual int  mbUp                 (Vector mp, int button) { return 0; }; //1 - left, 2 - right
virtual int  onDoubleClick        (Vector mp, int button) { return 0; };
virtual int  onKeyboard           (int key) { return 0; };  //just keyboard event(only capital character)
virtual int  onKeyboardChar       (int key) { return 0; };  //character(capital or regular) 
virtual int  onSize               (Vector managerSize, Rect newRect = {}); // return 0 if size didn't changed
virtual int  onMouseMove          (Vector mp, Vector delta) { return 0; };
virtual int  onTimer              (UINT_PTR timerName) { return 0; };// if your window have set timer here you will recieve it
virtual int  onClose              () { return 0; };// if you want to cancel closing you need to return non 0 value
virtual int  onDestroy            () { return 0; };// then destroying send, you are unable to stop it
virtual int  onEnterWindowSizeMove() { return 0; };
virtual int  onExitWindowSizeMove () { return 0; };
virtual int  onDrawEnd            () { validateViewState(); return 1; };//0 if you ignore this message
```
Но есть также и `Manager`
