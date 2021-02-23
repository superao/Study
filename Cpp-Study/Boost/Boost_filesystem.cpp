#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;

int main()
{ 
  // 定义当前路径下的 path 对象
  boost::filesystem::path path("./");
  
  // 构造目录迭代器，遍历所有普通文件
  boost::filesystem::directory_iterator fbegin("/home/superao");
  boost::filesystem::directory_iterator fend;
  for(; fbegin != fend; ++fbegin)
  {
    // 当前文件名称(带完整路径) / 获取当前路径
    string filename = fbegin->path().string();
    
    // 判断当前文件是否为一个文件夹
    if(boost::filesystem::is_directory(filename))
    {
      continue;
    }
    // 获取当前文件大小(只能获取非目录文件大小)
    uint64_t size = boost::filesystem::file_size(filename);
    cout << "文件名称:" << filename << "文件大小:" << size << endl;
  } 

  // 构造递归目录迭代器，遍历路径下的所有文件
  boost::filesystem::recursive_directory_iterator rbegin("/home/superao");
  boost::filesystem::recursive_directory_iterator rend;
  for(; rbegin != rend; ++rbegin)
  {
    string fname = rbegin->path().string();
    // 判断当前文件是否是一个普通文件
    if(boost::filesystem::is_regular_file(fname))
    { 
      // 获取当前文件大小
      uint64_t size = boost::filesystem::file_size(fname);
      cout << "文件名:" << fname << "文件大小:" << size << endl;
    }
    else 
    {
      cout << "文件名:" << fname << endl;
    }
  }

  // 判断当前文件是否存在(必须传入文件的绝对路径)
  if(boost::filesystem::exists("/home/superao/c++"))
  {
    cout << "该文件存在" << endl;
  }
  else 
  {
    cout << "该文件不存在" << endl;
  }
 
  // 创建一个 path 对象并赋初值 
  boost::filesystem::path file("/home/superao/c++/oop/Date.cpp");
  // 获取当前文件的文件名(不带路径)
  cout << "文件名为: " << file.filename().string() << endl;
  // 获取当前文件的文件名(不包含后缀名)
  cout << "文件名为: " << file.stem().string() << endl;
  // 获取当前文件的后缀名
  cout << "后缀名为: " << file.extension() << endl;
  // 获取文件的最后一次修改事件
  cout << "最后一次修改时间:" << last_write_time(file) << endl;

  // 后续函数用到在进行查找
  // https://blog.csdn.net/flyingleo1981/article/details/18596267

  return 0;
}
