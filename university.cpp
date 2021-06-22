#include "university.hpp"
#include "load.hpp"
#include "save.hpp"
#include "search.hpp"
#include "sort.hpp"
#include "student.hpp"
#include "delete.hpp"
#include <memory>
#include <utility>

void University::loadRecords(const std::string &filename) {
    std::unique_ptr<Load> load(new Load(this, filename));

    load->execute();
}
void University::saveRecords(const std::string &filename) {
    std::unique_ptr<Save> save(new Save(this, filename));

    save->execute();
}
void University::addStudent(Student *student) { students_.push_back(student); }
void University::printAllDatabase() {
    for (auto *student : students_)
        student->print();
}
void University::sortByPesel() {
    std::unique_ptr<Sort> sort(new Sort(this, [](Person *l, Person *p) {
        return l->getPesel() < p->getPesel();
    }));

    sort->execute();
}
void University::searchByPesel(int64_t pesel) {
    std::unique_ptr<Search> search(new Search(
            this, [pesel](Person *p) {
                return p->getPesel() == pesel;
            }));
    search->execute();
    auto personVec = search->getresVec();
    for (auto &it : personVec) {
        it->print();
    }
}

std::vector<Person *> University::getStudents() const {
    return students_;
}
void University::clearStudents() {
    for (auto *student : students_) {
        delete student;
    }
    students_.clear();
}
void University::searchBySurname(std::string surname) {
    std::unique_ptr<Search> search(new Search(
            this, [surname](Person *p) {
                return p->getSurname().compare(surname) == 0;
            }));
    search->execute();
    auto personVec = search->getresVec();
    for (auto &it : personVec) {
        it->print();
    }
}
void University::deleteByIndex(size_t index) {
    std::unique_ptr<DeleteC> deleteC(new DeleteC(
            this, [index](Student *p) {
               return  p->getIndex() == index;
            }));
    deleteC->execute();
    auto personVec = deleteC->getresVec();
    
}
