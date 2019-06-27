#include<iostream>
#include<string>
using namespace std;
class Record
{
	/*每条记录有进入时间，离开时间，该条记录专有的id*/
private:
	static int idSum;	//id总数
	int id;	//本条记录自身id
	long enterTime;
	long exitTime;
	double money;
public:
	void setmoney(double);
	Record() { id = 0, enterTime = 0, exitTime = 0; money = 0; }
	Record(int, long, long ,double);
	long return_entertime();
	double return_money() { return money; }
	void setEnterTime(long enterTime);
	void setExitTime(long exitTime);
	long returnEnterTime();
	long returnExitTime();
	friend class controlSystem;	//controlSystem为其友元
};
int Record::idSum = 0;	//静态id总数
void Record::setmoney(double money) {
	this->money = money;
}
long Record::returnEnterTime() {
	return enterTime;
}
long Record::returnExitTime() {
	return exitTime;
}
long Record::return_entertime() {
	return enterTime;
}
void Record::setEnterTime(long enterTime) {
	this->enterTime = enterTime;
}
void Record::setExitTime(long exitTime) {
	this->exitTime = exitTime;
}
Record::Record(int id, long EnterTime, long exitTime,double money) {
	idSum++;
	this->id = id;
	this->enterTime = EnterTime;
	this->exitTime = exitTime;
	this->money = money;
}
struct Node											//链表头结点
{
	Record* record;                                   //指向record的地址
	Node* next;										//指向下一个结点的指针
};
class Car
{
private:             
	int state;							//根据奇偶性统计进入次数
	string plate;	//车牌号
public:
	Node* head = NULL;						//相当于链表头指针
	Car();
	Car(string);		//构造函数，空链表
	~Car();				//析构函数，删除链表
	Node* get();
	Node* get(string plate);//读取指定车牌号的项,返回其指针
	Node* create_exitNode();
	void create_carlist(long intime);//创建节点无出车值
	string return_carplate() { return plate; }
};
Node*Car:: get() {
	return head;
}
void Car:: create_carlist(long intime) {       //创建节点无出车值 
	if (head == NULL)
	{
		head = new Node;
		head->record = new Record(0,intime,0,0);
		head->next = NULL;
	}
	if (head != NULL)
	{
		Node* q = head; Node* temp = q;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = new Node;
		q->next->record = new Record(0, intime, 0,0);
		q->next->next = NULL;
	}
}
Car::Car() {
	plate = "";
}
Car::Car(string Car_num) {
	this->plate = Car_num;
}

Node* Car::get(string plate) {
	return head;
}
Car::~Car() {
	Node* temp;
	temp = head;
	if (temp->next != NULL)
	{
		Node* q = temp->next;
		temp->next = temp->next->next;
		delete q;
	}
	delete temp;
	head = NULL;
	cout << "车辆" << plate << "记录已经删除" << endl;
}

class Passage
{
private:
	struct p
	{                             //新的结构体里面有next指针和车 
		Car c;
		struct p* next;
	};
public:
	struct  p* Head, * Tail;
	static int num2;   //便道车数量 	   
	Passage();
	int getnum2() { return num2; }
	struct p* create(Car& m)       //引用车辆信息 便道来车需要车的信息 
	{
		struct p* Temp=NULL;                          //申请结构体来保存车 
		Temp = (struct p*)malloc(sizeof(struct p));//分配地址 
		Temp->c = m;
		Temp->next = 0;
		if (!Head) Head = Tail = Temp;   //如果头指针为零，则接入第一辆车 接入后不为零 
		else                        //有第一辆车后，接入后面的车 
		{
			Tail->next = Temp;
			Tail = Temp;
		}
		num2++;
		return Head;                //返回按顺序的车的头指针，先进先出 
	}
	Car*enter_parkinglot();//便道内第一辆车进入停车场
};
Car* Passage:: enter_parkinglot()       //删除节点 不需要车应为按顺序进停车场 
{
	Car* q;       //定义新指针指向原来的Head 
	q = &(Head->c);
	Head = Head->next;     //Head指向第二个节点         
	num2--;
	return q;
}
Passage::Passage()
{
	Head = Tail = 0;
};
int Passage::num2 = 0;

class Time {                //TIME类
private:int day, hour, min;
public:
	Time(int a, int b, int c)
	{
		day = a; hour = b; min = c;//时分秒
	}
	int getday() { return day; }
	int gethour() { return hour; }
	int getmin() { return min; }
	long time_changer(Time& time);
	Time long_to_time(long time);
};
Time Time::long_to_time(long time) {
	day = (((time /60) / 60) / 24);//天数
	time -= (((day * 24) * 60) * 60);//剩的秒数
	hour = ((time / 60) / 60);
	time -= (hour * 60 * 60);//剩的秒数
	min = (time / 60);
	return *this;
}
long Time::time_changer(Time& time) {   //以一个月为基准 一个月30天 720小时 43200分钟 
	int day = time.getday();
	int hour = time.gethour();
	int min = time.getmin();
	long totalTime = 0;
	totalTime = (day * 24 * 60 + hour * 60 + min);//总共的分钟数
	totalTime *= 60;//总共的秒数
	return totalTime;
}
class ParkingLot {               //parkinglot类
	int cyclePeriod;// 计费小周期 
	double freePeriod;//免费时长
	double standardFee;// 每个小周期收费标准 
	int loopTime;//计费循环时间 (小时)
	double maximumPer;//每个计费循环的最高收费 
	int num;//总车位数
	int occupied;//占用车位数
	Car **cpt;//指向car数组的指针
	Passage *pas;//停车场的便道 
public:
	Record* rpt;//指向记录的指针
	int return_lot_num() { return num; }
	Passage* return_Passage() { return pas; }
	Car** return_car() { return cpt; }
	Record* return_record() { return rpt; }
	ParkingLot(int n)//创建一个有n个车位的停车场 
	{
		num = n; cyclePeriod = 30; freePeriod = 15; standardFee = 1.5;
		loopTime = 24; maximumPer = 30; rpt = new Record[500000]();  Car* report[50] ; cpt = report;
		for (int i = 0; i < n; ++i)//将新创建的停车场所有的车位设置为空
		{
			report[i] = NULL;
		}
	}
	void change_cyclePeriod(int a) { //改变计费小周期
		cyclePeriod = a;
	}
	void change_freePeriod(double b) {//改变免费时长
		freePeriod = b;
	}
	void change_standardFee(double c) {//改变收费标准
		standardFee = c;
	}
	void change_loopTime(int d) {//改变收费计费循环
		loopTime = d;
	}
	void change_maximumPer(double e) {//改变最高收费
		maximumPer = e;
	}
	double calculate(Time& t1, Time& t2);		//计算并返回收费额

};

double ParkingLot::calculate(Time& t1, Time& t2)
{
	int day_Time = 24 * 60 * (t1.getday() - t2.getday()) + (t1.gethour() - t2.gethour()) * 60 + t1.getmin() - t2.getmin();
	if (day_Time % (loopTime * 60) > maximumPer / standardFee * cyclePeriod)//总时间取余（计费循环时间）=不足一个计费循环的时间；最高收费/单价*周期=计费的总时间 
		return (day_Time / (loopTime * 60) + 1) * maximumPer;//不足一个计算循环时间&大于计费总时间  =加上一个最高收费 
	else if (day_Time % (loopTime * 60) > freePeriod)
		return day_Time / (loopTime * 60) * maximumPer + ((day_Time % (loopTime * 60) - 1)/cyclePeriod + 1) * standardFee;
	else return	 (day_Time / (loopTime * 60)) * maximumPer;
}
class ControlSystem //需要完成的功能 1.更改计费标准 2.查询指定车辆记录 3.查询时间段内记录
{                   //4.车辆进出管理 5.便道进入录入信息6.创造新停车场
private:
	ParkingLot mylot;//管理员管理的停车场
public:
	ControlSystem(int);
	void change_money();//改变收费标准
	void search_car();//搜索指定汽车记录
	void search_acctime();//按时间查找钱数
	void enter_Passage(Car& a);//进入便道
	void enter_parkinglot(long intime);//进入停车场
	void exit_parkinglot(Car& car,long out_time); //离开记录时间，并计费
	Record* create_record();
};

ControlSystem::ControlSystem(int num):mylot(num) {
	
	cout << "停车场创建成功!有" << num << "个车位" << endl;
}
Record* ControlSystem::create_record() {
	if (mylot.return_record() == NULL) {
		cout << "目前车辆记录为空，开始创建记录信息" << endl;

	}
	return mylot.return_record();
}
void ControlSystem::change_money() {
	cout << "欢迎来到更改收费标准程序，请重新设定收费标准" << endl;
	int freePeriod;//更改的免费时长
	while (1) {
		cout << "第一项，请设定你想设置的免费时长(分钟):";
		cin >> freePeriod;
		cout << "免费时长为：" << freePeriod << "分钟,确定吗？确定输入Y，重新输入请键入N";
		string a; 
			cin >> a;
			if (a == "Y")
			{
				mylot.change_freePeriod(freePeriod);//调用函数更改时间
				break;
			}
			else if(a =="N")
			{
				cout << "重新设置免费时长" << endl;
				continue;
			}
			else {
				cout << "输入错误，重新设置免费时长" << endl; 
				continue;
			}
	}
	int cyclePeriodx;//新计费周期
	while (1) {
			cout << "第二项，请设定你想设置的计费周期(分钟):";
			cin >> cyclePeriodx;
			cout << "计费周期为：" << cyclePeriodx << "分钟,确定吗？确定输入Y，重新输入请键入N";
			string a;
			cin >> a;
			if (a == "Y")
			{
				mylot.change_cyclePeriod(cyclePeriodx);//调用函数更改周期
				break;
			}
			else if (a == "N")
			{
				cout << "重新设置计费周期" << endl;
				continue;
			}
			else {
				cout << "输入错误，重新设置计费周期" << endl;
				continue;
			}
	}
	double standardFeex;//周期内计费标准
	while (1) {
		cout << "第三项，请设定你想设置的计费周期(元):";
		cin >> standardFeex;
		cout << "周期内计费标准为：" << standardFeex << "元,确定吗？确定输入Y，重新输入请键入N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_standardFee(standardFeex);//调用函数更改周期内计费标准
			break;
		}
		else if (a == "N")
		{
			cout << "重新设置周期内计费标准" << endl;
			continue;
		}
		else {
			cout << "输入错误，重新设置周期内计费标准" << endl;
			continue;
		}
	}
	int loopTime; //计费循环时间
	while (1) {
		cout << "第四项，请设定你想设置的计费循环时间(小时):";
		cin >> loopTime;
		cout << "计费循环时间为：" << loopTime << "小时,确定吗？确定输入Y，重新输入请键入N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_loopTime(loopTime);//调用函数更改计费循环时间
			break;
		}
		else if (a == "N")
		{
			cout << "重新设置计费循环时间" << endl;
			continue;
		}
		else {
			cout << "输入错误，重新设置计费循环时间" << endl;
			continue;
		}
	}
	double maximumPer;//每个计费循环时间的最高收费
	while (1) {
		cout << "第五项，请设定你想设置的每个计费循环时间的最高收费(元):";
		cin >> maximumPer;
		cout << "最高收费为：" << maximumPer<< "元,确定吗？确定输入Y，重新输入请键入N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_maximumPer(maximumPer);//调用函数更改每个计费循环时间的最高收费
			break;
		}
		else if (a == "N")
		{
			cout << "重新设置最高收费" << endl;
			continue;
		}
		else {
			cout << "输入错误，重新设置最高收费" << endl;
			continue;
		}
	}
	cout << "设置成功!" << endl;
}
void ControlSystem::enter_Passage(Car& a) {//进入便道
	mylot.return_Passage()->create(a);
}
void ControlSystem::enter_parkinglot(long intime) {//进入停车场
	int flag = 0;//判断车位是不是已满
	for (int i = 0; i < mylot.return_lot_num(); i++) {
		flag++;
		if (mylot.return_car()[i] == NULL) {
			mylot.return_car()[i] = mylot.return_Passage()->enter_parkinglot();//停车场的指针指向便道内第一个车
			mylot.return_car()[i]->create_carlist(intime);
			cout << "汽车成功进入停车场,车位为:" << i + 1 << endl;
			break;
		}
	}
	if (flag == mylot.return_lot_num() - 1)
	{
		cout << "车位已满，车辆不能进入" << endl;
	}
}
void ControlSystem::exit_parkinglot(Car& car,long out_time) {//离开记录时间
	int counter = 0;
	for (int i = 0;; i++)
	{
		if (mylot.rpt[i].returnEnterTime() == 0)
		{
			Node* q = car.get();
			while (q->next != NULL)
			{
				q = q->next;
			}
			q->record->setExitTime(out_time);
			mylot.rpt[i] = *(q->record);
			counter = i;
			break;
		}
	}
	//收费
	long entertime = mylot.rpt[counter].returnEnterTime();
	long exittime = mylot.rpt[counter].returnExitTime();
	Time intime(0, 0, 0); intime.long_to_time(entertime);
	Time outtime(0, 0, 0); outtime.long_to_time(exittime);
	double money;
	money=mylot.calculate(intime, outtime);
	mylot.rpt[counter].setmoney(money);
}
int main()
{
	Car s("9542");
	ControlSystem *a=new ControlSystem(50);
	a->enter_Passage(s);
	a->enter_parkinglot(9854441);
	a->exit_parkinglot(s,984645465);
}