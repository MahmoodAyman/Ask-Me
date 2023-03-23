#include <bits/stdc++.h>
#include <unordered_map>
#include <windows.h> // for sleep function
using namespace std;
char br = '|';
vector<string> main_menu(7);
struct User
{
    string name, username, password;
};
string user_q, user_ans, ID;
int id = 1;
// --------- just identifiers for functions-----------

void Login();

void welcome_page();

void Signup();

void Home_page();

void add_to_feed(int id, string ans);

// General Functions and Variables
fstream accounts, account_answers, account_questions, feed;
// ------------ function to validate input doesn't contain | symbol
// ------------ cause I use it as a break inside file
bool validate(string s)
{
    for (auto it : s)
        if (it == '|')
            return 0;
    return 1;
}
bool file_empty(fstream &pFile)
{
    return pFile.peek() == fstream::traits_type::eof();
}

// ---------- start function----------
void open_accounts(string id)
{
    user_q = id + "questions.txt";
    user_ans = id + "answers.txt";
    account_answers.open(user_ans, ios::app | ios::in | ios::out);
    account_questions.open(user_q, ios::app | ios::in | ios::out);
}
void welcome_page()
{
    cout << "Welcome To Ask!" << endl;
    cout << "1. Login\n"
         << "2. Signup\n";
    cout << "Enter Number 1 or 2 : ";
    int a;
    cin >> a;
    if (a == 1)
    {
        Login();
    }
    else if (a == 2)
    {
        Signup();
    }
    else
    {
        // exit error
        cout << "You Enter Wrong Choice Please try again" << endl;
        exit(1);
    }
}
// define a files stream

void Login()
{
    // steps to open accounts file
    accounts.open("accounts.txt", ios::in);
    if (accounts.fail())
    {
        cerr << "someting went wrong\n";
        exit(1);
    }
    // start taking input
    User data;
    cout << "Enter Your username: ";
    cin >> data.username;
    string pass;
    bool found = 0;
    string line;
    // search about matching data
    while (getline(accounts, line))
    {
        if (data.username == line.substr(0, line.size() - line.find('|') + 1))
        {
            found = 1;
            // save password just in case
            pass = line.substr(line.find('|') + 1);
            break;
        }
    }
    if (found)
    {
        cout << "Enter Your Password: ";
        while (cin >> data.password)
        {
            if (data.password == pass)
            {
                // Enter Account
                cout << "Cool You are in\n";
                cout << "Enojy :) \n";
                ID = data.username;
                user_q = data.username + "questions.txt";
                user_ans = data.username + "answers.txt";
                Sleep(2000);
                system("CLS");
                Home_page();
            }
            else
            {
                // Try again
                cout << "Wrong Password Please try again : ";
            }
        }
    }
    else
    {
        // try username
        cout << "username not found \n"
             << "Please Try again or Signup\n";
        accounts.close();
        welcome_page();
    }
    accounts.close();
}

// function to confirm that username is unique
bool validate_username(string s)
{
    string line;
    while (getline(accounts, line))
    {
        if (s == line.substr(0, line.size() - line.find('|') + 1))
        {
            return 0;
        }
    }
    return 1;
}

// signup function
void Signup()
{
    // same as login but with an extra steps
    accounts.open("accounts.txt", ios::app);
    if (accounts.fail())
    {
        cerr << "someting went wrong\n";
        exit(1);
    }
    User data;
    cout << "Enter Your Name: ";
    cin >> data.name;
    accounts << data.name << "\n";
    cout << "\nOH Hello " << data.name << " we are about to done\n";
    cout << "Enter Your User Name: ";
    bool chk_user1 = 0, chk_user2;
    while (cin >> data.username)
    {
        chk_user1 = validate(data.username);
        if (chk_user1)
            break;
        else
        {
            cout << "username contains Illegal Character | please remove it and try again\n";
            cout << "Enter Your User Name: ";
        }
        chk_user2 = validate_username(data.username);
        if (!chk_user2)
        {
            cout << "username is taken Please choose another one\n";
            cout << "Enter Your User Name: ";
        }
        else
            break;
    }
    accounts << data.username << "|";
    cout << "\n Just one step more\n";
    cout << "Enter Your Password: ";
    ID = data.username;
    bool chk_password = 0;
    while (cin >> data.password)
    {
        chk_password = validate(data.password);
        if (chk_password)
            break;
        else
        {
            cout << "Password contains Illegal Character | please remove it and try again\n";
            cout << "Enter Your User Password: ";
        }
    }
    accounts << data.password << endl;
    cout << "Now We are Done! \n";
    cout << "You Can Login :). \n";
    accounts << "-----------------------\n";
    accounts.close();
    open_accounts(ID);
    Sleep(3000);
    welcome_page();
}

// main operations

void show_your_answers()
{
    account_answers.open(user_ans, ios::in);
    if (account_answers.fail())
    {
        cerr << "Something Wrong Happened! \n";
        exit(1);
    }
    if (file_empty(account_answers))
    {
        cout << "You Don't Have Answer any Questions Yet\n";
        system("CLS");
        Sleep(2000); // just delay what's next 3 seconds
        Home_page();
    }
    else
    {
        string line;
        string question, question_id;
        bool f = 0; // if number inside question not id
        while (getline(account_answers, line))
        {
            for (int i = 0; i < (int)line.size(); i++)
            {
                if (isdigit(line[i]) && !f)
                    question_id += line[i];
                else
                {
                    f = 1;
                    question += line[i];
                }
            }
            line = question = "";
            cout << "Question with ID (" << question_id << ") "
                 << "\t Your Answer Is :  " << question << endl;
        }
    }
    Home_page();
}

// second operation show and ask Questions
bool save_question_ans(int id, string ans)
{
    if (account_answers.fail())
        return 0;
    add_to_feed(id, ans);
    account_answers << id << "|" << ans << endl;
    return 1;
}
void show_your_questions()
{
    // account_questions.open(user_q);
    if (account_questions.fail())
    {
        cout << user_q << endl;
        cerr << "Something Wrong Happened! \n";
        exit(1);
    }
    if (file_empty(account_questions))
    {
        cout << "You Don't Have Answer any Questions Yet\n";
        system("CLS");
        Sleep(3000); // just delay what's next 3 seconds
        Home_page();
    }
    else
    {
        unordered_map<int, string> mp;
        string line;
        string question, question_id;
        bool f = 0; // if number inside question not id
        while (getline(account_questions, line))
        {
            question_id = line.substr(0, '|');
            question = line.substr(line.find('|'));
            mp[stoi(line)] = question;
            line = question = "";
            cout << "Question with ID (" << question_id << ") "
                 << "\t Is :  " << question << endl;
        }
        cout << "1. Answer Question\n"
             << "2. Back to Home \n"
             << "Enter a Number of Your Choice: ";
        int a;
        cin >> a;
        if (a == 1)
        {
            cout << "Enter ID Of the Question You want to answer: ";
            int question_id;
            cin >> question_id;
            if (mp[question_id].size() > 0)
            {
                string ans;
                cout << "Enter Your Answer : ";
                getline(cin, ans);
                if (save_question_ans(question_id, ans))
                {
                    cout << "Answer Saved Successfully" << endl;
                    Home_page();
                }
                else
                {
                    cout << "Something Wrong Please Try Again Later\n";
                    system("CLS");
                    Home_page();
                }
            }
            else
            {
                cout << "Wrong ID Please Try Again\n";
            }
        }
        else if (a == 2)
        {
            system("CLS");
            Sleep(2000);
            Home_page();
        }
        else
        {
            cout << "Wrong Please choose a correct number\n";
        }
    }
    account_questions.close();
}

// ask question
unordered_map<string, int> get_all_accounts()
{
    accounts.open("accounts.txt", ios::in);
    if (accounts.fail())
    {
        cerr << "something went wrong try again later\n";
        exit(1);
    }
    unordered_map<string, int> mp;
    string line;
    while (getline(accounts, line))
    {
        if (line.find('|') == string::npos)
            continue;
        else
        {
            mp[line.substr(0, line.find('|') + 1)] = 1;
        }
    }
    return mp;
}

// List Users
void list_users()
{
    accounts.open("accounts.txt", ios::in);
    string line;
    while (getline(accounts, line))
    {
        if (line.find('|') == string::npos)
            cout << line;
        else
        {
            cout << " username is: ";
            cout << line.substr(0, line.find('|') + 1) << endl;
            ;
        }
    }
    int c;
    cout << "Enter 1 if You want Home or 2 if your want exit: ";
    cin >> c;
    if (c == 1)
    {
        accounts.close();
        Home_page();
    }
    else
    {
        accounts.close();
        return;
    }
}

// Feed
void add_to_feed(int id, string ans)
{
    feed << ID << "ans a Question with ID " << id << endl
         << ans << endl;
}
void show_feed()
{
    if (feed.fail())
    {
        cerr << "Something went Wrong\n";
        exit(1);
    }
    string line;
    while (getline(feed, line))
        cout << line << endl;
    int c;
    cout << "Enter 1 if You want Home or 2 if your want exit: ";
    cin >> c;
    if (c == 1)
        Home_page();
    else
        return;
}

// logout
void Logout()
{
    account_answers.close();
    account_questions.close();
    feed.close();
    cout << "We Will Miss You\n";
    system("CLS");
    Sleep(2000);
    welcome_page();
}
vector<string> one_run_func()
{
    vector<string> v;
    v.emplace_back("1. Show Your Answers\n");
    v.emplace_back("2. Show Your Questions\n");
    // v.emplace_back("3. Answer Question\n");
    v.emplace_back("3.Delete Question\n");
    v.emplace_back("4. Ask Question\n");
    v.emplace_back("5. List Users\n");
    v.emplace_back("6. Feed \n");
    v.emplace_back("7. Logout\n");
    return v;
}

void Home_page()
{
    main_menu = one_run_func();
    for (auto &it : main_menu)
        cout << it;
    cout << "\n Enter Number of What You Want: ";
    int a;
    cin >> a;
    if (a == 1)
        show_your_answers();
    else if (a == 2)
        show_your_questions();
    else if (a == 3)
    {
        cout << "Still in Development try again later";
        return;
    }
    else if (a == 4)
    {
        unordered_map<string, int> mp = get_all_accounts();
        cout << "Enter the username of the Person You Want to ask: ";
        string s;
        cin >> s;
        if (mp[s])
        {
            string question;
            cout << "Ask Your Question: ";
            getline(cin, question);
            if (question.back() != '?')
                question += '?';
            account_questions.open(s + "questions.txt", ios::app);
            string line;
            int qid = 0;
            while (getline(account_questions, line))
            {
                qid++;
            }
            account_questions << qid << "|" << question << endl;
            account_questions.close();
            cout << "Question Sent Successfully \n"
                 << "Enter 1 to Back Home or 2 to End: ";
            int a;
            cin >> a;
            if (a == 1)
                Home_page();
            else
                return;
        }
    }
    else if (a == 5)
        list_users();
    else if (a == 6)
        show_feed();
    else if (a == 7)
        Logout();
}

int main()
{
    welcome_page();
}