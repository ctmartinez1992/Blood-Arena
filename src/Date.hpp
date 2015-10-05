#ifndef RL_DATE_HPP
#define RL_DATE_HPP

//NOTE: Min Year: 0 / Max Year: Infinite
//NOTE: Min Month: 1 / Max Month: 6
//NOTE: Min Week: 1 / Max Week: 4
//NOTE: Min Day: 1 / Max Day: 5
//NOTE: Min Hour: 0 / Max Hour: 19
//NOTE: Min Minute: 0 / Max Minute: 39
//NOTE: Min Second: 0 / Max Second: 59

class Date : public Persistent {
public:
	unsigned int year;
	unsigned int month;
	unsigned int week;
	unsigned int day;

	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	Date();
	~Date();

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	void
	Reset();

	void
	Update();

	char*
	MonthToString();

	char*
	WeekToString();

	char*
	DayToString();

	char*
	DateToString();

	char*
	TimeToString();

	char*
	FullDateToString();
};

#endif