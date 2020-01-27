#include<iostream>
#include<list>
#include<iterator>
#include<utility>
#include<vector>
#include<unordered_map>
#include<map>
#include<queue>
#include<fstream>
using namespace std;

class Driver
{
	public:
	string dname;
	string vehicleNum;
	long int phoneNum;

	public:
	void setDriver(string name,long int phn,string vnum)
	{ dname=name;
		vehicleNum=vnum;
		phoneNum=phn;
	}
	void display()
	{
		cout<<dname<<"    "<<vehicleNum<<"      "<<phoneNum<<endl;
	}
};

struct Vertex
{ bool visited;
	string placeName;
	int driverCount;
	queue<Driver> driverQ;
	multimap<double, Vertex> links;
	/*pointers to the files that have the driver details */
	string name;
	string phn;
	string vnum;

	void getDriverDetails(ifstream &nFile,ifstream &pFile,ifstream &vFile)
	{ driverCount=3;
		Driver temp;
		for(int i=0;i<3;i++)
		{
		getline(nFile,name);
		pFile>>phn;
		getline(vFile,vnum);
		//temp.setDriver(name,phn,vnum);
		//temp.display();
		driverQ.push(temp);
		}
	}




};
void print_queue(queue<Driver> q)
{
	Driver temp;
	while (!q.empty())
	{
		temp=q.front();
		temp.display();
		cout<<endl;
		q.pop();
	}
	cout << endl;
}
class Graph
{ int noOfNodes;
	map<string, Vertex> nodes;

	public:
	Graph()
	{    }
	void makeFalse();
	void createGraph(vector<string>placeList);
	void addEdge(string u, string v, double weight);
	double findDist(string dest, string src);
	void calDist(map<string,Vertex>::iterator dest, map<string,Vertex>::iterator src, double &dist,string prev);
	friend void initGraph(Graph&);
	void displayNodes();

};


void Graph:: displayNodes()
{ cout<<endl<<"The nodes are:";
	for(auto it= nodes.begin(); it!=nodes.end(); it++)
	{  cout<<endl<<it->first<<" : "<< it->second.name<<endl;//<<" Linked to: ";
		//for(auto jt= it->second.links.begin(); jt!= it->second.links.end(); jt++)
		//    cout<<": "<<jt->first<<","<<jt->second.name;
		print_queue(it->second.driverQ);
	}
}



vector<string> places={"SHOLINGANALLUR",
	"KARAPPAKKAM",
	"MEDAVAKKAM",
	"VGP GOLDEN BEACH",
	"PALVAKKAM",
	"ALANDUR",
	"GANDHI NAGAR",
	"GUINDY",
	"ADYAR",
	"TEYNAMPET",
	"NANDANAM",
	"TARAMANI",
	"KODAMBAKKAM",
	"VADAPALANI",
	"ARUMBAKKAM",
	"MANDAVELI",
	"MYLAPORE",
	"VELACHERY",
	"ANNA NAGAR",
	"CHENNAI CENTRAL",
	"ANNA UNIVERSITY",
	"INDIAN INSTITUTE OF TECHNOLOGY",
	"ST THOMAS MOUNT",
	"MARINA BEACH",
	"EGMORE",
	"ARAKKONAM",
//	"AMBATTUR",
	"AVADI"};
void initGraph(Graph&G)
{ //createGraph function is called within this friend function
	G.createGraph(places);
	G.addEdge("SHOLINGANALLUR","KARAPPAKKAM",1.91);
	G.addEdge("KARAPPAKKAM","MEDAVAKKAM",5.69);
	G.addEdge("MEDAVAKKAM","VGP GOLDEN BEACH",16.23);
	G.addEdge("KARAPPAKKAM","VGP GOLDEN BEACH",11.08);
	G.addEdge("KARAPPAKKAM","PALVAKKAM",10.34);
	G.addEdge("PALVAKKAM","ALANDUR",10.96);
	G.addEdge("PALVAKKAM","GANDHI NAGAR",5.97);
	G.addEdge("GUINDY","ADYAR",6.9);
	G.addEdge("GUINDY","TEYNAMPET",8.5);
	G.addEdge("GUINDY","NANDANAM",7.0);
	G.addEdge("GUINDY","TARAMANI",7.8);
	G.addEdge("GUINDY","KODAMBAKKAM",6.3);
	G.addEdge("GUINDY","VADAPALANI",6.4);
	G.addEdge("GUINDY","MYLAPORE",7.6);
	G.addEdge("GUINDY","MANDAVELI",6.4);
	G.addEdge("GUINDY","ARUMBAKKAM",9.4);
	G.addEdge("GUINDY","VELACHERY",6.6);
	G.addEdge("GUINDY","ANNA NAGAR",12.2);
	G.addEdge("GUINDY","CHENNAI CENTRAL",15.5);
	G.addEdge("GUINDY","ANNA UNIVERSITY",5.02);
	G.addEdge("ANNA UNIVERSITY","INDIAN INSTITUTE OF TECHNOLOGY",4.26);
	G.addEdge("ANNA UNIVERSITY","VELACHERY",6.3);
	G.addEdge("INDIAN INSTITUTE OF TECHNOLOGY","ST THOMAS MOUNT",7.66);
	G.addEdge("GUINDY","ST THOMAS MOUNT",5.63);

	G.addEdge("ANNA UNIVERSITY","GANDHI NAGAR",2.73);
	G.addEdge("GANDHI NAGAR","MARINA BEACH",8.16);
	G.addEdge("ANNA UNIVERSITY","MARINA BEACH",10.9);
	G.addEdge("MARINA BEACH","EGMORE",6.14);
	G.addEdge("EGMORE","ARAKKONAM",78.1);
	G.addEdge("ARAKKONAM","AMBATTUR",64.1);
	//G.addEdge("AMBATTUR","AVADI",9.3);
	//G.addEdge("AMBATTUR","ANNA NAGAR",8.9);
	G.addEdge("AVADI","CENTRAL",25.0);
	//G.addEdge("GUINDY","ALANDUR",4.81);
	G.addEdge("EGMORE","CENTRAL",2.5);
	//G.displayNodes();
}
void make_empty(queue<Driver> &q)
{
	while(!q.empty())
		q.pop();


}

void copyqueue(queue<Driver> &dest,queue<Driver> src)
{
	while(!src.empty())
	{
		dest.push(src.front());
		src.pop();
	}
}
void Graph:: createGraph(vector<string>placeList)
{
	Vertex temp;
	string name,vnum;
	long int phn;
	ifstream nFile("namesDriver.txt");
	ifstream pFile("phoneNum.txt");
	ifstream vFile("vehiclenum.txt");
	queue<Driver> tq;
	for(auto it=placeList.begin(); it!=placeList.end(); it++)
	{ //add each place from the the vector
		temp.placeName=*it;
		make_empty(temp.driverQ);
		make_empty(tq);
		//initialise visited to false
		temp.visited=false;
		//cout<<*it<<endl;
		//gets the details of drivers
		//temp.getDriverDetails(nameFile,phnFile,vFile);
		for(int i=0;i<3;i++)
		{


			//	print_queue(temp.driverQ);
			Driver d;
			if(nFile.eof()||vFile.eof() || pFile.eof())
				return ;
			getline(nFile,name);
			pFile>>phn;
			getline(vFile,vnum);
			d.dname=name;
			d.phoneNum=phn;
			d.vehicleNum=vnum;
			//d.display();
			tq.push(d);
			//print_queue(tq);
		}
		//make_empty(temp.driverQ);
		copyqueue(temp.driverQ,tq);
		//inputting details into a pair
		pair<string, Vertex> P1;
		P1.first=temp.placeName;
		P1.second=temp;

		//inserting pair into the nodes
		nodes.insert(P1);

	}
}


void Graph::addEdge(string u, string v, double weight)
{   map<string, Vertex>::iterator i,j;
	i=nodes.find(u);
	j=nodes.find(v);
	if(i== nodes.end() || j==nodes.end())
		return;
	pair<double, Vertex> P1;
	P1.first=weight;
	P1.second=j->second;
	i->second.links.insert(P1);
	P1.second=i->second;
	j->second.links.insert(P1);

}
void Graph::makeFalse()
{
	for(auto it=nodes.begin();it!=nodes.end();it++)
	{
		it->second.visited=false;
		for(auto jt=it->second.links.begin();jt!=it->second.links.end();jt++)
			jt->second.visited=false;
	}
}

double Graph:: findDist(string dest, string src)
{

	auto jt=nodes.find(dest);
	auto it=nodes.find(src);
	if(it== nodes.end() || jt==nodes.end())
		return -1;
	if(it->second.driverQ.empty())
	{
		cout<<"Sorry! All vehicles are full "<<endl;
		return 0.0;
	}
	cout<<endl<<"***Your ride is arriving***"<<endl;
	cout<<"---DRIVER DETAILS---"<<endl;
	Driver onduty=it->second.driverQ.front();
	it->second.driverQ.pop();
	jt->second.driverQ.push(onduty);

	onduty.display();
	double sum=0.0;
	cout<<"**THE ROUTE**"<<endl;
	calDist(jt,it,sum,src);
	cout<<dest<<endl;
	return sum;
}

	void Graph:: calDist(map<string,Vertex>::iterator dest,map<string,Vertex>::iterator src, double &dist,string prev)
{ if(dest==src)
	return;
	if(!src->second.visited)
	{
		cout<<src->first<<"->";
		//marking source node as visited
		src->second.visited=true;
		//checking if destination is contained within the links of the source and if so, found
		for(auto j=src->second.links.begin(); j!=src->second.links.end(); j++)
			if(j->second.placeName==dest->first)
			{ dist+=j->first;
				return;
			}
		//if destination is not a part of source's links then analyzing the links of the source
		auto i=src->second.links.begin();
		//if any of the links contain a link to the source, its nullified to prevent cycles
		while(i!=src->second.links.end())
		{ if(i->second.placeName==prev)
			i->second.visited=true;
			i++;
		}
		//checking for the first viable link
		i=src->second.links.begin();
		while(i->second.visited==true)
		{ i++;
		}
		dist+= i->first;
		auto sr=nodes.find(i->second.placeName);
		calDist(dest,sr,dist,src->first);
	}
}

double findFare(double d)
{
	if(d==0.0)
		return 0.0;

	else if(d<=15.0)
	{
		return d*8.0;
	}
	else if(d>15)
	{
		double cost=0.0;
		cost=15*8.0;
		d-=15.0;
		cost+=d*14.0;
		return cost;
	}
}



int main()
{ Graph G;
	initGraph(G);
	string src,dest;
	int s,d,i=1;
	int ch=0;
	while(ch!=2)
	{	
		cout<<endl<<"**Enter your choice**"<<endl;
		cout<<"1.Ride Now \n2.Exit "<<endl;
		cout<<"**Your choice "<<":";
		cin>>ch;
		G.makeFalse();
		if(ch==1)
		{
			i=1;
			for(auto it=places.begin();it!=places.end();it++,i++)
			{
				cout<<i<<"."<<*it<<endl;

			}

			cout<<endl<<"* ENTER PICK-UP POINT: ";
			cin>>s;
			while(s>27)
			{	cout<<endl<<"* ENTER PICK-UP POINT FROM THE ABOVE LIST: ";
				cin>>s;
			}
			i=1;
			for(auto it=places.begin();it!=places.end();it++,i++)
			{
				cout<<i<<"."<<*it<<endl;
			}
			cout<<endl<<"* ENTER DROP POINT: ";
			cin>>d;
			while(d>27)
			{	cout<<endl<<"* ENTER DROP POINT FROM THE ABOVE LIST: ";
				cin>>d;
			}
			if(s==d)
			{	cout<<endl<<"**Please Enter a different Source and Destination to avail services."<<endl;
				continue;
			}
			src=places.at(s-1);
			dest=places.at(d-1);
			cout<<endl<<"**PICK UP LOCATION :"<<src<<endl;
			cout<<"**DROP AT :         "<<dest<<endl;

			double distance=G.findDist(dest,src);
			if(distance==-1)
			{
				cout<<endl<<"Sorry..Can't find place"<<endl;
				return -1;
			}
			cout<<distance<<endl;
			double cost=findFare(distance);
			cout<<endl<<"** Your bill"<<endl;
			cout<<"** Rupees   "<<cost<<endl;
		}
	}

	if(ch==2)
		cout<<endl<<"****----THANK YOU FOR AVAILING OUR SERVICES----****\n"<<endl;
  return 0;
}
