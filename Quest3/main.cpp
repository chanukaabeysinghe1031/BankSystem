#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

using namespace std;

// This function is to calculate the charges for lower / negative balance
double calculateDateEndBalance(list<string> accounts,double totBalOfBankAtYrBeg){
    list<string>::iterator it;
    double amount = 0.0;
    string fileName2 = "/Users/chanukaabeysinghe/CLionProjects/Quest3/BankAccount.txt";
    ofstream bankAccount2(fileName2,std::ios::out|std::ios::app);
    for(it = accounts.begin(); it != accounts.end(); it++)
    {
        string tp;
        fstream newfile;
        double previousBalance;
        string date;
        string accountNo;
        double accountBalance;
        string fileName = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+*it+".txt";
        newfile.open(fileName,ios::in);
        if (newfile.is_open()) {
            //loop over the lines of the balanece file
            while (getline(newfile, tp)) { //read data from file object and put it into string.
                stringstream ss(tp);
                vector<string> vect;
                while( ss.good() )
                {
                    string substr;
                    getline( ss, substr, ',' );
                    vect.push_back( substr );
                }
                date = vect[0];
                accountNo =  vect[1];
                previousBalance = stod(vect[4]);
            }
        }


        if(previousBalance<0){
            amount = 50;
            previousBalance -= 50;
            accountBalance = previousBalance;
            totBalOfBankAtYrBeg += amount;
            ofstream account(fileName,std::ios::out|std::ios::app);
            account<< date<<","<<accountNo<<",4,"<<amount<<fixed<<setprecision(2)<<","<<accountBalance<<setprecision(2)<<fixed<<"\n";
            account.close();

            // Save the all the opening balances in Bank Account file
            bankAccount2<<date<<","<<accountNo <<",4,"<<amount<<fixed<<setprecision(2)<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";
        }else if(previousBalance<1000){
            amount = 10;
            previousBalance -=10;
            accountBalance = previousBalance;
            totBalOfBankAtYrBeg += amount;
            ofstream account(fileName,std::ios::out|std::ios::app);
            account<< date<<","<<accountNo<<",4,"<<amount<<fixed<<setprecision(2)<<","<<accountBalance<<setprecision(2)<<fixed<<"\n";
            account.close();

            // Save the all the opening balances in Bank Account file
            bankAccount2<<date<<","<<accountNo <<",4,"<<amount<<fixed<<setprecision(2)<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";

        }

        bankAccount2.close();
    }

    return amount;
}

double calculateInterest(list<string> accounts,double totBalOfBankAtYrBeg){
    list<string>::iterator it;
    double amount = 0;
    string fileName2 = "/Users/chanukaabeysinghe/CLionProjects/Quest3/BankAccount.txt";
    ofstream bankAccount2(fileName2,std::ios::out|std::ios::app);
    for(it = accounts.begin(); it != accounts.end(); it++)
    {
        string tp;
        fstream newfile;
        double previousBalance;
        string date;
        string accountNo;
        double accountBalance;
        string fileName = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+*it+".txt";
        newfile.open(fileName,ios::in);
        if (newfile.is_open()) {
            //loop over the lines of the balanece file
            while (getline(newfile, tp)) { //read data from file object and put it into string.
                stringstream ss(tp);
                vector<string> vect;
                while( ss.good() )
                {
                    string substr;
                    getline( ss, substr, ',' );
                    vect.push_back( substr );
                }
                date = vect[0];
                accountNo =  vect[1];
                previousBalance = stod(vect[4]);
            }
        }


        if(previousBalance<0){
            amount = previousBalance * 0.002/100;
            totBalOfBankAtYrBeg -= amount;
            accountBalance = previousBalance+amount;
            ofstream account(fileName,std::ios::out|std::ios::app);
            account<< date<<","<<accountNo<<",3,"<<amount<<fixed<<setprecision(2)<<","<<accountBalance<<setprecision(2)<<fixed<<"\n";
            account.close();

            // Save the all the opening balances in Bank Account file
            bankAccount2<<date<<","<<accountNo <<",3,"<<amount<<fixed<<setprecision(2)<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";
        }
        bankAccount2.close();
    }
    return amount;
}


int main() {
    int length;
    string tp;
    fstream newfile;
    string subStrings[6];

    double totBalOfBankAtYrBeg=0;

    list<string> accounts;

    string fileName2 = "/Users/chanukaabeysinghe/CLionProjects/Quest3/BankAccount.txt";
    ofstream bankAccount(fileName2);
    bankAccount<<totBalOfBankAtYrBeg<<"\n";
    bankAccount.close();
    newfile.open("/Users/chanukaabeysinghe/CLionProjects/Quest3/balance.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) {   //checking whether the file is open

        //loop over the lines of the balanece file
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            stringstream ss(tp);
            stringstream stringStream(tp);
            int count=0;

            string date;
            string accountNo;
            double openingBalance;

            // Get the date, account opening balance and account number
            while( stringStream.good() )
            {
               string subString;
               getline( stringStream, subString, ',' );
               if(count==0){
                   date = subString;
               }else if(count==1){
                    accountNo = subString;
               }else if(count==2){
                    openingBalance = stod(subString);
                    totBalOfBankAtYrBeg+=openingBalance;
               }
               count++;
            }

            // save the data in a seperate file for each account

            string fileName = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+accountNo+".txt";
            ofstream account(fileName);
            account<< date<<","<<accountNo<<",0,"<<openingBalance<<fixed<<setprecision(2)<<","<<openingBalance<<setprecision(2)<<fixed<<"\n";
            account.close();

            ofstream bankAccount2(fileName2,std::ios::out|std::ios::app);
            // Save the all the opening balances in Bank Account file
            bankAccount2<<date<<","<<accountNo <<",0,"<<openingBalance<<fixed<<setprecision(2)<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";
            bankAccount2.close();
            accounts.push_back(accountNo);

        }
    }

    newfile.close(); //close the file object

    // read the transactions file and save them in the accounts
    newfile.open("/Users/chanukaabeysinghe/CLionProjects/Quest3/transaction.txt",ios::in);
    if (newfile.is_open()) {   //checking whether the file is open

        //loop over the lines of the balanece file
        string checkDate = "";

        while (getline(newfile, tp)) {
            stringstream stringStream(tp);
            int count=0;

            string date;
            string accountNo;
            string transactionType;
            double amount;

            // Get the date, account opening balance and account number
            while( stringStream.good() )
            {
                string subString;
                getline( stringStream, subString, ',' );
                if(count==0){
                    date = subString;

                }else if(count==1){
                    accountNo = subString;
                }else if(count ==2){
                    transactionType = subString;
                }else if(count==3){
                    amount = stod(subString);
                    if(transactionType=="1"){

                        // Check whether current date is a new date
                        if(checkDate==""){
                            checkDate =date;
                            totBalOfBankAtYrBeg = totBalOfBankAtYrBeg - calculateInterest(accounts,totBalOfBankAtYrBeg);
                        }else if(checkDate.compare(date)!=0){
                            //  At the end of the date update the account balance
                            totBalOfBankAtYrBeg =totBalOfBankAtYrBeg +  calculateDateEndBalance(accounts,totBalOfBankAtYrBeg);
                            // Then update the checkdate to current date
                            checkDate = date;
                            for (auto const& i : accounts) {
                            }
                        }

                        string fileName3 = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+accountNo+".txt";
                        ofstream account;
                        double previousBalance;
                        double accountBalance;

                        // Read the latest account balance from the account file
                        string tp2;
                        fstream newfile2;

                        newfile2.open(fileName3,ios::in);
                        if (newfile2.is_open()) {
                            //loop over the lines of the balanece file
                            while (getline(newfile2, tp2)) { //read data from file object and put it into string.
                                stringstream ss(tp2);
                                vector<string> vect;
                                while( ss.good() )
                                {
                                    string substr;
                                    getline( ss, substr, ',' );
                                    vect.push_back( substr );
                                }
                                previousBalance = stod(vect[4]);
                            }
                        }

                        newfile2.close();

                        accountBalance = previousBalance + amount;
                        totBalOfBankAtYrBeg += amount;

                        account.open (fileName3,std::ios::out|std::ios::app);
                        account <<date<<","<<accountNo<<",1,"<<amount<<fixed<<setprecision(2)<<","<<accountBalance<<fixed<<setprecision(2)<< "\n";
                        account.close();

                        ofstream bankAccount2(fileName2,std::ios::out|std::ios::app);
                        bankAccount2<<date<<","<<accountNo <<",1,"<<amount<<fixed<<setprecision(2)<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";
                        bankAccount2.close();
                    }else if(transactionType=="2"){
                        string fileName3 = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+accountNo+".txt";
                        ofstream account;
                        double previousBalance;
                        double accountBalance;

                        // Read the latest account balance from the account file
                        string tp2;

                        fstream newfile2;

                        newfile2.open(fileName3,ios::in);
                        if (newfile2.is_open()) {
                            //loop over the lines of the balanece file
                            while (getline(newfile2, tp2)) { //read data from file object and put it into string.
                                stringstream ss(tp2);
                                vector<string> vect;
                                while( ss.good() )
                                {
                                    string substr;
                                    getline( ss, substr, ',' );
                                    vect.push_back( substr );
                                }
                                previousBalance = stod(vect[4]);
                            }
                        }

                        newfile2.close();

                        accountBalance = previousBalance - amount;
                        totBalOfBankAtYrBeg -= amount;
                        account.open (fileName3,std::ios::out|std::ios::app);
                        account <<date<<","<<accountNo<<",2,"<<amount<<fixed<<setprecision(2)<<","<<accountBalance<<fixed<< setprecision(2)<<"\n";
                        account.close();

                        ofstream bankAccount2(fileName2,std::ios::out|std::ios::app);
                        bankAccount2<<date<<","<<accountNo <<",2,"<<amount<<setprecision(2)<<fixed<<","<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<"\n";
                        bankAccount2.close();
                    }
                }
                count++;
            }
        }
    }
    bankAccount.close();

    cout<<"===================================================================="<<endl;
    cout<<"===================URBAN DEVELOPMENT BANK SYSTEM===================="<<endl;
    cout<<"===================================================================="<<endl;
    cout<<"SELECT THE OPTION (1,2,3)"<<endl;
    cout<<"1) VIEW BANK VAULT BALANCE"<<endl;
    cout<<"2) VIEW CURRENT BALANCES OF ALL THE BANK ACCOUNTS"<<endl;
    cout<<"3) VIEW BEGINING AND ENDING BALANCE OF ANY BANK ACCOUNT"<<endl;
    cout<<"4) EXIT"<<endl;
    int option;
    cin>>option;

    while(true){
        if(option==1){
            cout<<"===================================================================="<<endl;
            cout<<"BANK VAULT BALANCE  : - Rs. "<<totBalOfBankAtYrBeg<<fixed<<setprecision(2)<<endl;
            cout<<"===================================================================="<<endl;
        }else if(option==2){
            list<string>::iterator it;
            for(it = accounts.begin(); it != accounts.end(); it++) {
                string tp;
                fstream newfile;
                double previousBalance;
                string date;
                string accountNo;
                double amount = 0;
                double accountBalance;
                string fileName = "/Users/chanukaabeysinghe/CLionProjects/Quest3/" + *it + ".txt";
                newfile.open(fileName, ios::in);
                if (newfile.is_open()) {
                    //loop over the lines of the balanece file
                    while (getline(newfile, tp)) { //read data from file object and put it into string.
                        stringstream ss(tp);
                        vector<string> vect;
                        while (ss.good()) {
                            string substr;
                            getline(ss, substr, ',');
                            vect.push_back(substr);
                        }
                        date = vect[0];
                        accountNo = vect[1];
                        accountBalance = stod(vect[4]);
                    }
                }

                cout<<"===================================================================="<<endl;
                cout<<"ACCOUNT NO : - "<<accountNo<<endl;
                cout<<"ACCOUNT BALANCE : Rs. - "<<accountBalance<<setprecision(2)<<fixed<<endl;
            }

        }else if(option==3){
            cout<<"===================================================================="<<endl;
            cout<<"PLEASE ENTER THE ACCOUNT NUMBER : - ";
            string accountNumber ;
            cin>>accountNumber;
            cout<<"PLEASE ENTER THE DATE (YYYYMMDD) FORMAT : - ";
            string currentDate;
            bool notFound = true;
            string date;
            cin>>currentDate;
            string accountNo;
            double previousBalance = 0;
            double  beginingBalance ;
            double endBalance = 0;
            double amount;
            string fileName = "/Users/chanukaabeysinghe/CLionProjects/Quest3/"+accountNumber+".txt";
            newfile.open(fileName,ios::in);
            if (newfile.is_open()) {
                //loop over the lines of the balanece file
                while (getline(newfile, tp)) { //read data from file object and put it into string.
                    stringstream ss(tp);
                    vector<string> vect;
                    while( ss.good() )
                    {
                        string substr;
                        getline( ss, substr, ',' );
                        vect.push_back( substr );
                    }
                    date = vect[0];

                    if(date==currentDate&&notFound){
                        previousBalance = stod(vect[4]);
                        amount = stod(vect[3]);
                        beginingBalance = previousBalance - amount;
                        notFound=false;
                    }

                    endBalance = stod(vect[4]);
                }

                cout<<"BEGINING BALANCE : - Rs. "<<beginingBalance<<setprecision(2)<<fixed<<endl;
                cout<<"ENDING BALANCE : - Rs. "<<endBalance<<setprecision(2)<<fixed<<endl;

//                if(notFound){
//                    cout<<"INVALID DATE"<<endl;
//                }else{
//                    cout<<"BEGINING BALANCE : - Rs. "<<beginingBalance<<setprecision(2)<<fixed<<endl;
//                    cout<<"ENDING BALANCE : - Rs. "<<endBalance<<setprecision(2)<<fixed<<endl;
//                }
            }else{
                cout<<"THERE IS NO ACCOUNT WITH THIS NUMBER"<<endl;
            }

            cout<<"===================================================================="<<endl;

        }else if(option==4){
            break;
        }else{
            cout<<"SORRY WRONG INPUT"<<endl;
        }
        cout<<"SELECT THE OPTION (1,2,3)"<<endl;
        cout<<"1) VIEW BANK VAULT BALANCE"<<endl;
        cout<<"2) VIEW CURRENT BALANCES OF ALL THE BANK ACCOUNTS"<<endl;
        cout<<"3) VIEW BEGINING AND ENDING BALANCE OF ANY BANK ACCOUNT"<<endl;
        cout<<"4) EXIT"<<endl;
        cin>>option;
    }


    return 0;
}
