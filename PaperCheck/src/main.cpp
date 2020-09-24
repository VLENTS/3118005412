#include "main.h"

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int MAX = 1e5;

string adr_r,adr_t,adr_a;
//字符集转码
wstring UTF8ToUnicode(const string& str)
{
	wstring ans;
	try {
		wstring_convert< codecvt_utf8<wchar_t> > wcv;
		ans = wcv.from_bytes(str);
	}
	catch (const exception & e) {
		cerr << e.what() << endl;
	}
	return ans;
}
//数据结构优化dp
int dat[MAX + 5];
int bit[MAX + 5];

void build(int n) {
	for (int i = 1; i <= n; i++) 
		dat[i] = bit[i] = 0;
}

void mod(int x, int y,int n) {
	dat[x] = y;
	while (x <= n) {
		bit[x] = dat[x];
		int m = x & -x;
		for (int i = 1; i < m; i <<= 1) 
			bit[x] = max(bit[x], bit[x - i]);
		x += x & -x;
	}
}

int ask(int x) {
	int ans = 0;
	while (x) {
		ans = max(ans, bit[x]);
		x -= x & -x;
	}
	return ans;
}

wstring s, t;
vector<int> pos[MAX + 5];
vector<P> buf;
//文本预处理
void init() {
	for (int i = 1; i <= MAX; i++) pos[i].clear();
	for (int i = 1; i < t.length(); i++)
		pos[t[i]].push_back(i);
}
//核心算法：动态规划
int dp() {
	build(t.length() - 1); buf.clear();
	for (int i = 1; i<s.length(); i++) {
		for (int j : pos[s[i]])
			buf.push_back(P(ask(j - 1) + 1, j));
		if (buf.size()) {
			for (P p : buf)
				if (dat[p.second] < p.first) mod(p.second, p.first, t.length() - 1);
			buf.clear();
		}
	}
	return ask(t.length() - 1);
}
//检查命令行参数
bool check(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Argc Error!\n";
		return false;
	}
	if (_access(argv[1], 00) == -1 || _access(argv[2], 00) == -1) {
		if (_access(argv[1], 00) == -1) cout << "Refer Adress Error\n";
		if (_access(argv[2], 00) == -1) cout << "Test Adress Error\n";
		return false;
	}
	return true;
}
//创建多级目录
void CreatDir(string dir) {
	if (_access(dir.c_str(), 00) == -1)
		CreatDir(dir.substr(0, dir.rfind('\\')));
	else return;
	_mkdir(dir.c_str());
}

double solve(int argc, char* argv[]) {
	clock_t st, et;
	st = clock();
	double ans=-1;
	if (check(argc, argv)) {
		adr_r = string(argv[1]); adr_t = string(argv[2]); adr_a = string(argv[3]);
		//IO
		ifstream refer, test;
		refer.open(adr_r); test.open(adr_t);

		ofstream out;
		CreatDir(adr_a.substr(0, adr_a.rfind('\\')));
		out.open(adr_a);

		s.append(L" "); t.append(L" ");
		string temp;
		while (refer >> temp) s.append(UTF8ToUnicode(temp));
		while (test >> temp) t.append(UTF8ToUnicode(temp));
		if (s.length() <= 1 || t.length() <= 1) {
			et = clock();
			cout << "runtime:" << 1.0 * (0LL + et - st) / CLOCKS_PER_SEC << "s\n";
			return ans;
		}
		//核心算法处理
		init(); ans = 100.0 * dp() / (t.length() - 1);
		out << fixed << setprecision(3) << ans << "%\n";
		refer.close(); test.close(); out.close();
	}
	et = clock();
	cout << "runtime:" << 1.0 * (0LL + et - st) / CLOCKS_PER_SEC << "s\n";
	return ans;
}

int main(int argc, char* argv[]) {
	double ans = solve(argc, argv);
}