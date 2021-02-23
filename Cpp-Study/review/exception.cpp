#if 0
#include <iostream>
#include <string>
using namespace std;

void func()
{
	int a = 10;
	int b = 0;

	if (b == 0)
		throw "除0错误！";
	else
		cout << a / b << endl;
}

int main()
{
	try{
		// 这里可能发生异常
		func();
	}
	catch (const char* name)
	{
		cout << "当前异常为: " << name << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}

	system("pause");
	return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
using namespace std;

// 父类的异常体系
class Except{
public:
	Except(string name = "")
		:_name(name)
	{ }

	string what()
	{
		return _name;
	}

private:
	string _name;
};

// 子类的异常体系
class runtime : public Except
{
private:
	string _name;
public:
	runtime(string name)
		:_name(name)
	{ }

	string what()
	{
		return _name;
	}
};

class A
{
public:
	A(int a, int b) throw(bad_alloc)
		:_a(a),
		_b(b)
	{ }

	// 函数的异常规范
	void func() throw(const char*, Except, runtime)   // 此函数一共会抛出三个异常
	{
		if (_a == 0 && _b == 0)
		{
			throw "hahhhahaa!";                // const char*
		}
		if (_a == 0)
		{
			Except e("维加了!!!!!");           // Except
			cout << &e << endl;
			throw e;
		}
		if (_b == 0)
		{
			runtime r("runtime error!");      // runtime
			throw r;
		}
		else
		{
			cout << _a / _b << endl;
		}
	}
private:
	int _a;
	int _b;
};

int main()
{
	try{
		A a(0, 10);
		a.func();
	}
	catch (runtime& e)
	{
		cout << e.what() << endl;
	}
	catch (Except e1)
	{
		cout << &e1 << endl;
		cout << e1.what() << endl;
	}
	catch (...)
	{
		cout << "unknow!" << endl;
	}


	system("pause");
	return 0;
}
#endif

#include <iostream>
#include <string>
using namespace std;

// 服务器开发中通常使用的异常继承体系
class Exception
{
public:
	virtual void what()
	{
		cout << "基类异常描述信息" << endl;
	}
protected:
	string _errmsg;
	int _id;
	// list<StackInfo> _traceStack;
	// ...
};

class SqlException : public Exception
{
public:
	virtual void what()
	{
		cout << "SqlException类异常描述信息" << endl;
	}
};

class CacheException : public Exception
{
public:
	virtual void what()
	{
		cout << "CacheException类异常描述信息" << endl;
	}
};

class HttpServerException : public Exception
{
public:
	virtual void what()
	{
		cout << "HttpServerException类异常描述信息" << endl;
	}
};

int main()
{
	try{
		// server.Start();
		// 抛出对象都是子类对象
		// SqlException e;
		// throw e;
		HttpServerException e;
		throw e;
	}
	catch (Exception& e)     
	{
		// 根据父类的引用可以区分不同子类异常(多态机制)
		cout << typeid(e).name() << endl;
	}
	catch (...)
	{
		cout << "Unkown Exception" << endl;
	}

	system("pause");
	return 0;
}