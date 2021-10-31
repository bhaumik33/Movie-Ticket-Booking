#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

//display of seats variables
int screen,movie,time_movie,no_of_seats;
int seats_array[5][6][5][12][18];
//[screen no][movie no. ][movie time][rows][columns] 

class MovieBookingSystem
{
private:
    //manager variables
    int movie_id,movie_screen;
    char movie_name[50],movie_genre[50],movie_age_rating[10],movie_language[50],movie_duration[10];
    char movie_time[100],movie_info[250];

    //customer variables
    float movie_price[3]={200,300,500}; //silver, gold, platinum
    float movie_price_total;

    int flag_book_tickets;

public:
    MovieBookingSystem()
    {
        movie_id=0,movie_screen=0,flag_book_tickets=0;
        strcpy(movie_name," ");
        strcpy(movie_genre," ");
        strcpy(movie_age_rating," ");
        strcpy(movie_language," ");
        strcpy(movie_duration," ");
        strcpy(movie_time," ");
        strcpy(movie_info," ");

        movie_price_total=0.0;
    }
    ~MovieBookingSystem(){};

    //LOGIN (MAIN FUNCTION)
    void Lets_Login();

    //manager functions
    int get_movie_id()//code here itself
    {
        return movie_id;
    }
    int manager_check_count();

    void manager_mode();
    void manager_write();
    void manager_add_movie();
    void manager_delete_movie();

    //common function between customer and manger
    void display_movies(int c_or_m);
    void display_movie_details() //code here itself
    {
        cout<<"\n\nID: "<<movie_id<<endl;
        cout<<"Name and duration: "<<movie_name<<"\t"<<movie_duration<<endl;
        cout<<"Timings: "<<movie_time<<endl;
        cout<<"Screen no: "<<movie_screen<<endl;
        cout<<"Genre: "<<movie_genre<<endl;
        cout<<"Age Rating: "<<movie_age_rating<<endl; 
        cout<<"Language: "<<movie_language<<endl;
        cout<<"Synopsis: "<<movie_info<<"\n";
    }

    //customer functions
    void customer_mode();
    void customer_tickets_booking();
    void customer_assign_seats(int n_o_s);
    void customer_seat_display(int flag_book_tickets,int nos);
    void customer_snacks();
    void customer_billing();
};

void MovieBookingSystem::display_movies(int c_or_m)
{
    MovieBookingSystem mbs_d;
    ifstream fin;
    int no_display=0;
    fin.open("movie_names.dat",ios::in);
    fin.seekg(0);
    cout<<"\n**************************************************************\n";

    while (fin.read((char *)&mbs_d,sizeof(mbs_d)))
    {
        if(fin.eof())break;
        if (mbs_d.movie_id!=0)
        {
            mbs_d.display_movie_details();
            no_display++;
        }
        else
        {
            continue;
        }
    }
    if (no_display==0)
    {
        cout<<"\n\t|No data was found, please enter the movies|\n";
    }
    fin.close();
    cout<<"\n**************************************************************";
    if (c_or_m==1)
    {
        MovieBookingSystem::manager_mode();
    }
    else if (c_or_m==0)
    {
        MovieBookingSystem::customer_mode();
    }
}

//START OF MANGER FUNCTIONS
void MovieBookingSystem::manager_delete_movie()
{
    MovieBookingSystem mbs;
    ifstream fin;
    fin.open("movie_names.dat");
    ofstream fout;
    fout.open("temp_movie_names.dat");

    int flag_got_data=0,temp_movie_id=0;
    char confirm_delete='a';
    cout<<"\nEnter the ID of movie that is to be deleted: ";
    cin>>temp_movie_id;

    while (fin.read((char *)&mbs,sizeof(mbs)))
    {
        if (mbs.get_movie_id()==temp_movie_id)
        {
            mbs.display_movie_details();
            flag_got_data=1;
            cout<<"\n\nAre you SURE???[y/n] ";
            cin>>confirm_delete;
            if(confirm_delete=='n')
            {
                fout.write((char *)&mbs,sizeof(mbs));
            }
        }
        else
        {
            fout.write((char *)&mbs,sizeof(mbs));
        }
    }
    if (flag_got_data==0)
    {
        cout<<"\n\t|No data was found, please try again|\n";
        MovieBookingSystem::manager_mode();
    }
    fin.close();
    fout.close();
    remove("movie_names.dat");
    rename("temp_movie_names.dat","movie_names.dat");

    cout<<"\n\t|Deletion of Data Completed|\n\t|Data available in the file now will be shown below|\n\n";
    MovieBookingSystem::display_movies(1);
    //MovieBookingSystem::manager_mode();
}

void MovieBookingSystem::manager_write()
{
    cout<<"\nEnter the Movie ID [int]: ";
    cin>>movie_id;
    cout<<"\nEnter the Movie Name: ";
    fflush(stdin);
    cin.getline(movie_name,50);
    cout<<"\nEnter the Movie Duration(eg: [2h 20m] ): ";
    fflush(stdin);
    cin.getline(movie_duration,10);
    cout<<"\nEnter the Movie Timings (All): ";
    fflush(stdin);
    cin.getline(movie_time,100);
    cout<<"\nEnter the Movie screen no. [int]: ";
    cin>>movie_screen;
    cout<<"\nEnter the Movie Genre: ";
    fflush(stdin);
    cin.getline(movie_genre,50);
    cout<<"\nEnter the Movie age rating: ";
    fflush(stdin);
    cin.getline(movie_age_rating,10);
    cout<<"\nEnter the Movie Languages: ";
    fflush(stdin);
    cin.getline(movie_language,50);
    cout<<"\nEnter the Movie info: ";
    fflush(stdin);
    cin.getline(movie_info,250);
    cout<<"\n\n#######################################################\n";
}

int MovieBookingSystem::manager_check_count()
{
    MovieBookingSystem mbs_d;
    ifstream fin;
    int count_of_movies=0;
    fin.open("movie_names.dat",ios::in);
    fin.seekg(0);

    while (fin.read((char *)&mbs_d,sizeof(mbs_d)))
    {
        if(fin.eof())break;
        if (mbs_d.movie_id!=0)
        {
            count_of_movies++;
        }
        else
        {
            continue;
        }
     }
    fin.close();
    return count_of_movies;
}

void MovieBookingSystem::manager_add_movie()
{
    int add_cap=MovieBookingSystem::manager_check_count();
    fstream file;
    MovieBookingSystem mbs_e;
    file.open("movie_names.dat",ios::in|ios::app|ios::out);

    if (add_cap==5)
    {
        cout<<"\n\t|Please delete some movies to add more :( |\n";
        MovieBookingSystem::manager_mode();
    }
    else
    {
        cout<<"\n\t|You can add "<<5-add_cap<<" more movies|\n";
        cout<<"\n\nEnter the details of the movie \n";
        mbs_e.manager_write();
        file.write((char *)&mbs_e,sizeof(mbs_e));
        cout<<"\n\t|Data added into the file|\n";
        file.close();
        MovieBookingSystem::manager_mode();
    }
}

void MovieBookingSystem::manager_mode()
{
    MovieBookingSystem mbs;
    char choice_manager_mode[5];

    cout<<"\n\n\t--------------------------------";
    cout<<"\n\t| 1)Add the movie details      |";
    cout<<"\n\t| 2)Delete the movie details   |";
    cout<<"\n\t| 3)Display the movie details  |";
    cout<<"\n\t| 4)Go back to login           |";
    cout<<"\n\t--------------------------------\n";
    cout<<"\nEnter your choice: ";
    fflush(stdin);
    cin>>choice_manager_mode;

    if (strcmp(choice_manager_mode,"1")==0)
    {
        mbs.manager_add_movie();
    }
    else if (strcmp(choice_manager_mode,"2")==0)
    {
        mbs.manager_delete_movie();
    }
    else if (strcmp(choice_manager_mode,"3")==0)
    {
        mbs.display_movies(1);
    }
    else if (strcmp(choice_manager_mode,"4")==0)
    {
        cout<<"\n\n\t|| Hope To See You Soon :) ||\n";
        mbs.Lets_Login();
    }
    else
    {
        cout<<"\n\t|Invalid input, please try again|";
        mbs.manager_mode();
    }
}

//START OF CUSTOMER FUNCTIONS
void MovieBookingSystem::customer_mode()
{
    MovieBookingSystem mbs;
    char choice_customer_mode[5];

    cout<<"\n\n\t--------------------------------";
    cout<<"\n\t| 1)See the movie details      |";
    cout<<"\n\t| 2)Book Tickets               |";
    cout<<"\n\t| 3)Go back to login           |";
    cout<<"\n\t--------------------------------\n";
    cout<<"\nEnter your choice: ";
    fflush(stdin);
    cin>>choice_customer_mode;

    if (strcmp(choice_customer_mode,"1")==0)
    {
        mbs.display_movies(0);
    }
    else if (strcmp(choice_customer_mode,"2")==0)
    {
        mbs.customer_tickets_booking();
    }
    else if (strcmp(choice_customer_mode,"3")==0)
    {
        cout<<"\n\n\t|| Hope To See You Soon :) ||\n";
        mbs.Lets_Login();
    }
    else
    {
        cout<<"\n\t|Invalid input, please try again|";
        mbs.customer_mode();
    }
}

void MovieBookingSystem::customer_tickets_booking()
{
    MovieBookingSystem mbs_ctb;
    // function to show only the id, name and duration of movie
    remove("customer_bill.txt");
    cout<<"\n\nEnter the Movie Id of the movie: ";
    cin>>movie;

    (movie==4)?cout<<"\n\n1) 9:00 to 11:20\n2) 12:00 to 14:20\nEnter the Time For the Show: ":
    (movie==5)?cout<<"\n\n3) 15:00 to 17:20\n4) 18:00 to 20:20\nEnter the Time For the Show: ":
    cout<<"\n\n1) 9:00 to 11:20\n2) 12:00 to 14:20\n3) 15:00 to 17:20\n4) 18:00 to 20:20\nEnter the Time For the Show: ";
    cin>>time_movie;

    (movie==1)?screen=1:(movie==2)?screen=2:(movie==3)?screen=3:screen=4;

    cout<<"\nEnter the No: of seats you want to book: ";
    cin>>no_of_seats;
    int nos_1=no_of_seats;

    flag_book_tickets=0;
    mbs_ctb.customer_seat_display(flag_book_tickets,0);

    char choice_book_tickets[5];
    cout<<"\nEnter 1 to continue booking tickets for this movie\nEnter 2 to Go back to customer menu";
    cout<<"\nYour Choice: ";
    fflush(stdin);
    cin>>choice_book_tickets;
    if (strcmp(choice_book_tickets,"1")==0)
    {
        flag_book_tickets=1;
        mbs_ctb.customer_seat_display(flag_book_tickets,nos_1);
    }
    else 
    {
        cout<<"\n\t|Going To Customer Menu|\n";
        mbs_ctb.customer_mode();
    }
    MovieBookingSystem::customer_snacks();
}

void MovieBookingSystem::customer_assign_seats(int n_o_s)
{
    movie_price_total=0;
    cout<<"\n*No of seats: "<<n_o_s<<endl;
    char bill_row[220];int bill_seat_no[220];
    for (int k = 0; k < n_o_s; k++)
    {
        int choice_column=0,row_number=0;
        cout<<"\n*********************Entry no: "<<k+1<<" *********************\n";
        cout<<"\nEnter the Row you want [The letter]: ";
        cin>>bill_row[k];
        cout<<"\nEnter the Seat No. you want [integer]: ";
        cin>>bill_seat_no[k];
        choice_column=bill_seat_no[k]-1;
        for(int i=0;i<13;i++)
        {
            char row_letter='M';
            row_letter=row_letter-i;
            cout<<"\t";
            if (bill_row[k]==row_letter)
            {
                row_number=i;
            }
        }
        if (bill_row[k]=='M'||bill_row[k]=='L')
        {
            movie_price_total=movie_price_total+movie_price[2];
        }
        if (bill_row[k]=='D'||bill_row[k]=='E'||bill_row[k]=='F'||bill_row[k]=='G'||bill_row[k]=='H'||bill_row[k]=='I'||bill_row[k]=='J'||bill_row[k]=='K')
        {
            movie_price_total=movie_price_total+movie_price[1];
        }
        if (bill_row[k]=='A'||bill_row[k]=='B'||bill_row[k]=='C')
        {
            movie_price_total=movie_price_total+movie_price[0];
        }

        //cout<<"\nNet Movie_Price_without GST : "<<movie_price_total<<endl;
        if (seats_array[screen][movie][time_movie][row_number][choice_column]!=1)
        {
            seats_array[screen][movie][time_movie][row_number][choice_column]=1;
        }
        else
        {
            cout<<"\n\t|You selected an already booked seat :(  |";
            cout<<"\n\t|       Please Select with caution       |\n";
            MovieBookingSystem::customer_assign_seats(n_o_s);
        }
    }
    cout<<"\n\t|Tickets Booked :D|\n";

    ofstream file_write;
    file_write.open("customer_bill.txt",ios::out|ios::app);
    file_write<<"\n_________________________________________________________________\n";
    if (movie==1)
    {
        file_write<<"\nTickets for Shang-Chi and the Lege...[ "<<n_o_s<<" ] \t"<<movie_price_total<<"Rs\nScreen No: "<<screen<<endl<<"Seats: ";

        for (int i = 0; i < n_o_s; i++)
        {
            file_write<<" "<<bill_row[i]<<bill_seat_no[i];
        }
        file_write<<endl;

        if (time_movie==1)
        {
            file_write<<"Time: 9:00 to 11:20 \n";
        }
        else if (time_movie==2)
        {
            file_write<<"Time: 12:00 to 14:20 \n";
        }
        else if (time_movie==3)
        {
            file_write<<"Time: 15:00 to 17:20 \n";
        }
        else
        {
            file_write<<"Time: 18:00 to 20:20 \n";
        }
    }
    else if (movie==2)
    {
        file_write<<"\nTickets for Bell Bottom[ "<<n_o_s<<" ]\t\t\t"<<movie_price_total<<"Rs\nScreen No: "<<screen<<endl<<"Seats: ";
        for (int i = 0; i < n_o_s; i++)
        {
            file_write<<" "<<bill_row[i]<<bill_seat_no[i];
        }
        file_write<<endl;
        if (time_movie==1)
        {
            file_write<<"Time: 9:00 to 11:20 \n";
        }
        else if (time_movie==2)
        {
            file_write<<"Time: 12:00 to 14:20 \n";
        }
        else if (time_movie==3)
        {
            file_write<<"Time: 15:00 to 17:20 \n";
        }
        else
        {
            file_write<<"Time: 18:00 to 20:20 \n";
        }
    }
    else if (movie==3)
    {
        file_write<<"\nTickets for Thalaivii[ "<<n_o_s<<"]\t\t\t"<<movie_price_total<<"Rs\nScreen No: "<<screen<<endl<<"Seats: ";
        for (int i = 0; i < n_o_s; i++)
        {
            file_write<<" "<<bill_row[i]<<bill_seat_no[i];
        }
        file_write<<endl;
        if (time_movie==1)
        {
            file_write<<"Time: 9:00 to 11:20 \n";
        }
        else if (time_movie==2)
        {
            file_write<<"Time: 12:00 to 14:20 \n";
        }
        else if (time_movie==3)
        {
            file_write<<"Time: 15:00 to 17:20 \n";
        }
        else
        {
            file_write<<"Time: 18:00 to 20:20 \n";
        }
    }
    else if (movie==4)
    {
        file_write<<"\nTickets for Jungle Cruise[ "<<n_o_s<<" ]\t\t\t"<<movie_price_total<<"Rs\nScreen No: "<<screen<<endl<<"Seats: ";
        for (int i = 0; i < n_o_s; i++)
        {
            file_write<<" "<<bill_row[i]<<bill_seat_no[i];
        }
        file_write<<endl;
        if (time_movie==1)
        {
            file_write<<"Time: 9:00 to 11:20 \n";
        }
        else if (time_movie==2)
        {
            file_write<<"Time: 12:00 to 14:20 \n";
        }
        else if (time_movie==3)
        {
            file_write<<"Time: 15:00 to 17:20 \n";
        }
        else
        {
            file_write<<"Time: 18:00 to 20:20 \n";
        }
    }
    else if (movie==5)
    {
        file_write<<"\nTickets for Don't Breath 2[ "<<n_o_s<<" ]\t\t\t"<<movie_price_total<<"Rs\nScreen No: "<<screen<<endl<<"Seats: ";
        for (int i = 0; i < n_o_s; i++)
        {
            file_write<<" "<<bill_row[i]<<bill_seat_no[i];
        }
        file_write<<endl;
        if (time_movie==1)
        {
            file_write<<"Time: 9:00 to 11:20 \n";
        }
        else if (time_movie==2)
        {
            file_write<<"Time: 12:00 to 14:20 \n";
        }
        else if (time_movie==3)
        {
            file_write<<"Time: 15:00 to 17:20 \n";
        }
        else
        {
            file_write<<"Time: 18:00 to 20:20 \n";
        }
    }
    file_write.close();
}

void MovieBookingSystem::customer_seat_display(int flag_book_tickets,int nos)
{
    if (flag_book_tickets==1)
    {
        MovieBookingSystem::customer_assign_seats(nos);
    }
    int i,j;
    char seat_letter='M';
    //system("cls");
    cout<<"\n____________________________________________________________________________________________________________________________\n";
    cout<<"\n\n\t\tCOST OF PLATINUM:Rs 500/-\t\t";
    cout<<"COST OF GOLD :Rs 300/-\t\t";
    cout<<"COST OF  SILVER :Rs 200/-\n";
   	cout<<"\n\n\t\t\t\t\t\t\tBOOKED SEATS ARE MARKED WITH [x]\n\nPlatinum\n";
    for(i=0;i<13;i++)
    {
        char seat_letter='M';
        seat_letter=seat_letter-i;
        cout<<seat_letter<<"\t";
        for(j=0;j<18;j++)
        {
            if(seats_array[screen][movie][time_movie][i][j]==1 && j<9)
            {
                cout<<"["<<" X"<<"]";
            }
            else if(seats_array[screen][movie][time_movie][i][j]==1 && j>8)
            {
                cout<<"["<<" X "<<"]";
            }
            else
            {
                cout<<"["<<seat_letter<<j+1<<"]";
            }
            cout<<" ";//1 white space given
                      //the seat would be displayed in format [A1]
            if(j==4||j==12)
            {
                cout<<"\t";
            }
        }
        cout<<"\n\n";
        if (i==1)
        {
            cout<<"\n\nGold\n";
        }
        if (i==9)
        {
            cout<<"\n\nSilver\n";
        }
        if(i==12)
        {
            cout<<"\n\t_____________________________________________-|SCREEN HERE|-_______________________________________________________\n";
        }
    }
    char random_cin[3];
    cout<<"\nPress a key and then enter to continue: ";fflush(stdin);cin>>random_cin;
    if (flag_book_tickets==1)
    {
        cout<<"\n\n\n\t|We Have Some Special Combos For You !!!|\n";
        MovieBookingSystem::customer_snacks();
    }
}

void MovieBookingSystem::customer_snacks()
{
    char food[3];
    int end_snacks=1;
    while (end_snacks==1)
    {
        cout << "\n\e[1m \t------------------------------------------------\e";
        cout << "\n\e[1m \t|1)DORITOS NACHOS COMBO 400Rs [Before: 550Rs]:   |\e";
        cout << "\n\e[0m \t|Nachos Doritos + 1pepsi(900ml)                  |\e";
        cout << "\n\e[1m \t|2)POPCORN COMBO 300Rs [Before: 410Rs]:          |\e";
        cout << "\n\e[0m \t|Salted popcorn + 1pepsi(900ml)                  |\e";
        cout << "\n\e[1m \t|3)CHEESE COMBO 400Rs [Before: 525Rs]:           |\e";
        cout << "\n\e[0m \t|Cheese popcorn + 1pepsi(900ml)                  |\e";
        cout << "\n\e[1m \t|4)CARAMEL COMBO 350Rs [Before: 475Rs]:          |\e";
        cout << "\n\e[0m \t|Caramel popcorn + 1pepsi(900ml)                 |\e";
        cout << "\n\e[1m \t|5)COUPLE COMBO 500Rs [Before: 675Rs]:           |\e";
        cout << "\n\e[0m \t|2 Large tub popcorn(Any Flavour) + 2pepsi(900ml)|\e";
        cout << "\n\e[1m \t|6)No, thanks :) / That will be all :)           |\e";
        cout << "\n\e[0m \t--------------------------------------------------\e";

        ofstream file_billing;
        file_billing.open("customer_bill.txt",ios::app);
        cout<<"\n\n|Enter your Choice: ";
        fflush(stdin);
        cin>>food;
        if (strcmp(food,"1") == 0)
        {
            cout << "\n\t|You have added Nachos combo|";
            movie_price_total = movie_price_total + 400;
            file_billing<<"\nNachos Combo\t\t\t\t\t400Rs ";
        }
        else if (strcmp(food,"2") == 0)
        {
            cout << "\n\t|You have added Popcorn Combo|";
            movie_price_total = movie_price_total + 300;
            file_billing<< "\nPopcorn Combo\t\t\t\t\t300Rs ";
        }
        else if (strcmp(food, "3") == 0)
        {
            cout << "\n\t|You have added Cheese Combo|";
            movie_price_total = movie_price_total + 400;
            file_billing<< "\nCheese Combo\t\t\t\t\t400Rs ";
        }
        else if (strcmp(food, "4") == 0)
        {
            cout << "\n\t|You have added Caramel Combo|";
            movie_price_total = movie_price_total + 350;
            file_billing<< "\nCaramel Combo\t\t\t\t\t350Rs ";
        }
        else if (strcmp(food, "5") == 0)
        {
            cout << "\n\t|You have added Couple Combo|";
            movie_price_total = movie_price_total + 500;
            file_billing<< "\nCouple Combo\t\t\t\t\t500Rs ";
        }
        else if (strcmp(food, "6") == 0)
        {
            cout << "\n\t|Going to Billing|\n";
            end_snacks--;
        }
        else
        {
            cout<<"\n\t|Enter a valid input please|\n";
        }
    }
    MovieBookingSystem::customer_billing();
}

void MovieBookingSystem::customer_billing()
{
    ifstream file_billing;
    float gst_amount=movie_price_total*0.28;
    file_billing.open("customer_bill.txt");
    char c;
    cout<<"\n*****************************************************************\n";
    cout << "\n\t\t\t*******BILL*******:\n";
    cout << "\n\tPURCHASED\t\t\t\tPrice";
    while (!file_billing.eof())
    {
        file_billing.get(c);
        cout << c;
    }
    file_billing.close();
    cout<<"\n_________________________________________________________________\n";
    cout << "\n\n\tTotal Amount: "<<movie_price_total;
    cout << "\n\tGST Amount: "<<gst_amount;
    movie_price_total=movie_price_total+gst_amount;
    cout << "\n\tTOTAL AMOUNT + GST : "<<movie_price_total<<endl;
    cout<<"\n*****************************************************************\n";

    char end_bill[2];
    cout<<"\nPress any key and then enter to continue: ";
    cin>>end_bill;
    MovieBookingSystem::customer_mode();
}

//LOGIN (MAIN FUNCTION)
void MovieBookingSystem::Lets_Login()
{
    char choice_login[5],choice_end[5],manager_id[20],manager_password[20],customer_id[20],customer_password[20];
    char verification_id_m[20]="m123",verification_pass_m[20]="123m";
    char verification_id_c[20]="c123",verification_pass_c[20]="123c";
    cout << "\n\n\t------------------";
    cout << "\n\t|1) Manager Mode |";
    cout << "\n\t|2) Customer Mode|";
    cout << "\n\t|3) EXIT         |";
    cout << "\n\t------------------\n";
    cout << "\nEnter your choice: ";
    fflush(stdin);
    cin >>choice_login;

    if (strcmp(choice_login,"1") == 0)
    {
        cout << "\nEnter Manager ID:";
        fflush(stdin);
        cin >> manager_id;
        cout << "\nEnter Password:";
        fflush(stdin);
        cin >> manager_password;
        if ((strcmp(manager_password,verification_pass_m)==0) && (strcmp(manager_id,verification_id_m)==0))
        {
            cout<<"\n\t\t| WELCOME MANAGER! |\n";
            MovieBookingSystem::manager_mode();
        }
        else
        {
            cout << "\n\t|Entered password or ID is wrong :( |\n\t\t|Please try again|";
            MovieBookingSystem::Lets_Login();
        }
    }
    else if (strcmp(choice_login, "2") == 0)
    {
        cout << "\nEnter Customer ID:";
        fflush(stdin);
        cin >> customer_id;
        cout << "\nEnter Password:";
        fflush(stdin);
        cin >> customer_password;
        if ((strcmp(customer_password,verification_pass_c)==0) && (strcmp(customer_id,verification_id_c) == 0))
        {
            cout<<"\n\t\t| WELCOME CUSTOMER! |\n";
            MovieBookingSystem::customer_mode();
        }
        else
        {
            cout << "\n\t|Entered password or ID is wrong :( |\n\t|Please try again|";
            MovieBookingSystem::Lets_Login();
        }
    }
    if (strcmp(choice_login,"3") == 0)
    {
        cout<<"\n\t|All of todays booking data will be sent to the sever and you will not be able to access it|";
        cout<<"\n\t\t\t Are you sure you want to exit???[y/n] ";
        fflush(stdin);
        cin>>choice_end;
        if (strcmp(choice_end,"y")==0||strcmp(choice_end,"Y")==0)
        {
            cout<<"\n\n\t\t\t\t| GOODBYE (^_^) |\n\n\n\n";
            cout<<"\n-----------------------------------------------------------------------------------------\n";
            exit(0);
        }
        else
        {
            MovieBookingSystem::Lets_Login();
        }
    }
    else
    {
        cout << "\n\t|Entered a valid input please (T_T)|\n";
        MovieBookingSystem::Lets_Login();
    }
}

int main()
{
    MovieBookingSystem MBS;
    cout<<"\n-----------------------------------------------------------------------------------------\n";
    cout<<"\n\t\t|| WELCOME TO STARLIGHT CINEMAS (^_^) ||\n";
    MBS.Lets_Login();
    cout<<"\n-----------------------------------------------------------------------------------------\n";
    return 0;
}