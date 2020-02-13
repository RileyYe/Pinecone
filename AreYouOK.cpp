#include <Windows.h>
#include <string>
using namespace std;
class Page
{
private:
	string url = string();
	const string command = "start ";
	void MouseLeftDown()
	{
		INPUT  Input = { 0 };
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		SendInput(1, &Input, sizeof(INPUT));
	}
	void MouseLeftUp()
	{
		INPUT  Input = { 0 };
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(1, &Input, sizeof(INPUT));

	}

public:
	void Move(int x, int y)
	{
		auto fScreenWidth = (double)(::GetSystemMetrics(SM_CXSCREEN) - 1);
		auto fScreenHeight = (double)(::GetSystemMetrics(SM_CYSCREEN) - 1);
		double fx = x * (65535.0f / fScreenWidth);
		double fy = y * (65535.0f / fScreenHeight);
		INPUT  Input = { 0 };
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
		Input.mi.dx = fx;
		Input.mi.dy = fy;
		SendInput(1, &Input, sizeof(INPUT));
	}
	void Click()
	{
		MouseLeftDown();
		MouseLeftUp();
	}
	void Ctrl(char ch)
	{
		keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(ch, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(ch, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
	}
	void PageDown(int times)
	{
		for (int i = 0; i < times; i++)
		{
			keybd_event(0x28, 0, KEYEVENTF_EXTENDEDKEY, 0);
			keybd_event(0x28, 0, KEYEVENTF_KEYUP, 0);
		}
	}
	void Input(string Str)
	{
		for (auto i : Str)
		{
			keybd_event(i, 0, 0, 0);
			keybd_event(i, 0, 2, 0);
			Sleep(100);
		}
	}
	void Enter()
	{
		keybd_event(0x0d, 0, 0, 0);
		keybd_event(0x0d, 0, 2, 0);
	}
	void Open(string url)
	{
		string temp = command + url;
		system((temp.c_str()));
	}
	void MoveClick(int x, int y)
	{
		Move(x, y);
		Click();
	}
	Page(string url)
	{
		this->url = url;
		string temp = command + url;
		system((temp.c_str()));
	}
};
void progress(string id, string password, int code, string temprature)
{
	string url = "http://eos.suda.edu.cn/default/work/suda/jkxxtb/jkxxcj.jsp";
	Page page = Page(url);
	Sleep(4000);  // 等待网页打开
	page.MoveClick(1200, 460);//学号处
	page.Input(id);
	page.MoveClick(1200, 515); //密码处
	Sleep(500); //必须加Sleep,否则接下来Input会漏字符
	page.Input(password);
	page.Enter();


	/*	第二页面	*/

	Sleep(1500);
	page.Open(url);
	Sleep(5000);
	page.MoveClick(1133, 1034); //体温处
	page.Ctrl('A');
	Sleep(300);
	page.Input(temprature);
	page.MoveClick(1700, 700);
	Sleep(300);
	page.PageDown(15);
	Sleep(800);
	page.MoveClick(415, 105);// 正常
	page.MoveClick(530, 710); //具体地址
	page.Ctrl('A');
	Sleep(200);
	page.Ctrl('C');
	Sleep(200);
	switch (code)
	{
	case 0:
		page.MoveClick(415, 457);
		break;
	case 1:
		page.MoveClick(415, 490);
		break;
	case 2:
		page.MoveClick(415, 527);
		break;
	case 3:
		page.MoveClick(415, 560);
		break;
	case 4:
		page.MoveClick(415, 593);
		break;
	case 5:
		page.MoveClick(415, 628);
		break;
	default:
		exit(-1);
	} 	/*	留校(415,457),
		苏州(415,490),
		江苏省内其他地区（415，527）
		湖北(415,560),
		温州……(415,593),
		其他地区(415,628)
	*/

	page.MoveClick(530, 710); //具体地址
	page.Ctrl('V');
	page.MoveClick(462, 760);
	page.MoveClick(915, 960);
}
int main()
{
	progress("1234567890", "SUDA12345678", 2, "36.5");
	/*0.  只针对1920*1080的PC，其他分辨率自行改坐标，
		或者不要尝试！不要尝试！不要尝试！不要尝试！
		1.	progress中四个参数分别表示学号、密码、地区代码、打卡体温；
		2.	password中的小写字母必须大写，暂不支持输入包含大写字母的字符串；
		3.	地区代码如下
				留校 : 0
				苏州 : 1
				江苏省内其他地区 : 2
				湖北 : 3
				温州 : 4,
				其他地区 : 5
		4.如果网络带宽较慢，或者pc性能不足，先测试一下从打开浏览器到载入
		http://eos.suda.edu.cn/default/work/suda/jkxxtb/jkxxcj.jsp 的时间 t1,
		在第96行，将Sleep中的参数改为t1*1000 (参数为毫秒计）；打开
		http://eos.suda.edu.cn/default/work/suda/jkxxtb/jkxxcj.jsp
		记录时间t2,在第106行修改参数。
	*/
}
