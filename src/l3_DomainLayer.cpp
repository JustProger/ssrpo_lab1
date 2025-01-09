/* Программа-заготовка для домашнего задания
*/

#include "hw/l3_DomainLayer.h"

using namespace std;

bool Performance::invariant() const
{
    regex timeRegex(R"(\d{2}:\d{2})");  
    return !_group_name.empty() && _group_name.size() <= MAX_STRING_LENGTH
    && !_genre.empty()  && _genre.size() <= MAX_STRING_LENGTH  
    && regex_match(_time_start, timeRegex)
    && regex_match(_time_end, timeRegex);
}

Performance::Performance(const std::string & group_name, const std::string & genre, uint16_t order, const std::string & time_start, const std::string & time_end)
    : _group_name(group_name), _genre(genre), _order(order), _time_start(time_start), _time_end(time_end)
{
    assert(invariant());
}

const string & Performance::getGroupName() const
{
    return _group_name;
}

const string & Performance::getGenre() const
{
    return _genre;
}

uint16_t Performance::getOrder() const
{
    return _order;
}

const string & Performance::getTimeStart() const
{
    return _time_start;
}

const string & Performance::getTimeEnd() const
{
    return _time_end;
}

bool   Performance::write(ostream& os)
{
    writeString(os, _group_name);
    writeString(os, _genre);
    writeNumber(os, _order);
    writeString(os, _time_start);
    writeString(os, _time_end);

    return os.good();
}



shared_ptr<ICollectable> ItemCollector::read(istream& is)
{
    string   group_name = readString(is, MAX_STRING_LENGTH);
    string   genre  = readString(is, MAX_STRING_LENGTH);
    uint16_t order = readNumber<uint16_t>(is);
    string   time_start  = readString(is, TIME_LENGTH);
    string   time_end  = readString(is, TIME_LENGTH);


    return std::make_shared<Performance>(group_name, genre, order, time_start, time_end);
}


