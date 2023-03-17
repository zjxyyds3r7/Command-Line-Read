# c++�����в�����ȡ
- ��������
  - ��������:1.���� 2.�Ǳ���  
  `enum paramType {
		paramTypeMust, paramTypeOptional
	};`
  - ����Ҫ��: ������'-'��ͷ ����ֵ������'-'��ͷ �ڲ�������'-'
- ���캯��
  - `Param() {}` �޲ι���
  - `Param(vector<string> paramList, paramType pt =paramTypeMust)` ʹ�ò��������Ĭ������
  - `Param(vector<string> paramList, vector<paramType> paramTypeList)` ʹ�ò����������������
- ��Ա���� 
  - `Param* addParam(string param, paramType pt)` ���һ������
  - `vector<string> getParamSet()` ��ȡ���в�����vector
  - `map<string, string> getAllParam()`  ��ȡ���в�����ֵ��map
  - `int loadParam(int argc, char** argv)` ��main�������ݽ����Ĳ�����ȡ���� ���ض�ȡ�����ĸ��� 
    main��������`int main(int argc, char** argv)`
- ʹ��demo  
```
using namespace myParam;
int main(int argc, char** argv) {

	vector<string> paramList = {"par1", "parn"};
	vector<paramType> paramTypeList = {
		myParam::paramTypeMust, 
		myParam::paramTypeOptional
	}; 
	// �����б�Ͳ��������б�

	Param a(paramList, paramTypeList);
	a.addParam("par2", paramTypeOptional);
	a.addParam("par3", paramTypeMust);
	// ��Ӳ���

	a.loadParam(argc, argv);
	// ��ȡ����

	auto i = a.getAllParam();
	// ��ȡ����,ֵ��map
	
	cout << "����,ֵ��map" << endl;
	for (auto [k, v] : i) {
		cout << k << "\t" << v << endl;
	}

	cout << "������������ȡpar1��ֵ:\t" << a["par1"] << endl;
	// �����±������
	
	return 0;
}
```

- ʹ��ʱ��shell  
`.\��Ŀ14 --par1 1 --par3 z-jx -ad -par2 123 -sfa`  
���  
```
Error: The param is undefined:  ad
Error: The param is undefined:  sfa
����,ֵ��map
par1    1
par2    123
par3    z-jx
������������ȡpar1��ֵ:       1
```