# c++命令行参数读取
- 基本概念
  - 参数类型:1.必须 2.非必须  
  `enum paramType {
		paramTypeMust, paramTypeOptional
	};`
  - 参数要求: 参数以'-'开头 参数值不能以'-'开头 内部可以有'-'
- 构造函数
  - `Param() {}` 无参构造
  - `Param(vector<string> paramList, paramType pt =paramTypeMust)` 使用参数数组和默认类型
  - `Param(vector<string> paramList, vector<paramType> paramTypeList)` 使用参数数组和类型数组
- 成员函数 
  - `Param* addParam(string param, paramType pt)` 添加一个参数
  - `vector<string> getParamSet()` 获取所有参数的vector
  - `map<string, string> getAllParam()`  获取所有参数和值的map
  - `int loadParam(int argc, char** argv)` 从main函数传递进来的参数获取参数 返回读取参数的个数 
    main函数定义`int main(int argc, char** argv)`
- 使用demo  
```
using namespace myParam;
int main(int argc, char** argv) {

	vector<string> paramList = {"par1", "parn"};
	vector<paramType> paramTypeList = {
		myParam::paramTypeMust, 
		myParam::paramTypeOptional
	}; 
	// 参数列表和参数类型列表

	Param a(paramList, paramTypeList);
	a.addParam("par2", paramTypeOptional);
	a.addParam("par3", paramTypeMust);
	// 添加参数

	a.loadParam(argc, argv);
	// 读取参数

	auto i = a.getAllParam();
	// 获取参数,值的map
	
	cout << "参数,值的map" << endl;
	for (auto [k, v] : i) {
		cout << k << "\t" << v << endl;
	}

	cout << "重载运算符后读取par1的值:\t" << a["par1"] << endl;
	// 重载下标运算符
	
	return 0;
}
```

- 使用时的shell  
`.\项目14 --par1 1 --par3 z-jx -ad -par2 123 -sfa`  
结果  
```
Error: The param is undefined:  ad
Error: The param is undefined:  sfa
参数,值的map
par1    1
par2    123
par3    z-jx
重载运算符后读取par1的值:       1
```