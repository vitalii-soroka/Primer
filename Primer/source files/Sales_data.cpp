#include "Sales_data.h"

bool operator<(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() < rhs.isbn();
}

bool compareIsbn(const Sales_data& lhs, const Sales_data
    & rhs) {
    return lhs.isbn() < rhs.isbn();
}

Sales_data::Sales_data(const Sales_data& rhs) : bookNo(rhs.bookNo), units_sold(rhs.units_sold), revenue(rhs.revenue) {}
Sales_data::Sales_data(Sales_data&& rhs) noexcept : bookNo(std::move(rhs.bookNo)), units_sold(rhs.units_sold), revenue(rhs.revenue) {}
Sales_data& Sales_data::operator=(const Sales_data& rhs)
{
    //.
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}
Sales_data& Sales_data::operator=(Sales_data&& rhs) noexcept {
    if (this != &rhs) {
        bookNo = std::move(rhs.bookNo);
        units_sold = rhs.units_sold;
        revenue = rhs.revenue;
    }
    return *this;
}
Sales_data& Sales_data::operator=(const std::string& rhs)
{
    *this = Sales_data(rhs);
    return *this;
}
Sales_data& Sales_data::operator+=(const Sales_data& rhs){
    // ch18
    if (isbn() != rhs.isbn())
        throw isbn_mismatch("wrong isbn", isbn(), rhs.isbn());

    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;

    //Sales_data data(rhs + *this);
    //*this = data;
}
double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else 
        return 0;
}
Sales_data& operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}
bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.isbn() == rhs.isbn() &&
        lhs.units_sold == rhs.units_sold &&
        lhs.revenue == rhs.revenue;

}
bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
    return !(lhs == rhs);
}
std::istream& operator>>(std::istream& is, Sales_data& item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();
    return is;
}
std::ostream& operator<<(std::ostream& os, const Sales_data& item)
{
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}