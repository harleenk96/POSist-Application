#include<bits/stdc++.h>
#include <time.h>
#include<conio.h>
#include<vector>
#include<map>
#include<string.h>
#include<algorithm>
#include<math.h>
#include <unistd.h>
#include<stdlib.h>
using namespace std;

#define ll  int
#define mod 1000000007
#define pd push_back

string s3 = "\t\t\t";
ll unique_id=0;



// struct node
struct node{
	
	struct  data{
		string name;
		string address;
		string number;
		string phone;
		string password;
	};  
	
	data *info= new data;  
	string time_stamp;
	ll node_number;
	ll node_uniqid;
	ll parent_address;
	ll enc_key;
	ll sub_node=-1;
	
	struct node * next =NULL;
	
	node * subnode[99999] ={NULL};	
	
};

//  Substitution encryption and decryption modulde

string encrypt(string  str, int key){
	
	key=key%27;
	
	for(int i = 0; (i < 100 && str[i] != '\0'); i++)
            str[i] = str[i] + key; 

	return str;	
}

string decrypt(string  str, int key){
	
	 key=key%27;
	
	 for(int i = 0; (i < 100 && str[i] != '\0'); i++)
    	     str[i] = str[i] - key;       
	 return str;	
}

//  check error

bool check(){
	if(unique_id == 0){
		cout<<"\n\n\n\n\t\t\tSegmentation error : Please fill main list first :"<<endl;
		sleep(2);
		eturn 1;
	}
}


// generate unique number
int generateUniqueInt()
{
  int a= abs((((rand()*999999999)/13)*17)*3);
  
  return a;
}


// get time stamp
string gettime(){
	char temp[100]; 
	
        time_t current_time = time(NULL);
        struct tm *tm = localtime(&current_time);
        strftime(temp, sizeof(temp), "%c", tm);
        return temp;
}


// create node
node * createnode( node * head,  ll parent_id, ll total_node ){
	
	string name,address,number,phone,password;
	int key;
	head = new node;
		
	
		// data-fill
		cout<<" 	  enter the name of the user \t"<<endl;	 cin>>name; 
		cout<<"	  			address"<<"\t"<<endl; 				 cin>>address; 
		cout<<"				number"<<"\t"<<endl; 		     		 cin>>number; 
		cout<<"				phone"<<"\t"<<endl;				 cin>>phone; 
		cout<<"				password"<<"\t"<<endl;				 cin>>password; 
		cout<<"				encrypt-key"<<"\t"<<endl;			 cin>>key;
	
		// persional details
		
		head->time_stamp = gettime();
		head->info->name=encrypt(name,key);
		head->info->address=encrypt(address,key);
		head->info->number=encrypt(number,key);
		head->info->phone=encrypt(phone,key);
		head->info->password=encrypt(password,key);
		head->enc_key=key;
		
		head->node_number=total_node;
		head->parent_address=parent_id;
		head->node_uniqid=generateUniqueInt();
		head->next=NULL;
			
	return head;
}


//  create node combo
node * setnode(int total_node){
	
	bool start=0;
	node * head, * temp;
	
	 for(int i=0;i<total_node;i++){
	 	if(start==0){
	 		head = createnode(head,0,++unique_id);
	 		temp=head;
	 		start=1;
		 }else{ 	
		 	temp->next=createnode(head,temp->node_number,++unique_id);
		 	temp=temp->next;
		 	
		 }
	 }
}


// Recursion Search for all sub node maximum lenght 
int chech_all_subnode_max_lenght(node *temp){
	
	int subcount=0,nextcount=0;
		
	if(temp->sub_node != -1){
		
		for(int i=temp->sub_node; i>=0; i--){
			
			subcount = max(subcount , chech_all_subnode_max_lenght( temp->subnode[temp->sub_node] ) );
			
		}	
	}	
	if(temp->next != NULL){
		
		nextcount = chech_all_subnode_max_lenght(temp->next);
		
	}	
	
	return (max(subcount , nextcount) + 1);
	
}

int main(){
	
	ios::sync_with_stdio(0); cin.tie(0);
	 
	int total_node, total_subnode, parent_id, module, node_id;
	node *head, * subnode, *temp, * oneadd, *extra_temp;
	
	do{
		
	cout<<"\n\n\n"<<s3<<"1  To create first node "<<endl<<endl;
	cout<<s3<<"2  To create sub-node "<<endl<<endl;
	cout<<s3<<"3  To adding new node "<<endl<<endl;
	cout<<s3<<"4  To break any node or subnode"<<endl<<endl;
	cout<<s3<<"5  To transfer owner of node or sub node to other owner"<<endl<<endl;
	cout<<s3<<"6  To Find the longest chain of main node "<<endl<<endl;
	cout<<s3<<"7  To Find the longest chain of sub node of a main node"<<endl<<endl;
	cout<<s3<<"8  To Merge two different set of node"<<endl<<endl;
	cout<<s3<<"0  For exit"<<endl<<endl;
	
	
	
	cin>>module;
	system("CLS");
	switch(module){
		
		case 1:{
			
			cout<<s3<<"enter the total number of nodes : "<<endl;
			cin>>total_node;
			cout<<endl<<endl;
			
			head = setnode(total_node);
			break;
			}
		
		case 2:{
			
			if(check()){
				break;
			}
			
			cout<<s3<<"enter the total number of nodes and the parent node number "<<endl;
			cin>>total_node>>parent_id;
			
			
			
			subnode = setnode(total_node);
			
			temp = head;
				while(parent_id--){
					temp=temp->next;
				}
			
			temp->subnode[++temp->sub_node] = temp;
			
			break;
		}
		
		case 3:{
			
			cout<<s3<<"Enter the node id on which you want to add new node between them";
			cin>>node_id;
			
			node_id--;
			temp=head;
			
			while(node_id--){
				temp=temp->next;
			}
			
			oneadd = createnode(head,temp->node_number,temp->node_number);
			
			oneadd->next=temp->next;
			temp->next=oneadd;
			
			
//			change all reamining node_number
			while(oneadd!=NULL){
				oneadd=oneadd->next;
				oneadd->node_number++;
			}
			
			break;
		}
		
		case 4:{
			
			int ccondition;
			
			cout<<s3<<"To break any node press     1"<<endl<<endl;
			cout<<s3<<"To break any subnode        2"<<endl<<endl;
			
			cin>>ccondition;
			
			switch(ccondition){
				
				case 1:{
					// delete node
					cout<<s3<<"Enter the node id number"<<endl<<endl;
					cin>>node_id;
					node_id--;
					
					temp = head;
					
					while(node_id--){
						temp=temp->next;
					}
					
					temp->next=temp->next->next;
					
					temp=temp->next;
					
				//	set remaining node number
				
					while(temp!=NULL){
						temp->node_number--;
						temp=temp->next;
					}
					
					break;
				}
				
				case 2:{
					
					cout<<s3<<"Enter the parent id of subnode "<<endl<<endl;
					cin>>node_id;
					
					node_id--;
					
					temp=head;
					while(node_id--){
						temp=temp->next;
					}
					
					if(temp->subnode[temp->sub_node]->sub_node == -1){
						cout<<"Their is no sub node under this node,  Check again";
					}else{
						temp->subnode[temp->sub_node] = NULL;
						temp->sub_node--;
						
						cout<<"Remove Successfully !";
						sleep(1000);
					}
					
					break;
				}
			}
			
			break;
		}
		
		case 5:{
			
			cout<<"\n\n\n\t\tWork under Construction"<<endl;
			sleep(1);
			
			break;
		}
		
		case 6:{
			
			temp=head;
			
			int count=0,maxx=0;
			
			
			while(temp!=NULL){
				
				if(temp->sub_node!=-1){
					count=temp->node_number;
					
					for(int i=temp->sub_node;i>=0;i--){
						
						extra_temp=temp->subnode[i];
						
						while(temp!=NULL){
							count++;
							extra_temp=extra_temp->next;
						}
						if(count>maxx)
						maxx=count;
						
					}
					
				}
				
				temp=temp->next;
			}
			
			cout<<"The answer of the longest chain of main node is : "<<count<<endl;
			
			
			break;
		}
		
		case 7:{
			
			temp= head;
			
			cout<<"The longest chain of sub node of a main node among the set of node is :  " << chech_all_subnode_max_lenght(temp) <<endl;
			
			
			break;
		}
		
		case 8:{
			
			cout<<"\n\n\n\t\tWork under Construction"<<endl;
			sleep(1);
			
			
			break;
		}
		
			
			
	}
		
	system("CLS");	
		
	}while(module != 0);
		
	 	
	return 0;
}
