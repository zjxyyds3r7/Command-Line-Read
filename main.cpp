#include <iostream>
#include <vector>
#include <map>

using namespace std;


namespace myParam {

	enum paramType {
		paramTypeMust, paramTypeOptional
	};

	map<string, string> errorMsg = {
		{"empty", "Error: Empty param."},
		{"size", "Error: The paramList size is not equal to the paramTypeList size."},
		{"undefined", "Error: The param is undefined:\t"},
		{"absence", "Error: The param value is absence:\t"},
		{"miss", "Error: Missing required parameters:\t"}
	};

	string remove(string s, char d) {
		for (auto it = s.begin(); it < s.end(); it++) {
			if (*it == d) {
				s.erase(it);
				it--;
			}else{
				break;
			}
		}
		return s;
	}
	class Param {

			map<string, pair<string, paramType>> paramMap;

		public:
			Param() {}

			Param(vector<string> paramList, paramType pt = paramTypeMust) {
				for (string i : paramList) {
					try {
						if (i.empty()) {
							throw errorMsg["empty"];
						}
						paramMap[i] = {"", pt};
					} catch (string e) {
						cerr << e << endl;

					}
				}
			}
			Param(vector<string> paramList, vector<paramType> paramTypeList) {
				int n = min(paramList.size(), paramTypeList.size());

				for (int i = 0; i < n; i++) {
					try {
						//if(paramTypeList[i] != paramTypeMust && paramTypeList[i] != paramTypeOptional){
						//	throw "Error: Wrong type of param";
						//}
						if (paramList[i].empty()) {
							throw errorMsg["empty"];
						}
						paramMap[paramList[i]] = {"", paramTypeList[i]};
					} catch (string e) {

						cerr << e << endl;
					}
				}

				try {
					if (paramList.size() != paramTypeList.size()) {
						throw errorMsg["size"];
					}
				} catch (string e) {
					cerr << e << endl;
				}
			}

			Param* addParam(string param, paramType pt) {
				try {
					if (param.empty()) {
						throw errorMsg["empty"];
					}
					paramMap[param] = {"", pt};
				} catch (string e) {
					cerr << e << endl;
				}
				return this;

			}

			vector<string> getParamSet() {
				vector<string> res;
				for (auto [k, v] : paramMap) {
					res.push_back(k);
				}
				return res;
			}

			string help() {
				return "help:";
			}

			string operator[](string a) {
				return paramMap[a].first;
			}

			map<string, string> getAllParam() {
				map<string, string> res;

				for (auto [k, v] : paramMap) {
					if (!v.first.empty()) {
						res[k] = v.first;
					}
				}

				return res;
			}

			int loadParam(int argc, char** argv) {
				int res = 0;
				for (int i = 1; i < argc; i++) {
					try {
						string oldParam = argv[i];
						string param = remove(oldParam, '-');
						if (oldParam == param) {
							continue;
						}

						if (paramMap.find(param) == paramMap.end()) {
							throw errorMsg["undefined"] + param;
						}
						string value = i + 1 < argc ? string(argv[i + 1]) : throw errorMsg["absence"] + param;
						if (value != remove(value, '-')) {
							throw errorMsg["absence"] + param;
						}

						paramMap[param].first = value;
						res++;
					} catch (string e) {
						cerr << e << endl;
					}
				}

				for (auto [k, v] : paramMap) {
					try {
						if (v.second == paramTypeMust && v.first.empty()) {
							throw errorMsg["miss"] + k;
						}
					} catch (string e) {
						cerr << e << endl;
					}
				}
				return res;
			}
	};
}
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
