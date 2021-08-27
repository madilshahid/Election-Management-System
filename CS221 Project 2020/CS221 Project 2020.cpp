#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<bits/stdc++.h>
using namespace std;
int showMenu_main();
class Party;
string Generate_UserName(int n);
void printShashkaLine(char element, int noOfTimes);

void Election_commission();
int Election_Management_Menu();

void party_login();
int party_login_menu();

void Voter_login();
int Voter_login_Menu();



class Election_Management //Election Management
{
	string user_name;
	string pasword;
	Election_Management *next;
	Election_Management *prev;
		public:
			Election_Management();//constructor for header node; will be called by default
			Election_Management(string name, string Pasword); // costructor for new node
			void generate_linked_list();
			void save_file();
			void change_pass();
			bool sign_in(string pass);
	
};
Election_Management::Election_Management()
{
	this->next=this;
	this->prev=this;
}
Election_Management::Election_Management(string name,string Pasword)
{
	user_name=name;
	pasword=Pasword;
}
void Election_Management::generate_linked_list()
{
	string name;
	string pasword;
	ifstream Election_Managementanagement;
	Election_Managementanagement.open("E_Management.txt",ios::in);
	while(Election_Managementanagement >> name >> pasword)
	{
		
		Election_Management *Node=new Election_Management(name,pasword);
		
		Node->next=this->next;
		Node->prev=this;
		this->next->prev=Node;
		this->next=Node;
	}
	Election_Managementanagement.close();
}
void Election_Management::save_file()
{
	Election_Management *temp=this->next;
	ofstream Election_Managementanagement;
	Election_Managementanagement.open("E_Management.txt",ios::out | ios::trunc);//trunc clear the file from already stored data.
	while(temp!=this)
	{
		Election_Managementanagement<<temp->user_name<<"\t"<<temp->pasword<<"\n";
		temp=temp->next;
	}
	Election_Managementanagement.close();
}
bool Election_Management::sign_in(string pass)
{
	if(this->next->pasword==pass)
	{
		cout<<"Getting Your Info . . . "<<endl;
		system("pause");
		return true;
	}
	
	return false;	
}
void Election_Management::change_pass()
{
	string old_pass;
	string new_pass;
	bool wrong=true;
	bool again = true;
	int option;
	while(again)
	{
		printShashkaLine('=', 50);
		cout<<"\t\tChange Password"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter your old password: ";
		cin>>old_pass;
		Election_Management *temp=this->next;
		while(temp!=this)
		{
			if(old_pass==temp->pasword)
			{
				wrong=false;
				again = false;
				cout<<"Old password matched..."<<endl;
				break;
				
			}
			temp=temp->next;
		}
		if(!wrong)
		{
			cout<<"Enter your new password: ";
			cin>>new_pass;
			Election_Management *temp=this->next;
			while(temp!=this)
			{
				if(old_pass==temp->pasword)
				{
					temp->pasword=new_pass;
					break;	
				}
				temp=temp->next;
			}
			this->save_file();//to save the new pasword
			cout<<"Password changed successfully..."<<endl;
		}
		else{
			cout<<"Incorrect Old password"<<endl;
			cout<<"Do you want to retry"<<endl;
			cout<<"1: Yes"<<endl;
			cout<<"2: No"<<endl;
			cout<<"Enter your option: ";
			cin>>option;
			if(option == 2)
			{
				again = false;
			}
		}
	}
}
 //Election_Management ends here...

struct Voter{
	string CNIC;
	long pasword;
	};
struct condidates{
	string name;
	string Party_status;
	string symbol;
	int no_of_votes; 
	string Election_result;
};

class Constituency{
	string region_name;
	string constituency_name;
	int no_of_condidates;
	int no_of_voters;
	Voter *V;
	condidates *C;
	Constituency *next;
	Constituency *previous;
	
	public:
		friend class Party;
		friend  void Voter_login();
		Constituency();
		Constituency(string R_name,string C_name,condidates *C_ptr,Voter *V_ptr);
		Constituency(string R_name,string C_name,int condidate_no,int voter_no,Voter *V_ptr,condidates *C_ptr);
		void generate_linked_list();
		void save_file();
		void print();
		void registor_constituency();
		void list_constituencies();
		void delete_contituencies();
		void update_contituencies();
		void registor_voter();
		Constituency* Sign_in_Voter(string cnic , long pasword);
		void cast_vote(Constituency *temp);
		bool Symbol_AlreadyExist(string symbol);
		bool constituency_present(string constituency);
		void Save_condidate(string name,string symbol,string party_status,string constituency);
		void Show_whole_result();
		void Quick_sort(Constituency *C , int LB , int UB , bool by_vote , bool by_name , bool by_symbol);
		int Partition(Constituency *C , int LB , int UB , bool by_vote , bool by_name , bool by_symbol);
		void swap(Constituency *C , int a , int b);
		void Show_Condidates();
		void Show_Party_result(string Party_name );
};
Constituency::Constituency()
{
	this->next=this;
	this->previous=this;
	region_name="";
	constituency_name="";
	no_of_condidates=0;
	no_of_voters=0;
	V=NULL;
	C=NULL;
}
Constituency::Constituency(string R_name,string C_name,condidates *C_ptr,Voter *V_ptr)
{
	constituency_name=C_name;
	region_name=R_name;
	no_of_condidates=0;
	no_of_voters=0;
	V=V_ptr;
	C=C_ptr;
}
Constituency::Constituency(string R_name,string C_name,int condidate_no,int voter_no,Voter *V_ptr,condidates *C_ptr)
{
	region_name=R_name;
	
	constituency_name=C_name;
	no_of_condidates=condidate_no;
	no_of_voters=voter_no;
	V=V_ptr;
	C=C_ptr;
}
void Constituency::generate_linked_list()
{
	string R_name;
	string C_name;
	int condidate_no;
	int voter_no;
	ifstream Constituency_file;
	Constituency_file.open("Constituency.txt",ios::in);
	while(Constituency_file>>C_name>>condidate_no>>voter_no)
	{
		Constituency_file.ignore();
		getline(Constituency_file,R_name);
		Voter *V_ptr=new Voter[voter_no+5];
		condidates *C_ptr=new condidates[condidate_no+5];
		for(int i=0;i<condidate_no;i++)
		{
			getline(Constituency_file,C_ptr[i].Party_status);
			Constituency_file>>C_ptr[i].no_of_votes>>C_ptr[i].Election_result>>C_ptr[i].symbol;
			Constituency_file.ignore();
			getline(Constituency_file,C_ptr[i].name);
		}
		for(int i=0;i<voter_no;i++)
		{
			Constituency_file>>V_ptr[i].CNIC>>V_ptr[i].pasword;
		}
		
		Constituency *Node=new Constituency(R_name, C_name ,condidate_no ,voter_no ,V_ptr ,C_ptr);
		Node->next=this->next;
		Node->previous=this;
		this->next->previous=Node;
		this->next=Node;
	}
	Constituency_file.close();
}
void Constituency::print()
{
	
	int j;
	Constituency *temp=this->next;
	printShashkaLine('=', 80);
	cout<< left << setw(8) << "S.No"<< left << setw(16) << "Constituency"<< left << setw(16) << "Region"<< left << setw(18) << "Name";
	cout<< left << setw(16) << "Party"<< left << setw(16) << "Symbol"<<endl;
	printShashkaLine('-', 80);
	while(temp!=this)
	{
		j=1;
		
		for(int i=0;i<temp->no_of_condidates;i++)
		{
			cout<< left << setw(8) <<j<< left << setw(16) << temp->constituency_name<< left << setw(16) << temp->region_name;
			cout<< left << setw(18) << temp->C[i].name<< left << setw(16) << temp->C[i].Party_status<< left << setw(16) << temp->C[i].symbol<<endl;
			j++;			
		}
		printShashkaLine('=', 80);
		temp = temp->next;
	}
}
void Constituency::save_file()
{
	Constituency *temp=this->next;
	ofstream Constituency_file;
	Constituency_file.open("Constituency.txt",ios::out | ios::trunc);
	while(temp!=this)
	{
		Constituency_file<<temp->constituency_name<<" "<<temp->no_of_condidates<<" "<<temp->no_of_voters<<" "<<temp->region_name<<"\n";
		for(int i=0;i<temp->no_of_condidates;i++)
		{
			Constituency_file<<temp->C[i].Party_status<<"\n"<<temp->C[i].no_of_votes<<" "<<temp->C[i].Election_result<<" "<<temp->C[i].symbol<<" "<<temp->C[i].name<<"\n";
		}
		for(int i=0;i<temp->no_of_voters;i++)
		{
			Constituency_file<<temp->V[i].CNIC<<" "<<temp->V[i].pasword<<"\n";	
		}
		temp=temp->next;
	}
	Constituency_file.close();
}
void Constituency::Quick_sort(Constituency *Node , int LB , int UB , bool by_vote , bool by_name , bool by_symbol)
{														 
	int place;														
	if(LB < UB)												
	{													
		place=this->Partition(Node , LB , UB ,  by_vote ,  by_name ,  by_symbol);
		this->Quick_sort(Node , LB , place-1 ,  by_vote ,  by_name ,  by_symbol);
		this->Quick_sort(Node , place+1 , UB ,  by_vote ,  by_name ,  by_symbol);
	}
}
int Constituency::Partition(Constituency *Node , int LB , int UB , bool by_vote , bool by_name , bool by_symbol)
{
	int start = LB;
	int end = UB;
	if(by_vote)
	{
		int pivot = Node->C[LB].no_of_votes;
		while(start < end)
		{
			while(Node->C[start].no_of_votes <= pivot)
			{
				start++;
			}
			while(Node->C[end].no_of_votes > pivot)
			{
				end--;
			}
			if(start < end)
			{
				Node->swap(Node , start , end);
			}
		}
		Node->swap(Node , LB , end);
	}
	 else if(by_name)
	{
		string pivot = Node->C[LB].name;
		while(start < end)
		{
			while(Node->C[start].name <= pivot && start <= UB)
			{
				start++;
			}
			while(Node->C[end].name > pivot)
			{
				end--;
			}
			if(start < end)
			{
				Node->swap(Node , start , end);
			}
		}
		Node->swap(Node , LB , end);
	}
	 else if(by_symbol)
	{
		string pivot = Node->C[LB].symbol;
		while(start < end)
		{
			while(Node->C[start].symbol <= pivot && start <= UB)
			{
				start++;
			}
			while(Node->C[end].symbol > pivot)
			{
				end--;
			}
			if(start < end)
			{
				Node->swap(Node , start , end);
			}
		}
		Node->swap(Node , LB , end);
	}
	return end;
	
}
void Constituency::swap(Constituency *Node , int a , int b)
{
	condidates *temp = new condidates[1];
	temp[0] = Node->C[a];
	Node->C[a] = Node->C[b];
	Node->C[b] = temp[0]; 
}
void Constituency::registor_constituency()
{
	string R_name;
	string C_name;
	printShashkaLine('=', 50);
	cout<<"\t\tConstituency Registration"<<endl;
	printShashkaLine('=', 50);
	cout<<"Enter the name of constituency: ";
	cin>>C_name;
	cout<<"Enter the name of the region: ";
	cin>>R_name;
	condidates *C_ptr=new condidates[5];
	Voter *V_ptr=new Voter[5];
	Constituency *Node=new Constituency(R_name,C_name,C_ptr,V_ptr);
	Node->next=this->next;
	Node->previous=this;
	this->next->previous=Node;
	this->next=Node;
	cout<<"Constituency Registered Successfully"<<endl;
	
}
void Constituency::list_constituencies()
{
	Constituency *temp=this->next;
	int i=1;
	cout<<"Following is the list of National assembly constituencies.."<<endl<<endl;
	printShashkaLine('=', 50);
	cout<<"S.No\tConstituency\tRegion"<<endl;
	printShashkaLine('-', 50);
	while(temp!=this)
	{
		cout<< left << setw(8) << i << left << setw(16) << temp->constituency_name<< left << setw(15) <<temp->region_name<<endl;
		i++;
		temp=temp->next;
	}
	printShashkaLine('=', 50);
}
void Constituency::delete_contituencies()
{
	string name_to_delete;
	bool find=true;
	int option=2;
	int S_No;
	int j=1;
	printShashkaLine('=', 50);
	cout<<"\t\tDelete Constituency"<<endl;
	printShashkaLine('=', 50);
	
	do
	{
		this->list_constituencies();
		cout<<"\nEnter option(S.No) of the Constituency which you want to delete: ";
		cin>>S_No;
		Constituency *temp1 = this;
		Constituency *temp2 = this->next;
		while(temp2!=this)
		{
			if(j==S_No)
			{
				temp1->next=temp2->next;
				temp2->next->previous=temp1;
				cout<<"Deleted successfully..."<<endl;
				find=false;
				break;
			}
			temp1=temp1->next;
			temp2=temp2->next;
			j++;
		}
		
	    if(find)
		{
			cout<<"Sorry! The constituencie you want to delete is not present in the list.."<<endl;
			cout<<"Select your option: "<<endl;
			cout<<"1: Retry"<<endl;
			cout<<"2: Leave"<<endl;
			cin>>option;
		}
	}while(option==1);
}
void Constituency::update_contituencies()
	{
		int option;
		bool updated=true;
		int check=2;//just use in the case when user entered invalid option
		string updated_constituencie_name;
		string updated_region_name;
		Constituency *temp=this->next;
		int index=1;
		printShashkaLine('=', 50);
		cout<<"\t\tUpdate Constituency"<<endl;
		printShashkaLine('=', 50);
		do
		{
			this->list_constituencies();
			cout<<"\nEnter option(S.No) of the Constituency which you want to update: ";
			cin>>option;
			int j=1;
			while(temp!=this)
			{
				if(j==option)
				{
					cout<<"Enter updated constituency: ";
					cin>>updated_constituencie_name;
					cout<<"Enter updated region name: ";
					cin>>updated_region_name;
					temp->constituency_name=updated_constituencie_name;
					temp->region_name=updated_region_name;
					cout<<"updated successfully"<<endl;
					updated=false;
					index=1;
				}
				temp=temp->next;
				j++;
			}
			if(updated)
			{
			cout<<"Sorry! Invalid option.."<<endl;
			cout<<"Select your option: "<<endl;
			cout<<"1: Retry"<<endl;
			cout<<"2: Leave"<<endl;
			cin>>option;
			}
		}while(check==1);
	}
bool Constituency::Symbol_AlreadyExist(string symbol)
{
	Constituency *temp=this->next;
	while(temp!=this)
	{
		for(int i=0;i<temp->no_of_condidates;i++)
		{
			if(temp->C[i].symbol==symbol)
			{
				return true;
			}
		}
		temp=temp->next;
	}
	return false;
}
bool Constituency::constituency_present(string constituency)
{
	Constituency *temp=this->next;
	while(temp!=this)
	{
		if(temp->constituency_name==constituency)
		return true;
		temp=temp->next;	
	} 
	return false;
}
void Constituency::registor_voter()
{
	printShashkaLine('=', 50);
	cout<<"\t\tVoter Registration"<<endl;
	printShashkaLine('=', 50);
	string constituency;
	string cnic;
	bool check=true;
	int option;
	cout<<"Enter your CNIC No: ";
	cin>>cnic;
	Constituency *temp=this->next;
	while(temp!=this)
	{
		for(int i=0;i<temp->no_of_voters;i++)
		{
			if(temp->V[i].CNIC==cnic)
			{
				cout<<"You are already registered in Constituency: "<<temp->constituency_name<<" Region: "<<temp->region_name;
				check=false;
				break;
			}
		}
		temp=temp->next;
	}
	if(check)
	{
		do
		{
			temp=this->next;
			this->list_constituencies();
			cout<<"Enter your Constituency according to your region: ";
			cin>>constituency;
			bool again=true;
			srand(time(NULL));//call it once to generate random number
			while(temp!=this)
			{
				if(temp->constituency_name==constituency)
				{
					for(int i=0;i<temp->no_of_voters;i++)
					{
						//just to traverse the whole loop so that to add the new record at the end
					}
					temp->V[temp->no_of_voters].CNIC=cnic;
					temp->V[temp->no_of_voters].pasword=rand()%10000;
					cout<<"You are registered successfully. "<<temp->V[temp->no_of_voters].pasword<<" is your pasword."<<endl;
					temp->no_of_voters++;
					cout<<"REMEMBER YOUR PASSWORD. YOU WILL NEED IT FOR CASTING VOTE\n";
					option=2;
					again=false;
					break;
				}
				temp=temp->next;
			}
			if(again)
			{
				cout<<"The Constituency you entered is not registered with Election Commision..."<<endl;
				this->list_constituencies();
				cout<<"Do you want to retry?"<<endl;
				cout<<"1. Yes\n2. No"<<endl;
				cin>>option;
			}
		}while(option==1);
	}
}
Constituency* Constituency::Sign_in_Voter(string cnic , long pasword)
{
	Constituency *temp=this->next;
	while(temp!=this)
	{
		for(int i=0;i<temp->no_of_voters;i++)
		{
			if(cnic==temp->V[i].CNIC && pasword==temp->V[i].pasword)
			{
				cout<<"Getting Your Info . . . "<<endl;
				system("Pause");
				return temp;
			}	
		}
		temp=temp->next;
	}
	return NULL; 
		
}
void Constituency::cast_vote(Constituency *temp)
{
	string cnic;
	long pasword;
	bool again=true;
	int S_No;
	printShashkaLine('=', 50);
	cout<<"\t\tCast Vote"<<endl;
	printShashkaLine('=', 50);
	cout<<endl;
	while(again)
	{
		cout<<"Following are the list of the contistants of your contituency: "<<endl;
		printShashkaLine('=', 60);
		cout<< left << setw(8) << "S.No" << left << setw(20) << "Name" << left << setw(20) << "Party Status" << left << setw(20) <<"Symbol" <<endl;
		printShashkaLine('-', 60);
		for(int j=0;j<temp->no_of_condidates;j++)
		{
			cout<< left << setw(8) << j+1 << left << setw(20) <<temp->C[j].name << left << setw(20) <<temp->C[j].Party_status << left << setw(20) <<temp->C[j].symbol<<endl;
		}
		printShashkaLine('=', 60);
		cout<<"Enter the Serial Number of the condidate, for whom you want to cast vote: ";
		cin>>S_No;
		if(S_No<=0 || S_No>temp->no_of_condidates)
		{
			cout<<"Invalid option, please select a valid option e.g 1 for "<<temp->C[0].name<<endl;
			again=true;
		}
		else
		{
			again=false;
			temp->C[S_No-1].no_of_votes++;
			cout<<"Your vote has been successfully added to "<<temp->C[S_No-1].name<<" Party Status:  "<<temp->C[S_No-1].Party_status<<endl;
			cout<<"THANK YOU FOR VOTING"<<endl;
			break;
		}
	}
}
void Constituency::Save_condidate(string name,string symbol,string party_status,string constituency)
{
	Constituency *Node=this->next;
	if(party_status == "Independent")
	{
		Node=this->next;
		while(Node!=this)
		{
			if(Node->constituency_name==constituency)
			{
				int j = Node->no_of_condidates;
				Node->C[j].name=name;
				Node->C[j].Party_status=party_status;
				Node->C[j].symbol=symbol;
				Node->C[j].no_of_votes=0;
				Node->C[j].Election_result="Pending";
				Node->no_of_condidates++;
			}
			Node=Node->next;
		}
	}
	else
	{
		while(Node!=this)
		{
			bool already_exist = false;
			if(Node->constituency_name==constituency)
			{
				for(int i=0 ; i<Node->no_of_condidates ; i++)
				{
					if(Node->C[i].symbol == symbol)
					{
						Node->C[i].name=name;
						Node->C[i].Party_status=party_status;
						Node->C[i].symbol=symbol;
						Node->C[i].no_of_votes=0;
						Node->C[i].Election_result="Pending";
						already_exist = true;
						break;
					}
				}
				if(!already_exist)
				{
					Node->C[no_of_condidates].name=name;
					Node->C[no_of_condidates].Party_status=party_status;
					Node->C[no_of_condidates].symbol=symbol;
					Node->C[no_of_condidates].no_of_votes=0;
					Node->C[no_of_condidates].Election_result="Pending";
					Node->no_of_condidates++;	
				}
				
			}
			Node=Node->next;
		}
		cout<<"Party has successfully  alloted ticket to "<<name<<" for "<<constituency<<endl;
	}
}
void Constituency::Show_whole_result()
{
	string constituency;
	int j;
	Constituency *temp=this->next;
	Constituency *Node = this->next;
	while(Node!=this)
	{
		Node->Quick_sort(Node , 0 , Node->no_of_condidates-1 , 1 , 0 , 0);
		Node=Node->next;
	}
	printShashkaLine('=', 110);
	cout<< left << setw(8) << "S.No"<< left << setw(16) << "Constituency"<< left << setw(16) << "Region"<< left << setw(18) << "Name";
	cout<< left << setw(25) << "Party"<< left << setw(14) << "Symbol"<< left << setw(8) << "Votes"<< left << setw(8) << "Rank"<<endl;
	printShashkaLine('-', 110);
	while(temp!=this)
	{
		j=1;
		for(int i = temp->no_of_condidates-1 ; i >= 0 ; i--)
		{
			cout<< left << setw(8) << j<< left << setw(16) << temp->constituency_name<< left << setw(16) << temp->region_name;
			cout<< left << setw(18) << temp->C[i].name<< left << setw(25) << temp->C[i].Party_status<< left << setw(14) << temp->C[i].symbol;
			cout<< left << setw(8) << temp->C[i].no_of_votes<< left << setw(8) << j << endl;
			j++;			
		}	
		temp = temp->next;
		if(temp->no_of_condidates >= 1)
		printShashkaLine('-', 110);
	}
	printShashkaLine('=', 105);
}


void Constituency::Show_Condidates()
{
	int choice;
	Constituency *Node = this->next;
	printShashkaLine('=' , 50);
	cout<<"\t\tCondidates"<<endl;
	printShashkaLine('=' , 50);
	cout<<"1. Sort by Symbol"<<endl;
	cout<<"2. Sort by Name"<<endl;
	cout<<"Enter your choice: ";
	cin>>choice; 
	if(choice == 1)
	{
		while(Node != this)
		{
			this->Quick_sort(Node , 0 , Node->no_of_condidates-1 , 0 , 0 , 1);
			Node = Node->next;
		}
	}
	else if(choice == 2)
	{
		while(Node != this)
		{
			this->Quick_sort(Node , 0 , Node->no_of_condidates-1, 0 , 1 , 0);
			Node = Node->next;
		}
	}
	else
	cout<<"Invalid Choice..."<<endl;
}

void Constituency::Show_Party_result(string Party_name )
{
	int choice;
	int index=1;
	bool have_condidate;
	Constituency *Node = this->next;
	printShashkaLine('=' , 50);
	cout<<"\t\tResults"<<endl;
	printShashkaLine('=' , 50);
	cout<<"1. Show Whole Result"<<endl;
	cout<<"2. Show Party Result"<<endl;
	cout<<"Enter your  choice: ";
	cin>>choice;
	system("cls");
	if(choice == 1)
	this->Show_whole_result();
	else if(choice == 2)
	{
		have_condidate=false;
		cout<<"Party Name: "<<Party_name<<endl;
		int j;
		while(Node!=this)
		{
			this->Quick_sort(Node , 0 , Node->no_of_condidates-1 , 1 , 0 , 0);
			for(int i=0 ; i < Node->no_of_condidates ; i++)
			{
				if(i==Node->no_of_condidates-1)
				Node->C[i].Election_result = "Won";
				else
				Node->C[i].Election_result = "lost";
			}
			Node=Node->next;
		}
		printShashkaLine('=' , 90);
		cout<< left << setw(8) << "S.No"<< left << setw(16) <<"Name"<< left << setw(16) <<"Constituency"<< left << setw(14) <<"Region";
		cout<< left << setw(10) <<"Votes"<< left << setw(8) <<"Election Result"<<endl;
		printShashkaLine('-' , 90);	
		Node = this->next;
		while(Node != this)
		{
			for(int i=0 ; i < Node->no_of_condidates ; i++)
			{
				if(Node->C[i].Party_status == Party_name)
				{	
					cout<< left << setw(8) << index<< left << setw(16) <<Node->C[i].name<< left << setw(16) <<Node->constituency_name;
					cout<< left << setw(14) <<Node->region_name<< left << setw(10) <<Node->C[i].no_of_votes<< left << setw(8) <<Node->C[i].Election_result<<endl;
					index++;
				}
			}
			Node = Node->next;
		}
		printShashkaLine('=' , 90);
	}

}

//=============================================================================================//
struct party_condidate
{
	string Name;
	string constituency;
	bool approval;
};
class Party{
	string Party_Name;
	string symbol;
	string user_name;
	string Pasword;
	int No_of_condidates;
	party_condidate *P;
	Party *next;
	Party *prev;
	public: 
		Party();
		Party(string p_name,string Symbol,string UserName,string pasword,int condidate_no,party_condidate *p);
		Party(string p_name,string Symbol,party_condidate *p);
		friend party_login_menu(Party *Node);
		friend void Show_result(Party *Node);
		void generate_linked_list();
		void party_login();
		void save_file();
		void register_party();
		void print();
		void register_condidate(Constituency *c);
		void approve_condidate(Party *Node,Constituency *c);
		void delete_condidate(Party *Node , string name , string constituency);
		string Tickect_already_alloted(Party *Node , string constituency);
		string Party_name(Party *Node);
		bool Sign_in(string UserName,string pasword);
		Party* Get_pointer(string UserName , string pasword);
		void Edit_username_and_pass(Party  *Node);
};
Party::Party()
{
	this->next=this;
	this->prev=this;
	Party_Name="";
	symbol="";
	user_name="";
	Pasword=-1;
	No_of_condidates=0;
	P=NULL;
}
Party::Party(string p_name,string Symbol,party_condidate *p)//constructer for newly registered party
{
	Party_Name=p_name;
	symbol=Symbol;
	No_of_condidates=0;
	P=p;	
	
}
Party::Party(string p_name,string Symbol,string UserName,string pasword,int condidate_no,party_condidate *p)
{
	Party_Name=p_name;
	symbol=Symbol;
	user_name=UserName;
	Pasword=pasword;
	No_of_condidates=condidate_no;
	P=p;	
}

void Party::generate_linked_list()
{
	string p_name;
	string Symbol;
	string UserName;
	string pasword;
	int condidate_no;
	
	ifstream Party_file;
	Party_file.open("Party.txt",ios::in);
	while(Party_file>>condidate_no>>UserName>>Symbol>>pasword)
	{
		Party_file.ignore();
		getline(Party_file,p_name);
		party_condidate *p=new party_condidate[condidate_no+5];
		for(int i=0;i<condidate_no;i++)
		{
			Party_file>>p[i].approval>>p[i].constituency;
			Party_file.ignore();
			getline(Party_file,p[i].Name);
		} 
		Party *Node=new Party(p_name , Symbol , UserName , pasword , condidate_no , p);
		Node->next=this->next;
		Node->prev=this;
		this->next->prev=Node;
		this->next=Node;
	}
	Party_file.close();
}
void Party::Edit_username_and_pass(Party *Node)
{
	string old_username;
	string old_pass;
	string new_pass;
	int option;
	bool wrong=true;
	bool again = true;
	while(again)
	{
		cout<<"Enter old Username: ";
		cin>>old_username;
		cout<<"Enter your old Password: ";
		cin>>old_pass;
		if(old_pass==Node->Pasword && old_username == Node->user_name)
		{
			wrong=false;
			cout<<"Old details matched..."<<endl;	
		}
		
		if(!wrong)
		{
			cout<<"Enter your new Username (without spaces): ";
			cin>>Node->user_name;
			cout<<"Enter your new password (without spaces): ";
			cin>>Node->Pasword;
			cout<<"Password changed successfully..."<<endl;
			again = false;
		}
		else
		{
			cout<<"Incorrect username or password"<<endl;
			cout<<"Do you want to retry"<<endl;
			cout<<"1: Yes"<<endl;
			cout<<"2: No"<<endl;
			cin>>option;
			if(option == 2)
			{
				again = false;
			}
		}
	}
}
void Party::save_file()
{
	ofstream Party_file;
	Party_file.open("Party.txt",ios::out | ios::trunc);
	Party *temp=this->next;
	while(temp!=this)
	{
		Party_file<<temp->No_of_condidates<<" "<<temp->user_name<<" "<<temp->symbol<<" "<<temp->Pasword<<" "<<temp->Party_Name<<"\n";
		for(int i=0;i<temp->No_of_condidates;i++)
		{
			Party_file<<temp->P[i].approval<<" "<<temp->P[i].constituency<<" "<<temp->P[i].Name<<"\n";
		}
		temp=temp->next;
	}
	Party_file.close();	
}
void Party::register_party()
{
	int index=1;
	bool again;
	string p_name;
	string Symbol;
	party_condidate *p=new party_condidate[5];
	printShashkaLine('=', 50);
	cout<<"\t\tParty Registration"<<endl;
	printShashkaLine('=', 50);
	cin.ignore();
	cout<<"Enter Party Name:  ";
	getline(cin,p_name);
	do
	{
		again=false;
		cout<<"please Enter symbol other than the symbols given in the list below..."<<endl<<endl;
		printShashkaLine('=', 40);
		cout<< left << setw(8) << "S.No"<< left << setw(16) << "Party Name"<< left << setw(16) << "Symbol"<<endl;
		printShashkaLine('-', 40);
		Party *temp=this->next;
		while(temp!=this)
		{
			cout<< left << setw(8) << index<< left << setw(16) << temp->Party_Name<< left << setw(16) << temp->symbol<<endl;
			index++;
			temp=temp->next;
		}
		printShashkaLine('=', 40);
		cout<<"Enter Symbol:\t ";
		cin>>Symbol;
		temp=this->next;
		while(temp!=this)
		{
			if(Symbol==temp->symbol)
			{
				cout<<"Invalid Symbol..."<<endl;
				system("pause");
				system("cls");
				again=true;
				index=1;
			}
			temp=temp->next;
		}
		Symbol[0] = toupper(Symbol[0]);
	}while(again);
	Party *Node=new Party(p_name,Symbol,p);
	srand(time(NULL));
	Node->user_name=Generate_UserName(5);
	Node->Pasword=Generate_UserName(4);

	Node->next=this->next;
	Node->prev=this;
	this->next->prev=Node;
	this->next=Node;
	cout<<"Party is successfully registered..."<<endl;
	cout<<"Following are the departy_tails so for..."<<endl<<endl;
	cout<<"USERNAME:\t "<<this->next->user_name<<endl;
	cout<<"PASWORD:\t "<<this->next->Pasword<<endl;
	cout<<"Party Name:\t "<<this->next->Party_Name<<endl;
	cout<<"Party Symbol:\t "<<this->next->symbol<<endl<<endl;
	cout<<"IMPORTANT: REMEMBER YOUR USERNAME AND PASSWORD YOU WILL NEED IT TO LOGIN. "<<endl<<endl;
}
bool Party::Sign_in(string UserName,string pasword)
{
	Party *temp=this->next;
	while(temp!=this)
	{
		if(temp->user_name==UserName && temp->Pasword==pasword)
		{
			return true;
		}
		temp=temp->next;
	}
	return false;
}
Party* Party::Get_pointer(string UserName,string pasword)
{
	Party *temp=this->next;
	while(temp!=this)
	{
		if(temp->user_name==UserName && temp->Pasword==pasword)
		{
			cout<<"Getting Your Info..."<<endl;
			system("pause");
			return temp;
		}
		temp=temp->next;
	}
	return NULL;
}
string Party::Party_name(Party *Node)
{
	Party *temp =this->next;
	while(temp != this)
	{
		if(temp->Party_Name == Node->Party_Name)
		return Node->Party_Name;
		temp = temp->next;
	}
}
string Party::Tickect_already_alloted(Party *Node,string constituency)
{
	for(int i=0;i<Node->No_of_condidates;i++)
	{
		if(Node->P[i].constituency==constituency)
		return Node->P[i].Name;
	}
	return "NULL";
}
void Party::register_condidate(Constituency *c)
{
	printShashkaLine('=', 50);
	cout<<"\t\tCondidate Registration"<<endl;
	printShashkaLine('=', 50);
	string name;
	string symbol;
	string constituency;
	string party_status;
	int option;
	cout<<"Enter your full Name: ";
	getline(cin,name);
	name[0] = toupper(name[0]);//to capitalize first alphabet
	c->list_constituencies();
	cout<<"Enter your constituency: ";
	cin>>constituency;
	while(!c->constituency_present(constituency))
	{
		cout<<"Unregistered Constituency...";
		cout<<"Please Enter valid Constituency according to your region : ";
		cin>>constituency;
	}
	cout<<"Are you an independent condidate?"<<endl;
	cout<<"1. Yes"<<endl;
	cout<<"2. No"<<endl;
	cin>>option;
	if(option==1)
	{
		party_status="Independent";
		cout<<"Enter your Symbol: ";
		cin>>symbol;
		while(c->Symbol_AlreadyExist(symbol))
		{
			cout<<"Sorry! this Symbol is already registered with election commission...";
			cout<<"Enter another Symbol: ";
			cin>>symbol;
		}
		symbol[0] = toupper(symbol[0]);
		c->Save_condidate(name,symbol,party_status,constituency);
		cout<<"Congratulation! you have been Successfully Registered for the Election"<<endl;
	}
	else if(option==2)
	{
		bool again;
		bool check;
		cout<<"Enter your Party Name: ";
		cin.ignore();
		do
		{
			check=true;
			getline(cin,party_status);
			Party *Node=this->next;
			while(Node!=this)
			{	
				if(Node->Party_Name==party_status)
				{
				Node->P[Node->No_of_condidates].Name=name;
				Node->P[Node->No_of_condidates].constituency=constituency;
				Node->P[Node->No_of_condidates].approval=0;
				Node->No_of_condidates++;
				cout<<"Your registeration will confirmed after the approval of "<<Node->Party_Name<<endl;
				again=false;
				check=false;
				break;
				}
				Node=Node->next;
			}
			if(check)
			{
				cout<<"The Party name you entered is not rigestered with Election commission..."<<endl;
				cout<<"Enter Valid Party name: ";
				again=true;
			}
		}while(again);
	}
	
}
void Party::approve_condidate(Party *Node , Constituency *c)
{
	int i=Node->No_of_condidates-1;
	printShashkaLine('=', 50);
	cout<<"\t\tNotifications"<<endl;
	printShashkaLine('=', 50);
	while(!Node->P[i].approval && i>=0)
	{
		int option;
		cout<<Node->P[i].Name<<" wants ticket of your party for "<<Node->P[i].constituency<<endl;
		cout<<"Select your option: "<<endl;
		cout<<"1. Allot Ticket"<<endl;
		cout<<"2. Reject"<<endl;
		cin>>option;
		if(option==1)
		{
			string already_exist;
			already_exist=this->Tickect_already_alloted(Node , Node->P[i].constituency);
			if(already_exist != Node->P[i].Name)//If this conditition fails ,  mean that there is only him(new condidate) in that constituency
			{
				cout<<"Party have already alloted this to "<<already_exist<<endl;
				cout<<"Do you still want to allot this to "<<Node->P[i].Name<<" and discard "<<already_exist<<endl;
				cout<<"1. yes"<<endl;
				cout<<"2. No"<<endl;
				cin>>option;
				if(option==1)
				{
				
					this->delete_condidate(Node , already_exist , Node->P[i].constituency);
					i--;
					c->Save_condidate(Node->P[i].Name , Node->symbol , Node->Party_Name , Node->P[i].constituency);
					Node->P[i].approval=1;
				}
			}
			else
			{
				Node->P[i].approval=1;
				c->Save_condidate(Node->P[i].Name , Node->symbol , Node->Party_Name , Node->P[i].constituency);
			}
		}
		if(option==2)
		{
			this->delete_condidate(Node , Node->P[i].Name , Node->P[i].constituency);
		}
		system("pause");
		i--;
	}
	cout<<"No new Notifications..."<<endl;
}
void Party::delete_condidate(Party *Node , string name , string constituency)
{
	int i;
	int j=Node->No_of_condidates-1;
	cout<<"Deleting "<<name<<endl;
	for(i=j;i>=0;i--)
	{
		if(Node->P[i].Name == name && Node->P[i].constituency == constituency)
		{
			for(i;i<j;i++)
			{
				Node->P[i] = Node->P[i+1];
			}
			Node->No_of_condidates--;
		}
	}
}

int main()
{
	int choice;
	bool again = true;
	int x;
	int a;
	while(again){
		choice = showMenu_main();
		switch(choice)
		
		{
			case 0: //exit program
				cout<<"Exit Program called"<<endl;
				again = false;
				break;
				
			case 1:
				Election_commission();
				break;
				
			case 2:
				party_login();
				break;
				
			case 3:
				Voter_login();
				break;
		
			default:
				cerr<<"Invalid choice"<<endl;
				cout<<"Kindly select a valid number from menu"<<endl;
				break;
		}
	}
	cout<<"Thank you for using our program"<<endl;
	return 0;
}	
int showMenu_main()
{
	int choice;
	printShashkaLine('=', 50);
	cout<<"\t\t Main Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Exit Program"<<endl;
	cout<<"1. Election Commission Login"<<endl;
	cout<<"2. Party Login"<<endl;
	cout<<"3. Voter Login"<<endl;
	printShashkaLine('=', 50);
	cout<<"Enter your choice: ";
	cin>>choice;
	return choice;
}
void Election_commission()
{
	system("cls");
	int choice;
	bool again = true;
	
	Election_Management *E = new Election_Management;
	Constituency *C = new Constituency;
	Party *P = new Party;

	E->generate_linked_list();
	C->generate_linked_list();
	P->generate_linked_list();
	
	string pass;
	bool match=false;
	
	//	password and id matching code
	
	
	while(!match)
	{
		printShashkaLine('=', 50);
		cout<<"\t\t Election Management Sign-in"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter Your Password : ";
		cin >> pass;
		match=E->sign_in(pass);
		
		if(!match)
		{
			system("cls");
			printShashkaLine('=', 50);
			cout<<endl<<endl<<"Incorrect Password"<<endl<<endl;
			printShashkaLine('=', 50);
			
			cout<<"0. Leave"<<endl;
			cout<<"1. Retry"<<endl;
			printShashkaLine('=', 50);
			cout<<"Enter your choice: ";
			cin>>choice;
			
			if(choice==0)
			{
				match=true;
				again=false;
			}
		}
		system("cls");
	}
	
	while(again)
	{
		choice = Election_Management_Menu();
		system("cls");
		
		switch(choice)
		{
			case 0:
				cout<<"logging Out"<<endl;
				C->save_file();
				P->save_file();
				again = false;
				break;
				
			case 1:
				E->change_pass();
				break;
				
			case 2:
				C->registor_constituency();
				break;
				
			case 3:
				C->list_constituencies();
				break;
				
			case 4:
				C->update_contituencies();
				break;
				
			case 5:
				C->delete_contituencies();
				break;
				
			case 6:
				P->register_party();
				break;
				
			case 7:
				cin.ignore();
				P->register_condidate(C);
				break;
				
			case 8:
				C->registor_voter();
				break;
				
			case 9:
				C->Show_whole_result();
				break;
				
			default : 
				cout<<"Invalid Option. Please select a valid option from the menu"<<endl;
		}
		system("pause");
		system("cls");
	}
}
int Election_Management_Menu()
{
	int option;
	printShashkaLine('=', 50);
	cout<<"\t\tElection Commission Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Sign out"<<endl;
	cout<<"1. Change Password"<<endl;
	cout<<"2. Register Constituency"<<endl;
	cout<<"3. List Constituencies"<<endl;
	cout<<"4. Update Constituency"<<endl;
	cout<<"5. Delete Constituency"<<endl;
	cout<<"6. Register Political Party"<<endl;
	cout<<"7. Register Condidate"<<endl;
	cout<<"8. Register Voter"<<endl;
	cout<<"9. Show Results"<<endl<<endl;
	cout<<"Enter your option: ";
	cin>>option;
	
	return option;
}

void party_login()
{
	system("cls");
	int choice;
	bool again = true;
	string Party_name;
	
	Constituency *C = new Constituency;
	Party *P = new Party;
	C->generate_linked_list();
	P->generate_linked_list();
	
	Party *Node = new Party;
	string user_name;
	string pass;
	bool match = false;
	
	//	password and id matching code
	
	
	while(!match)
	{
		printShashkaLine('=', 50);
		cout<<"\t\t Party Sign-in"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter Your Usernmae : ";
		cin >> user_name;
		cout<<"Enter Your Password : ";
		cin >> pass;
		match = P->Sign_in(user_name , pass);
		
		if(!match)
		{
			system("cls");
			printShashkaLine('=', 50);
			cout<<endl<<"Incorrect Username or Password"<<endl<<endl;
			printShashkaLine('=', 50);
			
			cout<<"0. Leave"<<endl;
			cout<<"1. Retry"<<endl;
			printShashkaLine('=', 50);
			cout<<"Enter your choice: ";
			cin>>choice;
			
			if(choice==0)
			{
				match=true;
				again=false;
			}
		}
		else
		Node=P->Get_pointer(user_name , pass);

	}
	system("cls");
	
	while(again)
	{
		choice = party_login_menu();
		system("cls");
		switch(choice)
		{
			case 0:
				cout<<"Logging Out"<<endl;
				P->save_file();
				C->save_file();
				again = false;
				break;
				
			case 1: 
				P->Edit_username_and_pass(Node);
				break;
				
			case 2: 
				P->approve_condidate(Node , C);
				break;
				
			case 3:
				Party_name = P->Party_name(Node);
				C->Show_Party_result(Party_name);
				break;
				
			default : 
				cout<<"Invalid Option. Please select a valid option from the menu"<<endl;	
		}
		system("pause");
		system("cls");	
	}
		
}

int party_login_menu()
{
	int option;
	printShashkaLine('=', 50);
	cout<<"\t\tOfficial Page "<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Sign Out"<<endl;
	cout<<"1. Edit Username or/and Password"<<endl;
	cout<<"2. Check Notifications"<<endl;
	cout<<"3. Check Result"<<endl<<endl;
	cout<<"Enter your option: ";
	cin>>option;
	
	return option;
}
void Voter_login()
{
	system("cls");
	int choice;
	bool again = true;
	
	Constituency *C = new Constituency;
	Party *P = new Party;
	C->generate_linked_list();
	P->generate_linked_list();
	
	Constituency *Node = new Constituency;
	string cnic;
	long pasword;
	bool repeat;
	
	//	password and id matching code
	
	
	do
	{
		repeat = false;
		printShashkaLine('=', 50);
		cout<<"\t\t Voter Sign-in"<<endl;
		printShashkaLine('=', 50);
		cout<<"Enter CNIC Number : ";
		cin >> cnic;
		cout<<"Enter Your Password : ";
		cin >> pasword;
		Node = C->Sign_in_Voter(cnic , pasword);
		
		if(Node == NULL)
		{
			system("cls");
			repeat = true;
			printShashkaLine('=', 50);
			cout<<endl<<endl<<"Incorrect CNIC Number or Password"<<endl<<endl;
			printShashkaLine('=', 50);
			
			cout<<"0. Leave"<<endl;
			cout<<"1. Retry"<<endl;
			printShashkaLine('=', 50);
			cout<<"Enter your choice: ";
			cin>>choice;
			
			if(choice==0)
			{
				repeat=false;
				again=false;
			}
		}
		system("cls");
		
	}while(repeat);
	
	while(again)
	{
		choice = Voter_login_Menu();
		system("cls");
		switch(choice)
		{
			case 0:
				cout<<"Logging Out"<<endl;
				P->save_file();
				C->save_file();
				again = false;
				break;
				
			case 1:
				C->Show_Condidates();
				C->print();
				break;
				
			case 2:
				C->cast_vote(Node);
				break;
				
			default : 
				cout<<"Invalid Option. Please select a valid option from the menu"<<endl;	
		}
		system("pause");
		system("cls");	
	}	
}

int Voter_login_Menu()
{
	int option;
	printShashkaLine('=', 50);
	cout<<"\t\tVoter Login Menu"<<endl;
	printShashkaLine('=', 50);
	
	cout<<"0. Sign Out"<<endl;
	cout<<"1. Show All Condidates with Symbols"<<endl;
	cout<<"2. Cast Vote"<<endl;
	cin>>option;
	
	return option;
} 
void printShashkaLine(char element, int noOfTimes)
{
	for(int i=0; i < noOfTimes; i++)
	{
		cout<<element;
	}
	cout<<endl;
}
string Generate_UserName(int n)
{
	char letters[36]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};
	string ran="";
	for(int i=0;i<n;i++)
	{
		ran=ran+letters[rand()%36];
	}
	return ran;
}

