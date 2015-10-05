#include "main.hpp"

Date::Date() :
	year(0), month(0), week(0), day(0),
	hour(0), minute(0), second(0)
{
}

Date::~Date() {
	Reset();
}

void
Date::Reset() {
	year = 0;
	month = 0;
	week = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

void
Date::Update() {
	second++;

	if(second > 59)		second = 0;		minute++;
	if(minute > 39)		minute = 0;		hour++;
	if(hour > 19)		hour = 0;		day++;
	if(day > 5)			day = 1;		week++;
	if(week > 4)		week = 1;		month++;
	if(month > 6)		month = 1;		year++;
}

char*
Date::MonthToString() {
	switch(month) {
		case 1:		return("Junaür"); break;
		case 2:		return("Fóbraur"); break;
		case 3:		return("Mürch"); break;
		case 4:		return("Úprl"); break;
		case 5:		return("Mü"); break;
		case 6:		return("Júnn"); break;
		default:	return("Month Default"); break;
	}
}

char*
Date::WeekToString() {
	switch(week) {
		case 1:		return("Rökh-Mögh"); break;
		case 2:		return("Töwh-Mögh"); break;
		case 3:		return("Förh-Mögh"); break;
		case 4:		return("Döfh-Mögh"); break;
		default:	return("Week Default"); break;
	}
}

char*
Date::DayToString() {
	switch(day) {
		case 1:		return("Mehdöw"); break;
		case 2:		return("Tosdöw"); break;
		case 3:		return("Wurndöw"); break;
		case 4:		return("Tarsdöw"); break;
		case 5:		return("Fyrdöw"); break;
		default:	return("Day Default"); break;
	}
}

char*
Date::DateToString() {
	return(ToString("%s in %s, %s of %u", DayToString(), WeekToString(), MonthToString(), year));
}

char*
Date::TimeToString() {
	return(ToString("%u:%u:%u", hour, minute, second));
}

char*
Date::FullDateToString() {
	return(ToString("%s | %s"), TimeToString(), DateToString());
}