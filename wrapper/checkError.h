#pragma once

//传入一个方法作为参数，先执行该方法，执行完毕后再执行 checkError方法 
//  类似C#里协程里yield return 一个迭代器，当其中的方法执行完毕后，在进行下面代码的执行
//也类似unity Dotween里的动画序列

//#ifdef DEBUG//预编译宏
//#define GL_CALL(fun)  fun;checkError();
//#else
#define GL_CALL(fun)  fun;
//#endif
void checkError();