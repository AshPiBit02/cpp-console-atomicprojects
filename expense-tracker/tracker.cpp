#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<sstream>
#include<cstdlib>
using namespace std;
string truncate(const string& text, size_t width)
{
    if(text.size()>width) 
    {
        return text.substr(0,width-4)+"....";
    }
    return text;
}
class Transaction{
    protected:
    string date;
    string description;
    double amount;
    public:
    Transaction(string date,string description, double amount)
    {
        this->date=date;
        this->description=(description.empty()? "null":description);
        this->amount=amount;
    }
    //Common getters
    string getDate() const { return date;}
    string getDescription() const{ return description; }
    double getAmount() const { return amount; }
};
class Expense: public Transaction{
    string category;
    public:
    Expense(string date,string category,string description,double amount): Transaction(date,description,amount)
    {
        this->category=category;
    }
    void save(const string& expense_file) const{
        ofstream expfile(expense_file,ios::app);
        if(expfile)
        {
            expfile<<date<<"|"<<category<<"|"<<amount<<"|"<<description<<endl;
        }
        else
        {
            cout<<"Error: Could not open file."<<endl;
        }
        expfile.close();
    }
};
void add_expense()
{
    string date,description;
    double amount;
    int category_choice;
    vector<string>categories={"Food & Grocery","Travel","Rent","Electricity","Stationery","Shopping","Lunch","Others","Miscategory"};
    cout<<"Enter date (DD MMM YYYY)";// 07 Jan 2026
    cin.ignore();
    getline(cin,date);
    cout<<"\n----------Categories--------"<<endl;
    for(size_t i=0;i<categories.size();i++)
    {
        cout<<i+1<<". "<<categories[i]<<endl;
    }
    cout<<"\nSelect Category:";
    cin>>category_choice;
    if(category_choice<1 || category_choice>categories.size())
    {
        cout<<"Invalid choice! Defaulting to Miscategory"<<endl;
        category_choice=categories.size();
    }
    cout<<"Enter amount:";
    cin>>amount;
    cin.ignore();
    cout<<"Enter description(Optional): ";
    getline(cin,description);
    Expense exp(date,categories[category_choice-1],description,amount);
    exp.save("expense_file.txt");//saves using class method
    cout<<"Expense added successfully"<<endl;

}
class Inflow: public Transaction{
    string source;
    public:
    Inflow(string date,string source,double amount,string description):Transaction(date,description,amount)
    {
        this->source=source.empty()?"Papa":source;
    }
    void save(const string& inflow_file) const{
        ofstream flowfile(inflow_file,ios::app);
        if(flowfile)
        {
            flowfile<<date<<"|"<<source<<"|"<<amount<<"|"<<description<<endl;
        }
        flowfile.close();
    }
};
void add_inflow()
{
    string date,description,source;
    double amount;
    cout<<"Enter date(DD MM YYY):";
    cin.ignore();
    getline(cin,date);
    cout<<"Enter source(If other than father):";
    getline(cin,source);
    cout<<"Enter amount:";
    cin>>amount;
    cin.ignore();
    cout<<"Enter description(Optional):";
    getline(cin,description);
    Inflow inflow(date,source,amount,description);
    inflow.save("inflow_file.txt");
    cout<<"Inflow added successfully"<<endl;
}
void view_expenses(){
    ifstream expfile("expense_file.txt");
    if(!expfile)
    {
        cout<<"No expense records found!"<<endl;
        return;
    }
    string line,date,category,description;
    double amount,totoal_amount=0;
    cout<<left<<setw(15)<<"Date"<<setw(15)<<"Category"<<setw(12)<<"Amount"<<setw(30)<<"Description"<<endl;
    cout<<string(77,'-')<<endl;
    //Display and read each record
    while(getline(expfile,line)){
        stringstream ss(line);
        getline(ss,date,'|');
        getline(ss,category,'|');
        ss>>amount;
        ss.ignore();
        ostringstream amt;
        amt<<"Rs."<<fixed<<setprecision(2)<<amount;
        getline(ss,description);
        cout<<left<<setw(15)<<date<<setw(15)<<category<<setw(14)<<amt.str()
        <<setw(30)<<truncate(description,30)<<endl;
        totoal_amount+=amount;
    }
    cout<<string(77,'.')<<endl;
    cout<<"Total Expense: Rs."<<totoal_amount<<endl;
    expfile.close();
}
void view_flow_summary(){
    ifstream flowfile("inflow_file.txt");
    if(!flowfile)
    {
        cout<<"No inflow records found!"<<endl;
        return ;
    }
    string line,date,source,description;
    double amount;
    double total_amount=0;
    cout<<left<<setw(15)<<"Date"<<setw(15)<<"Source"<<setw(12)<<"Amount"<<setw(30)<<"Description"<<endl;
    cout<<string(77,'-')<<endl;
    //Read and display each record if any
    while(getline(flowfile,line)){
        stringstream ss(line);
        getline(ss,date,'|');
        getline(ss,source,'|');
        ss>>amount;
        ss.ignore();
        getline(ss,description);
        ostringstream amt;
        amt<<"Rs."<<fixed<<setprecision(2)<<amount;
        cout<<left<<setw(15)<<date<<setw(15)<<source<<setw(14)<<
        amt.str()<<setw(30)<<truncate(description,30)<<endl;
        total_amount+=amount;
    }
    cout<<string(77,'.')<<endl;
    cout<<"Total Inflow: Rs."<<fixed<<setprecision(2)<<total_amount<<endl;
    flowfile.close();
}
void save_exit()
{
    cout<<"\nAll data has been saved successfully."<<endl;
    cout<<string(75,'.')<<endl;
    exit(0);
}
void erase_entire_data()
{
    const string security_code="2274";
    string entered_code;
    cout<<"\nEnter security code to erase entire data: ";
    cin>>entered_code;
    if(entered_code==security_code)
    {
        ofstream expfile("expense_file.txt",ios::trunc);
        ofstream flowfile("inflow_file.txt",ios::trunc);
        expfile.close();
        flowfile.close();
        cout<<"All data erase successfully!"<<endl;
    }
    else
    {
        cout<<"Invalid security code!"<<endl;
    }
}
void main_menu_bar()
{
    int menu_choice=0;
    while(menu_choice!=6){
        cout<<string(36,'.');
        cout<<"MENU";
        cout<<string(36,'.')<<endl;
        cout<<"1.Add Expense\n2.Add Inflow\n3.View Expenses\n4.View Flow Summary\n5.Erase Entire Data\n6.Save & Exit"<<endl;
        cout<<"Enter Operation:";
    cin>>menu_choice;
    switch(menu_choice)
    {
        case 1:
        add_expense();break;
        case 2:
        add_inflow();break;
        case 3:
        view_expenses();break;
        case 4:
        view_flow_summary();break;
        case 5:
        erase_entire_data();break;
        case 6:
        save_exit();break;
        default:
        cout<<"Invalid choice!"<<endl;break;
    }
}
}

int main()
{
    main_menu_bar();
    return 0;
}