#include <iostream>
/*This program will calculate the per capita GDP estimate for a given quarter,
 the user will enter the year and quarter for the calculation the program will
 then calculate the quarter difference from 1977 Q1, calculate the per capita GDP estimate
 and will then output the result
 */
int get_int();
double calculate_per_capita_gdp_estimate(int quarters_from_epoch);
std::string format_money(double money);
std::string quarter_to_ordinal(int quarter);
int main(){
    //ask the user to enter their inputs
    std::cout << "Please enter the year for the calculation: ";
    int user_year = get_int();
    std::cout << "Please enter the quarter for the calculation: ";
    int user_quarter = get_int();

    //calculate the quarter difference
    int Date = user_year * 4 + (user_quarter-1);
    int quarterdiff = Date - 1977 * 4;
    std::cout <<"In the " << quarter_to_ordinal(user_quarter) <<" quarter of "<< (user_year) <<", the projected contribution to GDP per working-age person is $" << format_money(calculate_per_capita_gdp_estimate(quarterdiff)) << ".\n";
return 0;
}