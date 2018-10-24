/*
 * c++程序调用python函数的简单示例代码
 * 2018/10/22
 * nidongdonggege
 * 
 */ 

#include <iostream>
#include <Python.h>

using namespace std;

int main(int argc, char** argv)
{
  // python函数调用前的初始化函数
  Py_Initialize();

  // 添加python模块的所在路径
  // 需要添加的python模块在哪就添加哪个路径
  PyRun_SimpleStringFlags("import sys",NULL);
  PyRun_SimpleStringFlags("sys.path.append('./libpython/')",NULL);
  
  // 导入python模块文件
  // 声明模块变量
  PyObject* pmodule = NULL;
  // 选择要调用的python模块
  pmodule = PyImport_ImportModule("libpython");
  if(pmodule==NULL)
    cout<<"pmodule is NULL"<<endl;
  
  cout<<"########## 无参函数的调用 ##########"<<endl;
  // 无参数函数的调用
  // 建立并加载指定函数
  PyObject* pfunc1 = NULL;
  // 第一个参数时模块名，第二个是函数名
  pfunc1 = PyObject_GetAttrString(pmodule,"hello");
  // 函数调用
  PyObject_CallObject(pfunc1,NULL);
  
  cout<<"########## 有参函数的调用 ##########"<<endl;
  // 有传入参数，传出参数函数的调用
  // 建立并加载指定函数
  PyObject* pfunc2 = NULL;
  pfunc2 = PyObject_GetAttrString(pmodule,"add_sub");
  // 构造输入参数对象，所使用模块的传入参有几个，参数就设定为几个
  PyObject* args = PyTuple_New(2);
  // 将输入参数转化为python的格式，并合并到上面建立的输入参数对象中
  // 第一个参数是格式，第二个参数是原始参数
  PyObject* args_1 = Py_BuildValue("i",200);
  PyObject* args_2 = Py_BuildValue("i",100);
  PyTuple_SetItem(args,0,args_1);
  PyTuple_SetItem(args,1,args_2);
  // 函数调用
  PyObject* results = PyObject_CallObject(pfunc2,args);
  // 返回参数解析
  int results_1 = 0;
  int results_2 = 0;
  // 第一个参数python调用返回的对象，第二个是需要解析成的对象格式
  // 后面的是存放解析结果的数据
  PyArg_ParseTuple(results,"ii",&results_1,&results_2);
  cout<<results_1<<"  "<<results_2<<endl;
  
  cout<<"########### 类对象的调用 ###########"<<endl;
  // 无参数函数的调用
  // 加载类
  PyObject* pclass = PyObject_GetAttrString(pmodule,"Player");
  // 用加载的类实例化一个对象
  PyObject* pinstance = PyInstance_New(pclass,NULL,NULL);
  // 调用无参函数
  // 第一个参数为类对象，第二个为成员函数名
  PyObject_CallMethod(pinstance,"slamdunk",NULL);
  // 调用无参函数
  // 第一个参数为类对象，第二个为成员函数名，第三个为输入对象格式，后面的时要输入的对象
  PyObject_CallMethod(pinstance,"yell","s","This is Miami!");
  
  // 释放
  Py_DecRef(pfunc1);
  Py_DecRef(pfunc2);
  Py_DecRef(args);
  Py_DecRef(args_1);
  Py_DecRef(args_2);
  Py_DecRef(results);
  Py_DecRef(pclass);
  Py_DecRef(pinstance);
  
  // python函数调用结束时需要调用的函数
  Py_Finalize();
  
  return 0;
}