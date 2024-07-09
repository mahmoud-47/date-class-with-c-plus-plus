#include"date.hpp"
#include <cstring>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  char* copy = new char[str.size() + 1]; 
  strcpy(copy, str.c_str());

  char* token = strtok(copy, &delimiter);
  while (token != nullptr) {
    tokens.push_back(token);
    token = strtok(nullptr, &delimiter);
  }

  delete[] copy;
  return tokens;
}

//Date of today
date::date(){
    time_t now = time(0); 
    // Convert to tm structure for breakdown
    tm *ltm = localtime(&now);
    
    char formatted_date[80];
    strftime(formatted_date, 80, "%Y-%m-%d", ltm);

    std::vector<std::string> res = split(formatted_date, '-');

    this->day = std::stoi(res[2]);
    this->month = std::stoi(res[1]);
    this->year = std::stoi(res[0]);

    this->is_correct();
}

date::date(const date& d){
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;
}

//The date is in the format j,m,y
date::date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
    this->is_correct();
}

//The date is in the format j-m-y
date::date(const std::string str){
    std::vector<std::string> res = split(str, '-');
    if(res.size() != 3){
        DateException date_exception("The format is not correct");
        throw date_exception;
    }

    this->day = std::stoi(res[0]);
    this->month = std::stoi(res[1]);
    this->year = std::stoi(res[2]);

    this->is_correct();
}

void date::is_correct() const{
    if(this->year <= 0){
        DateException d("Year must be at least 1");
        throw d;
    }
    if(this->month < 1 || this->month > 12){
        DateException d("Month must be between 1 and 12");
        throw d;
    }
    if(this->day < 1 || this->day > 31){
        DateException d("Incorrect day");
        throw d;
    }
    if(this->month == 4 || this->month == 6 || this->month == 9 || this->month == 11){
        if(this->day > 30){
            DateException d("Day must be bellow 31 ");
            throw d;
        }
    }
    if(this->month == 2){
        if(this->is_bissextil()){
            if(this->day > 29){
                DateException d("February in Bissextil year ends at 29");
                throw d;
            }
        }else{
            if(this->day > 28){
                DateException d("February in non Bissextil year ends at 28");
                throw d;
            }
        }
    }
}

//If a given date is bissextile
bool date::is_bissextil() const{
    if(this->year % 400 == 0 || this->year % 4 == 0 && this->year % 100 != 0)
        return true;
    return false;
}

//returns this date - date in parameter
int date::diff(const date& other) const{
    // int diff = this->year - other.year;
    // if(diff)
    //     return diff;
    
    // diff = this->month - other.month;
    // if(diff)
    //     return diff;
    
    // return this->day - other.day;
    return (this->year - other.year) ? this->year - other.year : 
        (this->month - other.month)? this->month - other.month :
         this->day - other.day;
}

//Next date
date date::next() const{
    date d(*this);
    bool month_in_46911 = d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11;

    if(month_in_46911 && d.day == 30 || d.day == 31){
        d.day = 1; d.month++; 
        if(d.month == 13){
            d.month = 1;
            d.year++;
        }
    }else if(d.is_bissextil() && d.month == 2 && d.day == 29){
        d.day = 1;
        d.month++;
    }else if(!d.is_bissextil() && d.month == 2 && d.day == 28){
        d.day = 1;
        d.month++;
    }else
        d.day ++;

    d.is_correct();
    return d;
}

//Previous date
date date::previous() const{
    date d(*this);
    bool month_in_2468911 = d.month == 2 || d.month == 4 || d.month == 6 || d.month == 8 || d.month == 9 || d.month == 11;

    if(d.day == 1){
        if(month_in_2468911){
            d.day = 31;
            d.month --;
        }else if(d.month != 1 && d.month != 3){
            d.day = 30;
            d.month --;
        }else if(d.month == 3){
            d.month --;
            if(d.is_bissextil())
                d.day = 29;
            else
                d.day = 28;
        }else{
            d.day = 31;
            d.month = 12;
            d.year --;
        }
    }else
        d.day --;
    
    d.is_correct();
    return d;
}

//index of the week day in a list [0-6]
int date::get_day_week() const{ //essayer de faire des pas de 7
    // std::string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    // std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    date ref("1-1-1990");
    int index_day = 0;
    while (this->diff(ref) != 0){
        if(this->diff(ref) > 0){
            ref = ref.next();
            index_day++;
            if(index_day == 7)
                index_day = 0;
        }else{
            ref = ref.previous();
            index_day--;
            if(index_day == -1)
                index_day = 6;
        }
    }
    return index_day;
}

//get day
int date::get_day() const{
    return this->day;
}

//get month
int date::get_month() const{
    this->month;
}

//get year
int date::get_year() const{
    return this->year;
}

//date + number of days
date date::operator+(int add) const{
    if(add < 0)
        return *this - (-add);
    date d(*this);
    int i = 0;
    while(i<add){
        d = d.next();
        i++;
    }
    return d;
}

//date - number of days
date date::operator-(int minus) const{
    if(minus < 0)
        return *this + (-minus);
    date d(*this);
    int i = 0;
    while(i<minus){
        d = d.previous();
        i++;
    }
    return d;
}

//date - another date -> number of days between them
int date::operator-(const date& d) const{
    int difference = this->diff(d);
    date min, max; 
    int signe = 1;
    if(difference == 0)
        return 0;
    else if(difference > 0){
        min = d;
        max = *this;
    }else{
        min = *this;
        max = d;
        signe *= -1;
    }
    int count = 0;
    while(max.diff(min) > 0){
        min = min.next();
        count ++;
    }
    return signe * count;
}

//print a date
std::ostream& operator<<(std::ostream& os, const date& d){
    os << d.day << "-" << d.month << "-" << d.year;
    return os;
}

date& date::operator=(const date& d){
    if(this == &d)
        return *this;
    this->day = d.day;
    this->month = d.month;
    this->year = d.year;
    return *this;
}

bool date::operator==(const date& d) const{
    return this->diff(d) == 0;
}

bool date::operator<(const date& d) const{
    return this->diff(d) < 0;
}

bool date::operator<=(const date& d) const{
    return this->diff(d) <= 0;
}

bool date::operator>(const date& d) const{
    return this->diff(d) > 0;
}

bool date::operator>=(const date& d) const{
    return this->diff(d) >= 0;
}