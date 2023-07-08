#include<conio.h>
#include<string.h>
#include<iostream>
#include <iomanip>   
#include<fstream>
#include<ctime> 
using namespace std;
void login();
class EarnedMoney{
    private:
        int carType;
        int busType;
        int trcukType;
        int bikeType;
        int cycleType;
        int total;
    public:
        EarnedMoney(){
            this->carType=0;
            this->busType=0;
            this->trcukType=0;
            this->bikeType=0;
            this->cycleType=0;
            this->total=0;
        }
        void setEarnedMoney(int carType,int busType,int trcukType,int bikeType,int cycleType,int total){
            this->carType=carType;
            this->busType=busType;
            this->trcukType=trcukType;
            this->bikeType=bikeType;
            this->cycleType=cycleType;
            this->total=total;
        }
        void showEarnedMoney(){
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(10)<<"Car|"<<setw(10)<<"Bus|"<<setw(10)<<"PasApp|"<<setw(10)<<"Bike|"<<setw(10)<<"Moto|"<<setw(10)<<"Total|";
            cout<<"\n--------------------------------------------------------------\n";
            cout<<setw(9)<<this->carType<<"|"<<setw(9)<<this->busType<<"|"<<setw(9)<<this->trcukType<<"|"<<setw(9)<<this->bikeType<<"|"<<setw(9)<<this->cycleType<<"|"<<setw(9)<<this->total<<"|";
            cout<<"\n--------------------------------------------------------------\n";
        }
        void getAllEarnedMoney();
        friend void addTwoMoney(EarnedMoney,EarnedMoney&);
};
void EarnedMoney:: getAllEarnedMoney(){
    ifstream fin;
    fin.open("Monry.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        //this->showEarnedMoney();
    }
}
void addTwoMoney(EarnedMoney oldMoney,EarnedMoney &newMoney){
    newMoney.carType+=oldMoney.carType;
    newMoney.busType+=oldMoney.busType;
    newMoney.trcukType+=oldMoney.trcukType;
    newMoney.bikeType+=oldMoney.bikeType;
    newMoney.cycleType+=oldMoney.cycleType;
    newMoney.total+=oldMoney.total;
}
class VehicleType{
    private:
        char vehicleTypeName[50];
    public:
        VehicleType(){
            strcpy(vehicleTypeName,"Panha");
        }
        int total =0;
        void setVehivleType(EarnedMoney &earnedMoney){
            while(1){
                cout<<"\nSelect Vehicle Type:";
                cout<<"\n1. Car  2. Bus  3. pasApp  4. Bike  5. Moto\n";
                int vehicleType;
                cin>>vehicleType;
                if(vehicleType==1){
                    strcpy(this->vehicleTypeName,"Car");
                    earnedMoney.setEarnedMoney(1000,0,0,0,0,1000);
                    break;
                }
                else if(vehicleType==2){
                    strcpy(vehicleTypeName,"Bus");
                    earnedMoney.setEarnedMoney(0,2000,0,0,0,2000);
                    break;
                }
                else if(vehicleType==3){
                    strcpy(vehicleTypeName,"PasApp");
                    earnedMoney.setEarnedMoney(0,0,500,0,0,500);
                    break;
                }
                else if(vehicleType==4){
                    strcpy(vehicleTypeName,"Bike");
                    earnedMoney.setEarnedMoney(0,0,0,300,0,300);
                    break;
                }
                else if(vehicleType==5){
                    strcpy(vehicleTypeName,"Moto");
                    earnedMoney.setEarnedMoney(0,0,0,0,300,300);
                    break;
                }
                else{
                    cout<<"\nInvalid Choice:";
                }
            }
        }
        void showVehicleType(){cout<<vehicleTypeName<<"  ";}
};

class Vehicle:public VehicleType{
    private:
        int vehicleNo;
        char shortDescription[60];
        char description[100];
        char createdBy[50];
        char lastUpdatedBy[50];
        char createdDateTime[50];
        char lastUpdatedDateTime[50];
        EarnedMoney earnedMoney;
    public:
        Vehicle(){
            this->vehicleNo=0;
            strcpy(this->shortDescription,"default");
            strcpy(this->description,"default");
            strcpy(this->createdBy,"Muni");
            strcpy(this->lastUpdatedBy,"Muni");
            time_t tt;
            time(&tt);
            strcpy(this->createdDateTime,asctime(localtime(&tt)));
            strcpy(this->lastUpdatedDateTime,asctime(localtime(&tt)));
        }
        void setVehicle(){
            cout<<"\nEnter The Vehicle Number: ";
            cin>>vehicleNo;
            cin.ignore();
            cout<<"\nEnter The Vehicle Short Description: ";
            cin.getline(shortDescription,50);
            cout<<"\nEnter The Vehicle Description: ";
            cin.getline(description,100);
            strcpy(createdBy,"Muni");
            strcpy(lastUpdatedBy,"Muni");
            setVehivleType(earnedMoney);
            //date and time
            time_t tt;
            time (&tt); 
            strcpy(createdDateTime,asctime(localtime(&tt)));
            strcpy(lastUpdatedDateTime,asctime(localtime(&tt)));
        }
        void showVehicle(){
            cout<<vehicleNo<<"  "<<shortDescription<<"  ";
            cout<<description<<"  ";
            showVehicleType();
            cout<<createdBy<<"  "<<lastUpdatedBy<<"  ";
            cout<<createdDateTime<<lastUpdatedDateTime<<endl;
            //earnedMoney.showEarnedMoney();
        }
        void addVehicle();
        void getAllVehicleList();
        void searchVehicle(int vno);
        void deleteVehicle(int vno);
        void updateVehicle(int vno);
};

void Vehicle:: addVehicle(){
    ofstream fout;
    fout.open("data.txt",ios_base::app|ios_base::binary);
    getch();
    fout.write((char*)this,sizeof(*this));
    fout.close();

    EarnedMoney em;
    em.getAllEarnedMoney();
    addTwoMoney(em,this->earnedMoney);
    fout.open("Monry.txt",ios_base::out|ios_base::binary);
    fout.write((char*)(&this->earnedMoney),sizeof(this->earnedMoney));
    fout.close();
    cout<<"\nRecord Added Successfully\n";
}

void Vehicle:: getAllVehicleList(){
    system("cls");
    ifstream fin;
    int nor=0;
    fin.open("data.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            this->showVehicle();
            nor++;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nFile Has No Record:";
        }
    }
}

void Vehicle:: searchVehicle(int vno){
    system("cls");
    ifstream fin;
    int nor=0;
    fin.open("data.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            if(this->vehicleNo==vno){
                this->showVehicle();
                nor=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(nor==0){
            cout<<"\nRecord Not Found:";
        }
    }
}

void Vehicle:: deleteVehicle(int vno){
    system("cls");
    ifstream fin;
    ofstream fout;
    int flag=0;
    fin.open("data.txt",ios_base::in|ios_base::binary);
    if(!fin){
        cout<<"\nFile Not Found";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        fout.open("aaTempVehivleData.txt",ios_base::out|ios_base::binary);
        while(!fin.eof()){
            if(this->vehicleNo==vno){
                flag=1;
            }
            else{
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        if(flag==0){
            cout<<"\nRecord Not Found: Hence Can Not delete";
            remove("aaTempVehivleData.txt");
        }
        else{
            cout<<"\nRecord Deleted:";
            remove("data.txt");
            rename("aaTempVehivleData.txt","data.txt");
        }
    }
}

void Vehicle:: updateVehicle(int vno){
    system("cls");
    fstream foutIn;
    int flag=0;
    foutIn.open("data.txt",ios_base::in|ios_base::out|ios_base::ate|ios_base::binary);
    foutIn.seekg(0);
    if(!foutIn){
        cout<<"\nFile Not Found";
    }
    else{
        foutIn.read((char*)this,sizeof(*this));
        while(!foutIn.eof()){
            if(this->vehicleNo==vno){
                //this->setVehicle();
                cout<<"\nUpdating The Data:";
                cout<<"\nEnter The Vehicle Number: ";
                cin>>vehicleNo;
                cin.ignore();
                cout<<"\nEnter The Vehicle Short Description: ";
                cin.getline(shortDescription,50);
                cout<<"\nEnter The Vehicle Description: ";
                cin.getline(description,100);
                strcpy(createdBy,"Muni");
                strcpy(lastUpdatedBy,"Vashishth");
                //date and time
                time_t tt;
                time (&tt); 
                strcpy(lastUpdatedDateTime,asctime(localtime(&tt)));

                foutIn.seekp(foutIn.tellp()-sizeof(*this));
                foutIn.write((char*)this,sizeof(*this));
                cout<<"\nRecord Updated Successfully\n";
                flag=1;
                break;
            }
            foutIn.read((char*)this,sizeof(*this));
        }
        foutIn.close();
        if(flag==0){
            cout<<"\nRecord Not Found:";
        }
    }
}

int menu(){
    system("cls");
    Vehicle vehicle;
    EarnedMoney earnedMoney;
    int breakInfiniteloop=0,vno;
    int ch;
    while(1){
    printf("\n1. Add Vehicle");
    printf("\n2. Search Vehicle");
    printf("\n3. Delete Vehicle");
    printf("\n4. Update Vehicle");
    printf("\n5. List All Vehicle");
    printf("\n6. Check Earned Money");
    printf("\n7. Exit");
    printf("\nEnter Your Choice: ");
    scanf("%d",&ch);
        switch(ch){
            case 1:
                vehicle.setVehicle();
                vehicle.addVehicle();
                getch();
                break;
            case 2:
                cout<<"\nEnter The Vehicle Number To Searched: ";
                cin>>vno;
                vehicle.searchVehicle(vno);
                getch();
                break;
            case 3:
                cout<<"\nEnter The Vehicle Number To Deleted: ";
                cin>>vno;
                vehicle.deleteVehicle(vno);
                getch();
                break;
            case 4:
                cout<<"\nEnter The Vehicle Number To Updated: ";
                cin>>vno;
                vehicle.updateVehicle(vno);
                getch();
                break;
            case 5:
                vehicle.getAllVehicleList();
                getch();
                break;
            case 6:
                earnedMoney.getAllEarnedMoney();
                earnedMoney.showEarnedMoney();
                getch();
                break;
            case 7:
                breakInfiniteloop=1;
                break;
            default:
                cout<<"\nInvalid Choice:";
                getch();
        }//end of switch
        if(breakInfiniteloop==1){
            break;
        }
    }//enf of infinite loop
}

int main(){
    system("color f4");
    login();
    return 0;
}
void login(){// function login
	label:
	system("cls");
	cout<<"1.REGISTER"<<endl;
	cout<<"2.LOGIN"<<endl;
	cout<<"3.EXIT"<<endl;
    cout<<"Plese Enter Your Choice...";
	string p,q,w;
	int x;string s;
	cin>>x;
	if(x==1){

        system("cls");
        ofstream fout;
        cout<<"ENTER YOUR USERNAME"<<endl;
        cin>>s;
        cout<<"ENTER YOUR PASSWORD"<<endl;
        cin>>p;
        s=s+p;
        ifstream fin;
        string line;
        int offset=0;
        fin.open("myfile.txt");
        if(fin.is_open())
        {
            while(!fin.eof())
            {
                getline(fin,line);
                if(line.find(s,0)!=-1)
                {
                    cout<<"sorry! this username is not available"<<endl;
                    cout<<"Press any key to go to Home Page"<<endl;
                    char kk;
                    cin>>kk;
                    goto label;
                    //break;
                }
            }
        }
        fin.close();
        fout.open("myfile.txt",ios::app);
        fout<<s+"\n";
        fout.close();
        goto label;
	}
		else if(x==2){

			string line;
			system("cls");
  			ifstream fin;
  			int offset=0;
  			cout<<"ENTER YOUR USERNAME"<<endl;
  			cin>>q;
  			cout<<"ENTER YOUR PASSWORD"<<endl;
  			cin>>w;
  			q=q+w;
  			fin.open("myfile.txt");
  			if(fin.is_open())
  			{
  				while(!fin.eof())
  				{
  					getline(fin,line);
					if(line.find(q,0)!=-1)
					{
						cout<<"you are logged in !!"<<endl;
						offset=1;
                        menu();
						break;
                    }
				}
				if(offset==0)
				{
					cout<<"sorry you are unauthorised!!"<<endl;
					cout<<"Press 1 and enter to go to home page"<<endl;
					//getch();
					char o;
					cin>>o;
					goto label;
								  }
			}
  			fin.close();
	}
	else if(x==3){
		//return 0;
	}else{
	    goto label;
	}

}