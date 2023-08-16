# Что это?
Это графический движок, дополнительный слой абстракции над `Win API`. Отлично подходит для статических, классических десктопных приложений под Windows.
## Примеры проектов, выполненных на этом движке:
  - 📈 Приложение на **моем движке**, в котором я подбирая коэффициенты к функции по значениям, познаю градиентный спуск и обратное распространение ошибки (очень важные темы в эпоху нейросетей). [🔗](https://github.com/quqveik1/GradientDescent)
  - 📉 Приложение на **моем движке**, на котором я изучал сплайны. [🔗](https://github.com/quqveik1/Splines)
  - ➗ Решатель квадратных уравнений на **моем графическом движке**, с документацией. [🔗](https://github.com/quqveik1/QuadraticCalc)
  - 🧮 Изначально проект по работе со строками в `C++`, но потом прибавилось сравнение алгоритмов сортировки, но уже на моем движке. [🔗](https://github.com/quqveik1/StringSort)
    
# Архитектура
Библиотека основана на приципе ООП. Всё разбито на классы. 
## [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h)
Всё управление окнами происходит через главный класс [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h). Этот класс хранит в себе указатель на главное окно, и соответственно передаёт ему все действия. Перерисовка окон, обработка нажатий и т.п. - задача главного окна(по умолчанию рекомендуется использовать [`MainWindow`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/MainWindow.h). [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h) предоставляет всю техническую часть, собственно все API, для рисования, обработки касаний, работы со строками, холстами и кистями.
## Окна
Конечным родителем для всех кнопок является класс [`Window`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Window.h). Некотоыре события вы можете переопределить, не забудьте про вызов родительской функции в переопределённых функциях.
```cpp
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
Но есть также и [`Manager`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Manager.h). Особенность этого класса: он умеет хранить внутри себя и отображать окна. Все необоходимые для этого функции уже рализованы в нём.
```cpp
virtual bool addWindow(Window* window, MEM_TYPE _memtype = MT_DYNAMIC);//1 - if window was sucsessfully added, otherwise - 0
virtual bool addWindow(Window& window, MEM_TYPE _memtype = MT_STATIC); //1 - if window was sucsessfully added, otherwise - 0
```
Особенностью всех таких окон - наличие собственного холста, где хранится актуальное изображение окна/кнопки [`M_HDC`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/M_HDC.h). Они рисуют внутри него в функции `draw()`. А потом переносят в функции `print(M_HDC& finalDC)` на родительский холст. Это не всегда достаточно быстро, поэтому есть класс [`Layout`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Layout.h), который не имеет собственного холста и рисует сразу в функции `print(M_HDC& finalDC)`. Также присутсвют такие вещи как [`LinearLayout`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/LinearLayout.h), для удобной компоновки интерфейса.

# Установка и запуск
1. Скачайте этот репозиторий с `GitHub`. Для сборки и запуска рекомендую выбрать `Microsoft Visual Studio 19+`.
2. Создайте пустое консольное приложение.
3. Нажмите правой кнопкой мыши по названию проекта в правом меню. -> Properties
   
   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/06330df1-10cd-46d8-a10c-8f8638bccd99" width="400">
   
4. C++ -> General -> Additional include directories -> дорбавьте папку с библиотекой
5. 
    <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/e5dda115-2c88-4d01-9aaa-77ce38590cf8" width="400">
    
6. Библиотеке необоходим минимум С++17, рекомендуется сделать так. Properties -> C++ -> Command Line -> Введите `/std:c++latest` или `/std:c++17`
   
   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/59b5941d-7c65-42a1-9a9d-eb29d593a53e" width="400">
7. Properties -> Advanced -> Character Set -> Поменяйте Use Unicode Character Set -> Use Multi-Byte Character Set

   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/8be747f5-a571-4112-a603-1ebc8dd88178" width="400">

 8. Создайте класс наследник [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h).
    ```C++
    #include <AbstractApp.cpp>           

    struct TestEngine : AbstractAppData
    {
        TestEngine();
        virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    };

    TestEngine::TestEngine() :
    AbstractAppData(NULL, "..\\TESTWIN32_GRAPHICAPP\\x64\\Release")//обязательно укажите эту папку если хотите чтоыб работали фукции загрузки и сохранения картинок.
    {                                                              //незабудьте приложить dll в папке с финальной программой и поменять путь как нужно
    }
    
    
    void TestEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)//тут создаются все кнопки и окна
    {
        MainWindow* mainWnd = new MainWindow(this); 
        setMainManager(mainWnd); // обязательно укажите окно без этого ничего не будет работать.
    }
    ```
    Main.cpp:
    ```C++
    #include "TestEngine.cpp"

    int main()
    {
        TestEngine testEngine;
        testEngine.startApp();
    }
    ```

9. Создано пустое окно, поздравляю! В режиме `Debug` также будет показываться консоль, куда бьудут печаться раные детали, если собрать в режиме `Release`, то оно пропадёт.
    
   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/384cb0ec-211f-41da-a570-b23fca510c08" width="400">


----
- [English](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/README_EN.md)


