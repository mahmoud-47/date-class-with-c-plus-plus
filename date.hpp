#ifndef __COMPLEX__
    #define __COMPLEX__
    #include<iostream>
    #include <ctime>

    class DateException{
        private:
            std::string message;
        public:
            DateException(std::string message){
                this->message = message;
            }

            std::string get_message(){
                return message;
            }
    };

    //This class represents a date
    class date{
        private:
            int day;
            int month;
            int year;
        public:
            //Date of today
            date();

            date(const date&);

            //The date is in the format j,m,y
            date(int, int, int);

            //The date is in the format j-m-y
            date(const std::string);

            //check the date
            void is_correct() const;

            //If a given date is bissextile
            bool is_bissextil() const;

            //returns this date - date in parameter
            int diff(const date&) const;

            //Next date
            date next() const;

            //Previous date
            date previous() const;

            //index of the week day in a list [0-6]
            int get_day_week() const;

            //get day
            int get_day() const;

            //get month
            int get_month() const;

            //get year
            int get_year() const;

            //date + number of days
            date operator+(int) const;

            //date - number of days
            date operator-(int) const;

            //date - another date -> number of days between them
            int operator-(const date&) const;

            //print a date
            friend std::ostream& operator<<(std::ostream&, const date&);

            //affectation
            date& operator=(const date&);

            bool operator==(const date&) const;

            bool operator<(const date&) const;

            bool operator<=(const date&) const;

            bool operator>(const date&) const;

            bool operator>=(const date&) const;
    };

#endif