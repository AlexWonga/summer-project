#include<iostream>
#include<string>
using namespace std;
class Record
{
	/*ÿ����¼�н���ʱ�䣬�뿪ʱ�䣬������¼ר�е�id*/
private:
	static int idSum;	//id����
	int id;	//������¼����id
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
	friend class controlSystem;	//controlSystemΪ����Ԫ
};
int Record::idSum = 0;	//��̬id����
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
struct Node											//����ͷ���
{
	Record* record;                                   //ָ��record�ĵ�ַ
	Node* next;										//ָ����һ������ָ��
};
class Car
{
private:             
	int state;							//������ż��ͳ�ƽ������
	string plate;	//���ƺ�
public:
	Node* head = NULL;						//�൱������ͷָ��
	Car();
	Car(string);		//���캯����������
	~Car();				//����������ɾ������
	Node* get();
	Node* get(string plate);//��ȡָ�����ƺŵ���,������ָ��
	Node* create_exitNode();
	void create_carlist(long intime);//�����ڵ��޳���ֵ
	string return_carplate() { return plate; }
};
Node*Car:: get() {
	return head;
}
void Car:: create_carlist(long intime) {       //�����ڵ��޳���ֵ 
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
	cout << "����" << plate << "��¼�Ѿ�ɾ��" << endl;
}

class Passage
{
private:
	struct p
	{                             //�µĽṹ��������nextָ��ͳ� 
		Car c;
		struct p* next;
	};
public:
	struct  p* Head, * Tail;
	static int num2;   //��������� 	   
	Passage();
	int getnum2() { return num2; }
	struct p* create(Car& m)       //���ó�����Ϣ ���������Ҫ������Ϣ 
	{
		struct p* Temp=NULL;                          //����ṹ�������泵 
		Temp = (struct p*)malloc(sizeof(struct p));//�����ַ 
		Temp->c = m;
		Temp->next = 0;
		if (!Head) Head = Tail = Temp;   //���ͷָ��Ϊ�㣬������һ���� �����Ϊ�� 
		else                        //�е�һ�����󣬽������ĳ� 
		{
			Tail->next = Temp;
			Tail = Temp;
		}
		num2++;
		return Head;                //���ذ�˳��ĳ���ͷָ�룬�Ƚ��ȳ� 
	}
	Car*enter_parkinglot();//����ڵ�һ��������ͣ����
};
Car* Passage:: enter_parkinglot()       //ɾ���ڵ� ����Ҫ��ӦΪ��˳���ͣ���� 
{
	Car* q;       //������ָ��ָ��ԭ����Head 
	q = &(Head->c);
	Head = Head->next;     //Headָ��ڶ����ڵ�         
	num2--;
	return q;
}
Passage::Passage()
{
	Head = Tail = 0;
};
int Passage::num2 = 0;

class Time {                //TIME��
private:int day, hour, min;
public:
	Time(int a, int b, int c)
	{
		day = a; hour = b; min = c;//ʱ����
	}
	int getday() { return day; }
	int gethour() { return hour; }
	int getmin() { return min; }
	long time_changer(Time& time);
	Time long_to_time(long time);
};
Time Time::long_to_time(long time) {
	day = (((time /60) / 60) / 24);//����
	time -= (((day * 24) * 60) * 60);//ʣ������
	hour = ((time / 60) / 60);
	time -= (hour * 60 * 60);//ʣ������
	min = (time / 60);
	return *this;
}
long Time::time_changer(Time& time) {   //��һ����Ϊ��׼ һ����30�� 720Сʱ 43200���� 
	int day = time.getday();
	int hour = time.gethour();
	int min = time.getmin();
	long totalTime = 0;
	totalTime = (day * 24 * 60 + hour * 60 + min);//�ܹ��ķ�����
	totalTime *= 60;//�ܹ�������
	return totalTime;
}
class ParkingLot {               //parkinglot��
	int cyclePeriod;// �Ʒ�С���� 
	double freePeriod;//���ʱ��
	double standardFee;// ÿ��С�����շѱ�׼ 
	int loopTime;//�Ʒ�ѭ��ʱ�� (Сʱ)
	double maximumPer;//ÿ���Ʒ�ѭ��������շ� 
	int num;//�ܳ�λ��
	int occupied;//ռ�ó�λ��
	Car **cpt;//ָ��car�����ָ��
	Passage *pas;//ͣ�����ı�� 
public:
	Record* rpt;//ָ���¼��ָ��
	int return_lot_num() { return num; }
	Passage* return_Passage() { return pas; }
	Car** return_car() { return cpt; }
	Record* return_record() { return rpt; }
	ParkingLot(int n)//����һ����n����λ��ͣ���� 
	{
		num = n; cyclePeriod = 30; freePeriod = 15; standardFee = 1.5;
		loopTime = 24; maximumPer = 30; rpt = new Record[500000]();  Car* report[50] ; cpt = report;
		for (int i = 0; i < n; ++i)//���´�����ͣ�������еĳ�λ����Ϊ��
		{
			report[i] = NULL;
		}
	}
	void change_cyclePeriod(int a) { //�ı�Ʒ�С����
		cyclePeriod = a;
	}
	void change_freePeriod(double b) {//�ı����ʱ��
		freePeriod = b;
	}
	void change_standardFee(double c) {//�ı��շѱ�׼
		standardFee = c;
	}
	void change_loopTime(int d) {//�ı��շѼƷ�ѭ��
		loopTime = d;
	}
	void change_maximumPer(double e) {//�ı�����շ�
		maximumPer = e;
	}
	double calculate(Time& t1, Time& t2);		//���㲢�����շѶ�

};

double ParkingLot::calculate(Time& t1, Time& t2)
{
	int day_Time = 24 * 60 * (t1.getday() - t2.getday()) + (t1.gethour() - t2.gethour()) * 60 + t1.getmin() - t2.getmin();
	if (day_Time % (loopTime * 60) > maximumPer / standardFee * cyclePeriod)//��ʱ��ȡ�ࣨ�Ʒ�ѭ��ʱ�䣩=����һ���Ʒ�ѭ����ʱ�䣻����շ�/����*����=�Ʒѵ���ʱ�� 
		return (day_Time / (loopTime * 60) + 1) * maximumPer;//����һ������ѭ��ʱ��&���ڼƷ���ʱ��  =����һ������շ� 
	else if (day_Time % (loopTime * 60) > freePeriod)
		return day_Time / (loopTime * 60) * maximumPer + ((day_Time % (loopTime * 60) - 1)/cyclePeriod + 1) * standardFee;
	else return	 (day_Time / (loopTime * 60)) * maximumPer;
}
class ControlSystem //��Ҫ��ɵĹ��� 1.���ļƷѱ�׼ 2.��ѯָ��������¼ 3.��ѯʱ����ڼ�¼
{                   //4.������������ 5.�������¼����Ϣ6.������ͣ����
private:
	ParkingLot mylot;//����Ա�����ͣ����
public:
	ControlSystem(int);
	void change_money();//�ı��շѱ�׼
	void search_car();//����ָ��������¼
	void search_acctime();//��ʱ�����Ǯ��
	void enter_Passage(Car& a);//������
	void enter_parkinglot(long intime);//����ͣ����
	void exit_parkinglot(Car& car,long out_time); //�뿪��¼ʱ�䣬���Ʒ�
	Record* create_record();
};

ControlSystem::ControlSystem(int num):mylot(num) {
	
	cout << "ͣ���������ɹ�!��" << num << "����λ" << endl;
}
Record* ControlSystem::create_record() {
	if (mylot.return_record() == NULL) {
		cout << "Ŀǰ������¼Ϊ�գ���ʼ������¼��Ϣ" << endl;

	}
	return mylot.return_record();
}
void ControlSystem::change_money() {
	cout << "��ӭ���������շѱ�׼�����������趨�շѱ�׼" << endl;
	int freePeriod;//���ĵ����ʱ��
	while (1) {
		cout << "��һ����趨�������õ����ʱ��(����):";
		cin >> freePeriod;
		cout << "���ʱ��Ϊ��" << freePeriod << "����,ȷ����ȷ������Y���������������N";
		string a; 
			cin >> a;
			if (a == "Y")
			{
				mylot.change_freePeriod(freePeriod);//���ú�������ʱ��
				break;
			}
			else if(a =="N")
			{
				cout << "�����������ʱ��" << endl;
				continue;
			}
			else {
				cout << "������������������ʱ��" << endl; 
				continue;
			}
	}
	int cyclePeriodx;//�¼Ʒ�����
	while (1) {
			cout << "�ڶ�����趨�������õļƷ�����(����):";
			cin >> cyclePeriodx;
			cout << "�Ʒ�����Ϊ��" << cyclePeriodx << "����,ȷ����ȷ������Y���������������N";
			string a;
			cin >> a;
			if (a == "Y")
			{
				mylot.change_cyclePeriod(cyclePeriodx);//���ú�����������
				break;
			}
			else if (a == "N")
			{
				cout << "�������üƷ�����" << endl;
				continue;
			}
			else {
				cout << "��������������üƷ�����" << endl;
				continue;
			}
	}
	double standardFeex;//�����ڼƷѱ�׼
	while (1) {
		cout << "��������趨�������õļƷ�����(Ԫ):";
		cin >> standardFeex;
		cout << "�����ڼƷѱ�׼Ϊ��" << standardFeex << "Ԫ,ȷ����ȷ������Y���������������N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_standardFee(standardFeex);//���ú������������ڼƷѱ�׼
			break;
		}
		else if (a == "N")
		{
			cout << "�������������ڼƷѱ�׼" << endl;
			continue;
		}
		else {
			cout << "��������������������ڼƷѱ�׼" << endl;
			continue;
		}
	}
	int loopTime; //�Ʒ�ѭ��ʱ��
	while (1) {
		cout << "��������趨�������õļƷ�ѭ��ʱ��(Сʱ):";
		cin >> loopTime;
		cout << "�Ʒ�ѭ��ʱ��Ϊ��" << loopTime << "Сʱ,ȷ����ȷ������Y���������������N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_loopTime(loopTime);//���ú������ļƷ�ѭ��ʱ��
			break;
		}
		else if (a == "N")
		{
			cout << "�������üƷ�ѭ��ʱ��" << endl;
			continue;
		}
		else {
			cout << "��������������üƷ�ѭ��ʱ��" << endl;
			continue;
		}
	}
	double maximumPer;//ÿ���Ʒ�ѭ��ʱ�������շ�
	while (1) {
		cout << "��������趨�������õ�ÿ���Ʒ�ѭ��ʱ�������շ�(Ԫ):";
		cin >> maximumPer;
		cout << "����շ�Ϊ��" << maximumPer<< "Ԫ,ȷ����ȷ������Y���������������N";
		string a;
		cin >> a;
		if (a == "Y")
		{
			mylot.change_maximumPer(maximumPer);//���ú�������ÿ���Ʒ�ѭ��ʱ�������շ�
			break;
		}
		else if (a == "N")
		{
			cout << "������������շ�" << endl;
			continue;
		}
		else {
			cout << "�������������������շ�" << endl;
			continue;
		}
	}
	cout << "���óɹ�!" << endl;
}
void ControlSystem::enter_Passage(Car& a) {//������
	mylot.return_Passage()->create(a);
}
void ControlSystem::enter_parkinglot(long intime) {//����ͣ����
	int flag = 0;//�жϳ�λ�ǲ�������
	for (int i = 0; i < mylot.return_lot_num(); i++) {
		flag++;
		if (mylot.return_car()[i] == NULL) {
			mylot.return_car()[i] = mylot.return_Passage()->enter_parkinglot();//ͣ������ָ��ָ�����ڵ�һ����
			mylot.return_car()[i]->create_carlist(intime);
			cout << "�����ɹ�����ͣ����,��λΪ:" << i + 1 << endl;
			break;
		}
	}
	if (flag == mylot.return_lot_num() - 1)
	{
		cout << "��λ�������������ܽ���" << endl;
	}
}
void ControlSystem::exit_parkinglot(Car& car,long out_time) {//�뿪��¼ʱ��
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
	//�շ�
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