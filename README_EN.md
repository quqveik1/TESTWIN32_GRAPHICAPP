# What is this?
This is a graphics engine, an additional layer of abstraction over `Win API`. It is perfect for static, classic desktop applications for Windows.
## Examples of projects completed on this engine:
  - 📈 An application on **my engine**, where by selecting coefficients for a function based on values, I learn about gradient descent and backpropagation of error (very important topics in the era of neural networks). [🔗](https://github.com/quqveik1/GradientDescent)
  - 📉 An application on **my engine**, where I studied splines. [🔗](https://github.com/quqveik1/Splines)
  - ➗ A quadratic equation solver on **my graphics engine**, with documentation. [🔗](https://github.com/quqveik1/QuadraticCalc)
  - 🧮 Initially a project for working with strings in `C++`, but then added a comparison of sorting algorithms, but already on my engine. [🔗](https://github.com/quqveik1/StringSort)
    
# Architecture
The library is based on the OOP principle. Everything is broken down into classes. 
## [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h)
All window management takes place through the main class [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h). This class contains a pointer to the main window and accordingly passes all actions to it. Redrawing windows, handling presses, etc. are the task of the main window (by default, it is recommended to use [`MainWindow`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/MainWindow.h). [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h) provides all the technical part, namely all the APIs, for drawing, handling touches, working with strings, canvases, and brushes.
## Windows
The ultimate parent for all buttons is the [`Window`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Window.h) class. You can override some events, but don't forget to call the parent function.
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
But there is also [`Manager`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Manager.h). The peculiarity of this class is that it can store and display windows inside itself. All the necessary functions for this are already implemented in it.
```cpp
virtual bool addWindow(Window* window, MEM_TYPE _memtype = MT_DYNAMIC);//1 - if the window was successfully added, otherwise - 0
virtual bool addWindow(Window& window, MEM_TYPE _memtype = MT_STATIC); //1 - if the window was successfully added, otherwise - 0
```
A feature of all such windows is the presence of their own canvas, where the actual image of the window/button [`M_HDC`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/M_HDC.h) is stored. They draw inside it in the `draw()` function. And then transfer it in the `print(M_HDC& finalDC)` function to the parent canvas. This is not always fast enough, so there is a class [`Layout`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/Layout.h), which does not have its own canvas and draws directly in the `print(M_HDC& finalDC)` function. There are also things like [`LinearLayout`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/LinearLayout.h) for convenient interface layout.

# Installation and launch
1. Download this repository from `GitHub`. For compiling and running, I recommend choosing `Microsoft Visual Studio 19+`.
2. Create an empty console application.
3. Right-click on the project name in the right menu -> Properties

   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/06330df1-10cd-46d8-a10c-8f8638bccd99" width="400">
   
4. C++ -> General -> Additional include directories -> add the folder with the library
5. 
    <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/e5dda115-2c88-4d01-9aaa-77ce38590cf8" width="400">
    
6. The library requires at least C++17, it is recommended to do as follows. Properties -> C++ -> Command Line -> Enter `/std:c++latest` or `/std:c++17`
   
   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/59b5941d-7c65-42a1-9a9d-eb29d593a53e" width="400">
7. Properties -> Advanced -> Character Set -> Change Use Unicode Character Set -> Use Multi-Byte Character Set

   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/8be747f5-a571-4112-a603-1ebc8dd88178" width="400">

 8. Create a derived class [`AbstactAppData`](https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/blob/main/AbstractApp.h).
    ```C++
    #include <AbstractApp.cpp>           

    struct TestEngine : AbstractAppData
    {
        TestEngine();
        virtual void onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    };

    TestEngine::TestEngine() :
    AbstractAppData(NULL, "..\\TESTWIN32_GRAPHICAPP\\x64\\Release")//be sure to specify this folder if you want the functions for loading and saving images to work.
    {                                                              //don't forget to attach the dll in the folder with the final program and change the path as needed
    }
    
    
    void TestEngine::onCreate(HWND window, UINT message, WPARAM wParam, LPARAM lParam)//here all buttons and windows are created
    {
        MainWindow* mainWnd = new MainWindow(this); 
        setMainManager(mainWnd); // be sure to specify the window without this nothing will work.
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

9. An empty window is created, congratulations! In `Debug` mode, a console will also be displayed, where various details will be printed, if built in `Release` mode, it will disappear.
    
   <img src="https://github.com/quqveik1/TESTWIN32_GRAPHICAPP/assets/64206443/384cb0ec-211f-41da-a570-b23fca510c08" width="400">

