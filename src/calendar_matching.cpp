#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

struct StringMeeting
{
    string start;
    string end;
};

struct IntMeeting
{
    int start;
    int end;
};

string toTimeString(const int minutes);
int toMinutes(const string timeString);
StringMeeting toStringMeeting(const IntMeeting meeting);
IntMeeting toIntMeeting(const StringMeeting meeting);
vector<IntMeeting> toIntMeeting(const vector<StringMeeting> &meetings);
void addNonWorkingHoursAsMeetings(vector<IntMeeting> &calendar, const IntMeeting &dailyBound);
vector<IntMeeting> makeCombinedCalendar(const vector<IntMeeting> calendar1, const vector<IntMeeting> calendar2);
vector<IntMeeting> mergeOverlappingAndConsequtiveMeetings(const vector<IntMeeting> &calendar);
vector<IntMeeting> findTimeslot(const vector<IntMeeting> calendar, const int minutes);
vector<StringMeeting> toStringMeeting(const vector<IntMeeting> &meetings);

vector<StringMeeting> calendarMatching(vector<StringMeeting> calendar1,
                                       StringMeeting dailyBounds1,
                                       vector<StringMeeting> calendar2,
                                       StringMeeting dailyBounds2,
                                       int meetingDuration)
{
    auto cal1 = toIntMeeting(calendar1);
    addNonWorkingHoursAsMeetings(cal1, toIntMeeting(dailyBounds1));

    auto cal2 = toIntMeeting(calendar2);
    addNonWorkingHoursAsMeetings(cal2, toIntMeeting(dailyBounds2));

    auto mergedCalendar = makeCombinedCalendar(cal1, cal2);

    mergedCalendar = mergeOverlappingAndConsequtiveMeetings(mergedCalendar);

    return toStringMeeting(findTimeslot(mergedCalendar, meetingDuration));
}

string toTimeString(const int minutes)
{
    const auto hr = minutes / 60;
    const auto min = minutes % 60;
    return to_string(hr) + ":" + (min < 10 ? "0" + to_string(min) : to_string(min));
}

StringMeeting toStringMeeting(const IntMeeting meeting)
{
    StringMeeting strMeeting;
    strMeeting.start = toTimeString(meeting.start);
    strMeeting.end = toTimeString(meeting.end);
    return strMeeting;
}

int toMinutes(const string timeString)
{
    const auto separatorPos = timeString.find(':');
    auto minutes = stoi(timeString.substr(0, separatorPos + 1)) * 60;
    minutes += stoi(timeString.substr(separatorPos + 1, 2));

    return minutes;
}

IntMeeting toIntMeeting(const StringMeeting meeting)
{
    IntMeeting meet;
    meet.start = toMinutes(meeting.start);
    meet.end = toMinutes(meeting.end);
    return meet;
}

vector<IntMeeting> toIntMeeting(const vector<StringMeeting> &meetings)
{
    vector<IntMeeting> intMeetings(meetings.size());
    transform(cbegin(meetings), cend(meetings), begin(intMeetings), [](const auto meeting)
              { return toIntMeeting(meeting); });
    return intMeetings;
}

vector<StringMeeting> toStringMeeting(const vector<IntMeeting> &meetings)
{
    vector<StringMeeting> stringMeetings(meetings.size());
    transform(cbegin(meetings), cend(meetings), begin(stringMeetings), [](const auto meeting)
              { return toStringMeeting(meeting); });
    return stringMeetings;
}

void addNonWorkingHoursAsMeetings(vector<IntMeeting> &calendar, const IntMeeting &dailyBound)
{
    IntMeeting beforeWorkHrs;
    beforeWorkHrs.start = 0;
    beforeWorkHrs.end = dailyBound.start;

    IntMeeting afterWorkHrs;
    afterWorkHrs.start = dailyBound.end;
    afterWorkHrs.end = 2359;

    calendar.insert(begin(calendar), beforeWorkHrs);
    calendar.push_back(afterWorkHrs);
}

vector<IntMeeting> makeCombinedCalendar(const vector<IntMeeting> calendar1, const vector<IntMeeting> calendar2)
{
    const int len1 = calendar1.size(), len2 = calendar2.size();

    vector<IntMeeting> combinedCalendar(len1 + len2);

    int idx1{0}, idx2{0}, idxComb{0};

    while (idx1 < len1 and idx2 < len2)
        combinedCalendar[idxComb++] = calendar1.at(idx1).start < calendar2.at(idx2).start ? calendar1.at(idx1++) : calendar2.at(idx2++);

    while (idx1 < len1)
        combinedCalendar[idxComb++] = calendar1.at(idx1++);

    while (idx2 < len2)
        combinedCalendar[idxComb++] = calendar2.at(idx2++);

    return combinedCalendar;
}

vector<IntMeeting> mergeOverlappingAndConsequtiveMeetings(const vector<IntMeeting> &calendar)
{
    const int len = calendar.size();
    vector<IntMeeting> mergedCalendar;

    auto mergedMeeting = calendar.at(0);
    for (int idx{1}; idx < len; idx++)
    {
        const auto currentMeetingBound = calendar.at(idx);
        if (mergedMeeting.end < currentMeetingBound.start)
        {
            mergedCalendar.push_back(mergedMeeting);
            mergedMeeting = currentMeetingBound;
        }
        else
        {
            mergedMeeting.end = max(mergedMeeting.end, currentMeetingBound.end);
        }
    }
    mergedCalendar.push_back(mergedMeeting);

    return mergedCalendar;
}

vector<IntMeeting> findTimeslot(const vector<IntMeeting> calendar, const int minutes)
{
    const int len = calendar.size();
    vector<IntMeeting> availableSlots;

    for (int idx{1}; idx < len; idx++)
    {
        const auto prev{calendar.at(idx - 1)};
        const auto current{calendar.at(idx)};

        if (current.start - prev.end >= minutes)
        {
            IntMeeting freeSlot;
            freeSlot.start = prev.end;
            freeSlot.end = current.start;
            availableSlots.push_back(freeSlot);
        }
    }

    return availableSlots;
}

int main()
{
    const vector<StringMeeting> calendar1 = {
        {"9:00", "10:30"},
        {"12:00", "13:00"},
        {"16:00", "18:00"}};

    const StringMeeting dailyBound1{"9:00", "20:00"};

    const vector<StringMeeting> calendar2 = {
        {"10:00", "11:30"},
        {"12:30", "14:30"},
        {"14:30", "15:00"},
        {"16:00", "17:00"}};

    const StringMeeting dailyBound2{"10:00", "18:30"};

    const auto result = calendarMatching(calendar1, dailyBound1, calendar2, dailyBound2, 30);

    return 0;
}
