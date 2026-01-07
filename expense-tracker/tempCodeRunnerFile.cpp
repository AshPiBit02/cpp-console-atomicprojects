#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
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
    string getDescriptiona() const{ return description; }
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
            expfile<<date<<"\t\t\t\t\t\t"<<category<<"\t\t\t\t\t"<<amount<<"\t\t\t\t\t"<<description<<"\t\t\t\t\t"<<endl;
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
    cin>>date;
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
    Inflow(string date,string source,string description,double amount):Transaction(date,description,amount)
    {
        this->source=source.empty()?"Papa":description;
    }
    void save(const string& inflow_file) const{
        ofstream flowfile(inflow_file,ios::app);
        if(flowfile)
        {
            flowfile<<date<<"\t\t\t\t\t"<<source<<"\t\t\t\t\t"<<amount<<"\t\t\t\t\t"<<description<<endl;
        }
        flowfile.close();
    }
};
void add_inflow()
{
    string date,description;
    double amount;
}
void view_expenses(){ return;}
void view_flow_summary(){return ;}
void save_exit(){return ;}
void main_menu_bar()
{
    cout<<"---------------MENU-------------"<<endl;
    cout<<"1.Add Expense\n2.Add Inflow\n3.View Expenses\n4.View Flow Summary\n5.Save & Exit"<<endl;
    int menu_choice;
    cout<<"Enter Operation:";
    cin>>menu_choice;
    switch(menu_choice)
    {
        case 1:
        add_expense();
        case 2:
        add_inflow();
        case 3:
        view_expenses();
        case 4:
        view_flow_summary();
        case 5:
        save_exit();
    }

}
int main()
{
    
}