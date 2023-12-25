#include "person.h"
#include <iostream>
#include <string>
#include <stdexcept>


Person::Person(std::string id, std::string name, std::string town,
               std::string province, std::string country,
               int age, double rank, int entry_year)
{
    id_ = id;
    name_ = name;
    town_ = town;
    province_ = province;
    country_ = country;

    age_ = age;
    rank_ = rank;

    if (entry_year > 2000)
    {
        entry_year_ = entry_year;
    } else {
        entry_year_ = 0;
    }
}

std::string Person::GetDataStr() 
{
    std::string data;

    data = "Person:\n";
    data += "id: " + id_ + "\n";
    data += "name: " + name_ + "\n";
    data += "town: " + town_ + "\n";
    data += "province: " + province_ + "\n";
    data += "country: " + country_ + "\n";
    data += "age: " + std::to_string(age_) + "\n";
    data += "rank: " + std::to_string(rank_) + "\n";
    
    return data;
}

std::vector<std::string> Person::GetPreferences()
{
    return preferences_;
}

void Person::AddPreference(std::string preference)
{
    preferences_.push_back(preference);
}

void Person::AddPreferences(std::string pref1, std::string pref2, std::string pref3)
{
    preferences_.insert(preferences_.begin(), pref1);
    preferences_.insert(preferences_.end(), pref3);
    preferences_.insert(preferences_.begin()+(preferences_.size()/2), pref2);
}

void Person::ShowPreferences()
{
    std::cout << "\nPreferencias: " << "\n";
    for (const auto& pref : preferences_)
    {
        std::cout << pref << "\n";
    }
}

void Person::ChangePreference(int position, std::string newValue)
{
    try
    {
        preferences_.at(position) = newValue;
    } catch (std::out_of_range const exc)
    {
        std::cout << "Error: " << exc.what() << "\n";
    }
}

bool Person::SetAge(int age)
{
    if (age > 0) 
    {
        age_ = age;
        return true;
    }
    return false;
}

bool Person::SetEntryYear(int entry_year)
{
    if (entry_year > 2000)
    {
        entry_year_ = entry_year;
        return true;
    }
    return false;
}
