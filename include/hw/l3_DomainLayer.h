/* 
MIT License 

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов, 

Программа-заготовка для домашнего задания
*/

#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

const size_t MAX_STRING_LENGTH = 50;
const size_t TIME_LENGTH = 5;

class Performance : public ICollectable
{

    std::string _group_name;
    std::string _genre;
    uint16_t    _order;
    std::string _time_start;
    std::string _time_end;

protected:
    bool invariant() const;

public:
    Performance() = delete;
    Performance(const Performance & p) = delete;

    Performance & operator = (const Performance & p) = delete;

    Performance(
        const std::string & group_name, 
        const std::string & genre, 
        uint16_t            order, 
        const std::string & time_start, 
        const std::string & time_end
    );

    const std::string & getGroupName() const;
    const std::string & getGenre() const;
    uint16_t            getOrder() const;
    const std::string & getTimeStart() const;
    const std::string & getTimeEnd() const;

    virtual bool        write(std::ostream& os) override;
};


class ItemCollector: public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream& is) override;
};

#endif // HW_L3_DOMAIN_LAYER_H
